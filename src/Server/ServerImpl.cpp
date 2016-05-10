#include <Server/ServerImpl.h>
#include <Connection/Connection.h>

#include <stdexcept>
#include <functional>

namespace tvr {
    namespace server {
        static vrpn_ConnectionPtr getVRPNConnection(tvr::connection::ConnectionPtr const &conn) {
            vrpn_ConnectionPtr ret;
            ret = vrpn_ConnectionPtr(static_cast<vrpn_Connection *>(conn->getUnderlyingObject()));
            return ret;
        }

        ServerImpl::ServerImpl(tvr::connection::ConnectionPtr const &conn)
                    : m_conn(conn), m_host("localhost"), m_port(tvr::util::UseDefaultPort) {
            if (!m_conn) {
                throw std::logic_error("Can't pass a null ConnectionPtr into Server constructor!");
            }
            auto vrpnConn = getVRPNConnection(m_conn);
            if (!(vrpnConn->doing_okay())) {
                throw std::runtime_error("Could not create server - there is probably another instance of the server or a VRPN server running already.");
            }
            m_systemDevice = tvr::common::createServerDevice(vrpnConn);
            //m_systemComponent = m_systemDevice->addComponent(tvr::common::SystemComponent::create());
            //m_systemComponent->registerUpdateHandler();
            //m_commonComponent = m_systemDevice->addComponent(tvr::common::CommonComponent::create());
            //m_commonComponent->registerPingHandler([&] { m_queueTreeSend(); });

            vrpnConn->register_handler(vrpnConn->register_message_type(vrpn_got_first_connection), &ServerImpl::m_exitIdle, this);
            vrpnConn->register_handler(vrpnConn->register_message_type(vrpn_dropped_last_connection), &ServerImpl::m_enterIdle, this);
        }

        ServerImpl::~ServerImpl() {
            stop();
        }

        void ServerImpl::startAndAwaitShutdown() {
            m_start();
            m_awaitShutdown();
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
            m_commonComponent->registerPingHandler([&] { triggerHardwareDetect(); });            
        }

        void ServerImpl::triggerHardwareDetect() {
            m_callControlled([&] { m_triggeredDetect = true; });
        }

        void ServerImpl::update() {
            boost::unique_lock<boost::mutex> lock(m_runControl);
            if (m_everStarted) {
                throw std::logic_error("Can't call update() if you've ever started the server in its own thread!");
            }
            m_update();
        }

        void ServerImpl::addString(std::String const &key, std::String const &value) {
        }

        void ServerImpl::setSleepTime() {
            m_sleepTime = microseconds;
        }

        void ServerImpl::m_awaitShutdown() {
            m_thread.join();
        }

        void ServerImpl::m_start() {
            boost::unique_lock<boost::mutex> lock(m_runControl);
            if (!m_conn) {
                throw std::logic_error("Cannot start server - context or connection destroyed (probably attemping to restart a stopped server)");
            }
            m_everStarted = true;
            m_running = true;

            m_thread = boost::thread([&] {
                bool keepRunning = true;
                m_mainThreadId = m_thread.get_id();
                tvr::util::LoopGuard guard(m_run);
                do {
                    keepRunning = this->m_loop();
                } while (keepRunning);
               m_orderedDestruction();
               m_running = false;
               });
            m_run.signalAndWaitForStart();
        }

        bool ServerImpl::m_update() {
            m_conn->process();
            m_systemDevice->mainloop();
            if (m_triggeredDetect) {
                TVR_DEV_VERBOSE("");
                m_ctx->triggerHardwareDetect();
                m_triggeredDetect = false;
            }
            if (m_treeDirty) {
                TVR_DEV("");
                m_sendTree();
                m_treeDirty.reset();
            }
        }

        bool ServerImpl::m_loop() {
            bool shouldContinue;
            boost::unique_lock<boost::mutex> lock(m_mainThreadMutex);
            m_update();
            shouldContinue = m_run.shouldContinue();
            if (m_currentSleepTime > 0) {
                tvr::util::time::microsleep(m_currentSleepTime);
            }
            return shouldContinue;
        }

        void ServerImpl::m_orderedDestruction() {
            //m_ctx.reset();
            m_systemComponent = nullptr;
            m_systemDevice.reset();
            m_conn.reset();
        }

        void ServerImpl::m_sendTree() {
            auto config = pathTreeToJson(m_tree);
            Buffer<> buf;
            serialize(buf, msg);
            packMessage(buf, "treeOut");
            sendPending();
        }

        int ServerImpl::m_exitIdle(void *userdata, vrpn_HANDLERPARAM) {
            auto self = static_cast<ServerImpl *>(userdata);
            if (self->m_currentSleepTime > self->m_sleepTime) {
                self->currentSleepTime = self->m_sleepTime;
            }
            return 0;
        }

        int ServerImpl::m_enterIdle(void *userdata, vrpn_HANDLERPARAM) {
            auto self = static_cast<ServerImpl *>(userdata);
            if (self->m_currentSleepTime < IDLE_SLEEP_TIME) {
                TVR_DEV_VERBOSE("ServerImpl", "Dropped last client connection, entering idle mode.");
                self->m_currentSleepTime = IDLE_SLEEP_TIME;
            }
            return 0;
        }
    }
}
