#include <json/value.h>
#include <json/reader.h>
#include <boost/noncopyable.hpp>
#include <iostream>

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
}

void printSongInfo(Json::Value song){
    std::clog<<"\n-----------printing a song-------------\n";
    std::clog<<"Name=" << song["name"].asString();
    std::clog<<"Artist=" << song["artist"].asString();
}

void main() {
    std::unique_ptr<JsonData> m_data = new JsonData();
    const sd::string m_config = "catalog.json";
    std::out << "Loading configure file: " << m_config << std::endl;
    m_data.parse(m_config);
    Json::Value const &songs = m_data->getMember("songs");
    for (auto const &song : songs.getMemberNames()) {
    //    std::out << "song: " + << song << std::endl;
        printSongInfo(song);
    }
}
