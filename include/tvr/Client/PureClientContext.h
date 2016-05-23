#ifndef INC_ClientKit_PureClientContext_h
#define INC_ClientKit_PureClientContext_h
#include <tvr/Common/ClientContext.h>
#include <tvr/Common/BaseDevicePtr.h>
#include <tvr/Common/NetworkingSupport.h>
#include <tvr/Client/VRPNConnectionCollection.h>
#include <tvr/Client/RemoteHandlerFactory.h>
#include <tvr/Client/ClientInterfaceObjectManager.h>

#include <tvr/Common/PathTree.h>
#include <tvr/Common/PathTreeOwner.h>
#include <tvr/Client/InterfaceTree.h>

#include <vrpn_ConnectionPtr.h>
#include <json/value.h>

#include <string>

namespace tvr {
    namespace client {
        class PureClientContext : public ::TVR_ClientContextObject {
            public:
                PureClientContext(const char appId[], tvr::common::ClientContextDeleter del)
                                : PureClientContext(appId, "localhost", del) {}

                PureClientContext(const char appId[], const char host[], tvr::common::ClientContextDeleter del);

                virtual ~PureClientContext();
            private:
                virtual void m_update();

                virtual void m_sendData(std::string const &data);

                void m_handleNewInterface(tvr::common::ClientInterfacePtr const &iface) override;

                void m_handleReleasingInterface(tvr::common::ClientInterface const &iface) override;

                tvr::common::PathTree const &m_getPathTree() const override;

                void m_getStatus() const override;

                std::string m_host;

                vrpn_ConnectionPtr m_mainConn;

                VRPNConnectionCollection m_vrpnConns;

                tvr::common::BaseDevicePtr m_systemDevice;

                //tvr::common::SystemComponent *m_systemComponent;

                tvr::common::PathTreeOwner m_pathTreeOwner;

                RemoteHandlerFactory m_factory;

                tvr::common::NetworkingSupport m_network;

                bool m_gotConnection = false;

                ClientInterfaceObjectManager m_ifaceMgr;
        };
    }
}

#endif
