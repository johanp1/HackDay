
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/bf0701daa9f5b30e5882e2f8f9a5280bcba87e77.zip
)
FetchContent_MakeAvailable(googletest)

set(TEST_SOURCE
  lcd_writer_tests.cpp
  main.cpp)

add_executable(mpg-LCD-writer_test ${TEST_SOURCE})
target_include_directories(mpg-LCD-writer_test PUBLIC . ../src)
target_link_libraries(mpg-LCD-writer_test mpg-LCD-writer gtest_main gmock_main)

include(GoogleTest)
gtest_discover_tests(mpg-LCD-writer_test)
