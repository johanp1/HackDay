include(FetchContent)
FetchContent_Declare(
  arduinoMock
  GIT_REPOSITORY https://github.com/johanp1/arduino-mock.git)

FetchContent_MakeAvailable(arduinoMock)

add_library(stepGen
    step_gen.cpp)
target_include_directories(stepGen PUBLIC . ${arduinoMock_SOURCE_DIR})
target_link_libraries(stepGen arduinoMock)

add_library(axisCtrl
    axis_ctrl.cpp)
target_include_directories(stepGen PUBLIC .)
target_link_libraries(axisCtrl stepGen)
