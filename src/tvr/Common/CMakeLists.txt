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

#set(API
#    "${HEADER_LOCATION}/NetworkingSupport.h")

set(SOURCE
    ClientContext.cpp
    RawSenderType.cpp
    BaseDevice.cpp
    CreateDevice.cpp
    DeviceWrapper.cpp
    VrpnGenericServerObject.cpp
    NetworkingSupport.cpp
    AliasProcessor.cpp
    RoutingConstants.cpp
    RoutingKeys.cpp
    ParseAlias.cpp
    PathTree.cpp
    PathNode.cpp
    PathElementTools.cpp
    PathElementTypes.cpp
    PathTreeObserver.cpp
    PathTreeOwner.cpp
    PathTreeSerialization.cpp)

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
    "${CMAKE_BINARY_DIR}/src"
    $<BUILD_INTERFACE:${VRPN_INCLUDE_DIR}>
    $<BUILD_INTERFACE:${Boost_INCLUDE_DIRS}>
    PRIVATE)

target_link_libraries(${LIBNAME_FULL}
    PUBLIC
    PRIVATE
    JsonCpp::JsonCpp)
