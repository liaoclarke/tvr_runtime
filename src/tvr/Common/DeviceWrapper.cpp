#include <tvr/Common/DeviceWrapper.h>
#include <tvr/Util/SharedPtr.h>

#include <vrpn_BaseClass.h>

namespace tvr {
    namespace common {
		DeviceWrapper::DeviceWrapper(std::string const &name, vrpn_ConnectionPtr const &conn, bool client)
                    : vrpn_BaseClass(name.c_str(), conn.get()), m_conn(conn), m_client(client) {
            vrpn_BaseClass::init();
            m_setup(conn, tvr::common::RawSenderType(d_sender_id), name);
            if (!m_client) {
                m_serverPtr = make_shared<VrpnGenericServerObject>(name, conn);
                m_serverPtr->init();
            }
        }

        DeviceWrapper::~DeviceWrapper() {}

        void DeviceWrapper::mainloop() {
            update();
        }

        void DeviceWrapper::m_update() {
            if (m_client) {
                m_getConnection()->mainloop();
                client_mainloop();
            } else {
                m_serverPtr->server_mainloop();
                server_mainloop();
            }
        }

        void DeviceWrapper::triggerHardwareDetect() {
            if (!m_client) {
                m_serverPtr->hardware_detect();
            }
        }

        int DeviceWrapper::register_types() {
            return 0;
        }
    }
}
