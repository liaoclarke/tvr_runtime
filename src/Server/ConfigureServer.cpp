
#include <json/value.h>
#include <json/reader.h>

#include <iostream>
#include <fstream>

namespace tvr {
    namespace server {
        ConfigureServer::ConfigureServer() : m_data(new ConfigureServerData()) {}
        ConfigureServer::~ConfigureServer() {}

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
        }
       
        void ConfigureServer::loadConfig(std::string const &json) {
            m_data->parse(json);
        }

        void ConfigureServer::loadConfig(std::string &json) {
            m_data->parse(json);
        }

        ServerPtr ConfigureServer::constructServer() {
            Json::Value const &root(m_data->root);
            boost::optional<int> port;
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

        static const char DISPLAY_KEY[] = "display";
        bool ConfigureServer::processDisplay() {
            bool success = false;
            Json::Value const &display = m_data->getMember(DISPLAY_KEY);
            if (display.isNull()) {
                return success;
            }
            success = m_server->addString(DISPLAY_KEY, display.asString());
            return success;
        }

        static const char RENDERMANAGER_KEY[] = "renderManagerConfig";
        bool ConfigureServer::processRenderManagerParameters() {
            bool success = false;
            Json::Value const &renderManager = m_data->getMember(RENDERMANAGER_KEY);
            if (renderManager.isNull()) {
                return success; 
            }
            success = m_server->addString(RENDERMANAGER_KEY, renderManager.asString());
            return success;
        }
    }
}
