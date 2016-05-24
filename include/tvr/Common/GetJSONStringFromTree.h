#ifndef INC_Common_GetJSONStringFromTree_h
#define INC_Common_GetJSONStringFromTree_h

// Internal Includes
#include <tvr/Common/PathElementTypes.h>
#include <tvr/Common/PathNode.h>
#include <tvr/Common/PathTree.h>

// Library/third-party includes
#include <boost/variant.hpp>

// Standard includes
// - none

namespace tvr {
namespace common {
    namespace {
        struct GetStringVisitor : boost::static_visitor<std::string> {
            std::string operator()(elements::StringElement const &elt) const {
                return elt.getString();
            }
            template <typename T> std::string operator()(T const &) const {
                return std::string{};
            }
        };
    }
    inline std::string getJSONStringAtNode(PathNode const &node) {
        return boost::apply_visitor(GetStringVisitor(), node.value());
    }
    inline std::string getJSONStringFromTree(PathTree const &tree,
                                             std::string const &path) {
        try {
            auto const &desiredNode = tree.getNodeByPath(path);
            return getJSONStringAtNode(desiredNode);
        } catch (util::tree::NoSuchChild &) {
            return std::string{};
        }
    }
}
}

#endif
