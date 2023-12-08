cmake_minimum_required(VERSION 3.26)
project(uint_192_lib
        LANGUAGES CXX
        VERSION 1
        DESCRIPTION "Simple uint194 implementation")

add_library(uint_192_lib INTERFACE src/uint_192.hpp)
set_target_properties(uint_192_lib PROPERTIES LINKER_LANGUAGE CXX)

target_include_directories(uint_192_lib INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/src")

add_subdirectory(tests)

add_executable(main main.cpp)
