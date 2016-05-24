cmake_minimum_required (VERSION 2.6)
project (tvr_client_server_connection)

set(TVR_INCLUDE_DIR "E:/TencentVR/tvr_runtime/include")

configure_file("${CMAKE_CURRENT_SOURCE_DIR}/Export.h.in" tvr/ClientKit/Export.h @ONLY NEWLINE_STYLE LF)

# add the executable
add_executable(tvr_client_server_connection tvr_client_server_connection.cpp ClientMainloopThread.h)
target_include_directories(tvr_client_server_connection 
    PUBLIC 
    "${CMAKE_BINARY_DIR}"
    ${TVR_INCLUDE_DIR})
target_link_libraries(tvr_client_server_connection tvrClientKit tvrClient)
