#ifndef INC_Client_RemoteHandlerFactory_h
#define INC_Client_RemoteHandlerFactory_h
#include <tvr/Client/RemoteHandler.h>
#include <tvr/Util/SharedPtr.h>
#include <tvr/Common/OriginalSource.h>
#include <tvr/Common/InterfaceList.h>
#include <tvr/Client/RemoteHandler.h>

#include <functional>
#include <unordered_map>

namespace tvr {
    namespace client {
        class VRPNConnection;
        class RemoteHandlerFactory {
            public:
                typedef shared_ptr<RemoteHandler> FactoryProduct;
                typedef std::function<FactoryProduct(tvr::common::OriginalSource const &,
                                                     tvr::common::InterfaceList &,
                                                     tvr::common::ClientContext &)> SpecificFactory;

                void addFactory(std::string const &name, SpecificFactory factory) {
                    m_factoriesByInterface[name] = factory;
                }

                bool isKnownInterfaceType(std::string const &name) const {
                    return m_factoriesByInterface.find(name) != end(m_factoriesByInterface);
                }

                FactoryProduct invokeFactory(tvr::common::OriginalSource const &source,
                                             tvr::common::InterfaceList &ifaces,
                                             tvr::common::ClientContext &ctx) const {
                    auto factory = m_factoriesByInterface.find(source.getInterfaceName());

                    if (factory == end(m_factoriesByInterface)) {
                        return FactoryProduct();
                    }
                }
                
            private:
                std::unordered_map<std::string, SpecificFactory> m_factoriesByInterface;
        };

        TVR_CLIENT_EXPORT void populateRemoteHandlerFactory(RemoteHandlerFactory &factory,
                                                            VRPNConnection const &conns);
    }
}

#endif
