cmake_minimum_required(VERSION 3.26)
project(uint_192
        LANGUAGES CXX
        VERSION 1
        DESCRIPTION "Simple uint192 implementation")
set(CMAKE_CXX_STANDARD 23)
SET(CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/cmake)
Include(FetchContent)

add_subdirectory(uint_192_lib)
