#ifndef INC_Common_CreateDevice_h
#define INC_Common_CreateDevice_h
#include <tvr/Common/BaseDevicePtr.h>
#include <vrpn_ConnectionPtr.h>

namespace tvr {
    namespace common {
        BaseDevicePtr createServerDevice(std::string const &name, vrpn_ConnectionPtr const &conn);
    }
}

#endif
