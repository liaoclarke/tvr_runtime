#include <Server/Server.h>
#include <Server/ServerPtr.h>
#include <Connection/Connection.h>

namespace tvr {
    namespace server {

        Server::Server(connection::ConnectionPtr const &conn, 
                       private_constructor const &) 
                : m_impl(new ServerImpl(conn)) {}

        Server::~Server() {}

        ServerPtr Server::create() {
            tvr::connection::ConnectionPtr conn(connection::Connection::createConnection());
            ServerPtr ret(std::make_shared<Server>(conn, private_constructor{}));
            return ret;
        }

        void Server::update() {
            m_impl->update();
        }

        void Server::startAndAwaitShutdown() {
            m_impl->awaitShutdown();
        }

        void Server::stop() {
            m_impl->stop();
        }

        void Server::signalStop() {
            m_impl->signalStop();
        }

        void Server::setHardwareDetectOnConnection() {
            m_impl->setHardwareDetectOnConnection();
        }

        void Server::triggerHardwareDetect() {
            m_impl->triggerHardwareDetect();
        }

        bool Server::addString(std::string const &key, std::string const &value) {
            return m_impl->addString(key, value);
        }

        void Server::setSleepTime(int microseconds) {
            m_impl->setSleepTime(microseconds);
        }
    }
}
