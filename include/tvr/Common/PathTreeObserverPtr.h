#ifndef INC_Common_PathTreeObserverPtr_h
#define INC_Common_PathTreeObserverPtr_h

// Internal Includes
// - none

// Library/third-party includes
#include <tvr/Util/SharedPtr.h>

// Standard includes
// - none

namespace tvr {
namespace common {
    class PathTreeObserver;
    typedef shared_ptr<PathTreeObserver> PathTreeObserverPtr;
    typedef weak_ptr<PathTreeObserver> PathTreeObserverWeakPtr;
}
}

#endif
