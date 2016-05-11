#ifndef COMMON_CommonComponent_H
#define COMMON_CommonComponent_H
#include <vector>
#include <functional>
namespace tvr {
    namespace common {
        namespace messages {
            class VRPNPing : public MessageRegistration<VRPNPing> {
              public:
                OSVR_COMMON_EXPORT static const char *identifier();
            };
            class VRPNPong : public MessageRegistration<VRPNPong> {
              public:
                OSVR_COMMON_EXPORT static const char *identifier();
            };
            using CommonComponentMessageTypes =
            typepack::list<VRPNPing, VRPNPong>;
        }
        class CommonComponent : public DeviceComponent {
            public:
                static shared_ptr<CommonComponent> create();
                typedef std::function<void()> Handler;
                message::VRPNPing ping;
                void registerPingHandler(Handler const &handler);
                message::VRPNPong pong;
                void registerPongHandler(Handler const &handler);
                template <typename T> 
                void registerHandler(MessageRegistration<T> const &message, Handler const &handler) {
                    auto &handler = typepack::get<T>(m_handler);
                    m_registerHandlerImpl(handlers, message.getMessageType(), handler);
                }

            private:
                CommonComponent();
                void m_parentSet() override;
                using HandlerList = std::vector<Handler>;
                void m_registerHandlerImpl(HandlerList &handlers, tvr::common::RawMessageType rawMessageType, Handler const &handler);
                static int m_baseHandler(void *userdata, vrpn_HANDLERPARAM);
                typepack::TypeKeyedMap<message::CommonComponentMessageTypes, std::vector<Handler>> m_handlers;
        };
    }
}

#endif
