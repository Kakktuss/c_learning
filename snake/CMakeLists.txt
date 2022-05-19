cmake_minimum_required(VERSION 3.21)
project(snake C)

set(CMAKE_C_STANDARD 99)

include(DownloadProject.cmake)

download_project(PROJ uv
                 GIT_REPOSITORY https://github.com/libuv/libuv.git
                 GIT_TAG     master)

add_subdirectory(${uv_SOURCE_DIR} ${uv_BINARY_DIR})
add_executable(snake main.c)
target_link_libraries(snake uv)