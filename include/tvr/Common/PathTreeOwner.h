#ifndef INC_Common_PathTreeOwner_h
#define INC_Common_PathTreeOwner_h

// Internal Includes
#include <tvr/Common/PathTreeObserverPtr.h>
#include <tvr/Common/PathTree.h>
#include <tvr/Common/Export.h>

// Library/third-party includes
#include <boost/noncopyable.hpp>
#include <json/value.h>

// Standard includes
#include <vector>

namespace tvr {
namespace common {
    /// @brief Object responsible for owning a path tree (specifically a
    /// "downstream"/client path tree), replacing its contents from
    /// JSON-serialized data, and notifying a collection of observers of such
    /// events.
    ///
    /// @sa tvr::common::PathTreeObserver
    class PathTreeOwner : private boost::noncopyable {
      public:
        PathTreeOwner() = default;

        /// non-copyable
        PathTreeOwner(PathTreeOwner const &) = delete;
        /// non-copy-assignable
        PathTreeOwner &operator=(PathTreeOwner const &) = delete;

        /// @brief reports whether the path tree has been populated (by a call
        /// to replaceTree() )
        explicit operator bool() const { return m_valid; }

        /// @brief Make an observer object that can hold callbacks for tree
        /// updates. Callbacks are called in the order their observers were
        /// created.
        ///
        /// @sa tvr::common::PathTreeObserver
        TVR_COMMON_EXPORT PathTreeObserverPtr makeObserver();

        /// @brief Replace the entirety of the path tree from the given
        /// serialized array of nodes.
        TVR_COMMON_EXPORT void replaceTree(Json::Value const &nodes);

        /// @brief Access the path tree object itself
        PathTree &get() { return m_tree; }

        /// @brief Access the path tree object itself - constant reference
        PathTree const &get() const { return m_tree; }

      private:
        PathTree m_tree;
        std::vector<PathTreeObserverWeakPtr> m_observers;
        bool m_valid = false;
    };
} // namespace common
} // namespace tvr
#endif
