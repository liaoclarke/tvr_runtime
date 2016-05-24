tvr_setup_lib_vars(Client)

set(API
    "${HEADER_LOCATION}/CreateContext.h")

set(SOURCE
    VRPNConnectionCollection.cpp
    CreateContext.cpp
    PureClientContext.cpp)

tvr_add_library()

message("LIBNAME_FULL" = ${LIBNAME_FULL})
message("TVR_VERSION" = ${TVR_VERSION})
message("CURRENT_BINARY_DIR" = ${CMAKE_BINARY_DIR})
message("INTERFACE_tvrcore_MAJOR_VERSION" = ${INTERFACE_tvrcore_MAJOR_VERSION})

set_target_properties(${LIBNAME_FULL} PROPERTIES
    VERSION ${TVR_VERSION}
    SOVERSION 0)

set_property(TARGET ${LIBNAME_FULL} APPEND PROPERTY
    COMPATIBLE_INTERFACE_STRING tvrcore_MAJOR_VERSION)

target_include_directories(${LIBNAME_FULL}
    PUBLIC
    "${CMAKE_BINARY_DIR}/src"
    ${Boost_INCLUDE_DIRS})

target_link_libraries(${LIBNAME_FULL}
    PRIVATE
    tvrCommon
    tvrConnection
    ${VRPN_LIBRARIES}
    )
