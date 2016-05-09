#ifndef SERVER_ServerPtr_H
#define SERVER_ServerPtr_H
#include <Util/SharedPtr.h>

namespace tvr {
    namespace server {
        class Server;
        typedef shared_ptr<Server> ServerPtr;
        typedef weak_ptr<Server> ServerWeakPtr;
    }
}
#endif
