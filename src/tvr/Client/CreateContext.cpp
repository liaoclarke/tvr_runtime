#include <tvr/Client/CreateContext.h>
#include <tvr/Client/PureClientContext.h>
#include <tvr/Util/Verbosity.h>

#include <cstring>

namespace tvr {
    namespace client {
        tvr::common::ClientContext *createContext(const char appId[], const char host[]) {
            tvr::common::ClientContext *ret = nullptr;
            if (!appId || std::strlen(appId) == 0) {
                TVR_DEV_VERBOSE("Could not create client context - null or empty appId provided!");
                return ret;
            }
            ret = tvr::common::makeContext<PureClientContext>(appId, host);
            return ret;
        }
    }
}
