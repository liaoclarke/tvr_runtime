#ifndef CONNECTION_Connection_H
#define CONNECTION_Connection_H

#include <boost/noncopyable.h>
#include <boost/optional.h>

#include <string>
#include <vector>
#include <functional>
#include <tuple>

namespace tvr {
    namespace connection {
        class Connection : boost::noncopyable, public enable_shared_from_this<Connection> {
            public:
                static ConnectionPtr createConnection();
                virtual ~Connection();

            protected:
                virtual void m_process() = 0;
                Connection();
        }
    }
}

#endif

