#ifndef INC_Common_VrpnGenericServerObject_h
#define INC_Common_VrpnGenericServerObject_h
#include <boost/noncopyable.hpp>
#include <vrpn_ConnectionPtr.h>
#include <vrpn_MainloopContainer.h>

namespace tvr {
    namespace common {
        class VrpnGenericServerObject {
            public:
                VrpnGenericServerObject();
                ~VrpnGenericServerObject();
                void init();
                void server_mainloop();
                inline bool doing_okay() const { return m_doing_okay; }
            protected:
                void close_devices();
                bool m_doing_okay;
                vrpn_ConnectionPtr m_connection;
                vrpn_MainloopContainer *m_devices;
                bool setup_Tencent_DK0();
        };
    }
}

#endif
