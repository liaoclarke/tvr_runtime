#ifndef INC_Common_DeviceWrapper_h
#define INC_Common_DeviceWrapper_h
#include <tvr/Common/BaseDevice.h>
#include <tvr/Util/UniquePtr.h>
#include <tvr/Common/VrpnGenericServerObject.h>

#include <vrpn_BaseClass.h>
#include <vrpn_ConnectionPtr.h>

#include <string>

namespace tvr {
    namespace common {
        class DeviceWrapper : public vrpn_BaseClass, public BaseDevice {
            public:
                DeviceWrapper(std::string const &name, vrpn_ConnectionPtr const &conn, bool client);
                virtual ~DeviceWrapper();
                void triggerHardwareDetect();
            private:
                shared_ptr<VrpnGenericServerObject> m_serverPtr;
                bool m_client;
                virtual void mainloop();
                virtual int register_types();
                virtual void m_update();
                vrpn_ConnectionPtr m_conn;
        };
    }
}

#endif
