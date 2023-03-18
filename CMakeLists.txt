cmake_minimum_required(VERSION 3.0.0)
project(tcp_ip VERSION 0.1.0)

# 设置 c++版本
set(CMAKE_CXX_STANDARD 20)

include(CTest)
enable_testing()

#aux_source_directory(src SRC)
#aux_source_directory(include INCLUDE)

# 将 当前目录下的源文件保存到 DIR_SRCS
# aux_source_directory(. DIR_SRCS)

add_executable(tcp_ip main.cpp chapter_5/echo_server_5.c chapter_5/echo_client_5.c chapter_5/op_client.c
        chapter_5/op_server.c chapter_6/udp_server.c chapter_6/udp_client.c chapter_7/file_server.c chapter_7/file_client.c chapter_9/gethostbyname.c chapter_10/wait.c)

set(CPACK_PROJECT_NAME tcp_ip)
set(CPACK_PROJECT_VERSION 0.1.0)
include(CPack)

