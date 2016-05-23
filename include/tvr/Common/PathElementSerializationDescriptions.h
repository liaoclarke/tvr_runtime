#ifndef INC_Common_PathElementSerializationDescriptions_h
#define INC_Common_PathElementSerializationDescriptions_h

// Internal Includes
#include <tvr/Common/PathElementTypes.h>

// Library/third-party includes
// - none

// Standard includes
#include <type_traits>

namespace tvr {
namespace common {
    namespace {

        /// @brief "using" statement to combine/simplify the enable_if test for
        /// an element type's serialization.
        template <typename Input, typename Known>
        using enable_if_element_type = typename std::enable_if<std::is_same<
            typename std::remove_const<Input>::type, Known>::value>::type;

        /// @brief Description for DeviceElement
        template <typename Functor, typename ValType>
        inline enable_if_element_type<ValType, elements::DeviceElement>
        serializationDescription(Functor &f, ValType &value) {
            f("device_name", value.getDeviceName());
            f("server", value.getServer());
            f("descriptor", value.getDescriptor());
        }

        /// @brief Description for AliasElement
        template <typename Functor, typename ValType>
        inline enable_if_element_type<ValType, elements::AliasElement>
        serializationDescription(Functor &f, ValType &value) {
            f("source", value.getSource());
            f("priority", value.priority());
        }

        /// @brief Description for StringElement
        template <typename Functor, typename ValType>
        inline enable_if_element_type<ValType, elements::StringElement>
        serializationDescription(Functor &f, ValType &value) {
            f("string", value.getString());
        }

        // Descriptions for elements without extra data
        template <typename Functor, typename ValType>
        inline enable_if_element_type<ValType, elements::NullElement>
        serializationDescription(Functor &, ValType &) {}
        template <typename Functor, typename ValType>
        inline enable_if_element_type<ValType, elements::PluginElement>
        serializationDescription(Functor &, ValType &) {}
        template <typename Functor, typename ValType>
        inline enable_if_element_type<ValType, elements::InterfaceElement>
        serializationDescription(Functor &, ValType &) {}
        template <typename Functor, typename ValType>
        inline enable_if_element_type<ValType, elements::SensorElement>
        serializationDescription(Functor &, ValType &) {}

    } // namespace
}
}
#endif // INCLUDED_PathElementSerializationDescriptions_h_GUID_88DACA90_818A_4B81_9655_1177F10E8142
