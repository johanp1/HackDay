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
   MOCK_METHOD(void, SetStepsPerSec, (unsigned int steps_per_sec), (override));
   //void SetUseRamping(bool use_ramping);
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
   ASSERT_TRUE(ac.GetPosition() == 0.0f);   
}

TEST(AxisCtrlTestGroup, test_set_speed)
{
   NiceMock<MockStepGen> mockStepGen(0,0,0);
   AxisCtrl ac(mockStepGen);

   EXPECT_CALL(mockStepGen, SetStepsPerSec(2));
   ac.SetSpeed(2);
}

TEST(AxisCtrlTestGroup, test_set_rel_pos_no_scale)
{
   NiceMock<MockStepGen> mockStepGen(0,0,0);
   AxisCtrl ac(mockStepGen);

   EXPECT_CALL(mockStepGen, Step(2u)).Times(3);

   ac.SetRelativePosition(2);
   ASSERT_TRUE(ac.GetPosition() == 2.0f);

   ac.SetRelativePosition(2);
   ASSERT_TRUE(ac.GetPosition() == 4.0f);

   ac.SetRelativePosition(-2);
   ASSERT_TRUE(ac.GetPosition() == 2.0f);
}

TEST(AxisCtrlTestGroup, test_set_abs_pos_no_scale)
{
   NiceMock<MockStepGen> mockStepGen(0,0,0);
   AxisCtrl ac(mockStepGen);

   EXPECT_CALL(mockStepGen, Step(2));
   EXPECT_CALL(mockStepGen, Step(4));
   //EXPECT_CALL(mockStepGen, Step(2));

   ac.SetAbsolutPosition(2);
   ASSERT_TRUE(ac.GetPosition() == 2.0f);

   // this request shall not end up in any call to stepGen.Step...
   ac.SetAbsolutPosition(2);
   ASSERT_TRUE(ac.GetPosition() == 2.0f);

   ac.SetAbsolutPosition(-2);
   ASSERT_TRUE(ac.GetPosition() == -2.0f);
}

TEST(AxisCtrlTestGroup, test_set_scale)
{
   NiceMock<MockStepGen> mockStepGen(0,0,0);
   AxisCtrl ac(mockStepGen);

   ac.SetScale(1600.0f/360.0f); // steps/unit (degrees)
   EXPECT_CALL(mockStepGen, SetStepsPerSec((20*1600)/360));
   ac.SetSpeed(20); //
}

}