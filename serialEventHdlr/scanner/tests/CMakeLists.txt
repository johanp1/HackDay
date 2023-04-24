
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/bf0701daa9f5b30e5882e2f8f9a5280bcba87e77.zip
)
FetchContent_MakeAvailable(googletest)

add_executable(scanner_test scanner_tests.cpp main.cpp)
target_include_directories(scanner_test PUBLIC . ..)
target_link_libraries(scanner_test scanner gtest_main gmock_main)

add_executable(stepGenTests step_gen_tests.cpp main.cpp)
target_link_libraries(stepGenTests stepGen gtest_main gmock_main)

add_executable(axisCtrlTests axis_ctrl_tests.cpp main.cpp)
target_link_libraries(axisCtrlTests axisCtrl gtest_main gmock_main)

include(GoogleTest)
gtest_discover_tests(stepGenTests)
gtest_discover_tests(axisCtrlTests)
gtest_discover_tests(scanner_test)


