#ifndef INC_Common_PathElementTypes_h
#define INC_Common_PathElementTypes_h

// Internal Includes
#include <tvr/Common/Export.h>
#include <tvr/Common/PathElementTypes_fwd.h> // IWYU pragma: export
#include <tvr/Util/PortFlags.h>

// Library/third-party includes
#include <boost/variant/variant.hpp>
#include <boost/mpl/contains.hpp>
#include <boost/operators.hpp>
#include <json/value.h>

// Standard includes
#include <string>
#include <type_traits>

namespace tvr {
namespace common {
/// @brief Namespace for the various element types that may constitute a
/// node in the path tree.
#ifndef TVR_DOXYGEN_EXTERNAL
///
/// Note that any changes that add/remove data members should result in
/// corresponding serialization changes in
/// src/tvr/Common/PathTreeSerialization.cpp
#endif
    namespace elements {
        /// @brief Base, using the CRTP, providing some basic functionality for
        /// path elements.
        template <typename Type> class ElementBase {
          public:
            typedef Type type;
            typedef ElementBase<Type> base_type;

            const char *getTypeName() const;

          protected:
            /// @brief Protected constructor to force subclassing.
            ///
            /// Inline implementation at the bottom of the file contains static
            /// assertions.
            ElementBase();
        };

        /// @brief Base, using the CRTP, of "empty" path elements (those that
        /// don't store additional data but derive their meaning from their
        /// path)
        template <typename Type>
        class EmptyElementBase : public ElementBase<Type>,
                                 boost::operators<Type> {
          public:
            /// @brief Trivial equality comparison operator

            bool operator==(EmptyElementBase<Type> const &) const {
                return true;
            }

          protected:
            /// @brief Protected constructor to force subclassing.
            EmptyElementBase() {}
        };

        /// @brief The element type created when requesting a path that isn't
        /// yet in the tree.
        class NullElement : public EmptyElementBase<NullElement> {
          public:
            NullElement() = default;
        };

        /// @brief The element type corresponding to a plugin
        class PluginElement : public EmptyElementBase<PluginElement> {
          public:
            PluginElement() = default;
        };

        /// @brief The element type corresponding to a device, which implements
        /// 0 or more interfaces
        class DeviceElement : public ElementBase<DeviceElement>,
                              boost::operators<DeviceElement> {
          public:
            DeviceElement() = default;
            DeviceElement(std::string const &deviceName,
                          std::string const &server)
                : m_devName(deviceName), m_server(server) {}

            TVR_COMMON_EXPORT static DeviceElement
            createVRPNDeviceElement(std::string const &deviceName,
                                    std::string const &server);

            /// Can also pass util::OmitAppendingPort as a special port
            /// value.
            TVR_COMMON_EXPORT static DeviceElement
            createDeviceElement(std::string const &deviceName,
                                std::string const &server,
                                int port = util::UseDefaultPort);

            TVR_COMMON_EXPORT std::string &getDeviceName();
            TVR_COMMON_EXPORT std::string const &getDeviceName() const;
            TVR_COMMON_EXPORT std::string &getServer();
            TVR_COMMON_EXPORT std::string const &getServer() const;
            TVR_COMMON_EXPORT std::string getFullDeviceName() const;

            TVR_COMMON_EXPORT Json::Value &getDescriptor();
            TVR_COMMON_EXPORT Json::Value const &getDescriptor() const;

            /// @brief Equality comparison operator
            bool operator==(DeviceElement const &other) const {
                return m_devName == other.m_devName &&
                       m_server == other.m_server &&
                       m_descriptor == other.m_descriptor;
            }

          private:
            std::string m_devName;
            std::string m_server;
            Json::Value m_descriptor;
        };

        /// @brief The element type corresponding to an interface, which often
        /// may have one or more sensors
        class InterfaceElement : public EmptyElementBase<InterfaceElement> {
          public:
            InterfaceElement() = default;
        };

        /// @brief The element type corresponding to a particular sensor of an
        /// interface
        class SensorElement : public EmptyElementBase<SensorElement> {
          public:
            SensorElement() = default;
        };

        /// @brief The element type corresponding to a path alias, with a
        /// priority level for sorting out whether automatic routes should
        /// replace or update it.
        ///
        /// This is a "shallow" alias - does not link to children.
        class AliasElement : public ElementBase<AliasElement>,
                             boost::operators<DeviceElement> {
          public:
            /// @brief Constructor with source and priority.
            TVR_COMMON_EXPORT
            AliasElement(std::string const &source, AliasPriority priority);

            /// @brief Constructor with source.
            TVR_COMMON_EXPORT
            AliasElement(std::string const &source);

            /// @brief default constructor
            AliasElement() : AliasElement("", ALIASPRIORITY_MINIMUM) {}

            /// @brief Sets the source of this alias
            /// @param source absolute path of the target, possibly wrapped in
            /// transforms.
            /// @todo support relative paths - either here or at a different
            /// level
            TVR_COMMON_EXPORT void setSource(std::string const &source);

            /// @brief Get the source of data for this alias
            TVR_COMMON_EXPORT std::string &getSource();
            /// @overload
            TVR_COMMON_EXPORT std::string const &getSource() const;

            /// @brief Get/set whether this alias was automatically set (and
            /// thus subject to being override by explicit routing)
            TVR_COMMON_EXPORT AliasPriority &priority();
            /// @overload
            TVR_COMMON_EXPORT AliasPriority priority() const;

            /// @brief Equality comparison operator
            bool operator==(AliasElement const &rhs) const {
                return m_priority == rhs.m_priority && m_source == rhs.m_source;
            }

          private:
            std::string m_source;
            AliasPriority m_priority;
        };

        /// @brief The element type corresponding to a string value
        /// such as a JSON string
        class StringElement : public ElementBase<StringElement> {
          public:
            /// @brief Default constructor
            TVR_COMMON_EXPORT
            StringElement();

            /// @brief Constructor with value.
            TVR_COMMON_EXPORT
            StringElement(std::string const &s);

            /// @brief Get/set (if non const) the stored string
            TVR_COMMON_EXPORT std::string &getString();

            /// @overload
            TVR_COMMON_EXPORT std::string const &getString() const;

            TVR_COMMON_EXPORT void setString(std::string const &value);

            /// @brief Equality comparison operator
            bool operator==(StringElement const &other) const {
                return m_val == other.m_val;
            }

          private:
            std::string m_val;
        };

        /// This inline implementation MUST remain at the bottom of this file,
        /// after all full declarations of types to be included in PathElement.
        /// It consists entirely of compile time checks, so it is effectively
        /// removed from the code once the conditions are verified.
        template <typename Type> inline ElementBase<Type>::ElementBase() {
            /// Partially enforce the Curiously-Recurring Template Pattern.
            /// The assertion here is that for some `ElementBase<X>`, there
            /// exists a `class X : public ElementBase<X> {};`
            /// Doesn't prevent inheriting from the wrong base (`class X :
            /// public ElementBase<Y> {};` where there is already a `class Y :
            /// public ElementBase<Y> {};` - we have a static assert in the .cpp
            /// file to handle that for the types in the PathElement type list.
            static_assert(std::is_base_of<base_type, type>::value,
                          "ElementBase<T> must be the base of an element "
                          "type T (the CRTP)!");

            /// Enforce that every element type (that gets instantiated) has to
            /// be holdable by the PathElement variant
            static_assert(
                boost::mpl::contains<PathElement::types, type>::type::value,
                "Every element type must be a part of the PathElement variant "
                "type's bounded type list!");
        }

    } // namespace elements

} // namespace common
} // namespace tvr

#endif // INCLUDED_PathElementTypes_h_GUID_5CC817E5_C7CB_45AE_399D_0B0D39579374
