#ifndef INC_Common_DeviceComponentPtr_h
#define INC_Common_DeviceComponentPtr_h
#include <tvr/Util/SharedPtr.h>
#include <tvr/Common/DeviceComponent.h>

#include <vector>

namespace tvr {
    namespace common {
        class DeviceComponent;
        typedef shared_ptr<DeviceComponent> DeviceComponentPtr;
        typedef std::vector<DeviceComponentPtr> DeviceComponentList;
    }
}

#endif
