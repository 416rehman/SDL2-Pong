cmake_minimum_required(VERSION 3.16)
project(cppGameDev)
set(CMAKE_CXX_STANDARD 14)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/modules)
set(SDL2_PATH "SDL2-2.0.18\\x86_64-w64-mingw32")

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})

add_executable(cppGameDev main.cpp game/Game.cpp game/Game.h)

target_link_libraries(cppGameDev ${SDL2_LIBRARY} -static-libstdc++ -static-libgcc -static)