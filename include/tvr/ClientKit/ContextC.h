#ifndef INC_ClientKit_ContextC_h
#define INC_ClientKit_ContextC_h
#include <tvr/ClientKit/Export.h>
#include <tvr/Util/APIBaseC.h>
#include <tvr/Util/ReturnCodesC.h>
#include <tvr/Util/ClientOpaqueTypesC.h>
#include <tvr/Util/StdInt.h>
TVR_EXTERN_C_BEGIN

TVR_CLIENTKIT_EXPORT TVR_ClientContext tvrClientInit(const char applicationIdentifier[]);
TVR_CLIENTKIT_EXPORT TVR_ReturnCode tvrClientUpdate(TVR_ClientContext ctx);
TVR_CLIENTKIT_EXPORT TVR_ReturnCode tvrClientCheckStatus(TVR_ClientContext ctx);
TVR_CLIENTKIT_EXPORT TVR_ReturnCode tvrClientShutdown(TVR_ClientContext ctx);

TVR_EXTERN_C_END
#endif
