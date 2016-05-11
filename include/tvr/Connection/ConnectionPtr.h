#ifndef CONNECTION_ConnectionPtr_H
#define CONNECTION_ConnectionPtr_H
#include <Util/SharedPtr.h>
namespace tvr {
    namespace connection {
        class Connection;
        typedef shared_ptr<Connection> ConnectionPtr;
    }
}
#endif
