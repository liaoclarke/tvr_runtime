#ifndef INC_Common_JSONHelpers_h
#define INC_Common_JSONHelpers_h

// Internal Includes
// - none

// Library/third-party includes
#include <json/value.h>
#include <json/reader.h>
#include <json/writer.h>

// Standard includes
#include <string>

namespace tvr {
namespace common {
    /// @brief Parses a string as JSON, returning a null value if parsing fails.
    inline Json::Value jsonParse(std::string const &str) {
        Json::Reader reader;
        Json::Value val = Json::nullValue;
        if (!reader.parse(str, val)) {
            // in case the failed parse modified the value somehow
            val = Json::nullValue;
        }
        return val;
    }

    /// @brief Turns the JSON value into a compact string representation.
    inline std::string jsonToCompactString(Json::Value const& val) {
        Json::FastWriter writer;
        return writer.write(val);
    }

    /// @brief Turns the JSON value into a pretty-printed, human-targeted string
    /// representation.
    inline std::string jsonToStyledString(Json::Value const& val) {
        return val.toStyledString();
    }

} // namespace common
} // namespace tvr

#endif
