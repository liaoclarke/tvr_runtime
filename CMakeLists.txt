cmake_minimum_required (VERSION 2.6)
project (tvrcore)

set(CMAKE_INSTALL_LIBDIR "${CMAKE_INSTALL_PREFIX}/lib")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/test/cmake/")

include(LibFindMacros)

################################
# Boost
################################
ADD_DEFINITIONS(-DBOOST_LOG_DYN_LINK)
ADD_DEFINITIONS(-DBoost_USE_STATIC_LIBS=ON)
#set_property(GLOBAL PROPERTY FIND_LIBRARY_USE_LIB64_PATHS ON)
set(Boost_INCLUDE_DIR "C:/Boost/include/boost-1_60")
set(Boost_LIBRARY_DIR "C:/Boost/lib")
include_directories( ${Boost_INCLUDE_DIR} )
link_directories(${Boost_LIBRARY_DIR})
set(NEED_BOOST_PROGRAM_OPTIONS ON)
set(NEED_BOOST_FILESYSTEM ON)
set(NEED_BOOST_LOCALE ON)
set(NEED_BOOST_THREAD ON)

message("----------- trying to find Jsoncpp & Boost & VRPN -------------")
find_package(JsonCpp)
find_package(VRPN)
include(BoostTargets)
include(EnableExtraCompilerWarnings)
include(Version)

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

if (VRPN_FOUND)
    message("INFO: we found VRPN on your pc.")
    message(VRPN_FOUND = ${VRPN_FOUND})
    message(VRPN_INCLUDE_DIR = ${VRPN_INCLUDE_DIR})
    message(VRPN_LIBRARIES = ${VRPN_LIBRARIES})
else(VRPN_FOUND)
    message("WARNING: we couldn't find VRPN on your pc. DLC is disabled.")
endif(VRPN_FOUND)

# Set the include dir variables and the libraries and let libfind_process do the rest.
# NOTE: Singular variables for this library, plural for libraries this this lib depends on.
set(JsonCpp_PROCESS_INCLUDES JsonCpp_INCLUDE_DIR)
set(JsonCpp_PROCESS_LIBS JsonCpp_LIBRARY)

set(HEADER_BASE "${CMAKE_CURRENT_SOURCE_DIR}/include")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/src/tvr")
message(HEADER_BASE = ${HEADER_BASE})
message(VRPN_INCLUDE_DIR = ${VRPN_INCLUDE_DIR})

# add the executable
add_executable(tvr_client tvr_client.cpp)
target_include_directories(tvr_client PUBLIC ${Boost_INCLUDE_DIR})
target_link_libraries(tvr_client ${VRPN_LIBRARIES})
target_link_libraries(tvr_client ${Boost_LIBRARIES})
target_link_libraries(tvr_client ${JsonCpp_LIBRARY})
target_link_libraries(tvr_client tvrClientKit tvrClient tvrCommon tvrConnection boost_thread)

add_executable(tvr_reader tvr_reader.cpp)
target_include_directories(tvr_reader PUBLIC ${Boost_INCLUDE_DIR})
target_link_libraries(tvr_reader ${VRPN_LIBRARIES})
target_link_libraries(tvr_reader ${Boost_LIBRARIES})
target_link_libraries(tvr_reader ${JsonCpp_LIBRARY})
target_link_libraries(tvr_reader tvrClientKit tvrClient tvrCommon tvrConnection boost_thread)

add_executable(tvr_server tvr_server.cpp)
target_include_directories(tvr_server PUBLIC $<BUILD_INTERFACE:${HEADER_BASE}>)
target_include_directories(tvr_server PUBLIC $<BUILD_INTERFACE:${VRPN_INCLUDE_DIR}>)
target_include_directories(tvr_server PUBLIC $<BUILD_INTERFACE:${JsonCpp_INCLUDE_DIR}>)
target_include_directories(tvr_server PUBLIC $<BUILD_INTERFACE:${Boost_INCLUDE_DIR}>)
target_link_libraries(tvr_server ${VRPN_LIBRARIES})
target_link_libraries(tvr_server ${JsonCpp_LIBRARY})
target_link_libraries(tvr_server ${Boost_LIBRARIES})
target_link_libraries(tvr_server tvrCommon tvrServer tvrConnection)
