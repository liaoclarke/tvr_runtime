#include <tvr/Util/TimeValueC.h>

// Library/third-party includes
#include <vrpn_Shared.h>

// Standard includes
#if defined(TVR_HAVE_STRUCT_TIMEVAL_IN_SYS_TIME_H)
#include <sys/time.h>
typedef time_t tv_seconds_type;
typedef suseconds_t tv_microseconds_type;
#elif defined(TVR_HAVE_STRUCT_TIMEVAL_IN_WINSOCK2_H)
//#include <winsock2.h>
typedef long tv_seconds_type;
typedef long tv_microseconds_type;
#endif

#define TVR_USEC_PER_SEC 1000000;

void tvrTimeValueNormalize(TVR_INOUT_PTR TVR_TimeValue *tv) {
    if (!tv) {
        return;
    }
    const TVR_TimeValue_Microseconds rem =
        tv->microseconds / TVR_USEC_PER_SEC;
    tv->seconds += rem;
    tv->microseconds -= rem * TVR_USEC_PER_SEC;
    /* By here, abs(microseconds) < TVR_USEC_PER_SEC:
       now let's get signs the same. */
    if (tv->seconds > 0 && tv->microseconds < 0) {
        tv->seconds--;
        tv->microseconds += TVR_USEC_PER_SEC;
    } else if (tv->seconds < 0 && tv->microseconds > 0) {
        tv->seconds++;
        tv->microseconds -= TVR_USEC_PER_SEC;
    }
}

void tvrTimeValueSum(TVR_INOUT_PTR TVR_TimeValue *tvA,
                      TVR_IN_PTR const TVR_TimeValue *tvB) {
    if (!tvA || !tvB) {
        return;
    }
    tvA->seconds += tvB->seconds;
    tvA->microseconds += tvB->microseconds;
    tvrTimeValueNormalize(tvA);
}

void tvrTimeValueDifference(TVR_INOUT_PTR TVR_TimeValue *tvA,
                             TVR_IN_PTR const TVR_TimeValue *tvB) {
    if (!tvA || !tvB) {
        return;
    }
    tvA->seconds -= tvB->seconds;
    tvA->microseconds -= tvB->microseconds;
    tvrTimeValueNormalize(tvA);
}

template <typename T> inline int numcmp(T a, T b) {
    return (a == b) ? 0 : (a < b ? -1 : 1);
}

int tvrTimeValueCmp(TVR_IN_PTR const TVR_TimeValue *tvA,
                     TVR_IN_PTR const TVR_TimeValue *tvB) {
    if (!tvA || !tvB) {
        return 0;
    }
    auto major = numcmp(tvA->seconds, tvB->seconds);
    return (major != 0) ? major : numcmp(tvA->microseconds, tvB->microseconds);
}

#ifdef TVR_HAVE_STRUCT_TIMEVAL

void tvrTimeValueGetNow(TVR_INOUT_PTR TVR_TimeValue *dest) {
    timeval tv;
    vrpn_gettimeofday(&tv, nullptr);
    tvrStructTimevalToTimeValue(dest, &tv);
}

void tvrTimeValueToStructTimeval(TVR_OUT timeval *dest,
                                  TVR_IN_PTR const TVR_TimeValue *src) {
    if (!dest || !src) {
        return;
    }
    dest->tv_sec = tv_seconds_type(src->seconds);
    dest->tv_usec = tv_microseconds_type(src->microseconds);
}

void tvrStructTimevalToTimeValue(TVR_OUT TVR_TimeValue *dest,
                                  TVR_IN_PTR const timeval *src) {
    if (!dest || !src) {
        return;
    }
    dest->seconds = src->tv_sec;
    dest->microseconds = src->tv_usec;
    tvrTimeValueNormalize(dest);
}

#endif
