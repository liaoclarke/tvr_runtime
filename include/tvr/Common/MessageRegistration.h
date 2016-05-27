#ifndef INC_Common_MessageRegistration_h
#define INC_Common_MessageRegistration_h

// Internal Includes
#include <tvr/Common/RawMessageType.h>

// Library/third-party includes
// - none

// Standard includes
// - none

namespace tvr {
namespace common {
    /// @brief CRTP class template wrapping message-specific data and/or logic.
    ///
    /// @tparam Derived Derived class, your message-specific type: must have a
    /// `static const char * identifier()` method returning the string ID of the
    /// message.
    template <typename Derived> class MessageRegistration {
      public:
        static const char *identifier() { return Derived::identifier(); }

        RawMessageType getMessageType() const { return m_type; }
        void setMessageType(RawMessageType msgType) { m_type = msgType; }

      private:
        Derived &derived() { return *static_cast<Derived *>(this); }
        Derived const &derived() const {
            return *static_cast<Derived const *>(this);
        }

        RawMessageType m_type;
    };
} // namespace common
} // namespace vr
#endif
