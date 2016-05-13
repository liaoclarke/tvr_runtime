#ifndef INC_Server_ConfigureServerFromFile_h
#define INC_Server_ConfigureServerFromFile_h
#include <tvr/Server/ConfigureServer.h>
#include <tvr/Server/ServerPtr.h>
#include <tvr/Server/Server.h>

#include <iostream>
#include <fstream>
#include <exception>

namespace tvr {
    namespace server {
        inline const char *getDefaultConfigFilename() {
            return "e:/TencentVR/tvr_runtime/config/tvr_server_config.json";
        }

        ServerPtr configureServerFromFile(std::string const &configName) {
            ServerPtr ret;
            std::cout << "Using config file '" << configName << "'" << std::endl;
            std::ifstream config(configName);
            if (!config.good()) {
                std::cout << "Could not open config file" << std::strerror(errno) << std::endl;
                return nullptr;
            }
            tvr::server::ConfigureServer srvConfig;
            std::cout << "Constructing server as configured..." << std::endl;
            try {
                srvConfig.loadConfig(config);
                ret = srvConfig.constructServer();
            } catch (std::exception &e) {
                std::cerr << "Caught exception constructing server from JSON config file: " << e.what() << std::endl;
                return nullptr;
            }
            
            /*std::out << "Instantiating configured drivers..." << std::endl;
            bool success = srvConfig.instantiateDrivers();
            if (!srvConfig.getSuccessfulInstantiations().empty()) {
                std::out << "Successes:" << std::endl;
                for (auto const &driver : srvConfig.getSuccessfulInstantiations()) {
                    std::out << " - " << driver << std::endl;
                }
                std::out << "\n";
            }
            if (!srvConfig.getFailedInstantiations().empty()) {
                std::out << "Errors:" << std::endl;
                for (auto const &error : srvConfig.getFailedInstantiations()) {
                    std::out << " - " << error.first << "\t" << error.second << std::endl;
                }
                std::out << "\n";
            }

            if (srvConfig.processExternalDevices()) {
                std::out << "External devices found and parsed from config file." << std:endl;
            }*/

            if (srvConfig.processDisplay()) {
                std::cout << "Display descriptor found and parsed from config file." << std::endl;
            } else {
                std::cout << "Using Emulator HMD for display configuration. "
                            "Did not find an alternate valid display object in config file." 
                         << std::endl;
            }

            if (srvConfig.processRenderManagerParameters()) {
                std::cout << "RenderManager config found and parsed from the config file." << std::endl;
            }

            std::cout << "Triggering automatic hardware detection..." << std::endl;
            ret->triggerHardwareDetect();

            return ret;
        }
    }
}
#endif
