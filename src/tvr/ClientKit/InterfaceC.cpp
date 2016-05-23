#include <tvr/ClientKit/InterfaceC.h>
#include <tvr/Common/ClientInterface.h>
#include <tvr/Common/ClientContext.h>

TVR_ReturnCode tvrClientGetInterface(TVR_ClientContext ctx,
                                     const char path[],
                                     TVR_ClientInterface *iface) {
    if (nullptr == ctx) {
        return TVR_RETURN_FAILURE;
    }
    tvr::common::ClientInterfacePtr ret = ctx->getInterface(path);
    if (ret) {
        *iface = ret.get();
        return TVR_RETURN_SUCCESS;
    }
    return TVR_RETURN_FAILURE;
}

TVR_ReturnCode tvrClientFreeInterface(TVR_ClientContext ctx, TVR_ClientInterface iface) {
    if (nullptr == ctx) {
        return TVR_RETURN_FAILURE;
    }
    if (nullptr == iface) {
        return TVR_RETURN_FAILURE;
    }

    tvr::common::ClientInterfacePtr ptr(ctx->releaseInterface(iface));
    if (!ptr) {
        return TVR_RETURN_FAILURE;
    }
    return TVR_RETURN_SUCCESS;
}
