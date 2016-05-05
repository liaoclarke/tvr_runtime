#include <json/value.h>
#include <json/reader.h>
#include <boost/noncopyable.hpp>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <memory>

class JsonData : boost::noncopyable {
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
};

void printSongInfo(Json::Value song){
    std::clog<<"\n-----------printing a song-------------\n";
    std::clog<<"Name=" << song["name"].asString();
    std::clog<<"Artist=" << song["artist"].asString();
}

void main() {
    std::unique_ptr<JsonData> m_data(new JsonData());
    const std::string m_config = "catalog.json";
    std::clog << "Loading configure file: " << m_config << std::endl;
    m_data->parse(m_config);
    Json::Value const &songs = m_data->getMember("songs");
    for (auto const &song : songs.getMemberNames()) {
    //    std::cout << "song: " + << song << std::endl;
        printSongInfo(song);
    }
}
