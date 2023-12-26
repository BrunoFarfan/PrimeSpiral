# Contenido de CMakeLists.txt
cmake_minimum_required(VERSION 3.10)

project(PrimesSDL2)

find_package(SDL2 REQUIRED)

add_executable(output_file src/main.cpp)

target_include_directories(output_file PRIVATE ${SDL2_INCLUDE_DIRS})
target_link_libraries(output_file PRIVATE ${SDL2_LIBRARIES})
