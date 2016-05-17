#ifndef INC_Common_BaseDevicePtr_h
#define INC_Common_BaseDevicePtr_h
#include <tvr/Util/SharedPtr.h>
#include <tvr/Common/BaseDevice.h>

namespace tvr {
    namespace common {
        class BaseDevice;
        typedef shared_ptr<BaseDevice> BaseDevicePtr;
    }
}

#endif
