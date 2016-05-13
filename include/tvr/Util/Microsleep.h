#ifndef INC_Util_Microsleep_h
#define INC_Util_Microsleep_h
#include <boost/thread/thread.hpp>

namespace tvr {
    namespace util {
        namespace time {
            inline void microsleep(uint64_t microseconds) {
                boost::this_thread::sleep(boost::posix_time::microseconds(microseconds));
            }
        }
    }
}
#endif
