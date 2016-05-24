#ifndef INC_Util_ReturnCodesC_h
#define INC_Util_ReturnCodesC_h
#include <tvr/Util/APIBaseC.h>
#include <tvr/Util/AnnotationMacrosC.h>
TVR_EXTERN_C_BEGIN

typedef TVR_RETURN_SUCCESS_CONDITION(
    return == TVR_RETURN_SUCCESS) char TVR_ReturnCode;

#define TVR_RETURN_SUCCESS (0)
#define TVR_RETURN_FAILURE (1)

TVR_EXTERN_C_END
#endif
