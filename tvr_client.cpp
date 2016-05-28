#include <tvr/ClientKit/ClientKit.h>
#include <tvr/ClientKit/Parameters.h>

#include <json/reader.h>
#include <json/value.h>
#include <json/json.h>

// Standard includes
#include <iostream>
#include <fstream>
#include <exception>
#include <thread>

static const std::chrono::milliseconds SLEEP_TIME(2000); // Dead looping

int main(int argc, char *argv[]) {
    const bool m_run = true;
    const char path[] = "/account";
    tvr::clientkit::ClientContext ctx("com.tvr.test.tvr_client");
	try {
        std::cout << "client mainloop start up..." << std::endl;
        std::string buf = tvr::clientkit::getStringParameter(ctx.get(), path);
        std::cout<< "account data: " << buf << std::endl;
        Json::Value root;
        Json::Reader reader;
        bool ret = reader.parse(buf, root);
        if (ret) {
            std::cout << "test: " << root.get("test", "default value").toStyledString() << std::endl;	
            root["test"] = "bar";
            tvr::clientkit::setStringParameter(ctx.get(), path, (root.toStyledString()).c_str());
        }
        while (m_run) {
            ctx.update();
            //std::cout << "client context update" << std::endl;
            std::this_thread::sleep_for(SLEEP_TIME);
        }
        std::cout << "client mainloop shut down..." << std::endl;
	}
	catch (std::exception &e) {
		std::cout << "Catch error : " << e.what() << std::endl;
	}
    return 0;
}
