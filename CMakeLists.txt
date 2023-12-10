cmake_minimum_required(VERSION 3.26)
project(my_uint192 LANGUAGES CXX VERSION 0.0.1)
set(CMAKE_CXX_STANDARD 23)
SET(CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/cmake)
Include(FetchContent)

add_subdirectory(uint_192_lib)
