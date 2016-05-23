#ifndef INC_Client_CreateContext_h
#define INC_Client_CreateContext_h
#include <tvr/Client/Export.h>
#include <tvr/Common/ClientContext_fwd.h>
namespace tvr {
    namespace client {
        TVR_CLIENT_EXPORT tvr::common::ClientContext *
            createContext(const char appId[], const char host[] = "localhost");
    }
}
class vrpn_ConnectionPtr;

#endif
