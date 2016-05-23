#include <tvr/ClientKit/InterfaceCallback.h>
#include <tvr/Commoon/ClientInterface.h>

#define TVR_CALLBACK_METHODS(TYPE) \
    TVR_ReturnCode tvrRegister##TYPE##Callback(TVR_ClientInterface iface, \
                                               TVR__##TYPE##Callback cb, \
                                               void &userdata) { \
        iface->registerCallback(cb, userdata); \
        return TVR_RETURN_SUCCESS;             \
    }

TVR_CALLBACK_METHODS(Pose);
TVR_CALLBACK_METHODS(Position);
TVR_CALLBACK_METHODS(Orientation);
TVR_CALLBACK_METHODS(Account);

#undef TVR_CALLBACK_METHODS
