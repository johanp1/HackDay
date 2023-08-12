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
   MOCK_METHOD(void, MoveToAbsolutPosition, (float pos), (override));
   MOCK_METHOD(void, MoveToRelativePosition, (float pos), (override));
   MOCK_METHOD(void, SetHome, (float pos), (override));
};

class MockLidar
{
    public:
    MockLidar(){};
    void begin(int, bool){};
    void configure(int){};
    int distance(bool = true){return 0;};
};

TEST(ScannerCtrlTestSuite, test_update_mode_inactive)
{
    MockStepGen mockStepGen;
    MockAxisCtrl mockAxisCtrl(mockStepGen);
    MockLidar mockLidar;
    ScannerCtrl<MockLidar> scannerCtrl(mockLidar, mockAxisCtrl, mockAxisCtrl);

    scannerCtrl.SetMode(mode_inactive);
    EXPECT_CALL(mockAxisCtrl, GetPosition()).Times(0);
    scannerCtrl.Update();
}

TEST(ScannerCtrlTestSuite, test_update_mode_test)
{
    MockStepGen mockStepGen;
    MockAxisCtrl mockAxisCtrl(mockStepGen);
    MockLidar mockLidar;
    ScannerCtrl<MockLidar> scannerCtrl(mockLidar, mockAxisCtrl, mockAxisCtrl);

    EXPECT_CALL(mockAxisCtrl, GetPosition()).Times(1).WillOnce(Return(0.0f));
    EXPECT_CALL(mockAxisCtrl, SetHome(0.0)).Times(1);
    EXPECT_CALL(mockAxisCtrl, MoveToAbsolutPosition(0.0f)).Times(1);
    scannerCtrl.SetMode(mode_test);

    for (int i = 0; i < 36; i++)
    {
        InSequence seq;
        EXPECT_CALL(mockAxisCtrl, GetPosition()).Times(1).WillOnce(Return(i*9.9f));
        //EXPECT_CALL(mockAxisCtrl, MoveToAbsolutPosition((i+1)*9.90f)).Times(1);
        EXPECT_CALL(mockAxisCtrl, MoveToAbsolutPosition(_)).Times(1);
        scannerCtrl.Update();
    }

    // last itteration
    {
        InSequence seq;
        EXPECT_CALL(mockAxisCtrl, GetPosition()).Times(1).WillOnce(Return(356.4f)); // 36*9.9
        EXPECT_CALL(mockAxisCtrl, MoveToAbsolutPosition(_)).Times(1);
        scannerCtrl.Update();
    }

    EXPECT_CALL(mockAxisCtrl, GetPosition()).Times(1).WillOnce(Return(360.0f));
    EXPECT_CALL(mockAxisCtrl, SetHome(0.0)).Times(1);
    scannerCtrl.Update();
    ASSERT_TRUE(scannerCtrl.GetMode() == mode_inactive);
}

TEST(ScannerCtrlTestSuite, test_set_end_pos)
{
    MockStepGen mockStepGen;
    MockAxisCtrl mockAxisCtrl(mockStepGen);
    MockLidar mockLidar;
    ScannerCtrl<MockLidar> scannerCtrl(mockLidar, mockAxisCtrl, mockAxisCtrl);

    EXPECT_CALL(mockAxisCtrl, GetPosition()).Times(1).WillOnce(Return(100.0f));
    scannerCtrl.SetHorizontalEndPosition();

    EXPECT_CALL(mockAxisCtrl, GetPosition()).Times(1).WillOnce(Return(100.0f));
    EXPECT_CALL(mockAxisCtrl, SetHome(100.0)).Times(1);
    EXPECT_CALL(mockAxisCtrl, MoveToAbsolutPosition(0.0f)).Times(1);
    scannerCtrl.SetMode(mode_test);

    for (int i = 0; i < 10; i++)
    {
        InSequence seq;
        EXPECT_CALL(mockAxisCtrl, GetPosition()).Times(1).WillOnce(Return(i*9.9f));
        //EXPECT_CALL(mockAxisCtrl, MoveToAbsolutPosition((i+1)*10.0f)).Times(1);
        EXPECT_CALL(mockAxisCtrl, MoveToAbsolutPosition(_)).Times(1);
        scannerCtrl.Update();
    }

    // last itteration
    {
        InSequence seq;
        EXPECT_CALL(mockAxisCtrl, GetPosition()).Times(1).WillOnce(Return(99.0f));
        EXPECT_CALL(mockAxisCtrl, MoveToAbsolutPosition(_)).Times(1);
        scannerCtrl.Update();
    }

    EXPECT_CALL(mockAxisCtrl, GetPosition()).Times(1).WillOnce(Return(360.0f));
    EXPECT_CALL(mockAxisCtrl, SetHome(0.0)).Times(1);
    scannerCtrl.Update();
    ASSERT_TRUE(scannerCtrl.GetMode() == mode_inactive);
}

// test start pos and end pos are absolute positions, not relative to eachother
TEST(ScannerCtrlTestSuite, test_set_start_pos)
{
    MockStepGen mockStepGen;
    MockAxisCtrl mockAxisCtrl(mockStepGen);
    MockLidar mockLidar;
    ScannerCtrl<MockLidar> scannerCtrl(mockLidar, mockAxisCtrl, mockAxisCtrl);

    // set end pos
    EXPECT_CALL(mockAxisCtrl, GetPosition()).Times(1).WillOnce(Return(99.0f));
    scannerCtrl.SetHorizontalEndPosition();

    // set start pos
    EXPECT_CALL(mockAxisCtrl, GetPosition()).Times(1).WillOnce(Return(30.0f));
    EXPECT_CALL(mockAxisCtrl, SetHome(0.0)).Times(1);
    scannerCtrl.SetHorizontalStartPosition();

    EXPECT_CALL(mockAxisCtrl, GetPosition()).Times(1).WillOnce(Return(30.0f));
    EXPECT_CALL(mockAxisCtrl, SetHome(30.0)).Times(1);
    EXPECT_CALL(mockAxisCtrl, MoveToAbsolutPosition(0.0f)).Times(1);
    scannerCtrl.SetMode(mode_test);

    for (int i = 0; i < 6; i++)
    {
        InSequence seq;
        EXPECT_CALL(mockAxisCtrl, GetPosition()).Times(1).WillOnce(Return(i*9.9f));
        //EXPECT_CALL(mockAxisCtrl, MoveToAbsolutPosition((i+1)*9.9f)).Times(1);
        EXPECT_CALL(mockAxisCtrl, MoveToAbsolutPosition(_)).Times(1);
        scannerCtrl.Update();
    }

    // last itteration
    {
        InSequence seq;
        EXPECT_CALL(mockAxisCtrl, GetPosition()).Times(1).WillOnce(Return(59.4f));
        EXPECT_CALL(mockAxisCtrl, MoveToAbsolutPosition(_)).Times(1);
        scannerCtrl.Update();
    }
    EXPECT_CALL(mockAxisCtrl, GetPosition()).Times(1).WillOnce(Return(360.0f));
    EXPECT_CALL(mockAxisCtrl, SetHome(0.0)).Times(1);
    scannerCtrl.Update();
    ASSERT_TRUE(scannerCtrl.GetMode() == mode_inactive);
}

// test start pos and end pos are absolute positions, not relative to eachother
TEST(ScannerCtrlTestSuite, test_get_position_fmod_360)
{
    MockStepGen mockStepGen;
    MockAxisCtrl mockAxisCtrl(mockStepGen);
    MockLidar mockLidar;
    ScannerCtrl<MockLidar> scannerCtrl(mockLidar, mockAxisCtrl, mockAxisCtrl);

    // set end pos
    EXPECT_CALL(mockAxisCtrl, GetPosition()).Times(1).WillOnce(Return(360.0f+99.0f));
    scannerCtrl.SetHorizontalEndPosition();

    // set start pos
    EXPECT_CALL(mockAxisCtrl, GetPosition()).Times(1).WillOnce(Return(360.0f+30.0f));
    EXPECT_CALL(mockAxisCtrl, SetHome(0.0)).Times(1);
    scannerCtrl.SetHorizontalStartPosition();

    EXPECT_CALL(mockAxisCtrl, GetPosition()).Times(1).WillOnce(Return(360.0f+30.0f));
    EXPECT_CALL(mockAxisCtrl, SetHome(30.0)).Times(1);
    EXPECT_CALL(mockAxisCtrl, MoveToAbsolutPosition(0.0f)).Times(1);
    scannerCtrl.SetMode(mode_test);

    for (int i = 0; i < 6; i++)
    {
        InSequence seq;
        EXPECT_CALL(mockAxisCtrl, GetPosition()).Times(1).WillOnce(Return(i*9.9f));
        //EXPECT_CALL(mockAxisCtrl, MoveToAbsolutPosition((i+1)*9.9f)).Times(1);
        EXPECT_CALL(mockAxisCtrl, MoveToAbsolutPosition(_)).Times(1);
        scannerCtrl.Update();
    }

    // last itteration
    {
        InSequence seq;
        EXPECT_CALL(mockAxisCtrl, GetPosition()).Times(1).WillOnce(Return(59.4f));
        EXPECT_CALL(mockAxisCtrl, MoveToAbsolutPosition(_)).Times(1);
        scannerCtrl.Update();
    }
    EXPECT_CALL(mockAxisCtrl, GetPosition()).Times(1).WillOnce(Return(360.0f));
    EXPECT_CALL(mockAxisCtrl, SetHome(0.0)).Times(1);
    scannerCtrl.Update();
    ASSERT_TRUE(scannerCtrl.GetMode() == mode_inactive);
}

}