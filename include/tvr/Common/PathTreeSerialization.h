#ifndef INC_Common_PathTreeSerialization_h
#define INC_Common_PathTreeSerialization_h

// Internal Includes
#include <osvr/Common/Export.h>
#include <osvr/Common/PathNode_fwd.h>
#include <osvr/Common/PathTree_fwd.h>

// Library/third-party includes
#include <json/value.h>

// Standard includes
#include <string>

namespace tvr {
namespace common {

    /// @brief Serialize a path node to a JSON object
    OSVR_COMMON_EXPORT Json::Value pathNodeToJson(PathNode const &node);

    /// @brief Serialize a path tree to a JSON array of objects, one for each
    /// node
    OSVR_COMMON_EXPORT Json::Value pathTreeToJson(PathTree const &tree,
                                                  bool keepNulls = false);

    /// @brief Deserialize a path tree from a JSON array of objects
    OSVR_COMMON_EXPORT void jsonToPathTree(PathTree &tree, Json::Value nodes);
}
}

#endif
