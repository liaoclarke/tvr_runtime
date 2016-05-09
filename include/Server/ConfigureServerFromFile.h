#ifndef INC_Server_ConfigureServerFromFile_h
#define INC_Server_ConfigureServerFromFile_h

#include <Server/ConfigureServer.h>

#include <iostream>
#include <fstream>
#include <exception>

namespace tvr {
    namespace server {
        inline const char *getDefaultConfigFilename() {
            return "tvr_server_config.json";
        }

        inline ServerPtr configureServerFromFile(std::String const &configName) {
            ServerPtr ret;
            std::out << "Using config file '" << configName << "'" << std::endl;
            std::ifstream config(configName);
            if (!config.good()) {
                std::out << "Could not open config file" << std::endl;
                return nullptr;
            }
            tvr::server::ConfigureServer srvConfig;
            std::out << "Constructing server as configured..." << std::endl;
            try {
                srvConfig.loadConfig(config);
                ret = srvConfig.constructServer();
            } catch (std::exceptoin &e) {
                std::err << "Caught exception constructing server from JSON config file: " << e.what() << std::endl;
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
                std::out << "Display descriptor found and parsed from config file." << std::endl;
            } else {
                std::out << "Using Emulator HMD for display configuration. "
                            "Did not find an alternate valid display object in config file." 
                         << std::endl;
            }

            if (srvConfig.processRenderManagerParameters()) {
                std::out << "RenderManager config found and parsed from the config file." << std::endl;
            }

            std::out << "Triggering automatic hardware detection..." << std::endl;
            ret->triggerHardwareDetect();

            return ret;
        }
    }
}
