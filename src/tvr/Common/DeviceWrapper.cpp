#include <tvr/Common/DeviceWrapper.h>

namespace tvr {
    namespace common {
        DeviceWrapper::DeviceWrapper(std::string const &name, vrpn_ConnectionPtr const &conn, bool client)
                      : VrpnGenericServerObject(conn), m_conn(conn) {
            VrpnGenericServerObject::init();
            m_setup(conn, common::RawSenderType(d_sender_id), name);
        }

        DeviceWrapper::~DeviceWrapper() {}

        void DeviceWrapper::mainloop() {
            update();
        }

        void DeviceWrapper::m_update() {
            server_mainloop();
        }
    }
}
