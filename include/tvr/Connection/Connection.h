#ifndef INC_Connection_Connection_h
#define INC_Connection_Connection_h
#include <tvr/Connection/ConnectionPtr.h>
#include <tvr/Util/SharedPtr.h>

#include <boost/noncopyable.hpp>
#include <boost/optional.hpp>

#include <string>
#include <vector>
#include <functional>

namespace tvr {
    namespace connection {
        class Connection : boost::noncopyable, public enable_shared_from_this<Connection> {
            public:
                static ConnectionPtr createConnection();
                virtual ~Connection();
                virtual void *getUnderlyingObject();

            protected:
                virtual void m_process() = 0;
                Connection();
        };
    }
}

#endif

