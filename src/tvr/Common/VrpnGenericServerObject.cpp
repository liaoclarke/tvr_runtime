#include <tvr/Common/VrpnGenericServerObject.h>
#include <tvr/Util/Verbosity.h>

#include <vrpn_Tencent.h>
#include <vrpn_ConnectionPtr.h>
#include <vrpn_MainloopContainer.h>
#include <vrpn_Shared.h>

#include <iostream>
#include <fstream>
#include <exception>

namespace tvr {
    namespace common {

        namespace vrpn {
			struct timeval m_timestamp;
            void VRPN_CALLBACK m_handle_poser(void *userdata, const vrpn_POSERCB p) {
                struct timeval *d_timestamp = (struct timeval *)userdata;
                printf("Poser orientation: (%1f, %1f, %1f, %1f) Timestamp: (%ld, %ld) Sleep: (%ld, %ld)\n",
                        p.quat[0], p.quat[1], p.quat[2], p.quat[3], 
                        d_timestamp->tv_sec, d_timestamp->tv_usec,
                        d_timestamp->tv_sec - tvr::common::vrpn::m_timestamp.tv_sec,
                        d_timestamp->tv_usec - tvr::common::vrpn::m_timestamp.tv_usec);
				tvr::common::vrpn::m_timestamp.tv_sec = d_timestamp->tv_sec;
                tvr::common::vrpn::m_timestamp.tv_usec = d_timestamp->tv_usec;
            }

            void VRPN_CALLBACK m_handle_pos(void *userdata, const vrpn_TRACKERCB t) {
                printf("Got tracker pos, sensor %d\n", t.sensor);
            }

            void VRPN_CALLBACK m_handle_vel(void *userdata, const vrpn_TRACKERVELCB t) {
                printf(" + vel, sensor %d\n", t.sensor);
            }
            
            void VRPN_CALLBACK m_handle_acc(void *userdata, const vrpn_TRACKERACCCB t) {
                printf(" + acc, sensor %d\n", t.sensor);
            }

            void VRPN_CALLBACK m_handle_button(void *userdata, const vrpn_BUTTONCB b) {
                printf("Button %d is now in state %d\n", b.button, b.state);
            }
        }

        VrpnGenericServerObject::VrpnGenericServerObject(std::string const &name, vrpn_ConnectionPtr const &conn) 
            : m_device(name), m_connection(conn), m_doing_okay(true), m_devices(new vrpn_MainloopContainer) {
        }

        VrpnGenericServerObject::~VrpnGenericServerObject() {
            close_devices();
            delete m_devices;
            m_devices = nullptr;
        }

        void VrpnGenericServerObject::init() {
            m_doing_okay = setup_Tencent_DK0();
        }

        void VrpnGenericServerObject::server_mainloop() {
            m_devices->mainloop();
            //TVR_DEV_VERBOSE("VrpnGenericServerObject", "devices mainloop");
        }

        void VrpnGenericServerObject::close_devices() {
        }

        void VrpnGenericServerObject::hardware_detect() {
            TVR_DEV_VERBOSE("VrpnGenericServerObject", "trigger hardware detect...");
        }

        bool VrpnGenericServerObject::setup_Tencent_DK0() {
            std::cout << "Opening vrpn_Tencent_DK0" << std::endl;
            try {
                vrpn_Tencent_DK0 *device = new vrpn_Tencent_DK0("Tencent_DK0", m_connection.get());
                device->register_poser_handler(NULL, tvr::common::vrpn::m_handle_poser);
                device->register_pos_handler(NULL, tvr::common::vrpn::m_handle_pos);
                device->register_vel_handler(NULL, tvr::common::vrpn::m_handle_vel);
                device->register_acc_handler(NULL, tvr::common::vrpn::m_handle_acc);
                device->register_button_handler(NULL, tvr::common::vrpn::m_handle_button);
                m_devices->add(device);
                //m_devices->add(new vrpn_Tencent_DK0("Tencent_DK0", m_connection.get()));
            } catch (std::exception &e) {
                throw std::runtime_error("Exception happens during setup tencent dk0 error");
            }
            return true;
        }
    }
}
