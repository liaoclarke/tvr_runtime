#ifndef INC_Common_TimeValueC_h
#define INC_Common_TimeValueC_h

/* Internal Includes */
#include <tvr/Util/Export.h>
#include <tvr/Util/APIBaseC.h>
#include <tvr/Util/AnnotationMacrosC.h>
#include <tvr/Util/PlatformConfig.h>
#include <tvr/Util/StdInt.h>
#include <tvr/Util/BoolC.h>

/* Library/third-party includes */
/* none */

/* Standard includes */
/* none */

TVR_EXTERN_C_BEGIN

/** @defgroup UtilTime Timestamp interaction
    @ingroup Util

    This provides a level of interoperability with struct timeval on systems
    with that facility. It provides a neutral representation with sufficiently
    large types.

    For C++ code, use of std::chrono or boost::chrono instead is recommended.

    Note that these time values may not necessarily correlate between processes
   so should not be used to estimate or measure latency, etc.

    @{
*/

/** @brief The signed integer type storing the seconds in a struct
    TVR_TimeValue */
typedef int64_t TVR_TimeValue_Seconds;
/** @brief The signed integer type storing the microseconds in a struct
    TVR_TimeValue */
typedef int32_t TVR_TimeValue_Microseconds;

/** @brief Standardized, portable parallel to struct timeval for representing
   both absolute times and time intervals.

   Where interpreted as an absolute time, its meaning is to be considered the
   same as that of the POSIX struct timeval:
   time since 00:00 Coordinated Universal Time (UTC), January 1, 1970.

   For best results, please keep normalized. Output of all functions here
   is normalized.
   */
typedef struct TVR_TimeValue {
    /** @brief Seconds portion of the time value. */
    TVR_TimeValue_Seconds seconds;
    /** @brief Microseconds portion of the time value. */
    TVR_TimeValue_Microseconds microseconds;
} TVR_TimeValue;

#ifdef TVR_HAVE_STRUCT_TIMEVAL
/** @brief Gets the current time in the TimeValue. Parallel to gettimeofday. */
TVR_UTIL_EXPORT void tvrTimeValueGetNow(TVR_OUT TVR_TimeValue *dest)
    TVR_FUNC_NONNULL((1));

struct timeval; /* forward declaration */

/** @brief Converts from a TimeValue struct to your system's struct timeval.

    @param dest Pointer to an empty struct timeval for your platform.
    @param src A pointer to an TVR_TimeValue you'd like to convert from.

    If either parameter is NULL, the function will return without doing
   anything.
*/
TVR_UTIL_EXPORT void
tvrTimeValueToStructTimeval(TVR_OUT struct timeval *dest,
                             TVR_IN_PTR const TVR_TimeValue *src)
    TVR_FUNC_NONNULL((1, 2));

/** @brief Converts from a TimeValue struct to your system's struct timeval.
    @param dest An TVR_TimeValue destination pointer.
    @param src Pointer to a struct timeval you'd like to convert from.

    The result is normalized.

    If either parameter is NULL, the function will return without doing
   anything.
*/
TVR_UTIL_EXPORT void
tvrStructTimevalToTimeValue(TVR_OUT TVR_TimeValue *dest,
                             TVR_IN_PTR const struct timeval *src)
    TVR_FUNC_NONNULL((1, 2));
#endif

/** @brief "Normalizes" a time value so that the absolute number of microseconds
    is less than 1,000,000, and that the sign of both components is the same.

    @param tv Address of a struct TimeValue to normalize in place.

    If the given pointer is NULL, this function returns without doing anything.
*/
TVR_UTIL_EXPORT void tvrTimeValueNormalize(TVR_INOUT_PTR TVR_TimeValue *tv)
    TVR_FUNC_NONNULL((1));

/** @brief Sums two time values, replacing the first with the result.

    @param tvA Destination and first source.
    @param tvB second source

    If a given pointer is NULL, this function returns without doing anything.

    Both parameters are expected to be in normalized form.
*/
TVR_UTIL_EXPORT void tvrTimeValueSum(TVR_INOUT_PTR TVR_TimeValue *tvA,
                                       TVR_IN_PTR const TVR_TimeValue *tvB)
    TVR_FUNC_NONNULL((1, 2));

/** @brief Computes the difference between two time values, replacing the first
    with the result.

    Effectively, `*tvA = *tvA - *tvB`

    @param tvA Destination and first source.
    @param tvB second source

    If a given pointer is NULL, this function returns without doing anything.

    Both parameters are expected to be in normalized form.
*/
TVR_UTIL_EXPORT void
tvrTimeValueDifference(TVR_INOUT_PTR TVR_TimeValue *tvA,
                        TVR_IN_PTR const TVR_TimeValue *tvB)
    TVR_FUNC_NONNULL((1, 2));

/** @brief  Compares two time values (assumed to be normalized), returning
    the same values as strcmp

    @return <0 if A is earlier than B, 0 if they are the same, and >0 if A
    is later than B.
*/
TVR_UTIL_EXPORT int tvrTimeValueCmp(TVR_IN_PTR const TVR_TimeValue *tvA,
                                      TVR_IN_PTR const TVR_TimeValue *tvB)
    TVR_FUNC_NONNULL((1, 2));

TVR_EXTERN_C_END

/** @brief Compute the difference between the two time values, returning the
    duration as a double-precision floating-point number of seconds.

    Effectively, `ret = *tvA - *tvB`

    @param tvA first source.
    @param tvB second source
    @return Duration of timespan in seconds (floating-point)
*/
TVR_INLINE double
tvrTimeValueDurationSeconds(TVR_IN_PTR const TVR_TimeValue *tvA,
                             TVR_IN_PTR const TVR_TimeValue *tvB) {
    TVR_TimeValue A = *tvA;
    tvrTimeValueDifference(&A, tvB);
    double dt = A.seconds + A.microseconds / 1000000.0;
    return dt;
}

/** @brief True if A is later than B */
TVR_INLINE TVR_CBool
tvrTimeValueGreater(TVR_IN_PTR const TVR_TimeValue *tvA,
                     TVR_IN_PTR const TVR_TimeValue *tvB) {
    if (!tvA || !tvB) {
        return TVR_FALSE;
    }
    return ((tvA->seconds > tvB->seconds) ||
            (tvA->seconds == tvB->seconds &&
             tvA->microseconds > tvB->microseconds))
               ? TVR_TRUE
               : TVR_FALSE;
}

#ifdef __cplusplus

#include <cmath>
#include <cassert>

/// Returns true if the time value is normalized. Typically used in assertions.
inline bool tvrTimeValueIsNormalized(const TVR_TimeValue &tv) {
#ifdef __APPLE__
    // apparently standard library used on mac only has floating-point abs?
    return std::abs(double(tv.microseconds)) < 1000000 &&
#else
    return std::abs(tv.microseconds) < 1000000 &&
#endif
           ((tv.seconds > 0) == (tv.microseconds > 0));
}

/// True if A is later than B
inline bool tvrTimeValueGreater(const TVR_TimeValue &tvA,
                                 const TVR_TimeValue &tvB) {
    assert(tvrTimeValueIsNormalized(tvA) &&
           "First timevalue argument to comparison was not normalized!");
    assert(tvrTimeValueIsNormalized(tvB) &&
           "Second timevalue argument to comparison was not normalized!");
    return (tvA.seconds > tvB.seconds) ||
           (tvA.seconds == tvB.seconds && tvA.microseconds > tvB.microseconds);
}

/// Operator > overload for time values
inline bool operator>(const TVR_TimeValue &tvA, const TVR_TimeValue &tvB) {
    return tvrTimeValueGreater(tvA, tvB);
}

/// Operator < overload for time values
inline bool operator<(const TVR_TimeValue &tvA, const TVR_TimeValue &tvB) {
    // Change the order of arguments before forwarding.
    return tvrTimeValueGreater(tvB, tvA);
}

/// Operator == overload for time values
inline bool operator==(const TVR_TimeValue &tvA, const TVR_TimeValue &tvB) {
    assert(
        tvrTimeValueIsNormalized(tvA) &&
        "First timevalue argument to equality comparison was not normalized!");
    assert(
        tvrTimeValueIsNormalized(tvB) &&
        "Second timevalue argument to equality comparison was not normalized!");
    return (tvA.seconds == tvB.seconds) &&
           (tvA.microseconds == tvB.microseconds);
}
/// Operator == overload for time values
inline bool operator!=(const TVR_TimeValue &tvA, const TVR_TimeValue &tvB) {
    assert(tvrTimeValueIsNormalized(tvA) && "First timevalue argument to "
                                             "inequality comparison was not "
                                             "normalized!");
    assert(tvrTimeValueIsNormalized(tvB) && "Second timevalue argument to "
                                             "inequality comparison was not "
                                             "normalized!");
    return (tvA.seconds != tvB.seconds) ||
           (tvA.microseconds != tvB.microseconds);
}
#endif

#endif
