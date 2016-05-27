tvr_setup_lib_vars(Util)

include(CheckStructHasMember)
include(CheckCSourceCompiles)

check_struct_has_member("struct timeval" tv_sec sys/time.h TVR_HAVE_STRUCT_TIMEVAL_IN_SYS_TIME_H LANGUAGE C)
check_struct_has_member("struct timeval" tv_sec winsock2.h TVR_HAVE_STRUCT_TIMEVAL_IN_WINSOCK2_H LANGUAGE C)
configure_file(PlatformConfig.h.in "${CMAKE_CURRENT_BINARY_DIR}/PlatformConfig.h")

set(SOURCE
    TimeValueC.cpp
    MessageKeys.cpp)

tvr_add_library()

set_target_properties(${LIBNAME_FULL} PROPERTIES
    VERSION ${TVR_VERSION}
    SOVERSION 0)

set_property(
    TARGET ${LIBNAME_FULL} APPEND PROPERTY
    COMPATIBLE_INTERFACE_STRING tvrcore_MAJOR_VERSION)

target_include_directories(${LIBNAME_FULL}
    PUBLIC
    "${CMAKE_BINARY_DIR}/src"
    ${VRPN_INCLUDE_DIR}
    ${Boost_INCLUDE_DIRS})

target_link_libraries(${LIBNAME_FULL}
    PUBLIC
    PRIVATE)

