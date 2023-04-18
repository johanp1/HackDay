
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/bf0701daa9f5b30e5882e2f8f9a5280bcba87e77.zip
)
FetchContent_MakeAvailable(googletest)

set(TEST_SOURCE
  axis_ctrl_tests.cpp
  main.cpp)

add_executable(axisCtrlTests ${TEST_SOURCE})
target_include_directories(axisCtrlTests PUBLIC . ../src)
target_link_libraries(axisCtrlTests axisCtrl gtest_main gmock_main)

include(GoogleTest)
gtest_discover_tests(axisCtrlTests)
