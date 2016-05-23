#ifndef INC_Client_RemoteHandler_h
#define INC_Client_RemoteHandler_h
#include <tvr/Util/SharedPtr.h>

namespace tvr {
    namespace client {
        class RemoteHandler {
            public:
                virtual ~RemoteHandler();
                virtual void update() = 0;
        };
        typedef shared_ptr<RemoteHandler> RemoteHandlerPtr;
    }
}

#endif
