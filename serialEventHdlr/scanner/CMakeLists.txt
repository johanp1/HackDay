cmake_minimum_required(VERSION 3.6)
project(scanner CXX)

enable_language(CXX)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_BUILD_TYPE Debug)

# Force the .ino file to be treated as C++
set_source_files_properties(scanner.ino
    PROPERTIES LANGUAGE CXX
)
set_source_files_properties(scanner.ino
    PROPERTIES COMPILE_FLAGS "-x c++"
)

add_library(scanner
    scanner.ino
    ../step_gen/src/step_gen.cpp
)
  
target_include_directories(scanner PUBLIC . ../step_gen/src)

add_subdirectory(../EventProxy/src build)

target_link_libraries(scanner arduinoEvents)

option(COMPILE_TESTS "Compile the tests" OFF)
if (COMPILE_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif(COMPILE_TESTS)
