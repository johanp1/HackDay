
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/bf0701daa9f5b30e5882e2f8f9a5280bcba87e77.zip
)
FetchContent_MakeAvailable(googletest)

set(TEST_SOURCE
  scanner_tests.cpp
  main.cpp)

add_executable(scanner_test ${TEST_SOURCE})
target_include_directories(scanner_test PUBLIC . ..)
target_link_libraries(scanner_test scanner gtest_main gmock_main)

include(GoogleTest)
gtest_discover_tests(scanner_test)
