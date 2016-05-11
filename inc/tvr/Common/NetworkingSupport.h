#ifndef INC_Common_NetworkingSupport_h
#define INC_Common_NetworkingSupport_h
#include <boost/noncopyable.hpp>

#include <string>

namespace tvr {
    namespace common {
        class NetworkingSupport : boost::noncopyable {
          public:
            NetworkingSupport();
            ~NetworkingSupport();
            bool isUp() const { return m_up; }
            bool wasSuccessful() const { return m_success; }
            std::string const &getError() const { return m_err; }
            void shutdown();

          private:
            bool m_start();
            bool m_stop();
            bool m_up;
            bool m_success;
            std::string m_err;
        };
    }
}
#endif
