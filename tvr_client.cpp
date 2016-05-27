#include <tvr/ClientKit/ClientKit.h>

// Standard includes
#include <iostream>
#include <fstream>
#include <exception>
#include <thread>

static const std::chrono::milliseconds SLEEP_TIME(2000); // Dead looping

int main(int argc, char *argv[]) {
    const bool m_run = true;
    tvr::clientkit::ClientContext ctx("com.tvr.test.tvr_client");
	try {
        std::cout << "client mainloop start up..." << std::endl;
        while (m_run) {
            ctx.update();
            std::cout << "client context update" << std::endl;
            std::this_thread::sleep_for(SLEEP_TIME);
        }
        std::cout << "client mainloop shut down..." << std::endl;
	}
	catch (std::exception &e) {
		std::cout << "Catch error : " << e.what() << std::endl;
	}
    return 0;
}
