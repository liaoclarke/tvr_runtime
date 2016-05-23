#ifndef INC_ClientKit_InterfaceCallbackC_h
#define INC_ClientKit_InterfaceCallbackC_h
#include <tvr/ClientKit/Export.h>
#include <tvr/Util/APIBaseC.h>
#include <tvr/Util/ReturnCodesC.h>
#include <tvr/Util/ClientOpaqueTypesC.h>
#include <tvr/Util/ClientCallbackTypesC.h>

TVR_EXTERN_C_BEGIN

#define TVR_INTERFACE_CALLBACK_METHOD(TYPE) \
    TVR_CLIENTKIT_EXPORT TVR_ReturnCode tvrRegister##TYPE##Callback(TVR_ClientInterface iface, TVR_##TYPE##Callback cb, void *userdata);

TVR_INTERFACE_CALLBACK_METHOD(Pose);
TVR_INTERFACE_CALLBACK_METHOD(Position);
TVR_INTERFACE_CALLBACK_METHOD(Orientation);
TVR_INTERFACE_CALLBACK_METHOD(Account);

#undef TVR_INTERFACE_CALLBACK_METHOD

TVR_EXTERN_C_END

#endif
