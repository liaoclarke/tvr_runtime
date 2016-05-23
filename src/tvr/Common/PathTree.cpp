// Internal Includes
#include <tvr/Common/PathTree.h>
#include <tvr/Common/PathNode.h>
#include <tvr/Common/PathElementTools.h>
#include <tvr/Common/RouteContainer.h>
#include <tvr/Common/ParseAlias.h>
#include <tvr/Common/RoutingConstants.h>
#include <tvr/Common/PathTreeSerialization.h>
#include <tvr/Util/Verbosity.h>
#include <tvr/Common/JSONHelpers.h>
#include <tvr/Common/AliasProcessor.h>
#include <tvr/Common/PathParseAndRetrieve.h>

// Library/third-party includes
#include <boost/variant/get.hpp>

// Standard includes
// - none

namespace tvr {
namespace common {
    PathTree::PathTree() : m_root(PathNode::createRoot()) {}
    PathNode &PathTree::getNodeByPath(std::string const &path) {
        return pathParseAndRetrieve(*m_root, path);
    }
    PathNode &
    PathTree::getNodeByPath(std::string const &path,
                            PathElement const &finalComponentDefault) {
        auto &ret = pathParseAndRetrieve(*m_root, path);

        // Handle null elements as final component.
        elements::ifNullReplaceWith(ret.value(), finalComponentDefault);
        return ret;
    }

    PathNode const &PathTree::getNodeByPath(std::string const &path) const {
        return pathParseAndRetrieve(const_cast<PathNode const &>(*m_root),
                                    path);
    }

    void PathTree::reset() { m_root = PathNode::createRoot(); }

    /// @brief Determine if the node needs updating given that we want to add an
    /// alias there pointing to source with the given automatic status.
    static inline bool aliasNeedsUpdate(PathNode &node,
                                        std::string const &source,
                                        AliasPriority priority) {
        elements::AliasElement *elt =
            boost::get<elements::AliasElement>(&node.value());
        if (nullptr == elt) {
            /// Always replace non-aliases
            return true;
        }
        if (priority > elt->priority()) {
            /// We're a higher-priority (manual vs automatic for instance), so
            /// override
            return true;
        }
        if (priority == elt->priority() && source != elt->getSource()) {
            /// Same automatic status, different source: replace/update
            return true;
        }
        return false;
    }

    static inline bool addAliasImpl(PathNode &node, std::string const &source,
                                    AliasPriority priority) {

        if (!aliasNeedsUpdate(node, source, priority)) {
            return false;
        }
        elements::AliasElement elt;
        elt.setSource(source);
        elt.priority() = priority;
        node.value() = elt;
        return true;
    }

    bool addAlias(PathNode &node, std::string const &source,
                  AliasPriority priority) {
        ParsedAlias newSource(source);
        if (!newSource.isValid()) {
            /// @todo signify invalid route in some other way?
            TVR_DEV_VERBOSE("PathTree", "Could not parse source: " << source);
            return false;
        }
        if (!isPathAbsolute(newSource.getLeaf())) {
            /// @todo signify not to pass relative paths here in some other way?
            TVR_DEV_VERBOSE("PathTree", "Source contains a relative path, not permitted: " << source);
            return false;
        }
        return addAliasImpl(node, newSource.getAlias(), priority);
    }

    bool addAliasFromRoute(PathNode &node, std::string const &route,
                           AliasPriority priority) {
        auto val = jsonParse(route);
        auto alias = applyPriorityToAlias(convertRouteToAlias(val), priority);
        return AliasProcessor().process(node, alias);
    }

    static inline std::string getAbsolutePath(PathNode &node,
                                              std::string const &path) {
        if (isPathAbsolute(path)) {
            return path;
        }
        return getFullPath(treePathRetrieve(node, path));
    }

    bool addAliasFromSourceAndRelativeDest(PathNode &node,
                                           std::string const &source,
                                           std::string const &dest,
                                           AliasPriority priority) {
        auto &aliasNode = treePathRetrieve(node, dest);
        ParsedAlias newSource(source);
        if (!newSource.isValid()) {
            /// @todo signify invalid route in some other way?
            TVR_DEV_VERBOSE("PathTree", "Could not parse source: " << source);
            return false;
        }
        auto absSource = getAbsolutePath(node, newSource.getLeaf());
        newSource.setLeaf(absSource);
        return addAliasImpl(aliasNode, newSource.getAlias(), priority);
    }

    bool isPathAbsolute(std::string const &source) {
        return !source.empty() && source.at(0) == getPathSeparatorCharacter();
    }

    void clonePathTree(PathTree const &src, PathTree &dest) {
        auto nodes = pathTreeToJson(src);
        jsonToPathTree(dest, nodes);
    }
}
}
