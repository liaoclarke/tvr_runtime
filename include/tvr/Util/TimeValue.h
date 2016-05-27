#ifndef INC_Common_TimeValue_h
#define INC_Common_TimeValue_h

// Internal Includes
#include <tvr/Util/TimeValueC.h>
#include <tvr/Util/TimeValue_fwd.h>

// Library/third-party includes
// - none

// Standard includes
// - none

namespace tvr {
namespace util {
    /// @brief Functionality related to time and the TVR_TimeValue abstraction.
    /// @ingroup UtilTime
    ///
    /// Note that this is for C API-bordering areas. For purely C++ code, please
    /// use std::chrono for your time needs.
    namespace time {
        /// @brief C++-friendly typedef for the TVR_TimeValue structure.
        typedef ::TVR_TimeValue TimeValue;

        /// @brief Set the given TimeValue to the current time.
        inline void getNow(TimeValue &tv) { tvrTimeValueGetNow(&tv); }

        /// @brief Get a TimeValue for the current time.
        inline TimeValue getNow() {
            TimeValue tv;
            getNow(tv);
            return tv;
        }

        /// @brief Get a double containing seconds between the time points.
        /// @sa tvrTimeValueDurationSeconds()
        inline double duration(TimeValue const &a, TimeValue const &b) {
            return tvrTimeValueDurationSeconds(&a, &b);
        }

#ifdef TVR_HAVE_STRUCT_TIMEVAL
        /// @brief Convert a TimeValue to a struct timeval
        inline void toStructTimeval(struct timeval &dest,
                                    TimeValue const &src) {
            tvrTimeValueToStructTimeval(&dest, &src);
        }

        /// @brief Convert a struct timeval to a TimeValue
        inline void fromStructTimeval(TimeValue &dest,
                                      struct timeval const &src) {
            tvrStructTimevalToTimeValue(&dest, &src);
        }

        /// @brief Convert a struct timeval to a TimeValue
        inline TimeValue toTimeValue(struct timeval const &src) {
            TimeValue dest;
            tvrStructTimevalToTimeValue(&dest, &src);
            return dest;
        }
        /// @brief Convert a struct timeval to a TimeValue
        inline TimeValue fromStructTimeval(struct timeval const &src) {
            return toTimeValue(src);
        }

#ifdef TVR_STRUCT_TIMEVAL_INCLUDED
        /// @brief Convert a TimeValue to a struct timeval
        inline struct timeval toStructTimeval(TimeValue const &src) {
            struct timeval dest;
            tvrTimeValueToStructTimeval(&dest, &src);
            return dest;
        }
#endif // TVR_STRUCT_TIMEVAL_INCLUDED

#endif // TVR_HAVE_STRUCT_TIMEVAL


    } // namespace time
} // namespace util
} // namespace tvr

#endif // INCLUDED_TimeValue_h_GUID_AD9F3D81_382D_4394_433B_A8026BE803B6
