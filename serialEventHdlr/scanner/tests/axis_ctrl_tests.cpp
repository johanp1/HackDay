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
   MockStepGen(Pin step_pin = 0, Pin dir_pin = 0, micro_sec t_on = 0, micro_sec t_off = 0){};
   ~MockStepGen(){};

   MOCK_METHOD(void, Update, (), (override));
   MOCK_METHOD(StepRetVal, Step, (unsigned int steps), (override));
   MOCK_METHOD(void, SetStepsPerSec, (unsigned int steps_per_sec), (override));
   MOCK_METHOD(void, SetDirection, (Direction d), (override));
   MOCK_METHOD(Direction, GetDirection, (), (override));
   MOCK_METHOD(bool, IsBusy, (), (override));
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
   float scale = 800.0f/360.0f;
   EXPECT_CALL(*mockStepGen, SetStepsPerSec(2));
   axisCtrl->SetSpeed(2);

   axisCtrl->SetScale(scale); // steps/unit (degrees)
   EXPECT_CALL(*mockStepGen, SetStepsPerSec(scale*360/4));
   axisCtrl->SetSpeed(360/4); // one full rev per 4 sec
}

TEST_F(AxisCtrlTestFixture, test_set_rel_pos_default_scale)
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
   
   axisCtrl->MoveToRelativePosition(2);
   axisCtrl->Update(); // 2 steps generated, will generate 2 stepObserver update calls
   ASSERT_TRUE(axisCtrl->GetPosition() == 1.0f);
   axisCtrl->Update();
   ASSERT_TRUE(axisCtrl->GetPosition() == 2.0f);

   axisCtrl->MoveToRelativePosition(2);
   axisCtrl->Update();
   ASSERT_TRUE(axisCtrl->GetPosition() == 3.0f);
   axisCtrl->Update();
   ASSERT_TRUE(axisCtrl->GetPosition() == 4.0f);

   axisCtrl->MoveToRelativePosition(-2);
   axisCtrl->Update();
   ASSERT_TRUE(axisCtrl->GetPosition() == 3.0f);
   axisCtrl->Update();
   ASSERT_TRUE(axisCtrl->GetPosition() == 2.0f);
}

TEST_F(AxisCtrlTestFixture, test_set_abs_pos_default_scale)
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

   axisCtrl->MoveToAbsolutPosition(2);
   axisCtrl->Update();  // 2 steps generated, will generate 2 stepObserver update calls
   ASSERT_TRUE(axisCtrl->GetPosition() == 1.0f);
   axisCtrl->Update();
   ASSERT_TRUE(axisCtrl->GetPosition() == 2.0f);

   // this request shall not end up in any call to stepGen.Step...
   axisCtrl->MoveToAbsolutPosition(2);
   ASSERT_TRUE(axisCtrl->GetPosition() == 2.0f);

   axisCtrl->MoveToAbsolutPosition(-2);
   axisCtrl->Update(); // 4 steps generated, will generate 4 stepObserver update calls
   ASSERT_TRUE(axisCtrl->GetPosition() == 1.0f);
   axisCtrl->Update();
   ASSERT_TRUE(axisCtrl->GetPosition() == 0.0f);
   axisCtrl->Update();
   ASSERT_TRUE(axisCtrl->GetPosition() == -1.0f);
   axisCtrl->Update();
   ASSERT_TRUE(axisCtrl->GetPosition() == -2.0f);
}

TEST_F(AxisCtrlTestFixture, test_set_scaled_steps_per_sec)
{
   float test_scale = 1600.0f/360.0f;
   axisCtrl->SetScale(test_scale); // steps/unit (degrees)

   // lets say we want 20 units(degrees) per sec. how many step/sec...
   unsigned int steps_per_sec = static_cast<unsigned int>(20.0f * test_scale);
   EXPECT_CALL(*mockStepGen, SetStepsPerSec(steps_per_sec));
   axisCtrl->SetSpeed(20); //
}

TEST_F(AxisCtrlTestFixture, test_set_rel_pos_scaled)
{
   float test_scale = 1600.0f/360.0f;
   axisCtrl->SetScale(test_scale); // steps/unit (degrees)

   // lets say we want 20 units(degrees) per sec. how many step/sec...
   unsigned int steps_per_sec = static_cast<unsigned int>(20.0f * test_scale);

   // lets say we want to how many steps are 10 units
   EXPECT_CALL(*mockStepGen, Step(1));
   EXPECT_CALL(*mockStepGen, GetDirection()).WillRepeatedly(Return(direction_forward));
   
   // smallest movement possible
   axisCtrl->MoveToRelativePosition(1/test_scale);
   axisCtrl->Update();
   ASSERT_TRUE(axisCtrl->GetPosition() == 0.225f);
}

TEST_F(AxisCtrlTestFixture, test_set_abs_pos_scaled)
{
   float test_scale = 1600.0f/360.0f;
   axisCtrl->SetScale(test_scale); // steps/unit (degrees)

   EXPECT_CALL(*mockStepGen, Step(1));
   EXPECT_CALL(*mockStepGen, GetDirection()).WillRepeatedly(Return(direction_forward));

   ASSERT_TRUE(axisCtrl->MoveToAbsolutPosition(1/test_scale) == kOk);
   axisCtrl->Update();  
   ASSERT_TRUE(axisCtrl->GetPosition() == 0.225f);
}

TEST_F(AxisCtrlTestFixture, test_set_home)
{
   EXPECT_CALL(*mockStepGen, Step(2));
   EXPECT_CALL(*mockStepGen, GetDirection()).Times(2).WillRepeatedly(Return(direction_forward));
   ASSERT_TRUE(axisCtrl->MoveToAbsolutPosition(2) == kOk);
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

TEST_F(AxisCtrlTestFixture, test_set_pos_busy)
{
   ASSERT_TRUE(axisCtrl->GetPosition() == 0.0f);
   {
      InSequence seq;      
      EXPECT_CALL(*mockStepGen, IsBusy()).WillOnce(Return(true));
   }
   ASSERT_TRUE(axisCtrl->MoveToAbsolutPosition(10) == kNotOk);
   ASSERT_TRUE(axisCtrl->GetPosition() == 0.0f);

   {
      InSequence seq;      
      EXPECT_CALL(*mockStepGen, IsBusy()).WillOnce(Return(true));
   }
   ASSERT_TRUE(axisCtrl->MoveToRelativePosition(10) == kNotOk);
   ASSERT_TRUE(axisCtrl->GetPosition() == 0.0f);
}

TEST(AxisCtrlTestGroup, test_set_home_rotary_axis)
{
   MockStepGen stepGen;
   RotaryAxisCtrl rotaryAxisCtrl(stepGen, 1);
   rotaryAxisCtrl.SetScale(2.5f);

   rotaryAxisCtrl.SetHome(180.0f);
   ASSERT_TRUE(rotaryAxisCtrl.GetPosition() == 180.0f);

   rotaryAxisCtrl.SetHome(360.0f);
   ASSERT_TRUE(rotaryAxisCtrl.GetPosition() == 0.0f);

   rotaryAxisCtrl.SetHome(450.0f);
   ASSERT_TRUE(rotaryAxisCtrl.GetPosition() == 90.0f);
}

TEST(AxisCtrlTestGroup, test_set_abs_pos_rotary)
{
   MockStepGen stepGen;
   RotaryAxisCtrl rotaryAxisCtrl(stepGen, 1);

   EXPECT_CALL(stepGen, IsBusy());
   EXPECT_CALL(stepGen, SetDirection(direction_forward));
   EXPECT_CALL(stepGen, Step(40));
   
   // test that actual move to abs pos is "fmod(request)" = 40 steps in this case
   ASSERT_TRUE(rotaryAxisCtrl.MoveToAbsolutPosition(400) == kOk);

   // rotate forward
   for (int i = 1 ; i <= 40; i++)
   {
      InSequence seq;
      EXPECT_CALL(stepGen, GetDirection()).WillOnce(Return(direction_forward));
      rotaryAxisCtrl.Update();
      //std::cout << i << std::endl;
      ASSERT_TRUE(rotaryAxisCtrl.GetPosition() == i);
   }
   
   EXPECT_CALL(stepGen, IsBusy());
   EXPECT_CALL(stepGen, SetDirection(direction_reverse));
   EXPECT_CALL(stepGen, Step(50));
   
   // check reverse direction move request
   ASSERT_TRUE(rotaryAxisCtrl.MoveToAbsolutPosition(-10) == kOk);

   // rotate reverse
   for (int i = 39 ; i >= -10; i--)
   {
      InSequence seq;
      EXPECT_CALL(stepGen, GetDirection()).WillOnce(Return(direction_reverse));
      rotaryAxisCtrl.Update();
      //std::cout << i << std::endl;
      ASSERT_TRUE(rotaryAxisCtrl.GetPosition() == i);
   }
}

TEST(AxisCtrlTestGroup, test_set_abs_pos_rotary_shortest_path)
{
   MockStepGen stepGen;
   RotaryAxisCtrl rotaryAxisCtrl(stepGen, 1);

   rotaryAxisCtrl.SetHome(350);
   EXPECT_CALL(stepGen, IsBusy());
   EXPECT_CALL(stepGen, SetDirection(direction_forward));
   EXPECT_CALL(stepGen, Step(10));
   ASSERT_TRUE(rotaryAxisCtrl.MoveToAbsolutPosition(0) == kOk);

   rotaryAxisCtrl.SetHome(350);
   EXPECT_CALL(stepGen, IsBusy());
   EXPECT_CALL(stepGen, SetDirection(direction_reverse));
   EXPECT_CALL(stepGen, Step(1));
   ASSERT_TRUE(rotaryAxisCtrl.MoveToAbsolutPosition(-11) == kOk);

   rotaryAxisCtrl.SetHome(-20);
   EXPECT_CALL(stepGen, IsBusy());
   EXPECT_CALL(stepGen, SetDirection(direction_forward));
   EXPECT_CALL(stepGen, Step(30));
   ASSERT_TRUE(rotaryAxisCtrl.MoveToAbsolutPosition(10) == kOk);
}

TEST(AxisCtrlTestGroup, test_set_abs_pos_scaled_rotary)
{
   MockStepGen stepGen;
   RotaryAxisCtrl rotaryAxisCtrl(stepGen, 1);
   float test_scale = 1600.0f/360.0f;

   rotaryAxisCtrl.SetScale(test_scale);

   {
      InSequence seq;
      EXPECT_CALL(stepGen, IsBusy());
      EXPECT_CALL(stepGen, SetDirection(direction_forward));
      EXPECT_CALL(stepGen, Step(1));
      
      ASSERT_TRUE(rotaryAxisCtrl.MoveToAbsolutPosition(1/test_scale) == kOk);

      EXPECT_CALL(stepGen, GetDirection()).WillOnce(Return(direction_forward));
      rotaryAxisCtrl.Update();
      ASSERT_TRUE(rotaryAxisCtrl.GetPosition() == 1/test_scale);
   }
}

}