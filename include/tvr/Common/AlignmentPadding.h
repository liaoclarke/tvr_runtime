#ifndef INC_Common_AlignmentPadding_h
#define INC_Common_AlignmentPadding_h

// Internal Includes
// - none

// Library/third-party includes
// - none

// Standard includes
#include <stddef.h>

namespace tvr {
namespace common {
    /// @brief Given an alignment in bytes, and a current size of a buffer,
    /// return the number of bytes of padding required to align the next field
    /// to be added to the buffer at the desired alignment within that buffer.
    ///
    /// That is, return some padding such that (currentSize + padding) %
    /// alignment == 0 for alignment > 1.
    ///
    /// @param alignment Alignment in bytes: both 0 and 1 are accepted to mean
    /// "no alignment"
    /// @param currentSize Current number of bytes in a buffer
    inline size_t computeAlignmentPadding(size_t alignment,
                                          size_t currentSize) {
        size_t ret = 0;
        if (2 > alignment) {
            /// No alignment requested
            return ret;
        }
        auto leftover = currentSize % alignment;
        if (leftover == 0) {
            /// Buffer is already aligned
            return ret;
        }
        /// Buffer needs some padding
        ret = alignment - leftover;
        return ret;
    }
} // namespace common
} // namespace tvr

#endif
