#ifndef INC_PathElementTools_h
#define INC_PathElementTools_h

// Internal Includes
#include <tvr/Common/Export.h>
#include <tvr/Common/PathElementTypes.h>

// Library/third-party includes
// - none

// Standard includes
#include <stddef.h>

namespace tvr {
namespace common {

#ifndef tVR_DOXYGEN_EXTERNAL
    namespace detail {
        struct AliasPriorityWrapper {
            AliasPriority priority;
        };
        template <typename T>
        T &&operator<<(T &&os, AliasPriorityWrapper const &wrapper) {
            switch (wrapper.priority) {
            case ALIASPRIORITY_MINIMUM:
                os << "Minimum (" << int(ALIASPRIORITY_MINIMUM) << ")";
                break;

            case ALIASPRIORITY_AUTOMATIC:
                os << "Automatic (" << int(ALIASPRIORITY_AUTOMATIC) << ")";
                break;
            case ALIASPRIORITY_SEMANTICROUTE:
                os << "Semantic Route (" << int(ALIASPRIORITY_SEMANTICROUTE)
                   << ")";
                break;
            case ALIASPRIORITY_MANUAL:
                os << "Manual/Max (" << int(ALIASPRIORITY_MANUAL) << ")";
                break;
            default:
                os << int(ALIASPRIORITY_MANUAL);
                break;
            }
            return os;
        }
    } // namespace detail
#endif

    /// @brief Helper method to output a priority in a formatted way to a
    /// stream.
    inline detail::AliasPriorityWrapper outputPriority(AliasPriority priority) {
        return detail::AliasPriorityWrapper{priority};
    }

    namespace elements {
        /// @brief Gets a string that indicates the type of path element. Do not
        /// use this for conditionals/comparisons unless there's really no
        /// better way! (There probably is a better way with a variant
        /// static_visitor)
        /// @param elt The element to investigate.
        TVR_COMMON_EXPORT const char *getTypeName(PathElement const &elt);

        /// @brief Gets the string that represents the templated type
        template <typename ElementType> inline const char *getTypeName() {
            return getTypeName(ElementType());
        }

        /// @brief If dest is a NullElement, replace it with the provided src
        /// element.
        /// @param dest Item to inquire about, and update if needed.
        /// @param src Replacement for dest if dest is a NullElement.
        void ifNullReplaceWith(PathElement &dest, PathElement const &src);

        /// @brief Returns true if the path element provided is a NullElement.
        bool isNull(PathElement const &elt);

        /// @brief Gets the length of the longest type name
        TVR_COMMON_EXPORT size_t getMaxTypeNameLength();
    } // namespace elements
    using elements::getTypeName;
} // namespace common
} // namespace tvr
#endif
