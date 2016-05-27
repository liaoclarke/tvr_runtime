#ifndef INC_Common_BaseMessageTraits_h
#define INC_Common_BaseMessageTraits_h
#include <tvr/Common/BaseDevice.h>
#include <tvr/Common/MessageHandler.h>

#include <vrpn_BaseClass.h>

namespace tvr {
    namespace common {
        class BaseDevice;
        typedef ImpliedSenderMessageHandleTraits<vrpn_MESSAGEHANDLER, BaseDevice> BaseDeviceMessageHandlerTraits;
    }
}
#endif
