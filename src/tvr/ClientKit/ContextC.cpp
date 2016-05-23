#include <tvr/ClientKit/ContextC.h>
#include <tvr/Common/ClientContext.h>
#include <tvr/Client/CreateContext.h>
#include <tvr/Util/Verbosity.h>

TVR_ClientContext tvrClientInit(const char applicationIdentifier[]) {
    return tvr::client::createContext(applicationIdentifier);
}

TVR_ReturnCode tvrClientUpdate(TVR_ClientContext ctx) {
    ctx->update();
    return TVR_RETURN_SUCCESS;
}

TVR_ReturnCode tvrClientCheckStatus(TVR_ClientContext ctx) {
    if (!ctx) {
        TVR_DEV_VERBOSE("ContextC", "Client check status failure");
        return TVR_RETURN_FAILURE;
    }
    return ctx->getStatus() ? TVR_RETURN_SUCCESS : TVR_RETURN_FAILURE;
}

TVR_ReturnCode tvrClientShutdown(TVR_ClientContext ctx) {
    if (nullptr == ctx) {
        TVR_DEV_VERBOSE("ContextC", "Can't delete a null Client Context!");
        return TVR_RETURN_FAILURE;
    }
    tvr::common::deleteContext(ctx);
    return TVR_RETURN_SUCCESS;
}
