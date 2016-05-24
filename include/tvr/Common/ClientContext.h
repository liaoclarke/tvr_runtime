#ifndef INC_Common_ClientContext_h
#define INC_Common_ClientContext_h
//#include <tvr/Common/ClientInterfacePtr.h>
//#include <tvr/Common/ClientInterfaceFactory.h>
#include <tvr/Common/Export.h>
#include <tvr/Common/PathTree_fwd.h>
#include <tvr/Common/ClientContext_fwd.h>
#include <tvr/Util/UniquePtr.h>
#include <tvr/Util/SharedPtr.h>

#include <boost/noncopyable.hpp>
#include <boost/any.hpp>

#include <string>
#include <vector>
#include <map>

struct TVR_ClientContextObject : boost::noncopyable {
    public:
        //typedef std::vector<tvr::common::ClienterInterfacePtr> InterfaceList;

        TVR_COMMON_EXPORT virtual ~TVR_ClientContextObject();

        TVR_COMMON_EXPORT void update();

        TVR_COMMON_EXPORT std::string const &getAppId() const;

        //TVR_COMMON_EXPORT tvr::common::ClientInterfacePtr getInterface(const char path[]);

        //TVR_COMMON_EXPORT tvr::comomn::ClientInterfacePtr releaseInterface(tvr::common::ClientInterface *iface);

        //InterfaceList const &getInterface() const { return m_interfaces; }

        TVR_COMMON_EXPORT void sendData(std::string const &data);

        TVR_COMMON_EXPORT std::string getStringParameter(std::string const &path) const;

        TVR_COMMON_EXPORT tvr::common::PathTree const &getPathTree() const;

        template<typename T>void *acquireObject(T obj) {
            return m_ownedObjects.acquire(obj);
        }

        TVR_COMMON_EXPORT bool releaseObject(void *obj);

        TVR_COMMON_EXPORT tvr::common::ClientContextDeleter getDeleter() const;

        TVR_COMMON_EXPORT bool getStatus() const; 

    protected:
        TVR_COMMON_EXPORT TVR_ClientContextObject(const char adppId[], 
                                                  tvr::common::ClientContextDeleter del);

        /*TVR_COMMON_EXPORT TVR_ClientContextObject(const char appId[], 
                                                  tvr::common::ClientInterfaceFactory const &interfaceFactory
                                                  tvr::common::ClientContextDeleter del);
                                                  */

    private:
        virtual void m_update() = 0;

        virtual void m_sendData(std::string const &data) = 0;

        TVR_COMMON_EXPORT virtual bool m_getStatus() const;

        //TVR_COMMON_EXPORT virtual void m_handleNewInterface(tvr::common::ClientInterfacePtr const &iface);

        //TVR_COMMON_EXPORT virtual void m_handleReleasingInterface(tvr::common::ClientInterfacePtr const &iface);

        TVR_COMMON_EXPORT virtual tvr::common::PathTree const &m_getPathTree() const = 0;
        
        std::string const m_appId;

        //InterfaceList m_interfaces;

        //tvr::common::ClientInterfaceFactory m_clientInterfaceFactory;

        //tvr::util::MultipleKeyedOwnershipContainer m_ownedObjects;

        tvr::common::ClientContextDeleter m_deleter;
};

namespace tvr {
    namespace common {
        TVR_COMMON_EXPORT void deleteContext(ClientContext *ctx);

        namespace detail {
            class ClientContextDeleter {
                void operator()(ClientContext *ctx) const {
                    if (ctx) {
                        deleteContext(ctx);
                    }
                }
            };
            template <typename T>
            inline void context_deleter(ClientContext *obj) {
                T *o = static_cast<T *>(obj);
                delete o;
            }
        }

        template<typename T, typename... Args>
        inline T *makeContext(Args... args) {
            return new T(std::forward<Args>(args)..., &detail::context_deleter<T>);
        }
    }
}

#endif
