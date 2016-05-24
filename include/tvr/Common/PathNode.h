#ifndef INC_Common_PathNode_h
#define INC_Common_PathNode_h

// Internal Includes
#include <tvr/Common/Export.h>
#include <tvr/Common/PathNode_fwd.h>
#include <tvr/Common/PathElementTypes.h> ///< @todo can we split out this include? I don't think all consumers of this header need it.
#include <tvr/Util/TreeNode.h>

// Library/third-party includes
// - none

// Standard includes
#include <string>

namespace tvr {
namespace common {
    /// @brief Gets the absolute path for the given node.
    ///
    /// @ingroup Routing
    TVR_COMMON_EXPORT std::string getFullPath(PathNode const &node);
} 
} 

#endif
