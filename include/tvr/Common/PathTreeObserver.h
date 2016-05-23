#ifndef INC_Common_PathTreeObserver_h
#define INC_Common_PathTreeObserver_h

// Internal Includes
#include <tvr/Common/PathTree_fwd.h>
#include <tvr/Common/PathTreeObserverPtr.h>
#include <tvr/Common/Export.h>

// Library/third-party includes
#include <boost/noncopyable.hpp>

// Standard includes
#include <map>
#include <functional>

namespace tvr {
namespace common {
    class PathTreeOwner;
    enum class PathTreeEvents : std::size_t { AboutToUpdate, AfterUpdate };
    class PathTreeObserver : public boost::noncopyable {
      public:
        using callback_argument = PathTree &;
        void notifyEvent(PathTreeEvents e, callback_argument arg) const;

        using callback_type = std::function<void(callback_argument)>;
        TVR_COMMON_EXPORT void setEventCallback(PathTreeEvents e,
                                                 callback_type const &callback);

      protected:
        PathTreeObserver() = default;

      private:
        std::map<PathTreeEvents, callback_type> m_handlers;
    };
}
}
#endif
