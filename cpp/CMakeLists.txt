cmake_minimum_required(VERSION 3.20)
project(cpp)

set(CMAKE_CXX_STANDARD 14)

if (CMAKE_BUILD_TYPE STREQUAL "Release")
    add_compile_definitions(NDEBUG)
endif()

include_directories(${PROJECT_SOURCE_DIR})

# add demo test algorithm
file(GLOB test_alg_source_files "${PROJECT_SOURCE_DIR}/demo/test_alg/*.cpp")
foreach (source_file ${test_alg_source_files})
    get_filename_component(target_name ${source_file} NAME_WE)
    add_executable(${target_name} ${source_file})
endforeach ()

# search all util source files
file(GLOB util_sources "${PROJECT_SOURCE_DIR}/util/*.cc")

add_executable(varint demo/varint.cc)
add_executable(dynamic_array demo/dynamic_array.cc)

add_executable(skiplist_test structure/skiplist_test.cc structure/skiplist.cc ${util_sources})