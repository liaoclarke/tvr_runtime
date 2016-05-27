#include <tvr/Common/SystemComponent.h>
#include <tvr/Common/BaseDevice.h>
#include <tvr/Common/Serialization.h>
#include <tvr/Common/JSONSerializationTags.h>
#include <tvr/Common/Buffer.h>
#include <tvr/Common/PathTreeSerialization.h>
#include <tvr/Util/MessageKeys.h>

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

        void SystemComponent::m_parentSet() {
            m_getParent().registerMessageType(treeOut);
        }

        SystemComponent::SystemComponent() {}

        shared_ptr<SystemComponent> SystemComponent::create() {
            shared_ptr<SystemComponent> ret(new SystemComponent);
            return ret;
        }

        /* Client register TreeReplace callback */
        void SystemComponent::registerReplaceTreeHandler(JsonHandler cb) {
            if (m_replaceTreeHandlers.empty()) {
                m_registerHandler(&SystemComponent::m_handleReplaceTree, this, treeOut.getMessageType());
            }
            m_replaceTreeHandlers.push_back(cb);
        }

        int SystemComponent::m_handleReplaceTree(void *userdata, vrpn_HANDLERPARAM p) {
            auto self = static_cast<SystemComponent *>(userdata);
            auto bufReader = readExternalBuffer(p.buffer, p.payload_len);
            messages::ReplacementTreeFromServer::MessageSerialization msg;
            deserialize(bufReader, msg);
            auto timestamp = tvr::util::time::fromStructTimeval(p.msg_time);
            BOOST_ASSERT_MSG(msg.getValue().isArray(), "replace tree message must be an array of nodes!");
            for (auto const &cb : self->m_replaceTreeHandlers) {
                cb(msg.getValue(), timestamp);
            }
            return 0;
        }

        void SystemComponent::sendReplacementTree(PathTree &tree) {
            auto config = pathTreeToJson(tree);
            Buffer<> buf;
            messages::ReplacementTreeFromServer::MessageSerialization msg(config);
            serialize(buf, msg);
            m_getParent().packMessage(buf, treeOut.getMessageType());
            m_getParent().sendPending();
        }
    }
}
