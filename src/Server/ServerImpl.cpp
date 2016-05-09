#include <Server/ServerImpl.h>
#include <Connection/Connection.h>

#include <stdexcept>
#include <functional>

namespace tvr {
    namespace server {
        ServerImpl::ServerImpl() {
            if (!m_conn) {
            }
            tvr::connection::Connection::storeConnection(*m_ctx, m_conn);
            auto vrpnConn = getVRPNConnection(m_conn);
            if (!(vrpnConn->doing_okay())) {
                throw ;
            }
            m_systemDevice = tvr::common::createServerDevice(vrpnConn);
            vrpnConn->register_handler(vrpnConn->register_message_type(vrpn_got_first_connection), &ServerImpl::m_exitIdle, this);
            vrpnConn->register_handler(vrpnConn->register_message_type(vrpn_dropped_last_connection), &ServerImpl::m_enterIdle, this);
        }

        ServerImpl::~ServerImpl() {
            stop();
        }

        void ServerImpl::startAndAwaitShutdown() {
            start();
            awaitShutdown();
        }

        void ServerImpl::awaitShutdown() {
            m_thread.join();
        }

        void ServerImpl::stop() {
            boost::unique_lock<boost::mutex> lock(m_runControl);
            if (m_everStarted) {
                m_run.signalAndWaitForShutdown();
                m_thread.join();
                m_thread = boost::thread();
            } else {
                m_orderDestruction();
            }
        }

        void ServerImpl::signalStop() {
            boost::unique_lock<boost::mutex> lock(m_runControl);
            m_run.signalShutdown();
        }

        void ServerImpl::setHardwareDetectOnConnection() {
            
        }

        void ServerImpl::triggerHardwareDetect() {

        }

        void ServerImpl::update() {
        }

        void ServerImpl::setSleepTime() {
            m_sleepTime = microseconds;
        }

        int ServerImpl::m_enterIdle(void *userdata, vrpn_HANDLERPARAM) {
            auto self = static_cast<ServerImpl *>(userdata);
            if (self->m_currentSleepTime < IDLE_SLEEP_TIME) {
                TVR_DEV_VERBOSE("ServerImpl", "Dropped last client connection, entering idle mode.");
                self->m_currentSleepTime = IDLE_SLEEP_TIME;
            }
        }
    }
}
