# Contenido de CMakeLists.txt
cmake_minimum_required(VERSION 3.10)

project(PrimesSDL2)

set(CMAKE_PREFIX_PATH "/usr/lib/x86_64-linux-gnu")

find_library(JSONCPP_LIBRARIES NAMES jsoncpp PATHS /usr/lib/x86_64-linux-gnu)
find_path(JSONCPP_INCLUDE_DIRS json/json.h PATHS /usr/include/jsoncpp)

find_package(SDL2 REQUIRED)
find_package(jsoncpp REQUIRED)

message(STATUS "JSONCPP_LIBRARIES = ${JSONCPP_LIBRARIES}")
message(STATUS "JSONCPP_INCLUDE_DIRS = ${JSONCPP_INCLUDE_DIRS}")

link_directories(/usr/lib/x86_64-linux-gnu)

include_directories(${JSONCPP_INCLUDE_DIRS})

add_executable(output_file
               src/main.cpp
               src/json_handler.cpp
               src/json_handler.h
               src/mapping.cpp
               src/mapping.h
               src/prime_computing.cpp
               src/prime_computing.h)

target_include_directories(output_file PRIVATE ${JSONCPP_INCLUDE_DIRS} ${SDL2_INCLUDE_DIRS})
target_link_libraries(output_file PRIVATE ${JSONCPP_LIBRARIES} ${SDL2_LIBRARIES})