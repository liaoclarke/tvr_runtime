#define TVR_DEV_VERBOSE_DISABLE

// Internal Includes
#include <tvr/Common/BaseDevice.h>
#include <tvr/Common/DeviceComponent.h>
#include <tvr/Util/Verbosity.h>

// Library/third-party includes
#include <boost/assert.hpp>

// Standard includes
#include <stdexcept>

namespace tvr {
namespace common {

    BaseDevice::BaseDevice() {}
    BaseDevice::~BaseDevice() {
        /// Clear the component list first to make sure handler are
        /// unregistered.
        m_components.clear();
    }

    void BaseDevice::m_addComponent(DeviceComponentPtr component) {
        if (!component) {
            throw std::logic_error(
                "Tried to add a null component pointer to a base device!");
        }
        m_components.push_back(component);
        component->recordParent(*this);
    }

    void BaseDevice::registerHandler(vrpn_MESSAGEHANDLER handler,
                                     void *userdata,
                                     RawMessageType const &msgType) {
        m_getConnection()->register_handler(msgType.get(), handler, userdata,
                                            getSender().get());
    }

    void BaseDevice::unregisterHandler(vrpn_MESSAGEHANDLER handler,
                                       void *userdata,
                                       RawMessageType const &msgType) {
        m_getConnection()->unregister_handler(msgType.get(), handler, userdata,
                                              getSender().get());
    }

    RawMessageType BaseDevice::m_registerMessageType(const char *msgString) {
        TVR_DEV_VERBOSE("BaseDevice", "BaseDevice registering message type " << msgString);
        return RawMessageType(
            m_getConnection()->register_message_type(msgString));
    }

    RawSenderType BaseDevice::getSender() { return m_sender; }

    void BaseDevice::update() {
        for (auto const &component : m_components) {
            component->update();
        }
        m_update();
    }

    void BaseDevice::sendPending() {
        m_getConnection()->send_pending_reports();
    }

    std::string const &BaseDevice::getDeviceName() const { return m_name; }

    void BaseDevice::m_packMessage(size_t len, const char *buf,
                                   RawMessageType const &msgType,
                                   util::time::TimeValue const &timestamp,
                                   uint32_t classOfService) {
        struct timeval t;
        util::time::toStructTimeval(t, timestamp);
        auto ret = m_getConnection()->pack_message(
            static_cast<uint32_t>(len), t, msgType.get(), getSender().get(),
            buf, classOfService);
        if (ret != 0) {
            throw std::runtime_error("Could not pack message!");
        }
    }

    void BaseDevice::m_setup(vrpn_ConnectionPtr conn, RawSenderType sender,
                             std::string const &name) {
        m_conn = conn;
        m_sender = sender;
        m_name = name;
    }

    vrpn_ConnectionPtr BaseDevice::m_getConnection() const { return m_conn; }
} // namespace common
} // namespace tvr
