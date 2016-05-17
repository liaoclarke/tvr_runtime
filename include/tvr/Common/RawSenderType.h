#ifndef INC_Common_RawSenderType_h
#define INC_Common_RawSenderType_h
#include <boost/optional.hpp>

#include <stdint.h>

namespace tvr {
    namespace common {
        class RawSenderType {
            public:
                typedef int32_t UnderlyingSenderType;
                RawSenderType();
                explicit RawSenderType(UnderlyingSenderType sender);
                UnderlyingSenderType get() const;
                UnderlyingSenderType getOr(UnderlyingSenderType valueIfNotSet) const;
            private:
                boost::optional<UnderlyingSenderType> m_sender;
        };
    }
}

#endif
