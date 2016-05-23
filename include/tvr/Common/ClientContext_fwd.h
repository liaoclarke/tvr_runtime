#ifndef INC_Common_ClientContext_fwd_h
#define INC_Common_ClientContext_fwd_h

// Internal Includes
#include <tvr/Util/ClientOpaqueTypesC.h>

// Library/third-party includes
// - none

// Standard includes
// - none

struct TVR_ClientContextObject;
namespace tvr {
namespace common {
    typedef ::TVR_ClientContextObject ClientContext;

    typedef void (*ClientContextDeleter)(ClientContext *);
}
}

#endif
