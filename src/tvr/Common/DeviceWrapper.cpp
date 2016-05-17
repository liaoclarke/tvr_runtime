#include <tvr/Common/DeviceWrapper.h>
#include <tvr/Common/RawSenderType.h>

#include <vrpn_BaseClass.h>

#include <string>

namespace tvr {
    namespace common {
		DeviceWrapper::DeviceWrapper(std::string const &name, vrpn_ConnectionPtr const &conn, bool client)
                    : VrpnGenericServerObject(conn), m_conn(conn), m_client(client) {
            VrpnGenericServerObject::init();
            m_setup(conn, tvr::common::RawSenderType(), name);
        }

        DeviceWrapper::~DeviceWrapper() {}

        void DeviceWrapper::mainloop() {
            update();
        }

        void DeviceWrapper::m_update() {
            server_mainloop();
        }

        void DeviceWrapper::triggerHardwareDetect() {
            hardware_detect();
        }
    }
}
