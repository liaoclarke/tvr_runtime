#include <tvr/Common/BaseDevice.h>
#include <tvr/Common/RawSenderType.h>
//#include <tvr/Common/DeviceComponent.h>

#include <boost/assert.hpp>
#include <vrpn_ConnectionPtr.h>

#include <stdexcept>

namespace tvr {
    namespace common {
        BaseDevice::BaseDevice() {}
        BaseDevice::~BaseDevice() {
            //m_components.clear();
        }

        /*void BaseDevice::m_addComponent(DeviceComponentPtr component) {
            if (!component) {
                throw std::logic_error("Tried to add a null component pointer to a base device!");
            }
            m_components.push_back(component);
            component->recordParent(*this);
        }*/

        void BaseDevice::update() {
            /*for (auto const &component : m_components) {
                component->update();
            }*/
            m_update();
        }

        void BaseDevice::sendPending() {
            m_getConnection()->send_pending_reports();
        }

        std::string const &BaseDevice::getDeviceName() const {
            return m_name;
        }

        void BaseDevice::m_setup(vrpn_ConnectionPtr conn, RawSenderType sender, std::string const &name) {
            m_conn = conn;
            m_sender = sender;
            m_name = name;
        }

        vrpn_ConnectionPtr BaseDevice::m_getConnection() const {
            return m_conn;
        }
    }
}
