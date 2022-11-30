
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/bf0701daa9f5b30e5882e2f8f9a5280bcba87e77.zip
)
FetchContent_MakeAvailable(googletest)

set(TEST_SOURCE
  mpg_tests.cpp
  main.cpp)

add_executable(mpgPendant_test ${TEST_SOURCE})
target_include_directories(mpgPendant_test PUBLIC . ..)
target_link_libraries(mpgPendant_test mpgPendant gtest_main gmock_main)

include(GoogleTest)
gtest_discover_tests(mpgPendant_test)
