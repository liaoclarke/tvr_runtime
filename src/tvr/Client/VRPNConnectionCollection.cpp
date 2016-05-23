#include <tvr/Client/VRPNConnectionCollection.h>

// Library/third-party includes
#include <vrpn_Connection.h>

// Standard includes
// - none

namespace tvr {
    namespace client {
        VRPNConnectionCollection::VRPNConnectionCollection()
            : m_connMap(make_shared<ConnectionMap>()) {}

        vrpn_ConnectionPtr VRPNConnectionCollection::getConnection(
            common::elements::DeviceElement const &elt) {
            return getConnection(elt.getDeviceName(), elt.getServer());
        }

        vrpn_ConnectionPtr
        VRPNConnectionCollection::addConnection(vrpn_ConnectionPtr conn,
                                                std::string const &host) {
            auto &connMap = *m_connMap;
            auto existing = connMap.find(host);
            if (existing != end(connMap)) {
                return existing->second;
            }
            connMap[host] = conn;
            BOOST_ASSERT(!empty());
            return conn;
        }

        vrpn_ConnectionPtr
        VRPNConnectionCollection::getConnection(std::string const &device,
                                                std::string const &host) {
            auto &connMap = *m_connMap;
            auto existing = connMap.find(host);
            if (existing != end(connMap)) {
                return existing->second;
            }
            auto fullName = device + "@" + host;

            vrpn_ConnectionPtr newConn(
                vrpn_get_connection_by_name(fullName.c_str(), nullptr, nullptr,
                                            nullptr, nullptr, nullptr, true));
            connMap[host] = newConn;
            newConn->removeReference(); // Remove extra reference.
            BOOST_ASSERT(!empty());
            return newConn;
        }

        void VRPNConnectionCollection::updateAll() {
            for (auto &connPair : *m_connMap) {
                connPair.second->mainloop();
            }
        }

    }
}
