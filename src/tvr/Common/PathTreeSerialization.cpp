// Internal Includes
#include <tvr/Common/PathTreeSerialization.h>
#include <tvr/Common/PathElementSerialization.h>
#include <tvr/Common/PathTreeFull.h>
#include <tvr/Common/PathElementTools.h>
#include <tvr/Common/PathNode.h>
#include <tvr/Common/ApplyPathNodeVisitor.h>
#include <tvr/Util/Verbosity.h>

// Library/third-party includes
#include <json/value.h>

// Standard includes
// - none

namespace tvr {
namespace common {
    namespace {
        /// @brief A PathNodeVisitor that returns a JSON object corresponding to
        /// a single PathNode (including its contained PathElement value)
        class PathNodeToJsonVisitor
            : public boost::static_visitor<Json::Value> {
          public:
            PathNodeToJsonVisitor() : boost::static_visitor<Json::Value>() {}

            /// @brief Adds data from the PathNode to an object containing
            /// PathElement data.
            void addNodeData(PathNode const &node, Json::Value &val) {
                val["path"] = getFullPath(node);
                val["type"] = getTypeName(node);
            }

            template <typename T>
            Json::Value operator()(PathNode const &node, T const &elt) {
                auto ret = pathElementToJson(elt);
                addNodeData(node, ret);
                return ret;
            }
        };
        Json::Value pathNodeToJson(PathNode const &node) {
            PathNodeToJsonVisitor visitor;
            return applyPathNodeVisitor(visitor, node);
        }
        /// @brief A PathNode (tree) visitor to recursively convert nodes in a
        /// PathTree to JSON
        class PathTreeToJsonVisitor {
          public:
            PathTreeToJsonVisitor(bool keepNulls)
                : m_ret(Json::arrayValue), m_keepNulls(keepNulls) {}

            Json::Value getResult() { return m_ret; }

            void operator()(PathNode const &node) {
                if (m_keepNulls || !elements::isNull(node.value())) {
                    // If we're keeping nulls or this isn't a null...
                    m_ret.append(pathNodeToJson(node));
                }
                // Recurse on children
                node.visitConstChildren(*this);
            }

          private:
            Json::Value m_ret;
            bool m_keepNulls;
        };
    } // namespace

    Json::Value pathTreeToJson(PathTree const &tree, bool keepNulls) {
        auto visitor = PathTreeToJsonVisitor{keepNulls};
        tree.visitConstTree(visitor);
        return visitor.getResult();
    }

    void jsonToPathTree(PathTree &tree, Json::Value nodes) {
        for (auto const &node : nodes) {
            elements::PathElement elt = jsonToPathElement(node);
            tree.getNodeByPath(node["path"].asString()).value() = elt;
        }
    }
}
}
