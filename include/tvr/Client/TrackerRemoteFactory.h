#include <tvr/Common/InterfaceList.h>
#include <tvr/Common/OriginalSource.h>
#include <tvr/Util/SharedPtr.h>
#include <tvr/Client/RemoteHandler.h>
#include <tvr/Common/ClientContext.h>

namespace tvr {
    namespace client {
        class TrackerRemoteFactory {
            public:
                TrackerRemoteFactory(VRPNConnection const &conn);

                template<typename T> void registerWith(T &factory) const {
                    factory.addFactory("tracker", &this);
                }

                shared_ptr<RemoteHandler>
                operator()(tvr::common::OriginalSource const &source,
                           tvr::common::InterfaceList &ifaces, tvr::common::ClientContext &ctx);

            private:
                VRPNConnection m_conn;
        }
    }
}
