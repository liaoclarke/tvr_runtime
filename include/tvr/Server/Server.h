#ifndef INC_Server_Server_h
#define INC_Server_Server_h
#include <tvr/Util/UniquePtr.h>
#include <tvr/Connection/ConnectionPtr.h>
#include <tvr/Server/ServerImpl.h>
#include <tvr/Server/ServerPtr.h>

#include <boost/noncopyable.hpp>

#include <string>
namespace tvr {
    namespace server {
        class ServerImpl;
        class Server : boost::noncopyable {
            struct private_constructor {};

            public:
                Server(tvr::connection::ConnectionPtr const &conn, private_constructor const &);
                ~Server();
                static ServerPtr create();
                void update();
                void startAndAwaitShutdown();
                void stop();
                void signalStop();
                void setHardwareDetectOnConnection();
                void triggerHardwareDetect();
                bool addString(std::string const &key, std::string const &value);
                void setSleepTime(int microseconds);

            private:
                tvr::unique_ptr<ServerImpl> m_impl;
        };
    }
}
#endif
