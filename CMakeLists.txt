cmake_minimum_required(VERSION 3.15)
project(mongo)

set(CMAKE_CXX_STANDARD 11)

include_directories(src/base)

add_subdirectory(src/base)
add_subdirectory(src/game)
add_subdirectory(src/net)