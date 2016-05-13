#ifndef INC_Common_DeviceWrapper_h
#define INC_Common_DeviceWrapper_h
#include <tvr/Common/BaseDevice.h>
#include <tvr/Util/UniquePtr.h>

#include <vrpn_BaseClass.h>
#include <vrpn_ConnectionPtr.h>

#include <string>

namespace tvr {
    namespace common {
        class DeviceWrapper : public VrpnGenericServerObject, public BaseDevice {
            public:
                DeviceWrapper(std::string const &name, vrpn_ConnectionPtr const &conn);
                virtual ~DeviceWrapper();
            private:
                virtual void mainloop();
                virtual void m_update();
                vrpn_ConnectionPtr m_conn;
        };
    }
}

#endif
