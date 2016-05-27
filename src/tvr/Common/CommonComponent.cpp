#include <tvr/Common/CommonComponent.h>

// Library/third-party includes
// - none

// Standard includes
// - none

namespace tvr {
namespace common {
    namespace messages {

        // These messages all must match the ones in VRPN exactly.

        /// @todo add test to verify that this matches VRPN: message type string
        /// not accessible as a constant, so we have to extract the message ID
        /// instead.
        const char *VRPNPing::identifier() { return "vrpn_Base ping_message"; }

        /// @todo add test to verify that this matches VRPN: message type string
        /// not accessible as a constant, so we have to extract the message ID
        /// instead.
        const char *VRPNPong::identifier() { return "vrpn_Base pong_message"; }

        const char *VRPNGotFirstConnection::identifier() {
            return "VRPN_Connection_Got_First_Connection";
        }
        const char *VRPNGotConnection::identifier() {
            return "VRPN_Connection_Got_Connection";
        }
        const char *VRPNDroppedConnection::identifier() {
            return "VRPN_Connection_Dropped_Connection";
        }
        const char *VRPNDroppedLastConnection::identifier() {
            return "VRPN_Connection_Dropped_Last_Connection";
        }

    } // namespace messages
    shared_ptr<CommonComponent> CommonComponent::create() {
        shared_ptr<CommonComponent> ret(new CommonComponent);
        return ret;
    }

    void CommonComponent::registerPingHandler(Handler const &handler) {
        /// Just forward to the templated implementation.
        registerHandler(ping, handler);
    }

    void CommonComponent::registerPongHandler(Handler const &handler) {
        /// Just forward to the templated implementation.
        registerHandler(pong, handler);
    }

    void CommonComponent::m_registerHandlerImpl(
        HandlerList &handlers, tvr::common::RawMessageType rawMessageType,
        Handler const &handler) {
        if (handlers.empty()) {
            m_registerHandler(&CommonComponent::m_baseHandler, &handlers,
                              rawMessageType);
        }
        handlers.push_back(handler);
    }

    CommonComponent::CommonComponent() {}
    void CommonComponent::m_parentSet() {
        m_getParent().registerMessageType(ping);
        m_getParent().registerMessageType(pong);
        m_getParent().registerMessageType(gotFirstConnection);
        m_getParent().registerMessageType(gotConnection);
        m_getParent().registerMessageType(droppedConnection);
        m_getParent().registerMessageType(droppedLastConnection);
    }

    int CommonComponent::m_baseHandler(void *userdata, vrpn_HANDLERPARAM) {
        /// Our userdata here is a pointer to a vector of handlers - it doesn't
        /// matter to us what kind.
        auto &handlers = *static_cast<std::vector<Handler> *>(userdata);
        for (auto const &cb : handlers) {
            cb();
        }
        return 0;
    }

} // namespace common
} // namespace tvr
