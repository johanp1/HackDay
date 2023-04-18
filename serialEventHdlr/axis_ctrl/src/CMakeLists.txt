#include(FetchContent)
#FetchContent_Declare(
#  arduinoMock
#  GIT_REPOSITORY https://github.com/johanp1/arduino-mock.git)
#FetchContent_MakeAvailable(arduinoMock)

add_library(axisCtrl
    axis_ctrl.cpp)

target_include_directories(axisCtrl PUBLIC . ../../step_gen)
target_link_libraries(axisCtrl)
