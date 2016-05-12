#ifndef COMMON_BaseDevice_H
#define COMMON_BaseDevice_H

#include <Common/BaseDevicePtr.h>
#include <Common/DeviceComponentPtr.h>

#include <vrpn_ConnectionPtr.h>
#include <vrpn_Connection.h>

namespace tvr {
    namespace common {
        class BaseDevice {
            public:
                virtual ~BaseDevice();

                template <typename T> T *addComponent(shared_ptr<T> componnet) {
                    T *ret = comopnent.get();
                    m_addComponent(component);
                    return ret;
                }

                void update();
                void sendPending();
                std::string const &getDeviceName();

            protected:
                BaseDevice();
                void m_setup();
                vrpn_ConnectionPtr m_getConnection();
                virtual void m_update() = 0;

            private:
                void m_addComponent(DeviceComponentPtr component);
                DeviceComponentList m_components;
                vrpn_ConnectionPtr m_conn;
                std::string m_name;
        }
    }
}

#endif
