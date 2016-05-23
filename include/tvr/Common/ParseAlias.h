#ifndef INC_Common_ParseAlias_h
#define INC_Common_ParseAlias_h

// Internal Includes
#include <tvr/Common/Export.h>

// Library/third-party includes
#include <json/value.h>

// Standard includes
#include <string>

namespace tvr {
namespace common {
    class ParsedAlias {
      public:
        /// @brief Constructor - performs parse and normalization of format.
        TVR_COMMON_EXPORT ParsedAlias(std::string const &src);

        /// @brief Constructor - performs normalization of format.
        ParsedAlias(Json::Value src);

        /// @brief Did the alias parse in a valid way?
        TVR_COMMON_EXPORT bool isValid() const;

        /// @brief Is this a simple (string-only, no transform) alias?
        TVR_COMMON_EXPORT bool isSimple() const;

        /// @brief Get the ultimate source/leaf of the alias
        TVR_COMMON_EXPORT std::string getLeaf() const;

        /// @brief Set the leaf of the alias: should be an absolute path.
        void setLeaf(std::string const &leaf);

        /// @brief Get the normalized, cleaned, compacted version of the alias.
        TVR_COMMON_EXPORT std::string getAlias() const;

        /// @brief Gets a copy of the normalized version of the alias as a
        /// Json::Value
        TVR_COMMON_EXPORT Json::Value getAliasValue() const;

      private:
        void m_parse(std::string const &src);
        void m_parse(Json::Value &val);
        Json::Value &m_leaf();
        Json::Value const &m_leaf() const;
        bool m_simple;
        Json::Value m_value;
    };
}
}
#endif
