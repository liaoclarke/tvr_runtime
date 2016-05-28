#ifndef INC_ClientKit_ParametersC_h
#define INC_ClientKit_ParametersC_h
#include <tvr/ClientKit/Export.h>
#include <tvr/Util/APIBaseC.h>
#include <tvr/Util/ReturnCodesC.h>
#include <tvr/Util/AnnotationMacrosC.h>
#include <tvr/Util/ClientOpaqueTypesC.h>

#include <stddef.h>

TVR_EXTERN_C_BEGIN

TVR_CLIENTKIT_EXPORT TVR_ReturnCode
tvrClientGetStringParameterLength(TVR_ClientContext ctx, const char path[], size_t *len);

TVR_CLIENTKIT_EXPORT TVR_ReturnCode
tvrClientGetStringParameter(TVR_ClientContext ctx, const char path[], char *buf, size_t len);

TVR_CLIENTKIT_EXPORT TVR_ReturnCode
tvrClientSetStringParameter(TVR_ClientContext ctx, const char path[], const char buf[]);

TVR_EXTERN_C_END

#endif
