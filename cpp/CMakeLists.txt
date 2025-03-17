cmake_minimum_required(VERSION 3.20)
project(cpp)

set(CMAKE_CXX_STANDARD 14)

if (CMAKE_BUILD_TYPE STREQUAL "Release")
    add_compile_definitions(NDEBUG)
endif()

include_directories(${PROJECT_SOURCE_DIR})

add_executable(varint demo/varint.cc)
add_executable(dynamic_array demo/dynamic_array.cc)

add_executable(skiplist_test structure/skiplist_test.cc structure/skiplist.cc)