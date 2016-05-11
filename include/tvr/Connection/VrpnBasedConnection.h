#ifndef CONNECTION_VrpnBasedConnection_H
#define CONNECTION_VrpnBasedConnection_H
#include <Connection/Connection.h>
#include <Common/NetworkingSupport.h>
#include <vrpn_Connection.h>
#include <vrpn_ConnectionPtr.h>

namespace tvr {
    namespace connection {
        class VrpnBasedConnection : boost::noncopyable {
            public:
                VrpnBasedConnection();
                virtual ~VrpnBasedConnection();
            private:
                void m_initConnection(const char NIC[] = nullptr);
                virtual void m_process();
                vrpn_ConnectionPtr m_vrpnConnection;
                tvr::common::NetworkingSupport m_network;
        }
    }
}

#endif
