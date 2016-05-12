tvr_setup_lib_vars(Connection)

#set(API
#    "${HEADER_LOCATION}/Connection.h"
#    "${HEADER_LOCATOIN}/ConnectionPtr.h"
#    "${HEADER_LOCATION}/VrpnBasedConnection.h"
#    "${HEADER_LOCATION}/SharedPtr.h")

set(SOURCE
    Connection.cpp
    VrpnBasedConnection.cpp)

tvr_add_library()

message("LIBNAME_FULL" = ${LIBNAME_FULL})
message("TVR_VERSION" = ${TVR_VERSION})
message("INTERFACE_tvrcore_MAJOR_VERSION" = ${INTERFACE_tvrcore_MAJOR_VERSION})

set_target_properties(${LIBNAME_FULL} PROPERTIES 
    VERSION ${TVR_VERSION} 
    SOVERSION 0)

set_property(TARGET ${LIBNAME_FULL} APPEND PROPERTY
    COMPATIBLE_INTERFACE_STRING tvrcore_MAJOR_VERSION)

target_include_directories(${LIBNAME_FULL}
    PUBLIC
    $<BUILD_INTERFACE:${VRPN_INCLUDE_DIR}>
    $<BUILD_INTERFACE:${Boost_INCLUDE_DIRS}>)

target_compile_options(${LIBNAME_FULL}
    PUBLIC)

target_link_libraries(${LIBNAME_FULL}
    PUBLIC
    PRIVATE
    tvrCommon)


