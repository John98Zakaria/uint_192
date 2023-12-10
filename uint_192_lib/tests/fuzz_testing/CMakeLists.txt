cmake_minimum_required(VERSION 3.26)


# <----------------------- Register all catch2 tests ------------------------------------>
find_package(GMP REQUIRED)

file(GLOB test_executables LIST_DIRECTORIES false RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} fuzz_test_*.cpp)
foreach (test_executable ${test_executables})
    add_executable(fuzz_${test_executable} ${test_executable})
    target_link_libraries(fuzz_${test_executable} PRIVATE Catch2::Catch2WithMain uint_192_lib GMP::STATIC)
    catch_discover_tests(fuzz_${test_executable})

endforeach ()
