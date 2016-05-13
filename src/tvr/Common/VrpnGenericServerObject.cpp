#include <tvr/Common/VrpnGenericServerObject.h>
#include <vrpn_Tencent.h>

#include <iostream>
#include <fstream>

namespace tvr {
    namespace common {
        VrpnGenericServerObject::VrpnGenericServerObject(vrpn_ConnectionPtr const &conn) 
            : m_connection(conn), m_doing_okay(true), m_devices(new vrpn_MainloopContainer) {
                m_doing_okay = setup_Tencent_DK0();                
            }

        VrpnGenericServerObject::~VrpnGenericServerObject() {
            close_devices();
            delete m_devices;
            m_devices = nullptr;
        }

        void VrpnGenericServerObject::server_mainloop() {
            m_devices->mainloop();
        }

        void VrpnGenericServerObject::close_devices() {
        }

        void VrpnGenericServerObject::init() {
        }

        bool VrpnGenericServerObject::setup_Tencent_DK0() {
            std::cout << "Opening vrpn_Tencent_DK0" << std::endl;
            m_devices->add(new vrpn_Tencent_DK0(m_connection));
        }
    }
}
