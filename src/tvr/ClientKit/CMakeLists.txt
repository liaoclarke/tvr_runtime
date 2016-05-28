tvr_setup_lib_vars(ClientKit)

set(API
    "${HEADER_LOCATION}/ContextC.h")

set(SOURCE
    ParametersC.cpp
    ContextC.cpp)

tvr_add_library()

message("LIBNAME_FULL" = ${LIBNAME_FULL})
message("TVR_VERSION" = ${TVR_VERSION})
message("INTERFACE_tvrcore_MAJOR_VERSION" = ${INTERFACE_tvrcore_MAJOR_VERSION})

set_target_properties(${LIBNAME_FULL} PROPERTIES
    VERSION ${TVR_VERSION}
    SOVERSION 0)

set_property(
    TARGET ${LIBNAME_FULL} APPEND PROPERTY
    COMPATIBLE_INTERFACE_STRING tvrcore_MAJOR_VERSION)

target_include_directories(${LIBNAME_FULL} 
    PUBLIC
    PRIVATE 
    "${CMAKE_BINARY_DIR}/src"
    ${Boost_INCLUDE_DIRS})

target_link_libraries(${LIBNAME_FULL} 
    PUBLIC
    tvrClient
    tvrCommon
    boost_filesystem)
