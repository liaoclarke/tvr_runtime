
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
        }

        bool ConfigureServer::instantiateDrivers() {
        }

        bool ConfigureServer::processExternalDevices() {
        }

        bool ConfigureServer::processDisplay() {
        }

        bool ConfigureServer::processRenderManagerParameters() {
        }
    }
}
