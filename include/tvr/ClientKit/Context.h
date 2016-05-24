#ifndef INC_ClientKit_Context_h
#define INC_ClientKit_Context_h
#include <tvr/ClientKit/Context_decl.h>
#include <tvr/ClientKit/ContextC.h>

#include <string>
#include <stdexcept>

namespace tvr {
    namespace clientkit {
        inline ClientContext::ClientContext(const char applicationIdentifier[])
            : m_context(tvrClientInit(applicationIdentifier)) {}

        inline ClientContext::ClientContext(TVR_ClientContext context)
            : m_context(context) {}

        inline ClientContext::~ClientContext() { tvrClientShutdown(m_context); }

        inline void ClientContext::update() {
            TVR_ReturnCode ret = tvrClientUpdate(m_context);
            if (TVR_RETURN_SUCCESS != ret) {
                throw std::runtime_error("Error updating context.");
            }
        }

       inline TVR_ClientContext ClientContext::get() { return m_context; }

        inline bool ClientContext::checkStatus() const {
            return tvrClientCheckStatus(m_context) == TVR_RETURN_SUCCESS;
        }

    } // end namespace clientkit
}

#endif
