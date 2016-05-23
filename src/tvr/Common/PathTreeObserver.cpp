// Internal Includes
#include <tvr/Common/PathTreeObserver.h>

// Library/third-party includes
// - none

// Standard includes
// - none

namespace tvr {
namespace common {

    void PathTreeObserver::notifyEvent(
        PathTreeEvents e, PathTreeObserver::callback_argument arg) const {
        auto it = m_handlers.find(e);
        if (end(m_handlers) != it) {
            auto &callback = (*it).second;
            if (callback) {
                callback(arg);
            }
        }
    }

    void PathTreeObserver::setEventCallback(
        PathTreeEvents e, PathTreeObserver::callback_type const &callback) {
        m_handlers[e] = callback;
    }

}
}
