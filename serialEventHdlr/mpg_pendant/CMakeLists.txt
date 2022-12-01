cmake_minimum_required(VERSION 3.6)
project(mpgPendant CXX)

enable_language(CXX)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_BUILD_TYPE Debug)

# Force the .ino file to be treated as C++
set_source_files_properties(mpg_pendant.ino
    PROPERTIES LANGUAGE CXX
)
set_source_files_properties(mpg_pendant.ino
    PROPERTIES COMPILE_FLAGS "-x c++"
)

add_library(mpgPendant
  mpg_pendant.ino)
  
target_include_directories(mpgPendant PUBLIC . )

add_subdirectory(../EventProxy/src build)
target_link_libraries(mpgPendant arduinoEvents)

option(COMPILE_TESTS "Compile the tests" OFF)
if (COMPILE_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif(COMPILE_TESTS)
