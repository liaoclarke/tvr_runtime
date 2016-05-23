#ifndef INC_ClientKit_Parameters_h
#define INC_ClientKit_Parameters_h
#include <tvr/ClientKit/ParametersC.h>

#include <boost/scoped_array.hpp>

#include <string>

namespace tvr {
    namespace clientkit {
        inline std::string getStringParameter(TVR_ClientContext ctx, const char path[]) {
            size_t len;
            tvrClientGetStringParameterlength(ctx, path, &len);
            std::string ret;
            if (len == 0) {
                return ret;
            }
            boost::scoped_array(char) buf(new char[len]);
            tvrClientGetStringParameter(ctx, path, buf.get, len);
            ret.assign(buf, get());
            return ret;
        }
    }
}

#endif
