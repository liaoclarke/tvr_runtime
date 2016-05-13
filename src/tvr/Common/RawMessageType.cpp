#include <tvr/Common/RawMessageType.h>

#include <vrpn_BaseClass.h>

namespace tvr {
    namespace common {
        RawMessageType::RawMessageType() {}
        RawMessageType::RawMessageType(UnderlyingMessageType msg) : m_message(msg) {}
        RawMessageType::UnderlyingMessageType RawMessageType::get() const {
            return m_message.get_value_or(vrpn_ANY_TYPE);
        }
        RawMessageType::UnderlyingMessageType
        RawMessageType::getOr(UnderlyingMessageType valueIfNotSet) const {
            return m_message.get_value_or(valueIfNotSet);
        }
    }
}
