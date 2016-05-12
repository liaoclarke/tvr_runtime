#include <tvr/Connection/Connection.h>
#include <tvr/Connection/ConnectionPtr.h>
#include <tvr/Connection/VrpnBasedConnection.h>
#include <tvr/Util/SharedPtr.h>

namespace tvr {
    namespace connection {
        ConnectionPtr Connection::createConnection() {
            ConnectionPtr conn(make_shared<VrpnBasedConnection>());
            return conn;
        }

        Connection::Connection() {}

        Connection::~Connection() {}

        void *Connection::getUnderlyingObject() { return nullptr; }
    }
}
