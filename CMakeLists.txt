cmake_minimum_required(VERSION 2.6)
project(mongo C CXX)

set(CXX_FLAGS
        -g
        -D_FILE_OFFSET_BITS=64
        -Wall # show all errror
        -Werror # Make all warnings into errors.
        -Wextra # This enables some extra warning flags that are not enabled by -Wall
        -Wconversion # Warn for implicit conversions that may alter a value
        -Wunused-parameter
        -std=c++11
)

find_package(Protobuf)
find_package(ZLIB)

include_directories(src/base)
include_directories(src/net)

add_subdirectory(src/base)
add_subdirectory(src/game)
add_subdirectory(src/net)
add_subdirectory(examples)