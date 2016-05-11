#include <Common/DeviceComponent.h>
#include <Common/BaseDevice.h>

#include <boost/assert.hpp>

namespace tvr {
    namespace common {
        DeviceComponent::DeviceComponent() : m_parent(nullptr) {}
        void DeviceComponent::recordParent(Parent &dev) {
            BOOST_ASSERT_MSG(nullptr == m_parent, "recordParent should only be called once!");
            m_parent = &dev;
            m_parentSet();
        }

        void DeviceComponent::update() {
            m_update();
        }

        bool DeviceComponent::m_hasParent() {
            return nullptr != m_parent;
        }

        DeviceComponent::m_registerHandler(vrpn_MESSAGEHANDLER handler, void *userdata, RawMessageType const &msgType) {
            auto h = make_shared<MessageHandler<BaseDeviceMessageHandlerTraits> >(handler, userdata, msgType);
            h->registerHandler(&m_getParent());
            m_messageHandlers.push_back(h);
        }
        void DeviceComponent::m_update() {}
    }
}
