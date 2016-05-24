#include <tvr/Common/ClientContext.h>
#include <tvr/Common/GetJSONStringFromTree.h>
//#include <tvr/Common/ClientInterface.h>
#include <tvr/Util/Verbosity.h>

#include <boost/assert.hpp>

#include <algorithm>
#include <string>

using ::tvr::common::ClientContextDeleter;
using ::tvr::common::ClientContext;

namespace tvr {
    namespace common {
        void deleteContext(ClientContext *ctx) {
            auto del = ctx->getDeleter();
            //(*del)(ctx);           
        }
    }
}

/*TVR_ClientContextObject::TVR_ClientContextObject(const char appId[],
                                                 tvr::common::ClientInterfaceFactory const &interfaceFactory,
                                                 tvr::common::ClientInterfaceFactory del) 
                                                : m_appId(appId), m_clientInterfaceFactory(interfaceFactory),
                                                  m_deleter(del) {
    TVR_DEV_VERBOSE("ClientContextObject", "Client context initialized for " << m_appId);
}*/

TVR_ClientContextObject::TVR_ClientContextObject(const char appId[], ClientContextDeleter del) {}
                        //: TVR_ClientContextObject(appId, tvr::common::getStandardClientInterfaceFactory(), del) {}

TVR_ClientContextObject::~TVR_ClientContextObject() {
    TVR_DEV_VERBOSE("ClientContextObject", "Client context shut down for " + std::string(m_appId));
}

std::string const &TVR_ClientContextObject::getAppId() const {
    return m_appId;
}

void TVR_ClientContextObject::update() {
    m_update();
    /*for (auto const &iface : m_interfaces) {
        iface->update();
    }*/
}

/*ClientInterfacePtr TVR_ClientContextObject::getInterface(const char path[]) {
    auto ret = m_clientInterfaceFactory(*this, path);
    if (!ret) {
        return ret;
    }
    m_handleNewInterface(ret);
    m_interface.push_back(ret);
    return ret;
}*/

/*ClientInterfacePtr ClientContextObject::releaseInterface(ClientInterface *iface) {
    ClientInterfacePtr ret;
    if (!iface) {
        return ret;
    }
    auto it = std::find_if(begin(m_interfaces), end(m_interfaces), 
                            [&](ClientInterfacePtr const &ptr) {
                                if (ptr.get() == iface) {
                                    ret = ptr;
                                    return true;
                                } 
                                return false;
                            });
    if (ret) {
        m_interfaces.erase(it);
        m_handleReleasingInterface(ret);
    }
    return ret;
}*/

std::string TVR_ClientContextObject::getStringParameter(std::string const &path) const {
    return getJSONStringFromTree(getPathTree(), path);
    //return NULL;
}

tvr::common::PathTree const &TVR_ClientContextObject::getPathTree() const {
    return m_getPathTree();
}

void TVR_ClientContextObject::sendData(std::string const &data) {
    m_sendData(data);
}

bool TVR_ClientContextObject::releaseObject(void *obj) {
    return true;
    //return m_ownedObjects.release(obj);
}

ClientContextDeleter TVR_ClientContextObject::getDeleter() const {
    return m_deleter;
}

bool TVR_ClientContextObject::getStatus() const {
    return m_getStatus();
}

bool TVR_ClientContextObject::m_getStatus() const {
    return true;
}

/*void TVR_ClientContextObject::m_handleNewInterface(tvr::common::ClientInterfacePtr const &) {
}*/

/*void TVR_ClientContextObject::m_handleReleasingInterface(tvr::common::ClientInterface const &) {
}*/
