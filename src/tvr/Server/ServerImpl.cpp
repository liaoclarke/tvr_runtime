#include <tvr/Server/ServerImpl.h>
#include <tvr/Connection/Connection.h>
#include <tvr/Common/CreateDevice.h>
#include <tvr/Util/Verbosity.h>
#include <tvr/Util/PortFlags.h>
#include <tvr/Util/Microsleep.h>

#include <vrpn_ConnectionPtr.h>

#include <stdexcept>
#include <functional>

namespace tvr {
    namespace server {
        static vrpn_ConnectionPtr getVRPNConnection(tvr::connection::ConnectionPtr const &conn) {
            vrpn_ConnectionPtr ret;
            ret = vrpn_ConnectionPtr(static_cast<vrpn_Connection *>(conn->getUnderlyingObject()));
            return ret;
        }

        ServerImpl::ServerImpl(tvr::connection::ConnectionPtr const &conn)
                    : m_conn(conn), m_host("localhost"), m_port(tvr::util::UseDefaultPort) {
            if (!m_conn) {
                throw std::logic_error("Can't pass a null ConnectionPtr into Server constructor!");
            }
            auto vrpnConn = getVRPNConnection(m_conn);
            if (!(vrpnConn->doing_okay())) {
                throw std::runtime_error("Could not create server - there is probably another instance of the server or a VRPN server running already.");
            }
            m_systemDevice = tvr::common::createServerDevice("TVR", vrpnConn);
            m_systemComponent = m_systemDevice->addComponent(tvr::common::SystemComponent::create());
            m_commonComponent = m_systemDevice->addComponent(tvr::common::CommonComponent::create());
            m_commonComponent->registerPingHandler([&] { m_queueTreeSend(); });

            //vrpnConn->register_handler(vrpnConn->register_message_type(vrpn_got_first_connection), &ServerImpl::m_exitIdle, this);
            //vrpnConn->register_handler(vrpnConn->register_message_type(vrpn_dropped_last_connection), &ServerImpl::m_enterIdle, this);
        }

        ServerImpl::~ServerImpl() {
            stop();
        }

        void ServerImpl::startAndAwaitShutdown() {
            m_start();
            m_awaitShutdown();
        }

        void ServerImpl::stop() {
            /*boost::unique_lock<boost::mutex> lock(m_runControl);
            if (m_everStarted) {
                m_run.signalAndWaitForShutdown();
                m_thread.join();
                m_thread = boost::thread();
            } else {
                m_orderDestruction();
            }*/
        }

        void ServerImpl::signalStop() {
            /*boost::unique_lock<boost::mutex> lock(m_runControl);
            m_run.signalShutdown();
            */
        }

        void ServerImpl::setHardwareDetectOnConnection() {
            m_commonComponent->registerPingHandler([&] { triggerHardwareDetect(); });            
        }

        void ServerImpl::triggerHardwareDetect() {
            m_callControlled([&] { m_triggeredDetect = true; });
        }

        void ServerImpl::update() {
            /*boost::unique_lock<boost::mutex> lock(m_runControl);
            if (m_everStarted) {
                throw std::logic_error("Can't call update() if you've ever started the server in its own thread!");
            }
            m_update();
            */
        }

        bool ServerImpl::addString(std::string const &path, std::string const &value) {
            bool wasChanged = false;
            auto newElement = tvr::common::PathElement{tvr::common::elements::StringElement{value}};
            m_callControlled([&] {
                    auto &node = m_tree.getNodeByPath(path);
                    if (!(newElement == node.value())) {
                        m_treeDirty.set();
                        wasChanged = true;
                        node.value() = newElement;
                    }});
            return wasChanged;
        }

        void ServerImpl::setSleepTime(int microseconds) {
            m_sleepTime = microseconds;
        }

        void ServerImpl::m_awaitShutdown() {
            m_thread.join();
        }

        void ServerImpl::m_start() {
            boost::unique_lock<boost::mutex> lock(m_runControl);
            if (!m_conn) {
                throw std::logic_error("Cannot start server - context or connection destroyed (probably attemping to restart a stopped server)");
            }
            m_everStarted = true;
            m_running = true;

            m_thread = boost::thread([&] {
                bool keepRunning = true;
                m_mainThreadId = m_thread.get_id();
                //tvr::util::LoopGuard guard(m_run);
                do {
                    keepRunning = this->m_loop();
                } while (keepRunning);
               m_orderedDestruction();
               m_running = false;
               });
            //m_run.signalAndWaitForStart();
        }

        void ServerImpl::m_update() {
            m_conn->process();
            m_systemDevice->update();
            if (m_triggeredDetect) {
                TVR_DEV_VERBOSE("ServerImpl", "trigger hardware detect");
                //m_systemDevice->triggerHardwareDetect();
                //m_ctx->triggerHardwareDetect();
                m_triggeredDetect = false;
            }
            if (m_treeDirty) {
                TVR_DEV_VERBOSE("ServerImpl", "json tree is dirty");
                m_sendTree();
                m_treeDirty.reset();
            }
        }

        bool ServerImpl::m_loop() {
            bool shouldContinue = true;
            boost::unique_lock<boost::mutex> lock(m_mainThreadMutex);
            m_update();
            //shouldContinue = m_run.shouldContinue();
            if (m_currentSleepTime > 0) {
                //TVR_DEV_VERBOSE("ServerImpl", "server go sleep");
                tvr::util::time::microsleep(m_currentSleepTime);
            }
            return shouldContinue;
            //return true;
        }

        void ServerImpl::m_orderedDestruction() {
            m_systemComponent = nullptr;
            /*m_systemDevice.reset();
            m_conn.reset();
            */
        }

        bool m_inServerThread() {
            return true;
        }

        void ServerImpl::m_queueTreeSend() {
            TVR_DEV_VERBOSE("ServerImpl", "Get incoming connection and send JsonTree");
            m_callControlled([&] { m_treeDirty += true; });
        }

        void ServerImpl::m_sendTree() {
            TVR_DEV_VERBOSE("ServerImpl", "Sending path tree to clients.");
            m_systemComponent->sendReplacementTree(m_tree);
            /*auto config = pathTreeToJson(m_tree);
            Buffer<> buf;
            serialize(buf, msg);
            packMessage(buf, "treeOut");
            sendPending();
            */
        }

        int ServerImpl::m_exitIdle(void *userdata, vrpn_HANDLERPARAM) {
            /*auto self = static_cast<ServerImpl *>(userdata);
            if (self->m_currentSleepTime > self->m_sleepTime) {
                self->currentSleepTime = self->m_sleepTime;
            }
            */
            return 0;
        }

        int ServerImpl::m_enterIdle(void *userdata, vrpn_HANDLERPARAM) {
            /*auto self = static_cast<ServerImpl *>(userdata);
            if (self->m_currentSleepTime < IDLE_SLEEP_TIME) {
                TVR_DEV_VERBOSE("ServerImpl", "Dropped last client connection, entering idle mode.");
                self->m_currentSleepTime = IDLE_SLEEP_TIME;
            }
            */
            return 0;
        }
    }
}
