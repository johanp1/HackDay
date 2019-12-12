#include "CommandLineTestRunner.h"
#include "TestHarness_c.h"


TEST_GROUP_C_WRAPPER(DriverTestGroup)
{
//    TEST_GROUP_C_SETUP_WRAPPER(DriverTestGroup); /** optional */
//    TEST_GROUP_C_TEARDOWN_WRAPPER(DriverTestGroup); /** optional */
};

TEST_C_WRAPPER(DriverTestGroup, openBus);
TEST_C_WRAPPER(DriverTestGroup, openCloseBus);
TEST_C_WRAPPER(DriverTestGroup, sendMsg)

int main(int ac, char** av)
{
    return RUN_ALL_TESTS(ac, av);
}
