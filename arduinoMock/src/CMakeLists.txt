add_library(arduinoMock
    arduino_stubs.cpp
    PinMock.cpp
    SerialStub.cpp
    String.cpp)
target_include_directories(arduinoMock PUBLIC .)
