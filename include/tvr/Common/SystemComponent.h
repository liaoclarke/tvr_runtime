#ifndef INC_Common_SystemComponent_h
#define INC_Common_SystemComponent_h
#include <tvr/Common/SystemComponent_fwd.h>
#include <tvr/Common/Export.h>
#include <tvr/Common/DeviceComponent.h>
#include <tvr/Common/SerializationTags.h>
#include <tvr/Common/PathTree_fwd.h>

#include <json/value.h>

namespace tvr {
    namespace common {
        namespace messages {
            class ReplacementTreeFromServer : public MessageRegistration<ReplacementTreeFromServer> {
                public:
                    class MessageSerialization;
                    static const char *identifier();
            };

            class ClientDataToServer : public MessageRegistration<ClientDataToServer> {
                public:
                    class MessageSerialization;
                    static const char *identifier();
            };
        }

        class SystemComponent : public DeviceComponent {
            public:
                TVR_COMMON_EXPORT static shared_ptr<SystemComponent> create();
                typedef std::function<void(Json::Value const &,
                                   util::time::TimeValue const &)> JsonHandler;
                /* Messag from server, updating/replaceing the client's configuratoin */
                messages::ClientDataToServer dataIn;
                TVR_COMMON_EXPORT void sendClientDataUpdate(std::string const &tree);
                TVR_COMMON_EXPORT void registerClientDataUpdateHandler(JsonHandler cb);

                messages::ReplacementTreeFromServer treeOut;
                TVR_COMMON_EXPORT void registerReplaceTreeHandler(JsonHandler cb);
                TVR_COMMON_EXPORT void sendReplacementTree(PathTree &tree);
            private:
                SystemComponent();
                virtual void m_parentSet();
                static int VRPN_CALLBACK m_handleReplaceTree(void *userdata, vrpn_HANDLERPARAM p);
                static int VRPN_CALLBACK m_handleUpdateData(void *userdata, vrpn_HANDLERPARAM p);
                std::vector<JsonHandler> m_replaceTreeHandlers;
                std::vector<JsonHandler> m_updateDataHandlers;
        };
    }
}

#endif
