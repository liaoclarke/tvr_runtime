#ifndef INC_Common_PathElementTypes_fwd_h
#define INC_Common_PathElementTypes_fwd_h

// Internal Includes
#include <tvr/Util/StdInt.h>

// Library/third-party includes
#include <boost/variant/variant_fwd.hpp>

// Standard includes
// - none

namespace tvr {
namespace common {
    typedef uint8_t AliasPriority;
    static const AliasPriority ALIASPRIORITY_MINIMUM = 0;
    static const AliasPriority ALIASPRIORITY_AUTOMATIC = 127;
    static const AliasPriority ALIASPRIORITY_SEMANTICROUTE = 128;
    static const AliasPriority ALIASPRIORITY_MANUAL = 255;
    namespace elements {
        // list is kept sorted here for convenience
        class AliasElement;
        class DeviceElement;
        class InterfaceElement;
        class NullElement;
        class PluginElement;
        class SensorElement;
        class StringElement;

/// @brief The variant type containing a particular kind of path element.
#ifndef TVR_DOXYGEN_EXTERNAL
///
/// NOTE: if you add an element type here, you must make sure it's:
///
/// - forward-declared above
/// - declared in PathElementTypes.h
/// - included in the name list in PathElementTools.cpp
///
/// Note that while most lists of these types are not order sensitive, and so
/// have been sorted, order does matter for the types in this typedef. Above
/// all, NullElement must remain first.
#endif
        typedef boost::variant<NullElement, AliasElement, SensorElement,
                               InterfaceElement, DeviceElement, PluginElement,
                               StringElement> PathElement;
    } // namespace elements

    using elements::PathElement;
}
}

#endif
