// Internal Includes
#include <tvr/Common/PathTreeOwner.h>
#include <tvr/Common/PathTreeObserver.h>
#include <tvr/Common/PathTreeSerialization.h>

// Library/third-party includes
// - none

// Standard includes
#include <algorithm>
#include <iterator>

namespace tvr {
namespace common {
    namespace {
        /// @brief Class for the sole purpose of being able to use
        /// make_shared with PathTreeObserver.
        class PathTreeObserverConcrete : public PathTreeObserver {
          public:
            PathTreeObserverConcrete() = default;
        };
    } // namespace

    /// Given a container of weak ptrs to some type and a functor that operates
    /// on references to that type, go through all elements of the container in
    /// a single pass, calling the functor on those elements still valid, and
    /// removing those invalid ones. (Uses member function resize with two
    /// iterators)
    template <typename T, typename F>
    inline void for_each_cleanup_pointers(T &c, F &&f) {
        using weak_ptr_type = typename T::value_type;
        auto newEnd =
            std::remove_if(begin(c), end(c), [&](weak_ptr_type const &ptr) {
                auto fullPtr = ptr.lock();
                if (fullPtr) {
                    f(*fullPtr);
                    return false; // don't remove this one
                }
                return true; // this one we couldn't lock - expired observer.
            });
        c.erase(newEnd, end(c));
    }

    PathTreeObserverPtr PathTreeOwner::makeObserver() {
        auto ret = PathTreeObserverPtr{make_shared<PathTreeObserverConcrete>()};
        m_observers.push_back(ret);
        return ret;
    }

    void PathTreeOwner::replaceTree(Json::Value const &nodes) {
        for_each_cleanup_pointers(
            m_observers, [&](PathTreeObserver const &observer) {
                observer.notifyEvent(PathTreeEvents::AboutToUpdate, m_tree);
            });

        m_tree.reset();

        common::jsonToPathTree(m_tree, nodes);

        m_valid = true;

        for_each_cleanup_pointers(
            m_observers, [&](PathTreeObserver const &observer) {
                observer.notifyEvent(PathTreeEvents::AfterUpdate, m_tree);
            });
    }
}
}
