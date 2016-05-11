#ifndef INC_Server_ServerImpl_h
#define INC_Server_ServerImpl_h
#include <tvr/Server/Server.h>
#include <tvr/Util/SharedPtr.h>
#include <tvr/Connection/ConnectionPtr.h>

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
                static int __stdcall m_exitIdle(void *userdata, vrpn_HANDLERPARAM);
                static int __stdcall m_enterIdle(void *userdata, vrpn_HANDLERPARAM);

                tvr::connection::ConnectionPtr m_conn;
                //tvr::common::BaseDevicePtr m_systemDevice;
                //tvr::common::SystemComponent *m_systemComponent = nullptr;
                //tvr::common::CommonComponent *m_commonComponent = nullptr;
                //tvr::common::PathTree m_tree;

                mutable boost::mutex m_runControl;
                boost::thread m_thread;
                bool m_triggeredDetect = false;
                bool m_running = false;
                bool m_everStarted = false;

                boost::thread::id m_mainThreadId;
                mutable boost::mutex m_mainThreadMutex;
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

    template <typename Callable>
    inline void ServerImpl::m_callControlled(Callable f) {
        boost::unique_lock<boost::mutex> lock(m_runControl);        
        if (m_running && boost::this_thread::get_id() != m_thread.get_id()) {
            boost::unique_lock<boost::mutex> lock(m_mainThreadMutex);
            TemporaryThreadIDChanger changer(m_mainThreadId);
            f();
        } else {
            f();
        } 
    }
}

#endif
