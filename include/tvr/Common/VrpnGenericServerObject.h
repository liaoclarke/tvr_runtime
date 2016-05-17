#ifndef INC_Common_VrpnGenericServerObject_h
#define INC_Common_VrpnGenericServerObject_h
#include <boost/noncopyable.hpp>
#include <vrpn_ConnectionPtr.h>
#include <vrpn_MainloopContainer.h>
#include <vrpn_Configure.h>
#include <vrpn_Poser.h>
#include <vrpn_Button.h>
#include <vrpn_Tracker.h>

namespace tvr {
    namespace common {
        class VrpnGenericServerObject {
            public:
                VrpnGenericServerObject(vrpn_ConnectionPtr const &conn);
                ~VrpnGenericServerObject();
                void init();
                void server_mainloop();
                void hardware_detect();
                inline bool doing_okay() const { return m_doing_okay; }
            protected:
                void close_devices();
                bool m_doing_okay;
                bool setup_Tencent_DK0();
                vrpn_ConnectionPtr m_connection;
                vrpn_MainloopContainer *m_devices;
                void VRPN_CALLBACK m_handle_poser(void* userdata, const vrpn_POSERCB p);
                void VRPN_CALLBACK m_handle_pos(void* userdata, const vrpn_TRACKERCB t);
                void VRPN_CALLBACK m_handle_vel(void* userdata, const vrpn_TRACKERVELCB t);
                void VRPN_CALLBACK m_handle_acc(void* userdata, const vrpn_TRACKERACCCB t);
                void VRPN_CALLBACK m_handle_button(void* userdata, const vrpn_BUTTONCB b);
        };
    }
}

#endif
