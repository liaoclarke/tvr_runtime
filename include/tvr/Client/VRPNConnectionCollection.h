#ifndef INC_Client_VRPNConnectionCollection_h
#define INC_Client_VRPNConnectionCollection_h

// Internal Includes
#include <tvr/Util/SharedPtr.h>
#include <tvr/Common/PathElementTypes.h>
#include <tvr/Client/Export.h>

// Library/third-party includes
#include <vrpn_ConnectionPtr.h>

// Standard includes
#include <string>
#include <unordered_map>

namespace tvr {
    namespace client {
        class VRPNConnectionCollection {
          public:
            TVR_CLIENT_EXPORT VRPNConnectionCollection();

            TVR_CLIENT_EXPORT vrpn_ConnectionPtr
            addConnection(vrpn_ConnectionPtr conn, std::string const &host);

            vrpn_ConnectionPtr getConnection(std::string const &device,
                                             std::string const &host);
            vrpn_ConnectionPtr
            getConnection(common::elements::DeviceElement const &elt);
            TVR_CLIENT_EXPORT void updateAll();
            bool empty() const {
                return m_connMap->empty();
            }

          private:
            typedef std::unordered_map<std::string, vrpn_ConnectionPtr>
                ConnectionMap;
            shared_ptr<ConnectionMap> m_connMap;
        };
    }
}

#endif
