#ifndef INC_Common_BaseDevice_h
#define INC_Common_BaseDevice_h

#include <tvr/Common/BaseDevicePtr.h>
#include <tvr/Common/RawSenderType.h>
//#include <tvr/Common/DeviceComponentPtr.h>

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
                std::string const &getDeviceName() const;

                /* the equal object to osvr RegistrationContext */
                virtual void triggerHardwareDetect() = 0;

            protected:
                BaseDevice();
                void m_setup(vrpn_ConnectionPtr conn, RawSenderType sender, std::string const &name);
                vrpn_ConnectionPtr m_getConnection() const;
                virtual void m_update() = 0;

            private:
                //void m_addComponent(DeviceComponentPtr component);
                //DeviceComponentList m_components;
                vrpn_ConnectionPtr m_conn;
                RawSenderType m_sender;
                std::string m_name;
        };
    }
}

#endif
