#include <tvr/Client/PureClientContext.h>
#include <tvr/Common/SystemComponent.h>
#include <tvr/Common/CreateDevice.h>
#include <tvr/Common/PathTreeFull.h>
#include <tvr/Common/PathElementTools.h>
//#include <tvr/Common/ClientInterface.h>
#include <tvr/Common/DeduplicatingFunctionWrapper.h>
#include <tvr/Util/Verbosity.h>

#include <boost/algorithm/string.hpp>

#include <json/value.h>

#include <unordered_set>
#include <thread>

namespace tvr {
    namespace client {
        static const std::chrono::milliseconds STARTUP_CONNECT_TIMEOUT(200); // Dead looping
        static const std::chrono::milliseconds STARTUP_TREE_TIMEOUT(1000);
        static const std::chrono::milliseconds STARTUP_LOOP_SLEEP(1);

        PureClientContext::PureClientContext(const char appId[], const char host[], tvr::common::ClientContextDeleter del)
                                        : ::TVR_ClientContextObject(appId, del), m_host(host)
                                            /*, m_ifaceMgr(m_pathTreeOwner, m_factory, *static_cast><tvr::common::ClientContext *>(this))*/
        {
            if (!m_network.isUp()) {
                throw std::runtime_error("Network error: " + m_network.getError());
            }

            //populateRemoteHandlerFactory(m_factory);

            std::string sysDeviceName = std::string("TVR@") + host;
            m_mainConn = m_vrpnConns.getConnection("TVR", host);
            m_systemDevice = tvr::common::createClientDevice(sysDeviceName, m_mainConn);
            m_systemComponent = m_systemDevice->addComponent(tvr::common::SystemComponent::create());
            m_commonComponent = m_systemDevice->addComponent(tvr::common::CommonComponent::create());
            m_commonComponent->registerPongHandler([&] { m_getPongMessage(); });
            using DedupJsonFunction = tvr::common::DeduplicatingFunctionWrapper<Json::Value const &>;
            m_systemComponent->registerReplaceTreeHandler(
                DedupJsonFunction([&](Json::Value nodes) {
                    TVR_DEV_VERBOSE("PureClientContext", "Replace path tree from server Nodes: " << nodes.toStyledString() );
                    m_pathTreeOwner.replaceTree(nodes);
                    }));
            typedef std::chrono::system_clock clock;
            auto begin = clock::now();

            auto connEnd = begin + STARTUP_CONNECT_TIMEOUT;
            while (clock::now() < connEnd && !m_gotConnection) {
                m_update();
                std::this_thread::sleep_for(STARTUP_LOOP_SLEEP);
            }
            if (!m_gotConnection) {
                TVR_DEV_VERBOSE("PureClientContext",
                    "Could not connect to TVR server in the timeout period allotted of"
                    << std::chrono::duration_cast<std::chrono::milliseconds>(STARTUP_CONNECT_TIMEOUT).count()
                    << "ms");
                return;
            }

            auto treeEnd = begin + STARTUP_TREE_TIMEOUT;
            while (clock::now() < treeEnd && !m_pathTreeOwner) {
                m_update();
                std::this_thread::sleep_for(STARTUP_LOOP_SLEEP);
            }
            auto timeToStartup = (clock::now() - begin);
            TVR_DEV_VERBOSE("PureClientContext", "Connection process took "
                            << std::chrono::duration_cast<std::chrono::milliseconds>(timeToStartup).count()
                            << "ms: " << (m_gotConnection ? "have connection to server"
                                                          : "don't have connection to server"));
        }

        PureClientContext::~PureClientContext() {}

        void PureClientContext::m_update() {
            m_vrpnConns.updateAll();
            if (!m_gotConnection && m_mainConn->connected()) {
                TVR_DEV_VERBOSE("PureClientContext", "Got connection to main TVR server");
                m_gotConnection = true;
            }

            m_systemDevice->update();
            //m_ifaceMgr.updateHandlers();
        }

        void PureClientContext::m_getPongMessage() {
            TVR_DEV_VERBOSE("PureClientContext", "Client get Pong message");
        }

        void PureClientContext::m_sendData(std::string const &data) {
            m_systemComponent->sendClientDataUpdate(data);
            m_update();
        }

        /*void PureClientContext::m_handleNewInterface(tvr::common::ClientInterfacePtr const &iface) {
            m_ifaceMgr.addInterface(iface);
        }*/

        /*void PureClientContext::m_handleReleasingInterface(tvr::common::ClientInterfacePtr const &iface) {
            //m_ifaceMgr.releaseInterface(iface);
        }*/

        bool PureClientContext::m_getStatus() const {
            return m_gotConnection && m_pathTreeOwner;
        }

        tvr::common::PathTree const &PureClientContext::m_getPathTree() const {
            return m_pathTreeOwner.get();
        }
    }
}

