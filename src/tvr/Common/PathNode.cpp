// Internal Includes
#include <tvr/Common/PathNode.h>
#include <tvr/Common/RoutingConstants.h>
#include <tvr/Common/PathElementTools.h>
#include <tvr/Util/TreeNodeFullPath.h>

// Library/third-party includes
// - none

// Standard includes
#include <sstream>

namespace tvr {
namespace common {
    const char *getTypeName(PathNode const &node) {
        return elements::getTypeName(node.value());
    }
    std::string getFullPath(PathNode const &node) {
        return util::getTreeNodeFullPath(node, getPathSeparator());
    }
}
}
