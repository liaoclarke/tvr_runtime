#ifndef INCLUDE_Util_SharedPtr_h
#define INCLUDE_Util_SharedPtr_h
#include <boost/shared_ptr.hpp>
namespace tvr {
    using boost::shared_ptr;
    using boost::weak_ptr;
    using boost::make_shared;
    using boost::enable_shared_from_this;
}
#endif
