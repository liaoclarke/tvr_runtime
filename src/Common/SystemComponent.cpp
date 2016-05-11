#include <Common/SystemComponent.h>

#include <json/value.h>

namespace tvr {
    namespace common {
        namespace messages {
            class ReplacementTreeFromServer::MessageSerialization {
              public:
                MessageSerialization(Json::Value const &msg = Json::arrayValue)
                    : m_msg(msg) {}

                template <typename T> void processMessage(T &p) {
                    p(m_msg, serialization::JsonOnlyMessageTag());
                }

                Json::Value const &getValue() const { return m_msg; }

              private:
                Json::Value m_msg;
            };
            const char *ReplacementTreeFromServer::identifier() {
                return "com.tvr.system.ReplacementTreeFromServer";
            }
        } 

        void SystemComponent::sendReplacementTree(PathTree &tree) {
            auto config = pathThreeToJson(tree);
            Buffer<> buf;
            messages::ReplacementTreeFromServer::MessageSerialization(config);
            serialize(buf, msg);
            m_getParent().packMessage(buf, treeOut.getMessageType());
            m_getParent().sendPending();
        }
    }
}
