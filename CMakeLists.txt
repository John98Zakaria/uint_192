cmake_minimum_required(VERSION 3.26)
project(my_uint192 LANGUAGES CXX VERSION 0.0.1)
set(CMAKE_CXX_STANDARD 23)

Include(FetchContent)

add_subdirectory(uint_192_lib)
