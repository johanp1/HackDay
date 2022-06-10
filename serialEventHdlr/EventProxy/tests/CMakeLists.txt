
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/bf0701daa9f5b30e5882e2f8f9a5280bcba87e77.zip
)
FetchContent_MakeAvailable(googletest)

set(TEST_SOURCE
  buffer_tests.cpp
  button_tests.cpp
  encoder_tests.cpp
  event_parser_tests.cpp
  receiver_tests.cpp
  selector_tests.cpp
  sender_tests.cpp
  lcd_writer_tests.cpp
  event_generator_tests.cpp
  main.cpp)

add_executable(arduinoEvents_test ${TEST_SOURCE})
target_include_directories(arduinoEvents_test PUBLIC . ../src)
target_link_libraries(arduinoEvents_test arduinoEvents gtest_main gmock_main)

include(GoogleTest)
gtest_discover_tests(arduinoEvents_test)
