#ifndef INC_Common_DeviceComponent_h
#define INC_Common_DeviceComponent_h
#include <tvr/Common/BaseDevice.h>
#include <tvr/Common/BaseDevicePtr.h>
#include <tvr/Common/MessageHandler.h>
#include <tvr/Common/BaseMessageTraits.h>
namespace tvr {
    namespace common {
        class DeviceComponent {
            public:
                typedef BaseDevice Parent;
                void recordParent(Parent &dev);
                void update();
            protected:
                DeviceComponent();
                bool m_hasParent() const;
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
