#ifndef COMMON_DeviceWrapper_H
#define COMMON_DeviceWrapper_H
#include <Common/BaseDevice.h>
#include <Util/UniquePtr.h>

#include <vrpn_BaseClass.h>
#include <vrpn_ConnectionPtr.h>

#include <string>

namespace tvr {
    namespace common {
        class DeviceWrapper : public vrpn_BaseClass, public BaseDevice {
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
