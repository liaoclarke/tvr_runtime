#include <Connection/Connection.h>
#include <Connection/ConnectionPtr.h>

namespace tvr {
    namespace connection {
        ConnectionPtr Connection::createConnection() {
            ConnectionPtr conn(make_shared<VrpnBasedConnection>());
            return conn;
        }
    }
}
