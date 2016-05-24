#include <tvr/ClientKit/ClientKit.h>
#include <ClientMainloopThread.h>

// Standard includes
#include <iostream>
#include <fstream>
#include <exception>

int main(int argc, char *argv[]) {
    tvr::clientkit::ClientContext ctx("com.tvr.test.tvr_client");
    ClientMainloopThread client(ctx);
	try {
		std::cout << "client mainloop start up..." << std::endl;
		client.start();
		//client.loopForDuration(boost::chrono::seconds(2));
		std::cout << "client mainloop shut down..." << std::endl;
	}
	catch (std::exception &e) {
		std::cout << "Catch error : " << e.what() << std::endl;
	}
    return 0;
}
