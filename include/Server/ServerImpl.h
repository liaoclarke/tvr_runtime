#ifndef SERVER_ServerImpl_h
#define SERVER_ServerImpl_h
#include <Server/Server.h>
#include <Util/SharedPtr.h>

#include <boost/noncopyable.hpp>
#include <boost/thread.hpp>
#include <boost/optional.hpp>
#include <vrpn_Connection.h>
#include <json/value.h>

#include <string>

namespace tvr {
    namespace server {
        class ServerImpl : boost::noncopyable {
            public:
                ServerImpl(tvr::connection::ConnectionPtr const &conn);
                ~ServerImpl();
                void startAndAwaitShutDown();
                void stop();
                void signalStop();
                void setHardwareDetectOnConnection();
                void triggerHardwareDetect();
                bool addString(std::string const &key, std::string const &value);
                void setSleepTime(int microseconds);
                void update();

            private:
                void m_start();
                void m_awaitShutdown();
                bool m_loop();
                void m_update();
                template<typename Callable> void m_callControlled(Callable f);
                void m_orderdDestruction();
                void m_queueTreeSend();
                void m_sendTree();
                bool m_inServerThead() const;
                static int VRPN_CALLBACK m_exitIdle(void *userdata, vrpn_HANDLERPARAM);
                static int VRPN_CALLBACK m_enterIdle(void *userdata, vrpn_HANDLERPARAM);

                tvr::connection::ConnectionPtr m_conn;
                tvr::common::BaseDevicePtr m_systemDevice;
                tvr::common::PathTree m_tree;
                bool m_triggeredDetect = false;
                bool m_running = false;
                bool m_everStarted = false;
                boost::thread m_thread;
                boost::thread::id m_mainThreadId;
                int m_sleepTime = 0;
                static const int IDLE_SLEEP_TIME = 1000;
                int m_currentSleepTime = IDLE_SLEEP_TIME;
                std::string m_host;
                int m_port;
        };

        class TemporaryThreadIDChanger : boost::noncopyable {
            public::
                TemporaryThreadIDChanger(boost::thread::id &id) 
                    : m_id(id), m_origID(id) {
                        m_id = boost::this_thread::get_id();
                }
                ~TemporaryThreadIDChanger() {
                    m_id = m_origID;
                } 

            private:
                boost::thread::id &m_id;
                boost::thread::id m_origID;
        };
    }
}

#endif
