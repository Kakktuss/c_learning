cmake_minimum_required(VERSION 3.21)
project(snake C)

set(CMAKE_C_STANDARD 99)

include(DownloadProject.cmake)

download_project(PROJ uv
                 GIT_REPOSITORY https://github.com/libuv/libuv.git
                 GIT_TAG     master)

add_subdirectory(${uv_SOURCE_DIR} ${uv_BINARY_DIR})
add_executable(snake main.c src/world/world.h src/world/world.c src/loop/utility.h src/loop/utility.c src/entity/entity.c src/entity/entity.h src/world/world_event.h src/world/world_event.c src/snake/snake_event.h src/snake/snake_event.c src/snake/snake.h src/snake/snake.c src/entity/utility.h)
target_link_libraries(snake uv)