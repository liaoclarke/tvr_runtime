#include <tvr/ClientKit/ParametersC.h>
#include <tvr/ClientKit/ClientContext.h>

TVR_ReturnCode tvrClientGetStringParameterLength(TVR_ClientContext ctx,
                                                 const char path[],
                                                 size_t *len) 
{
    if (ctx == nullptr) {
        return TVR_RETURN_FAILURE;
    }
    if (len == nullptr) {
        return TVR_RETURN_FAILURE;
    }
    std::string val = ctx->getStringParameter(path);
    *len = val.empty() ? 0 : (val.size() + 1);
    return TVR_RETURN_SUCCESS;
}

TVR_ReturnCode tvrClientGetStringParameter(TVR_ClientContext ctx,
                                           const char path[], char *buf, size_t len)
{
    if (ctx == nullptr) {
        return TVR_RETURN_FAILURE;
    }
    if (ctx == nullptr) {
        return TVR_RETURN_FAILURE;
    }
    std::string val = ctx->getStringParameter(path);
    if (val.size() + 1 > len) {
        return TVR_RETURN_FAILURE;
    }
    val.copy(buf, val.size());
    buf[val.size()] = '\0';
    return TVR_RETURN_SUCCESS;
}

TVR_ReturnCode tvrClientSetStringParameter(TVR_ClientContext ctx,
                                           const char path[], char *buf, size_t len)
{
    if (ctx == nullptr) {
        return TVR_RETURN_FAILURE;
    }
    if (ctx == nullptr) {
        return TVR_RETURN_FAILURE;
    }
    //std::string val = ctx->setStringParameter(path);
    //if (val.size() + 1 > len) {
    //    return TVR_RETURN_FAILURE;
    //}
    //val.copy(buf, val.size());
    //buf[val.size()] = '\0';
    return TVR_RETURN_SUCCESS;
}
