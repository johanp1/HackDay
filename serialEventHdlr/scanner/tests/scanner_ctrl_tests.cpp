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
using ::testing::AllOf;
using ::testing::Gt;
using ::testing::Lt;

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

class MockAxisCtrl : public AxisCtrl
{
   public:
   MockAxisCtrl(StepGen& s):AxisCtrl(s){};
   ~MockAxisCtrl(){};

   MOCK_METHOD(Position, GetPosition, (), (override));
   MOCK_METHOD(MoveRequestStatus, MoveToAbsolutPosition, (float pos), (override));
   MOCK_METHOD(MoveRequestStatus, MoveToRelativePosition, (Position pos), (override));
   MOCK_METHOD(void, SetHome, (float pos), (override));
   MOCK_METHOD(AxisCrtlStatus, GetStatus, (), (override));
};

class MockLidar
{
    public:
    MockLidar(){};
    void begin(int, bool){};
    void configure(int){};
    int distance(bool = true){return 0;};
};

static void ExpectedMoveToPos(MockAxisCtrl& axisCtrl, float pos, float tol = 0.1)
{
    EXPECT_CALL(axisCtrl, MoveToAbsolutPosition(AllOf(Gt(pos-tol),Lt(pos+tol)))).Times(1).WillOnce(Return(kOk));
}

TEST(ScannerCtrlTestSuite, test_update_mode_inactive)
{
    MockStepGen mockStepGen;
    MockAxisCtrl mockAxisCtrl(mockStepGen);
    MockLidar mockLidar;
    ScannerCtrl<MockLidar> scannerCtrl(mockLidar, mockAxisCtrl, mockAxisCtrl);

    scannerCtrl.SetMode(kModeInactive);
    EXPECT_CALL(mockAxisCtrl, GetPosition()).Times(0);
    scannerCtrl.Update();
}

TEST(ScannerCtrlTestSuite, test_homing)
{
    MockStepGen mockStepGen;
    MockAxisCtrl mockAxisCtrl(mockStepGen);
    MockLidar mockLidar;
    ScannerCtrl<MockLidar> scannerCtrl(mockLidar, mockAxisCtrl, mockAxisCtrl);

    scannerCtrl.SetMode(kModeNotHomed);
    EXPECT_CALL(mockAxisCtrl, GetPosition()).Times(1);
    EXPECT_CALL(mockAxisCtrl, SetHome(0.0f)).Times(1);
    scannerCtrl.SetVerticalHomePosition();
    ASSERT_TRUE(scannerCtrl.GetMode() == kModeInactive);
}

TEST(ScannerCtrlTestSuite, test_mode_basic_scanning)
{
    MockStepGen mockStepGen;
    MockAxisCtrl mockHorizontalAxisCtrl(mockStepGen);
    MockAxisCtrl mockVerticalAxisCtrl(mockStepGen);
    MockLidar mockLidar;
    ScannerCtrl<MockLidar> scannerCtrl(mockLidar, mockVerticalAxisCtrl, mockHorizontalAxisCtrl);
    int j;
    int i;
    int vertical_iterations = (int)((kDefaultVerticalEndPosition-kDefaultVerticalStartPosition)/kVerticalIncrement);
    int horizontal_iterations = (int)(kDefaultHorizontalEndPosition/kHorizontalIncrement);

    EXPECT_CALL(mockHorizontalAxisCtrl, GetPosition()).Times(1).WillOnce(Return(0.0f));
    EXPECT_CALL(mockHorizontalAxisCtrl, SetHome(0.0)).Times(1);
    EXPECT_CALL(mockHorizontalAxisCtrl, MoveToAbsolutPosition(kDefaultHorizontalStartPosition)).Times(1);
    EXPECT_CALL(mockVerticalAxisCtrl, MoveToAbsolutPosition(kDefaultVerticalStartPosition)).Times(1);
    scannerCtrl.SetMode(kModeScanning);
    
    for(j = 0; j < vertical_iterations; j++)
    {
        // one horizontal rev...
        for (i = 0; i < horizontal_iterations - 1; i++)
        {
            InSequence seq;
            EXPECT_CALL(mockHorizontalAxisCtrl, GetStatus()).Times(1).WillOnce(Return(kIdle));
            EXPECT_CALL(mockVerticalAxisCtrl, GetStatus()).Times(1).WillOnce(Return(kIdle));

            // from scan()
            EXPECT_CALL(mockHorizontalAxisCtrl, GetPosition()).Times(1);
            EXPECT_CALL(mockVerticalAxisCtrl, GetPosition()).Times(1);
            //////////////

            ExpectedMoveToPos(mockHorizontalAxisCtrl, (i+1)*kHorizontalIncrement);
            scannerCtrl.Update();
        }
        //last iteration
        {
            InSequence seq;
            EXPECT_CALL(mockHorizontalAxisCtrl, GetStatus()).Times(1).WillOnce(Return(kIdle));
            EXPECT_CALL(mockVerticalAxisCtrl, GetStatus()).Times(1).WillOnce(Return(kIdle));

            // from scan
            EXPECT_CALL(mockHorizontalAxisCtrl, GetPosition()).Times(1);
            EXPECT_CALL(mockVerticalAxisCtrl, GetPosition()).Times(1);
            ////////////

            // this is not needed for the absolut last iteration
            if (j != vertical_iterations - 1)
            {
                ExpectedMoveToPos(mockVerticalAxisCtrl, kDefaultVerticalStartPosition+(j+1)*kVerticalIncrement);
                EXPECT_CALL(mockHorizontalAxisCtrl, GetPosition()).Times(1);
                EXPECT_CALL(mockHorizontalAxisCtrl, SetHome(_)).Times(1);
                EXPECT_CALL(mockHorizontalAxisCtrl, MoveToAbsolutPosition(0.0f)).Times(1).WillOnce(Return(kOk));
            }
            scannerCtrl.Update();
        }
    }

    ASSERT_TRUE(scannerCtrl.GetMode() == kModeInactive);
}

}