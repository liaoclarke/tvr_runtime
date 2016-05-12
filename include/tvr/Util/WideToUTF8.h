#ifndef INC_Util_WideToUTF8_h
#define INC_Util_WideToUTF8_h

#define WIN32_LEAN_AND_MEAN
#include <tchar.h>

#include <boost/locale/encoding_utf.hpp>

#include <string>
#include <type_traits>

namespace tvr {
    namespace util {
        template <typename T> inline std::string wideToUTF8String(T input) {
            return boost::locale::conv::utf_to_utf<char>(input);
        }
    //#ifdef _UNICODE
    //    inline std::string tcharToUTF8String(TCHAR buf[]) {
    //        static_assert(std::is_same<TCHAR, wchar_t>::value, "This code path relies on TCHAR being a wchar_t!");
    //        return wideToUTF8String(buf);
    //    }
    //#else  // !_UNICODE
        inline std::string tcharToUTF8String(TCHAR buf[]) {
            static_assert(std::is_same<TCHAR, char>::value, "This code path relies on TCHAR being a single byte!");
            return std::string(buf);
        }
//#endif // _UNICODE
    }
}
#endif
