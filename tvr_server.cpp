#include <tvr/Server/ConfigureServerFromFile.h>
#include <iostream>

static tvr::server::ServerPtr server;

int main(int argc, char *argv[]) {
    std::string configName(tvr::server::getDefaultConfigFilename());
    if (argc > 1) {
	    configName = argv[1];
    } else {
        std::cout << "Using default config file - pass a filename on the command "
               "line to use a different one."
            << std::endl;
    }
    server = tvr::server::configureServerFromFile(configName);
    if (!server) {
	    return -1;
    }
    std::cout << "" << std::endl;
	server->startAndAwaitShutdown();
}
