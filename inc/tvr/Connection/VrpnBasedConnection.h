#ifndef INC_Connection_VrpnBasedConnection_h
#define INC_Connection_VrpnBasedConnection_h
#include <tvr/Connection/Connection.h>
#include <tvr/Common/NetworkingSupport.h>

#include <vrpn_Connection.h>
#include <vrpn_ConnectionPtr.h>

namespace tvr {
    namespace connection {
        class VrpnBasedConnection : public Connection {
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
