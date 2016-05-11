tvr_setup_lib_vars(Connection)

set(API
    "${HEADER_LOCATION}/Connection.h"
    "${HEADER_LOCATOIN}/ConnectionPtr.h"
    "${HEADER_LOCATION}/VrpnBasedConnection.h"
    "${HEADER_LOCATION}/SharedPtr.h")

set(SOURCE
    Connection.cpp
    VrpnBasedConnection.cpp)

tvr_add_library()

set_target_properties(${LIBNAME_FULL} PROPERTIES
    VERSION ${TVR_VERSION}
    INTERFACE_tvrcore_MAJOR_VERSION 0)

set_property(TARGET ${LIBNAME_FULL} APPEND PROPERTY
    COMPATIBLE_INTERFACE_STRING tvrcore_MAJOR_VERSION)

target_include_directories(${LIBNAME_FULL})

target_compile_options(${LIBNAME_FULL}
    PUBLIC
    ${TVR_CXX11_FLAGS})

target_link_libraries(${LIBNAME_FULL}
    PUBLIC
    PRIVATE
    tvrUtil
    tvrCommon)


