#ifndef INC_Common_RawMessageType_h
#define INC_Common_RawMessageType_h
#include <boost/optional.hpp>

namespace tvr {
    namespace common {
        class RawMessageType {
            public:
                typedef int32_t UnderlyingMessageType;
                RawMessageType();
                explicit RawMessageType(UnderlyingMessageType msg);
                UnderlyingMessageType get() const;
                UnderlyingMessageType getOr(UnderlyingMessageType valueIfNotSet) const;
            private:
                boost::optional<UnderlyingMessageType> m_message;
        };
    }
}
#endif
