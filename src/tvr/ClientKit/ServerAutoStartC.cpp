#include <tvr/ClientKit/ServerAutoStartC.h>

void tvrClientAttemptServerAutoStart()
{
    auto server = tvr::client::getServerBinaryDirectoryPath();
    if (server) {
        TVR_DEV_VERBOSE("Attemping to auto-start TVR server from path " << *server);
        auto exePath = tvr::client::getServerLauncherBinaryPath();
        if (!exePath) {
            TVR_DEV_VERBOSE();
            return;
        }
        if (tvrStartProcess(exePath->c_str(), server->c_str()) == TVR_RETURN_FAILURE) {
            TVR_DEV_VERBOSE();
            return;
        }
    } else {
        TVR_DEV_VERBOSE("The current server location is currently unknown. Assuming server is ready running");
    }
    return;
}

void tvrClientReleaseAutoStartedServer()
{
}
