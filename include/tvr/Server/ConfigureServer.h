#ifndef INC_Server_ConfigureServer_h
#define INC_Server_ConfigureServer_h

#include <Server/ServerPtr.h>

#include <boost/noncopyable.hpp>

#include <string>
#include <iosfwd>
#include <vector>

namespace tvr {
    namespace server {
        class ConfigureServer : boost::noncopyable {
            public:
                ConfigureServer();
                ~ConfigureServer();
                void loadConfig(std::string const &json);
                void loadConfig(std::istream &json);
                ServerPtr constructServer();
                typedef std::vector<std::string> SuccessList;
                typedef std::pair<std::string, std::string> ErrorPair;
                typedef std:vector<ErrorPair> ErrorList;
                bool instantiateDrivers();
                SuccessList const &getSuccessfulInstantiations() const;
                ErrorList const &getFailedInstantiations() const;
                bool processExternalDevices();
                bool processDisplay();
                bool processRenderManagerParameters();
            prvate:
                unique_ptr<ConfigureServerData> m_data;
                ServerPtr m_server;
                SuccessList m_successfulInstances;
                ErrorList m_failedInstances;
        };
    }
}
