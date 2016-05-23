#ifndef INC_Common_PathElementSerialization_h
#define INC_Common_PathElementSerialization_h

// Internal Includes
#include <tvr/Common/PathElementTypes.h>
#include <tvr/Common/PathElementTools.h>
#include <tvr/Common/PathElementSerializationDescriptions.h>

// Library/third-party includes
#include <json/value.h>
#include <json/reader.h>
#include <boost/variant.hpp>
#include <boost/mpl/for_each.hpp>
#include <boost/noncopyable.hpp>

// Standard includes
#include <type_traits>
#include <stdexcept>

namespace tvr {
namespace common {
    namespace {
        /// @brief Functor for use with PathElementSerializationHandler, for the
        /// direction PathElement->JSON
        class PathElementToJSONFunctor : boost::noncopyable {
          public:
            PathElementToJSONFunctor(Json::Value &val) : m_val(val) {}

            template <typename T>
            void operator()(const char name[], T const &data, ...) {
                m_val[name] = data;
            }

          private:
            Json::Value &m_val;
        };

        /// @brief Functor for use with a serializationDescription overload, for
        /// the direction JSON->PathElement
        class PathElementFromJsonFunctor : boost::noncopyable {
          public:
            PathElementFromJsonFunctor(Json::Value const &val) : m_val(val) {}

            /// @brief Deserialize a string
            void operator()(const char name[], std::string &dataRef) {
                m_requireName(name);
                dataRef = m_val[name].asString();
            }
            /// @brief Deserialize a bool
            void operator()(const char name[], bool &dataRef) {
                m_requireName(name);
                dataRef = m_val[name].asBool();
            }
            /// @brief Deserialize a bool with default
            void operator()(const char name[], bool &dataRef, bool defaultVal) {
                if (m_hasName(name)) {
                    dataRef = m_val[name].asBool();
                } else {
                    dataRef = defaultVal;
                }
            }

            /// @brief Deserialize a Json::Value from either nested JSON or a
            /// JSON string
            void operator()(const char name[], Json::Value &dataRef) {
                m_requireName(name);
                if (m_val[name].isString()) {
                    Json::Reader reader;
                    Json::Value val;
                    if (reader.parse(m_val[name].asString(), val)) {
                        dataRef = val;
                    }
                } else {
                    dataRef = m_val[name];
                }
            }

            /// @brief Deserialize a uint8_t (e.g. AliasPriority)
            void operator()(const char name[], uint8_t &dataRef) {
                m_requireName(name);
                dataRef = static_cast<uint8_t>(m_val[name].asInt());
            }

            /// @brief Deserialize a uint8_t (e.g. AliasPriority) with default
            void operator()(const char name[], uint8_t &dataRef,
                            uint8_t defaultVal) {
                if (m_hasName(name)) {
                    dataRef = static_cast<uint8_t>(m_val[name].asInt());
                } else {
                    dataRef = defaultVal;
                }
            }

            /// @todo add more methods here if other data types are stored
          private:
            void m_requireName(const char name[]) {
                if (!m_hasName(name)) {
                    throw std::runtime_error(
                        "Missing JSON object member named " +
                        std::string(name));
                }
            }
            bool m_hasName(const char name[]) { return m_val.isMember(name); }
            Json::Value const &m_val;
        };

        /// @brief Functor for use with the PathElement's type list and
        /// mpl::for_each, to convert from type name string to actual type and
        /// load the data.
        class DeserializeElementFunctor {
          public:
            DeserializeElementFunctor(Json::Value const &val,
                                      elements::PathElement &elt)
                : m_val(val), m_typename(val["type"].asString()), m_elt(elt) {}

            /// @brief Don't try to generate an assignment operator.
            DeserializeElementFunctor &
            operator=(const DeserializeElementFunctor &) = delete;

            template <typename T> void operator()(T const &) {
                if (elements::getTypeName<T>() == m_typename) {
                    T value;
                    PathElementFromJsonFunctor functor(m_val);
                    serializationDescription(functor, value);
                    m_elt = value;
                }
            }

          private:
            Json::Value const &m_val;
            std::string const m_typename;
            elements::PathElement &m_elt;
        };
    } // namespace

    /// @brief Returns a JSON object with any element-type-specific data for the
    /// given PathElement-holdable type
    template <typename T>
    inline Json::Value pathElementToJson(T const &element) {
        Json::Value ret{Json::objectValue};
        PathElementToJSONFunctor f(ret);
        serializationDescription(f, element);
        return ret;
    }

    inline elements::PathElement jsonToPathElement(Json::Value const &json) {
        elements::PathElement elt;
        DeserializeElementFunctor functor{json, elt};
        boost::mpl::for_each<elements::PathElement::types>(functor);
        return elt;
    }

}
}

#endif
