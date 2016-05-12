#include <tvr/Common/NetworkingSupport.h>
#include <tvr/Util/WideToUTF8.h>

#include <iostream>
#include <type_traits>

#include <winsock2.h>

namespace tvr {
    namespace common {
        static inline std::string wsaErrorCodeToString(int err) {
            TCHAR buf[256] = {0};

            FormatMessage(
                FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, nullptr,
                err, 0, &(buf[0]), sizeof(buf) / sizeof(buf[0]), nullptr);
            return tvr::util::tcharToUTF8String(buf);
        }

        inline bool NetworkingSupport::m_start() {
            WSADATA wsaData;
            auto status = WSAStartup(MAKEWORD(2, 2), &wsaData);
            if (0 == status) {
                m_up = true;
                return true;
            }
            m_err = "WSAStartup failed: " + wsaErrorCodeToString(status);
            return false;
        }

        inline bool NetworkingSupport::m_stop() {
            if (SOCKET_ERROR == WSACleanup()) {
                m_err =
                    "WSACleanup failed: " + wsaErrorCodeToString(WSAGetLastError());
                return false;
            }
            return true;
        }

        NetworkingSupport::NetworkingSupport() : m_up(false), m_success(true) {
            m_success = m_start();
        }

        NetworkingSupport::~NetworkingSupport() {
            shutdown();
            if (!wasSuccessful()) {
                std::cerr << getError() << std::endl;
            }
        }

        void NetworkingSupport::shutdown() {
            m_success = true;
            m_err.clear();
            if (m_up) {
                m_success = m_stop();
            }
        }
    }
} 
