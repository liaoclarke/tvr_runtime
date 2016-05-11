tvr_setup_lib_vars(Common)
include(CheckIncludeFile)
include(CheckCSourceCompiles)
check_include_file(intrin.h TVR_HAVE_INTRIN_H)
check_include_file(byteswap.h TVR_HAVE_BYTESWAP_H)
check_c_source_compiles("#include <intrin.h>\nint main() {return _byteswap_ushort(0x1234) + _byteswap_ulong(0x12345678) + (int)_byteswap_uint64(0x0123456789abcdef);}" TVR_HAVE_WORKING_MS_BYTESWAPS)
check_c_source_compiles("#include <byteswap.h>\nint main() {return bswap16(0x1234);}" TVR_HAVE_WORKING_BSWAP)
check_c_source_compiles("#include <byteswap.h>\nint main() {return bswap_16(0x1234);}" TVR_HAVE_WORKING_BSWAP_UNDERSCORE)
check_c_source_compiles("#include <byteswap.h>\nint main() {return __bswap_16(0x1234);}" TVR_HAVE_WORKING_UNDERSCORES_BSWAP)
configure_file(ConfigByteSwapping.h.cmake_in "${CMAKE_CURRENT_BINARY_DIR}/ConfigByteSwapping.h")

set(API
    "${HEADER_LOCATION}/CommonComponent.h"
    "${HEADER_LOCATION}/SystemComponent.h"
    "${HEADER_LOCATION}/DeviceComponentPtr.h")

set(SOURCE
    BaseDevice.cpp
    CommonComponent.cpp
    SystemComponent.cpp
    DeviceComponent.cpp
    DeviceWrapper.cpp
    NetworkingSupport.cpp
    CreateDevice.cpp)

tvr_add_libraray()

set_target_properties(${LIBNAME_FULL} PROPERTIES
    VERSION ${TVR_VERSION}
    INTERFACE_tvrcore_MAJOR_VERSION 0)

set_property(TARGET ${LIBNAME_FULL} APPEND PROPERTY
    COMPATIBLE_INTERFACE_STRING tvrcore_MAJOR_VERSION)

target_include_directories(${LIBNAME_FULL}
    PUBLIC
    $<BUILD_INTERFACE:${Boost_INCLUDE_DIRS}>
    PRIVATE)

target_link_libraries(${LIBNAME_FULL}
    PUBLIC
    PRIVATE
    JsonCpp::JsonCpp)