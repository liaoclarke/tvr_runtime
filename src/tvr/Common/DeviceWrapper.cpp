#include <Common/DeviceWrapper.h>
namespace tvr {
    namespace common {
        DeviceWrapper::DeviceWrapper(std::string const &name, vrpn_ConnectionPtr const &conn, bool client)
                      : vrpn_BaseClass(name.c_str(), conn.get()), m_conn(conn) {
            vrpn_BaseClass::init();
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
