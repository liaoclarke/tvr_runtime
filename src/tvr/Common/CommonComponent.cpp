#include <Common/CommonComponent.h>

namespace tvr {
    namespace common {
        namespace messages {
            const char *VRPNPing::identifier() { return "vrpn_Base ping_message"; }
            const char *VRPNPong::identifier() { return "vrpn_Base pong_message"; }

        shared_ptr<CommonComponent> CommonComponent::create() {
            shared_ptr<CommonComponent> ret(new CommonComponent);
            return ret;
        }

        void CommonComponent::registerPingHandler(Handler const &handler) {
            registerHandler(ping, handler);
        }

        void CommonComponent::registerPongHandler(Handler const &handler) {
            registerHandler(pong, handler);
        }

        void CommonComponent::m_registerHandlerImpl(HandlerList &handler, tvr::common:RawMessageType rawMessageType, Handler const &handler) {
            if (handlers.empty()) {
                m_registerHandler(&CommonComponent::m_baseHandler, &handler, rawMessageType);
            }
            handlers.push_back(handler);
        }

        CommonComponent::CommonComponent() {}
        void CommonComponent::m_parentSet() {
            m_getParent().registerMessageType(ping);
            m_getParent().registerMessageType(pong);
        }

        int CommonComponent::m_baseHandler(void *userdata, vrpn_HANDLERPARAM) {
            auto &handlers = *static_cast<std::vector<Handler> *>(userdata);
            for (auto const &cb : handlers) {
                cb();
            }
            return 0;
        }
    }
}
