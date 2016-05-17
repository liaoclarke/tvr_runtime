#include <tvr/Common/RawSenderType.h>

#include <vrpn_BaseClass.h>

namespace tvr {
    namespace common {
        RawSenderType::RawSenderType() {
        }

        RawSenderType::RawSenderType(UnderlyingSenderType sender) : m_sender(sender) {
        }

        RawSenderType::UnderlyingSenderType RawSenderType::get() const {
            return m_sender.get_value_or(vrpn_ANY_SENDER);
        }

        RawSenderType::UnderlyingSenderType
        RawSenderType::getOr(UnderlyingSenderType valueIfNotSet) const {
            return m_sender.get_value_or(valueIfNotSet);
        }
    }
}
