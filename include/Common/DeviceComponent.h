#ifndef COMMON_DeviceComponent_H 
#define COMMON_DeviceComponent_H
#include <Common/DeviceComponentPtr.h>
#include <Common/BaseDevicePtr.h>
namespace tvr {
    namespace common {
        class DeviceComponent {
            public:
                typedef BaseDevice Parent;
                void recordParent(Parent &dev);
                void update();
            protected:
                DeviceComponent();
                bool m_hasParent();
                Parent &m_getParent();
                void m_registerHandler(vrpn_MESSAGEHANDLER handler, void *userdata, RawMessageType const &msgType);
                virtual void m_parentSet() = 0;
                virtual void m_update();
            private:
                Parent *m_parent;
                MessageHandlerList<BaseDeviceMessageHandlerTraits> m_messageHandlers;
        };
    }
}

#endif
