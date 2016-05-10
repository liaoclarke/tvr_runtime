#include <Connection/VrpnBasedConnection.h>
#include <vrpn_ConnectionPtr.h>

namespace tvr {
    namespace connection {
        VrpnBasedConnection::VrpnBasedConnection() {
            m_initConnection("loopback:");
        }

        VrpnBasedConnection::m_initConnection(const char iface[]) {
            int port = vrpn_DEFAULT_LISTEN_PORT_NO;
            if (!m_network.isUp()) {
                TVR_DEV_VERBOSE("VrpnBasedConnection", "Network error: " << m_network.getError());
                throw std::runtime_error(m_network.getError());
            }
            m_VrpnConnection = vrpn_ConnectionPtr::create_server_connection(port, nullptr, nullptr, iface);
        }

        void VrpnBasedConnetion::m_process() {
            m_vrpnConnection->mainloop();
        }

        void *VrpnBasedConnection::getUnderlyingObject() {
            return static_cast<void *>(m_vrpnConnection.get());
        }
    }
}
