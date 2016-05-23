#include <tvr/Client/TrackerRemoteFactory.h>

namespace tvr {
    namespace client {
        class VRPNTrackerHandler : public RemoteHandler {
            public:
                struct Options {
                    bool reportPose = false;
                    bool reportPosition = false;
                    bool reportOrientation = false;
                };

                VRPNTrackerHandler(vrpn_ConnectionPtr const &conn, const char *src,
                                   Options const &options, tvr::common::InterfaceList &ifaces, tvr::common::ClientContext &ctx)
                    : m_remote(new vrpn_Tracker_Remote(src, conn.get())), m_ctx(ctx), m_internals(ifaces), m_opts(options) {
                    m_remote->register_change_handler(this, &VRPNTrackerHandle::handle);                    
                }

                virtual ~VRPNTrackerHandler() {
                    m_remote->unregister_change_handler(this, &VRPNTrackerHandler::handle);
                }

                static void VRPN_CALLBACK handle(void *userdata, vrpn_TRACKERCB info) {
                    auto self = static_cast<VRPNTrackerHandler *>(userdata);
                    self->m_handle(info);
                }

                virtual void update() {
                    m_remote->mainloop();
                }

            private:
                void m_handle(vrpn_TRACKERCB const &info) {
                    TVR_PoseReport report;
                    TVR_TimeValue timestamp;
                    tvrStrcutTimevalToTimeValue(&timestamp, &(info.msg_time));
                    tvrQuatFromQuatlib(&(report.pose.rotation), info.quat);
                    tvrVec3FromQuatlib(&(report.pose.translation), info.pos);

                    m_internals.setStateAndTriggerCallbacks(timestamp, report);

                    TVR_PositionReport positionReport;
                    positionReport.sensor = info.sensor;
                    positionReport.xyz = report.pose.translation;
                    m_interals.setStateAndTriggerCallbacks(timestamp, positionReport);

                    TVR_OrientationReport oriReport;
                    oriReport.sensor = info.sensor;
                    oriReport.rotation = report.pose.rotation;
                    m_internals.setStateAndTriggerCallbacks(timestamp, oriReport);
                }

                unique_ptr<vrpn_Tracker_Remote> m_remote;
                tvr::common::ClientContext &m_ctx;
                RemoteHandlerInternals m_internals;
                Options m_opts;
        };

        TrackerRemoteFactory::TrackerRemoteFactory(VRPNConnection const &conn) : m_conn(conn) {}

        shared_ptr<RemoteHandler> TrackerRemoteFactory::operator()(tvr::common::OriginalSource const &source, tvr::common::InterfaceList &ifaces, tvr::common::ClientContext &ctx) {
            shared_ptr<RemoteHandler> ret;
            VRPNTrackerHandler::Options opts;
            opts.reportPose = true;
            opts.reportPosition = true;
            opts.reportOrientation = true;
            ret.reset(new VRPNTrackerHandler(m_conn.getConnection(), "tracker", opts, ifaces, ctx));
        }
    }
}
