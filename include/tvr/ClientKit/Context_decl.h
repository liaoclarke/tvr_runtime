#ifndef INC_ClientKit_Contextdecl_h
#define INC_ClientKit_Contextdecl_h
#include <tvr/ClientKit/ContextC.h>

#include <boost/noncopyable.hpp>

#include <string>

namespace tvr {
    namespace clientkit {
        class ClientContext : private boost::noncopyable {
            public:
                ClientContext(const char applicationIdentifier[]);

                ClientContext(TVR_ClientContext context);

                ~ClientContext();

                void update();

                bool checkStatus() const;

                TVR_ClientContext get();

            private:
                TVR_ClientContext m_context;
        };
    }
}

#endif
