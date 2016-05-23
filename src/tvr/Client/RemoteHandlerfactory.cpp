#include <tvr/Client/RemoteHandlerFactory.h>
#include <tvr/Client/TrackerRemoteFactory.h>
#include <tvr/Client/AccountRemoteFactory.h>

namespace tvr {
    namespace client {
        void populateRemoteHandlerFactory(RemoteHandlerFactory &factory, VRPNConnection const &conns) {
            TrackerRemoteFactory(conn).registerWith(factory);
            AccountRemoteFactory(conn).registerWith(factory);
        }
    }
}
