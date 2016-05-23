#ifndef INC_Util_APIBaseC_h
#define INC_Util_APIBaseC_h

#ifdef __cplusplus
#define TVR_C_ONLY(X)
#define TVR_CPP_ONLY(X) X
#define TVR_EXTERN_C_BEGIN extern "C" {
#define TVR_EXTERN_C_END }
#define TVR_INLINE inline
#else
#define TVR_C_ONLY(X) X
#define TVR_CPP_ONLY(X)
#define TVR_EXTERN_C_BEGIN
#define TVR_EXTERN_C_END
#ifdef _MSC_VER
#define TVR_INLINE static __inline
#else
#define TVR_INLINE static inline
#endif
#endif

#endif
