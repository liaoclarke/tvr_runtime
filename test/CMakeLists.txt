cmake_minimum_required (VERSION 2.6)
project (Parser)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

include(LibFindMacros)

message("----------- trying to find Jsoncpp and Boost -------------")
find_package(JsonCpp)
include(BoostTargets)

if(JsonCpp_FOUND)
    message("INFO: we found LibJsoncpp on your pc.")
    message(JsonCpp_FOUND = ${JsonCpp_FOUND})
    message(JsonCpp_INCLUDE_DIR = ${JsonCpp_INCLUDE_DIR}) 
    message(JsonCpp_LIBRARY = ${JsonCpp_LIBRARY})
else(JsonCpp_FOUND)
    message("WARNING: we couldn't find LibJsoncpp on your pc. DLC is disabled.")
endif(JsonCpp_FOUND)

if (Boost_FOUND)
    message("INFO: we found Boost on your pc.")
    message(Boost_FOUND = ${Boost_FOUND})
    message(Boost_INCLUDE_DIR = ${Boost_INCLUDE_DIR})
    message(Boost_LIBRARIES = ${Boost_LIBRARIES})
else(Boost_FOUND)
    message("WARNING: we couldn't find Boost on your pc. DLC is disabled.")
endif(Boost_FOUND)

#set(LIBS ${Jsoncpp_LIBRARY})

# Set the include dir variables and the libraries and let libfind_process do the rest.
# NOTE: Singular variables for this library, plural for libraries this this lib depends on.
set(JsonCpp_PROCESS_INCLUDES JsonCpp_INCLUDE_DIR)
set(JsonCpp_PROCESS_LIBS JsonCpp_LIBRARY)

# add the executable
add_executable(boosttest boosttest.cpp)
target_include_directories(boosttest PUBLIC $<BUILD_INTERFACE:${JsonCpp_INCLUDE_DIR}>)
target_include_directories(boosttest PUBLIC $<BUILD_INTERFACE:${Boost_INCLUDE_DIR}>)
target_link_libraries(boosttest ${JsonCpp_LIBRARY})
target_link_libraries(boosttest ${Boost_LIBRARIES} )
#FIND_PACKAGE( Boost 1.40 COMPONENTS program_options REQUIRED )

