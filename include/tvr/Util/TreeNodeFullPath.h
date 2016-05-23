#ifndef INC_Util_TreeNodeFullPath_h
#define INC_Util_TreeNodeFullPath_h

// Internal Includes
#include <tvr/Util/TreeNode.h>

// Library/third-party includes
// - none

// Standard includes
#include <sstream>

namespace tvr {
namespace util {
    namespace tree {
        template <typename T>
        inline void buildPathRecursively(util::TreeNode<T> const &node,
                                         const char pathSeparator[],
                                         std::ostream &os) {
            auto parent = node.getParent();
            if (parent) {
                buildPathRecursively(*parent, pathSeparator, os);
            }
            if (!node.isRoot()) {
                os << pathSeparator << node.getName();
            }
        }

        /// @brief Given a tree node and a path separator, get the full path
        /// identifying that tree node.
        template <typename T>
        inline std::string getTreeNodeFullPath(util::TreeNode<T> const &node,
                                               const char pathSeparator[]) {
            /// Special case the root
            if (node.isRoot()) {
                return std::string(pathSeparator);
            }
            std::ostringstream os;
            buildPathRecursively(node, pathSeparator, os);
            return os.str();
        }
    } // namespace tree
    using tree::getTreeNodeFullPath;
}
}

#endif
