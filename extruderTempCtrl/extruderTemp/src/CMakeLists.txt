
include(FetchContent)
FetchContent_Declare(
  arduinoMock
  GIT_REPOSITORY https://github.com/johanp1/arduino-mock.git)

FetchContent_MakeAvailable(arduinoMock)


add_library(extruderTempCtrl
    controller.cpp
    extruder.cpp
   )

target_include_directories(extruderTempCtrl PUBLIC . ${arduinoMock_SOURCE_DIR})
target_link_libraries(extruderTempCtrl arduinoMock )
