#ifndef COMMON_SystemComponent_H
#define COMMON_SystemComponent_H

namespace tvr {
    namespace common {
        namespace messages {
            class ReplacementTreeFromServer : public MessageRegistration<ReplacementTreeFromServer> {
                public:
                    class MessageSerialization;
                    static const char *identifier();
            };
        }

        class SystemComponent : public DeviceComponent {
            public:
                static shared_ptr<SystemComponent> create();
                messages::ReplacementTreeFromServer treeOut;
                void sendReplacementTree(PathTree &tree);
            private:
                SystemComponent();
                virtual void m_parentSet();
        }
    }
}

#endif
