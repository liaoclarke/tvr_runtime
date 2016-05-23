// Internal Includes
#include <tvr/Common/RoutingConstants.h>

// Library/third-party includes
// - none

// Standard includes
// - none

namespace tvr {
namespace common {
    char getPathSeparatorCharacter() { return getPathSeparator()[0]; }

    const char *getPathSeparator() { return "/"; }
}
}
