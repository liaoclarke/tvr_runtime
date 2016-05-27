#ifndef INC_Common_MessageKeys_h
#define INC_Common_MessageKeys_h

// Internal Includes
#include <tvr/Util/Export.h>

// Library/third-party includes
// - none

// Standard includes
// - none

namespace tvr {
namespace util {
    /// @brief Contains methods to retrieve the constant strings identifying
    /// message or sender types.
    namespace messagekeys {
        /// @brief The sender type for system messages.
        TVR_UTIL_EXPORT const char *systemSender();
        /// @brief Return the string identifying routing data messages
        TVR_UTIL_EXPORT const char *routingData();
    } // namespace messagekeys
} // namespace util
} // namespace tvr

#endif
