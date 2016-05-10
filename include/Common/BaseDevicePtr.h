#ifndef COMMON_BaseDevicePtr_H
#define COMMON_BaseDevicePtr_H
#include <Util/SharedPtr.h>
namespace tvr {
    namespace common {
        class BaseDevice;
        typedef shared_ptr<BaseDevice> BaseDevicePtr;
    }
}

#endif
