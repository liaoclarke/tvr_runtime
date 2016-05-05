#include <iostream>
#include <fstream>
#include <json/reader.h>
#include <json/value.h>

void printSongInfo(Json::Value song){
    std::clog<<"\n-----------printing a song-------------\n";
    std::clog<<"Name=" << song["name"].asString();
    std::clog<<"Artist=" << song["artist"].asString();
}

int main(){

    std::ifstream catalogFile("catalog.json");

    Json::Value root;   // will contains the root value after parsing.
    Json::Reader reader;
    bool parsingSuccessful = reader.parse( catalogFile, root );
    if ( !parsingSuccessful ){
        // report to the user the failure and their locations in the document.
        std::cout  << "Failed to parse configuration\n"
                   << reader.getFormattedErrorMessages();
        return 1;
    }

    //parsing songs
    Json::Value songs = root["songs"];
    for ( int index = 0; index < songs.size(); ++index ){  // Iterates over the sequence elements.
        printSongInfo(songs[index]);
    }
    return 0;
}
