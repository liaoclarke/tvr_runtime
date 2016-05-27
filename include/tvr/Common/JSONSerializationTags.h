#ifndef INC_Common_JSONSerializationTags_h
#define INC_Common_JSONSerializationTags_h

// Internal Includes
#include <tvr/Common/SerializationTags.h>
#include <tvr/Common/SerializationTraits.h>

// Library/third-party includes
#include <json/value.h>
#include <json/writer.h>
#include <json/reader.h>

// Standard includes
#include <string>
#include <stdexcept>

namespace tvr {
namespace common {

    namespace serialization {
        /// @brief The basic serialization traits for a JSON value: piggybacks
        /// on your choice of serialization for strings.
        template <typename Tag, typename UnderlyingStringTag =
                                    DefaultSerializationTag<std::string> >
        struct JSONSerializationTraitsBase
            : BaseSerializationTraits<Json::Value> {
            typedef BaseSerializationTraits<Json::Value> Base;
            template <typename BufferType>
            static void serialize(BufferType &buf,
                                  typename Base::param_type val, Tag const &) {
                serializeRaw(buf, Json::FastWriter().write(val),
                             UnderlyingStringTag());
            }
            template <typename BufferReaderType>
            static void deserialize(BufferReaderType &buf,
                                    typename Base::reference_type val,
                                    Tag const &) {
                std::string str;
                deserializeRaw(buf, str, UnderlyingStringTag());
                Json::Reader reader;
                if (!reader.parse(str, val)) {
                    throw std::runtime_error(
                        "Could not parse JSON during deserialization!");
                }
            }
            static size_t spaceRequired(size_t existingBytes,
                                        typename Base::param_type val,
                                        Tag const &) {
                return getBufferSpaceRequiredRaw(existingBytes,
                                                 Json::FastWriter().write(val),
                                                 UnderlyingStringTag());
            }
        };

        /// @brief Default serialization traits for JSON: length-prefixed string
        ///
        /// Safe default, though a little extra overhead if your message is
        /// entirely JSON
        template <>
        struct SerializationTraits<DefaultSerializationTag<Json::Value>, void>
            : JSONSerializationTraitsBase<
                  DefaultSerializationTag<Json::Value>,
                  DefaultSerializationTag<std::string> > {};

        /// @brief A tag for use when the only field in a message is JSON so the
        /// length prefix is unnecessary
        struct JsonOnlyMessageTag {};

        /// @brief Traits invoked by using JsonOnlyMesssageTag - uses
        /// StringOnlyMessageTag to serialize the resulting string without a
        /// length prefix.
        template <>
        struct SerializationTraits<JsonOnlyMessageTag, void>
            : JSONSerializationTraitsBase<JsonOnlyMessageTag,
                                          StringOnlyMessageTag> {};
    } // namespace serialization

} // namespace common
} // namespace tvr

#endif // INCLUDED_JSONSerializationTags_h_GUID_3DE3DE8A_A912_4BB4_34BD_4AC35D791D6C
