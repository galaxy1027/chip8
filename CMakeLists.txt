cmake_minimum_required(VERSION 3.16)
project(chip8 C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(external/raylib/)

file(GLOB CHIP8_SOURCES src/*.c)
add_executable(chip8 ${CHIP8_SOURCES})

target_include_directories(chip8 PRIVATE include)
target_link_libraries(chip8 raylib)
