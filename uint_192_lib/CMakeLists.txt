cmake_minimum_required(VERSION 3.26)

add_library(uint_192_lib INTERFACE src/uint_192.hpp)
set_target_properties(uint_192_lib PROPERTIES LINKER_LANGUAGE CXX)
include(CompilerWarnings)
set_compiler_flags(uint_192_lib "on" "" "" "")
target_include_directories(uint_192_lib INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/src")

add_subdirectory(tests)
