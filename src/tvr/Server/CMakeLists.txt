tvr_setup_lib_vars(Server)

set(API
    "${HEADER_LOCATION}/Server.h"
    "${HEADER_LOCATION}/ServerPtr.h"
    "${HEADER_LOCATION}/ServerImpl.h"
    "${HEADER_LOCATION}/ConfigureServer.h"
    "${HEADER_LOCATION}/ConfigureServerFromFile.h"
    "${HEADER_LOCATION}/Connection.h"
    "${HEADER_LOCATION}/ConnectionPtr.h"
    "${HEADER_LOCATION}/Verbosity.h")

set(SOURCE
    Server.cpp
    ServerImpl.cpp
    ConfigureServer.cpp)

tvr_add_library()

set_target_properties(${LIBNAME_FULL} PROPERTIES
    VERSION ${TVR_VERSION}
    SOVERSION 0
    INTERFACE_tvrcore_MAJOR_VERSION 0)

set_property(TARGET ${LIBNAME_FULL} APPEND PROPERTY
    COMPATIBLE_INTERFACE_STRING tvrcore_MAJOR_VERSION)

target_include_directories(${LIBNAME_FULL}
    PUBLIC
    $<BUILD_INTERFACE:${Boost_INCLUDE_DIRS}>)

target_compile_options(${LIBNAME_FULLl}
    PUBLIC)

target_link_libraries(${LIBNAME_FULL}
    PUBLIC
    PRIVATE
    tvrConnection
    tvrCommon
    tvrUtil
    boost_filesystem
    JsonCpp::JsonCpp)
