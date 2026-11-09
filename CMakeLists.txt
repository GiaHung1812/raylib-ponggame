cmake_minimum_required(VERSION 3.20)
project(PongGame LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(RAYLIB_ROOT "" CACHE PATH "Path to a raylib source directory")

if (RAYLIB_ROOT)
    add_subdirectory(${RAYLIB_ROOT} raylib)
else()
    find_package(raylib 4.5 CONFIG REQUIRED)
endif()

add_executable(PongGame
    src/main.cpp
    src/Game.cpp
    src/Ball.cpp
    src/Paddle.cpp
)

target_link_libraries(PongGame PRIVATE raylib)
