#include <Common/CreateDevice.h>
#include <Common/DeviceWrapper.h>
namespace tvr {
    namespace common {
        BaseDevicePtr createServerDevice(std::string const &name, vrpn_ConnectionPtr const &conn) {
            auto ret = make_shared<DeviceWrapper>(name, conn);
            return ret;
        }
    }
}
