
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
FetchContent_MakeAvailable(googletest)

set(TEST_SOURCE
  controller_tests.cpp
  extruder_tests.cpp
  main.cpp)

add_executable(extruderTempCtrl_test ${TEST_SOURCE})
target_include_directories(extruderTempCtrl_test PUBLIC . ../src)
target_link_libraries(extruderTempCtrl_test extruderTempCtrl gtest_main)

include(GoogleTest)
gtest_discover_tests(extruderTempCtrl_test)
