#ifndef INC_Common_SerializationTags_h
#define INC_Common_SerializationTags_h

// Internal Includes
// - none

// Library/third-party includes
// - none

// Standard includes
#include <cstddef>

namespace tvr {
namespace common {

    namespace serialization {

        /// @brief The default "type tag" for specifying serialization behavior.
        ///
        /// Usage of tag types and matching type traits allows us to serialize
        /// the same underlying type different ways when requested. If no type
        /// tag is explicitly passed, default behavior based on the type will be
        /// invoked.
        template <typename T> struct DefaultSerializationTag {
            typedef T type;
        };

        /// @brief A tag for use for raw data (bytestream), optionally aligned
        ///
        /// Here, the tag is also used to transport size/alignment information
        /// to serialization/deserialization
        struct AlignedDataBufferTag {
          public:
            AlignedDataBufferTag(size_t length, size_t alignment = 1)
                : m_length(length), m_alignment(alignment) {}
            size_t length() const { return m_length; }
            size_t alignment() const { return m_alignment; }

          private:
            size_t m_length;
            size_t m_alignment;
        };

        /// @brief Used to indicate the kind of integer that should back the
        /// serialization of the enum provided.
        template <typename EnumType, typename IntegerType>
        struct EnumAsIntegerTag {};

        /// @brief A tag for use when the only field in a message is a string so
        /// the length prefix is unnecessary
        struct StringOnlyMessageTag {};

    } // namespace serialization

} // namespace common
} // namespace tvr

#endif
