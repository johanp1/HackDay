include(FetchContent)
FetchContent_Declare(
  arduinoMock
  GIT_REPOSITORY https://github.com/johanp1/arduino-mock.git)

FetchContent_MakeAvailable(arduinoMock)

#find_package(arduinoEvents) 
#find_library(ARDUINOEVENTS NAMES arduinoEvents HINTS ../../EventProxy)
add_subdirectory("../../EventProxy/src/"
                 "arduinoEvents_build") # util

add_library(mpg-LCD-writer
    model.cpp
    lcd_writer.cpp)

target_include_directories(mpg-LCD-writer PUBLIC . ../../EventProxy/src ${arduinoMock_SOURCE_DIR})
#target_include_directories(mpg-LCD-writer PUBLIC . ${arduinoEvents_Source_DIR} ${arduinoMock_SOURCE_DIR})
target_link_libraries(mpg-LCD-writer arduinoEvents arduinoMock)
