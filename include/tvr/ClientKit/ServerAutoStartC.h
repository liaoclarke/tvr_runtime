#ifndef INC_ClientKit_ServerAutoStartC_h
#define INC_ClientKit_ServerAutoStartC_h
#include <tvr/ClientKit/Export.h>
#include <tvr/Util/APIBaseC.h>

TVR_EXTERN_C_BEGIN

TVR_CLIENTKIT_EXPORT void tvrClientAttemptServerAutoStart();

TVR_CLIENTKIT_EXPORT void tvrClientReleaseAutoStartedServer();

TVR_EXTERN_C_END

#endif
