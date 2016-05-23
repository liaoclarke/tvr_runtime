#ifndef INC_Util_TreeNode_fwd_h
#define INC_Util_TreeNode_fwd_h

// Internal Includes
#include <tvr/Util/SharedPtr.h>

// Library/third-party includes
// - none

// Standard includes
// - none

namespace tvr {
namespace util {
    namespace tree {
        template <typename ValueType> class TreeNode;

        /// @brief Dummy struct containing the ownership pointer type for a
        /// TreeNode. (Actually a metafunction...)
        template <typename ValueType> struct TreeNodePointer {
            /// @brief Tree node pointer type (metafunction result type)
            typedef shared_ptr<TreeNode<ValueType> > type;
        };
    } // namespace tree
    using tree::TreeNode;
    using tree::TreeNodePointer;
}
}

#endif
