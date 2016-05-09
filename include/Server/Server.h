#ifndef SERVER_Server_h
#define SERVER_Server_h
namespace tvr {
    namespace server {
        class ServerImpl;
        class Server : boost::noncopyable {
            struct private_constructor {};

            public:
                Server(connection::ConnectionPtr const &conn, private_constructor const &);
                ~Server();
                static ServerPtr create();
                void update();
                void startAndAwaitShutDown();
                void stop();
                void signalStop();
                void setHardwareDetectOnConnection();
                void triggerHardwareDetect();
                bool addString(std::string const &key, std::string const &value);
                void setSleepTime(int microseconds);

            private:
                unique_ptr<ServerImpl> m_impl;
        }
    }
}
#endif
