#ifndef INC_Connection_ConnectionPtr_h
#define INC_Connection_ConnectionPtr_h
#include <tvr/Util/SharedPtr.h>
namespace tvr {
    namespace connection {
        class Connection;
        typedef shared_ptr<Connection> ConnectionPtr;
    }
}
#endif
