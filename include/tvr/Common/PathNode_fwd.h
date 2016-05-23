#ifndef INC_Common_PathNode_fwd_h
#define INC_Common_PathNode_fwd_h

// Internal Includes
#include <tvr/Common/Export.h>
#include <tvr/Common/PathElementTypes_fwd.h>
#include <tvr/Util/TreeNode_fwd.h> // IWYU pragma: export

// Library/third-party includes
// - none

// Standard includes
// - none

namespace tvr {
namespace common {
    /// @brief The specific tree node type that contains a path element.
    typedef ::tvr::util::TreeNode<PathElement> PathNode;

    /// @brief The ownership pointer of the specific tree node.
    typedef ::tvr::util::TreeNodePointer<PathElement>::type PathNodePtr;

    /// @brief The weak (non-owning) pointer used to refer to a parent tree node
    typedef PathNode *PathNodeParentPtr;

    /// @brief Gets an identifying string for the node value type.
    TVR_COMMON_EXPORT const char *getTypeName(PathNode const &node);
}
} 

#endif
