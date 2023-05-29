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
using ::testing::InSequence;
using ::testing::Return;

class MockStepGen : public StepGen
{
   public:
   MockStepGen(Pin step_pin = 0, Pin dir_pin = 0, milli_sec t_on = 0, milli_sec t_off = 0){};
   ~MockStepGen(){};

   MOCK_METHOD(void, Update, (), (override));
   MOCK_METHOD(StepRetVal, Step, (unsigned int steps), (override));
   MOCK_METHOD(void, SetStepsPerSec, (unsigned int steps_per_sec), (override));
   MOCK_METHOD(void, SetDirection, (Direction d), (override));
   MOCK_METHOD(Direction, GetDirection, (), (override));
};

class AxisCtrlTestFixture : public testing::Test 
{
   protected:
   std::unique_ptr<NiceMock<MockStepGen>> mockStepGen;
   std::unique_ptr<AxisCtrl> axisCtrl;

   void SetUp()
   {
      mockStepGen = std::make_unique<NiceMock<MockStepGen>>();
      axisCtrl = std::make_unique<AxisCtrl>(*mockStepGen);
   }
   
   void TearDown()
   {
      mockStepGen.reset();
      axisCtrl.reset();
   }
};

TEST_F(AxisCtrlTestFixture, test_init)
{
   ASSERT_TRUE(axisCtrl->GetPosition() == 0.0f);   
}

TEST_F(AxisCtrlTestFixture, test_set_speed)
{
   EXPECT_CALL(*mockStepGen, SetStepsPerSec(2));
   axisCtrl->SetSpeed(2);
}

TEST_F(AxisCtrlTestFixture, test_set_rel_pos_no_scale)
{
   EXPECT_CALL(*mockStepGen, Step(2u)).Times(3);
   {
      InSequence seq;

      EXPECT_CALL(*mockStepGen, SetDirection(direction_forward));
      EXPECT_CALL(*mockStepGen, GetDirection()).Times(2).WillRepeatedly(Return(direction_forward));

      EXPECT_CALL(*mockStepGen, SetDirection(direction_forward));
      EXPECT_CALL(*mockStepGen, GetDirection()).Times(2).WillRepeatedly(Return(direction_forward));

      EXPECT_CALL(*mockStepGen, SetDirection(direction_reverse));
      EXPECT_CALL(*mockStepGen, GetDirection()).Times(2).WillRepeatedly(Return(direction_reverse));
   }
   
   axisCtrl->SetRelativePosition(2);
   axisCtrl->Update(); // 2 steps generated, will generate 2 stepObserver update calls
   axisCtrl->Update();
   ASSERT_TRUE(axisCtrl->GetPosition() == 2.0f);

   axisCtrl->SetRelativePosition(2);
   axisCtrl->Update();
   axisCtrl->Update();
   ASSERT_TRUE(axisCtrl->GetPosition() == 4.0f);

   axisCtrl->SetRelativePosition(-2);
   axisCtrl->Update();
   axisCtrl->Update();
   ASSERT_TRUE(axisCtrl->GetPosition() == 2.0f);
}

TEST_F(AxisCtrlTestFixture, test_set_abs_pos_no_scale)
{
   EXPECT_CALL(*mockStepGen, Step(2));
   EXPECT_CALL(*mockStepGen, Step(4));
   {
      InSequence seq;

      EXPECT_CALL(*mockStepGen, SetDirection(direction_forward));
      EXPECT_CALL(*mockStepGen, GetDirection()).Times(2).WillRepeatedly(Return(direction_forward));

      EXPECT_CALL(*mockStepGen, SetDirection(direction_reverse));
      EXPECT_CALL(*mockStepGen, GetDirection()).Times(4).WillRepeatedly(Return(direction_reverse));
   }

   axisCtrl->SetAbsolutPosition(2);
   axisCtrl->Update();  // 2 steps generated, will generate 2 stepObserver update calls
   axisCtrl->Update();
   ASSERT_TRUE(axisCtrl->GetPosition() == 2.0f);

   // this request shall not end up in any call to stepGen.Step...
   axisCtrl->SetAbsolutPosition(2);
   ASSERT_TRUE(axisCtrl->GetPosition() == 2.0f);

   axisCtrl->SetAbsolutPosition(-2);
   axisCtrl->Update(); // 4 steps generated, will generate 4 stepObserver update calls
   axisCtrl->Update();
   axisCtrl->Update();
   axisCtrl->Update();
   ASSERT_TRUE(axisCtrl->GetPosition() == -2.0f);
}

TEST_F(AxisCtrlTestFixture, test_set_scale)
{
   axisCtrl->SetScale(1600.0f/360.0f); // steps/unit (degrees)
   EXPECT_CALL(*mockStepGen, SetStepsPerSec((20*1600)/360));
   axisCtrl->SetSpeed(20); //
}

TEST_F(AxisCtrlTestFixture, test_set_home)
{
   EXPECT_CALL(*mockStepGen, Step(2));
   EXPECT_CALL(*mockStepGen, GetDirection()).Times(2).WillRepeatedly(Return(direction_forward));
   axisCtrl->SetAbsolutPosition(2);
   axisCtrl->Update();
   axisCtrl->Update();
   ASSERT_TRUE(axisCtrl->GetPosition() == 2.0f);

   axisCtrl->SetHome(0);
   ASSERT_TRUE(axisCtrl->GetPosition() == 0.0f);

   axisCtrl->SetHome(2);
   ASSERT_TRUE(axisCtrl->GetPosition() == 2.0f);

   axisCtrl->SetHome(-2);
   ASSERT_TRUE(axisCtrl->GetPosition() == -2.0f);
}

}