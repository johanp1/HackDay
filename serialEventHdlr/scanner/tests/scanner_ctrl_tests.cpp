#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "axis_ctrl.h"
#include <memory>
#include <iostream>
#include <sstream>
#include "scanner_ctrl.h"

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
   MOCK_METHOD(bool, IsBusy, (), (override));
};

class MockAxisCtrl : public AxisCtrl
{
   public:
   MockAxisCtrl(StepGen& s):AxisCtrl(s){};
   ~MockAxisCtrl(){};

   MOCK_METHOD(float, GetPosition, (), (override));
   MOCK_METHOD(void, SetAbsolutPosition, (float pos), (override));
   MOCK_METHOD(void, SetRelativePosition, (float pos), (override));
};

TEST(ScannerCtrlTestSuite, test_update_mode_inactive)
{
    MockStepGen mockStepGen;
    MockAxisCtrl mockAxisCtrl(mockStepGen);
    ScannerCtrl scannerCtrl(mockAxisCtrl, mockAxisCtrl);

    scannerCtrl.SetMode(mode_inactive);
    EXPECT_CALL(mockAxisCtrl, GetPosition()).Times(0);
    scannerCtrl.Update();
}

TEST(ScannerCtrlTestSuite, test_update_mode_test)
{
    MockStepGen mockStepGen;
    MockAxisCtrl mockAxisCtrl(mockStepGen);
    ScannerCtrl scannerCtrl(mockAxisCtrl, mockAxisCtrl);

    EXPECT_CALL(mockAxisCtrl, SetAbsolutPosition(0.0f)).Times(1);
    scannerCtrl.SetMode(mode_test);

    for (int i = 0; i < 35; i++)
    {
        InSequence seq;
        EXPECT_CALL(mockAxisCtrl, GetPosition()).Times(1).WillOnce(Return(i*10.0f));
        EXPECT_CALL(mockAxisCtrl, SetAbsolutPosition((i+1)*10.0f)).Times(1);
        scannerCtrl.Update();
    }

    // last itteration
    {
        InSequence seq;
        EXPECT_CALL(mockAxisCtrl, GetPosition()).Times(1).WillOnce(Return(350.0f));
        // no setAbsolutPosition, measurement done
        scannerCtrl.Update();
    }
    scannerCtrl.Update();
    ASSERT_TRUE(scannerCtrl.GetMode() == mode_inactive);
}

TEST(ScannerCtrlTestSuite, test_set_end_pos)
{
    MockStepGen mockStepGen;
    MockAxisCtrl mockAxisCtrl(mockStepGen);
    ScannerCtrl scannerCtrl(mockAxisCtrl, mockAxisCtrl);

    EXPECT_CALL(mockAxisCtrl, SetAbsolutPosition(0.0f)).Times(1);
    scannerCtrl.SetMode(mode_test);

    EXPECT_CALL(mockAxisCtrl, GetPosition()).Times(1).WillOnce(Return(100.0f));
    scannerCtrl.SetHorizontalEndPosition();

    for (int i = 0; i < 9; i++)
    {
        InSequence seq;
        EXPECT_CALL(mockAxisCtrl, GetPosition()).Times(1).WillOnce(Return(i*10.0f));
        EXPECT_CALL(mockAxisCtrl, SetAbsolutPosition((i+1)*10.0f)).Times(1);
        scannerCtrl.Update();
    }

    // last itteration
    {
        InSequence seq;
        EXPECT_CALL(mockAxisCtrl, GetPosition()).Times(1).WillOnce(Return(90.0f));
        // no setAbsolutPosition, measurement done
        scannerCtrl.Update();
    }
    scannerCtrl.Update();
    ASSERT_TRUE(scannerCtrl.GetMode() == mode_inactive);
}

}