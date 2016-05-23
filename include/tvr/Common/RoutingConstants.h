#ifndef INC_Common_RoutingConstants_h
#define INC_Common_RoutingConstants_h

// Internal Includes
#include <tvr/Common/Export.h>

// Library/third-party includes
// - none

// Standard includes
// - none

namespace tvr {
namespace common {
    /// @name Constants
    /// @ingroup Routing
    /// @{
    /// @brief Gets the path separator character - a slash.
    OSVR_COMMON_EXPORT char getPathSeparatorCharacter();

    /// @brief Gets the path separator - a slash - as a null-terminated
    /// string.
    OSVR_COMMON_EXPORT const char *getPathSeparator();
    /// @}
}
}
#endif
