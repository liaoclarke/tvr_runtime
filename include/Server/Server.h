#ifndef SERVER_Server_h
#define SERVER_Server_h
namespace tvr {
    namespace server {
        class Server : boost::noncopyable {
            struct private_constructor {};

            public:
                Server();
                ~Server();
                static ServerPtr create(connection::ConnectionPtr const &conn);
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
