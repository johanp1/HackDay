
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

set(TEST_SOURCE
  arduino_mock_tests.cpp)

add_executable(arduinoMock_test ${TEST_SOURCE})
target_include_directories(arduinoMock_test PUBLIC .)
target_link_libraries(arduinoMock_test arduinoMock gtest_main)

include(GoogleTest)
gtest_discover_tests(arduinoMock_test)
