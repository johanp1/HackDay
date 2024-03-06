cmake_minimum_required(VERSION 3.6)
project(mpgPendantLathe CXX)

enable_language(CXX)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_BUILD_TYPE Debug)

# Force the .ino file to be treated as C++
set_source_files_properties(mpg_pendant_lathe_mk2.ino
    PROPERTIES LANGUAGE CXX
)
set_source_files_properties(mpg_pendant_lathe_mk2.ino
    PROPERTIES COMPILE_FLAGS "-x c++"
)

add_library(mpgPendantLathe
    mpg_pendant_lathe_mk2.ino    
)
  
target_include_directories(mpgPendantLathe PUBLIC . ./tests)

add_subdirectory(../EventProxy/src build)

target_link_libraries(mpgPendantLathe arduinoEvents)

option(COMPILE_TESTS "Compile the tests" OFF)
if (COMPILE_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif(COMPILE_TESTS)
