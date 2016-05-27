#include <tvr/Server/ConfigureServer.h>
#include <tvr/Server/Server.h>
#include <tvr/Server/ServerPtr.h>

#include <boost/noncopyable.hpp>
#include <json/value.h>
#include <json/reader.h>

#include <iostream>
#include <fstream>

namespace tvr {
    namespace server {
        class ConfigureServerData : boost::noncopyable {
            public:
                template<typename T> inline void parse(T &json) {
                    Json::Reader reader;
                    bool parsingSuccessful = reader.parse(json, root);
                    if (!parsingSuccessful) {
                        throw std::runtime_error("Error in parsing Json: " + reader.getFormattedErrorMessages());
                    }
                }

                const Json::Value &getMember(const char *memberName) const {
                    return root[memberName];
                }

                Json::Value root;
        };

        ConfigureServer::ConfigureServer() : m_data(new ConfigureServerData()) {}

        ConfigureServer::~ConfigureServer() {}
       
        void ConfigureServer::loadConfig(std::string const &json) {
            m_data->parse(json);
        }

        void ConfigureServer::loadConfig(std::istream &json) {
            m_data->parse(json);
        }

        ServerPtr ConfigureServer::constructServer() {
            Json::Value const &root(m_data->root);
            int sleepTime = 0;
            m_server = Server::create();
            if (sleepTime > 0.0) {
                m_server->setSleepTime(sleepTime);
            }
            m_server->setHardwareDetectOnConnection();
            return m_server;
        }

        bool ConfigureServer::instantiateDrivers() {
            return false;
        }

        bool ConfigureServer::processExternalDevices() {
            return false;
        }

        static const char ACCOUNT_KEY[] = "account";
        static const char ACCOUNT_PATH[] = "/account";
        bool ConfigureServer::processAccount() {
            bool success = false;
            Json::Value const &account = m_data->getMember(ACCOUNT_KEY);
            if (account.isNull()) {
                return success;
            }
            std::cout << "account value: " << account.toStyledString() << std::endl;
            success = m_server->addString(ACCOUNT_PATH, account.toStyledString());
            return success;
        }

        static const char DISPLAY_KEY[] = "display";
        static const char DISPLAY_PATH[] = "/display";
        bool ConfigureServer::processDisplay() {
            bool success = false;
            Json::Value const &display = m_data->getMember(DISPLAY_KEY);
            if (display.isNull()) {
                return success;
            }
            std::cout << "display value: " << display.toStyledString() << std::endl;
            success = m_server->addString(DISPLAY_PATH, display.toStyledString());
            return success;
        }

        static const char RENDERMANAGER_KEY[] = "rendermanager";
        static const char RENDERMANAGER_PATH[] = "/rendermanager";
        bool ConfigureServer::processRenderManagerParameters() {
            bool success = false;
            Json::Value const &renderManager = m_data->getMember(RENDERMANAGER_KEY);
            if (renderManager.isNull()) {
                return success; 
            }
            std::cout << "rendermanager value: " << renderManager.toStyledString() << std::endl;
            success = m_server->addString(RENDERMANAGER_PATH, renderManager.toStyledString());
            return success;
        }
    }
}
