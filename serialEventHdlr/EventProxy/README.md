# SerialEvents

This repository contains an event-generator/serializer/de-serializer for Ardiono
![Serial Events](serial_event.drawio.svg)

## Build
The implementation is done i C++ and the build chain uses CMake.
Use the steps below to build:

    mkdir build
    cd build
    cmake ..
    make all -j

## Unit Tests
The project includes a set of unit tests that use the [GoogleTest](https://github.com/google/googletest)
test framework.

To build the unit tests, set `COMPILE_TESTS=ON` when calling CMake.
Use the steps below to build and run the test:

    mkdir build
    cd build
    cmake -DCOMPILE_TESTS=ON ..
    make all test -j
