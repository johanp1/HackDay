#find_package(arduinoEvents)
find_library(ARDUINOEVENTS NAMES arduinoEvents HINTS ../../EventProxy)

add_library(mpg-LCD-writer
    lcd_writer.cpp)

target_include_directories(mpg-LCD-writer PUBLIC . ${arduinoEvents_INCLUDE_DIRS})
target_link_libraries(mpg-LCD-writer arduinoEvents)
