#include <tvr/ClientKit/ParametersC.h>
#include <tvr/Common/ClientContext.h>
#include <tvr/Common/PathTree.h>
#include <tvr/Common/PathElementTypes.h>
#include <tvr/Common/PathNode.h>
#include <tvr/Common/AliasProcessor.h>
#include <tvr/Common/ParseAlias.h>
#include <tvr/Common/JSONHelpers.h>
#include <tvr/Common/GetJSONStringFromTree.h>
#include <tvr/Common/PathTreeSerialization.h>
#include <tvr/Common/PathElementSerialization.h>
#include <tvr/Common/PathTreeFull.h>
#include <tvr/Common/PathElementTools.h>
#include <tvr/Common/ApplyPathNodeVisitor.h>

#include <boost/program_options.hpp>
#include <boost/thread/thread.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/variant/get.hpp>
#include <boost/optional.hpp>
#include <json/value.h>
#include <json/reader.h>

#include <iostream>
#include <exception>

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
    std::string val = ctx->getStringParameter(path);
    if (val.size() + 1 > len) {
        return TVR_RETURN_FAILURE;
    }
    val.copy(buf, val.size());
    buf[val.size()] = '\0';
    return TVR_RETURN_SUCCESS;
}

TVR_ReturnCode tvrClientSetStringParameter(TVR_ClientContext ctx,
                                           const char path[], const char buf[])
{
    if (ctx == nullptr) {
        return TVR_RETURN_FAILURE;
    }
    int ret = -1;
    std::string path_str = path; 
    std::string buf_str = buf;
    if (path_str.compare(0, 8, "/account") == 0) { 
        //auto newElement = tvr::common::elements::StringElement{buf_str};
        //auto node = (ctx->getPathTree()).getNodeByPath("/account");
        //node.value() = newElement;
        //auto value = tvr::common::pathElementToJson(newElement);
        //str.erase(std::remove(str.begin(), str.end(), '\n'), str.end());
		ctx->sendData(buf_str);
    } else if (path_str.compare(0, sizeof("/display"), "/display")) {
        //int ret =  ctx->setStringParameter(path, data);
    } else if (path_str.compare(0, sizeof("/rendermanager"), "/rendermanager")) {
        //int ret =  ctx->setStringParameter(path, data);
    }
    return TVR_RETURN_SUCCESS;
}
