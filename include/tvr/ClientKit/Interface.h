#ifndef INC_ClientKit_Interface_h
#define INC_ClientKit_Interface_h
#include <tvr/ClientKit/Interface_decl.h>
#include <tvr/ClientKit/Context_decl.h>
#include <tvr/ClientKit/InterfaceC.h>
#include <tvr/ClientKit/InterfaceCallbackC.h>

#include <boost/function.hpp>

namespace tvr {
    namespace clientkit {
        inline Interface::Interface(ClientContext &ctx, TVR_ClientInterface iface)
                            : m_ctx(&ctx), m_interface(iface) {}

        inline Interface::Interface() : m_ctx(NULL), m_interface(NULL) {}

        inline bool Interface::notEmpty() const {
            return m_ctx != NULL && m_interface != NULL;
        }

        inline TVR_ClientInterface Interface::get() {
            return m_interface;
        }

        inline ClientContext &Interface::getContext() {
            return *m_ctx;
        }

        inline void Interface::free() {
            m_deletables.clear();
            m_ctx->free(*this);
            m_ctx = NULL;
            m_interface = NULL;
        }

        inline void Interface::takeOwnership(tvr::)
    }
}

#endif
