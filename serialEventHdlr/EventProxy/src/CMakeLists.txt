
include(FetchContent)
FetchContent_Declare(
  arduinoMock
  GIT_REPOSITORY https://github.com/johanp1/arduino-mock.git)

FetchContent_MakeAvailable(arduinoMock)


add_library(arduinoEvents
    buffer.cpp
    button.cpp
    encoder.cpp
    event.cpp
    event_generator.cpp
    event_parser.cpp
    receiver.cpp
    selector.cpp
    sender.cpp)

target_include_directories(arduinoEvents PUBLIC . ${arduinoMock_SOURCE_DIR})
target_link_libraries(arduinoEvents arduinoMock )
