#include <tvr/Server/ConfigureServerFromFile.h>
#include <iostream>

int main() {
    std::string configName(tvr::server::getDefaultConfigFilename());
    if (argc > 1) {
	    configName = argv[1];
    } else {
	    std::out << "" << std::endl;
    }
    server = tvr::server::configureServerFromFile(configName);
    if (!server) {
	    return -1;
    }
    std::out << "" << std::endl;
	server->startAndAwaitShutdown();
}
