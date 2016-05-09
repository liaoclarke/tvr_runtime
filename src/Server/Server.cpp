#include <Server/Server.h>
#include <Connection/Connection.h>

namespace tvr {
    namespace server {

        Server::Server(connection::ConnectionPtr const &conn,
                       boost) {
        }

        ServerPtr Server::create() {
            connection::ConnectionPtr conn(connection::Connection::createConnection());
            ServerPtr ret(std::make_shared<Server>(conn, boost::none, boost::none, private_constructor{}));
            return ret;
        }

        void Server::update() {
            m_server->update();
        }
    }
}
