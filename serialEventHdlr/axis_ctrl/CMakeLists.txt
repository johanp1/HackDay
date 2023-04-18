cmake_minimum_required(VERSION 3.6)
project(AxisCtrl CXX)

enable_language(CXX)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_BUILD_TYPE Debug)

add_subdirectory(src)

option(COMPILE_TESTS "Compile the tests" OFF)
if (COMPILE_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif(COMPILE_TESTS)
