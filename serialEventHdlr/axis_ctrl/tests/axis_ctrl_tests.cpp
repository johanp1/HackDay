#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "axis_ctrl.h"
#include <memory>
#include <iostream>
#include <sstream>
#include "step_gen.h"

namespace {

using ::testing::_;
using ::testing::NiceMock;

class MockStepGen : public StepGen
{
   public:
   MockStepGen(Pin pin, milli_sec t_on, milli_sec t_off){};
   ~MockStepGen(){};
   MOCK_METHOD(void, Update, (), (override));
   MOCK_METHOD(stepRetVal, Step, (unsigned int steps), (override));
};

class AxisCtrlTestFixture : public testing::Test 
{
   protected:
   //std::unique_ptr<MockStepGen> mockStepGen;
   //std::unique_ptr<AxisCtrl> axisCtrl;
   void SetUp()
   {
      //mockStepGen = std::make_unique<MockStepGen>();
      //axisCtrl = std::make_unique<AxisCtrl>(*mockStepGen);
   }
   
   void TearDown()
   {
      //mockStepGen.reset();
      //axisCtrl.reset();
   }
};

TEST(AxisCtrlTestGroup, test_init)
{
   MockStepGen mockStepGen(0,0,0);
   AxisCtrl ac(mockStepGen);
   ASSERT_TRUE(true);   
}

}