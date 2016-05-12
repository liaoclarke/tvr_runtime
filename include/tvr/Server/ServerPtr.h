#ifndef INC_Server_ServerPtr_h
#define INC_Server_ServerPtr_h
#include <tvr/Util/SharedPtr.h>
namespace tvr {
    namespace server {
        class Server;
        typedef shared_ptr<Server> ServerPtr;
        typedef weak_ptr<Server> ServerWeakPtr;
    }
}
#endif
