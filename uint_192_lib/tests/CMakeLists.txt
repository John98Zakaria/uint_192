cmake_minimum_required(VERSION 3.26)

# <----------------------- Download Dependencies ------------------------------------>
FetchContent_Declare(
        catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG v3.4.0 # release-3.4.0
)
FetchContent_MakeAvailable(catch2)
include(CTest)
include(Catch)
list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)

# <----------------------- Register all catch2 tests ------------------------------------>

file(GLOB test_executables LIST_DIRECTORIES false RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} test_*.cpp)
foreach (test_executable ${test_executables})
    add_executable(${test_executable} ${test_executable})
    target_link_libraries(${test_executable} PRIVATE Catch2::Catch2WithMain uint_192_lib)
    catch_discover_tests(${test_executable})

endforeach ()

add_subdirectory(fuzz_testing)
