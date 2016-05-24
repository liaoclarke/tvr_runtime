#include <tvr/Common/CreateDevice.h>
#include <tvr/Common/DeviceWrapper.h>
namespace tvr {
    namespace common {
        BaseDevicePtr createServerDevice(std::string const &name, vrpn_ConnectionPtr const &conn) {
            auto ret = make_shared<DeviceWrapper>(name, conn, false);
            return ret;
        }

        BaseDevicePtr createClientDevice(std::string const &name, vrpn_ConnectionPtr const &conn) {
            auto ret = make_shared<DeviceWrapper>(name, conn, true);
            return ret;
        }
    }
}
