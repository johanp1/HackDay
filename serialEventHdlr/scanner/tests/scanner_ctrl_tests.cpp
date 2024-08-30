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

TEST(ScannerCtrlTestSuite, test_init)
{
    MockStepGen mockStepGen;
    MockAxisCtrl mockAxisCtrl(mockStepGen);
    MockLidar mockLidar;
    ScannerCtrl<MockLidar> scannerCtrl(mockLidar, mockAxisCtrl, mockAxisCtrl);

    ASSERT_TRUE(scannerCtrl.GetMode() == kModeNotHomed);
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
/*
TEST(ScannerCtrlTestSuite, test_basic_scanning)
{
    MockStepGen mockStepGen;
    MockAxisCtrl mockHorizontalAxisCtrl(mockStepGen);
    MockAxisCtrl mockVerticalAxisCtrl(mockStepGen);
    MockLidar mockLidar;
    ScannerCtrl<MockLidar> scannerCtrl(mockLidar, mockVerticalAxisCtrl, mockHorizontalAxisCtrl);
    int j;
    int i;
    int vertical_iterations = (int)((kDefaultVerticalEndPosition-kDefaultVerticalStartPosition)/kDefaultVerticalIncrement);
    int horizontal_iterations = (int)(kDefaultHorizontalEndPosition/kDefaultHorizontalIncrement);

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

            ExpectedMoveToPos(mockHorizontalAxisCtrl, (i+1)*kDefaultHorizontalIncrement);
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
                ExpectedMoveToPos(mockVerticalAxisCtrl, kDefaultVerticalStartPosition+(j+1)*kDefaultVerticalIncrement);
                EXPECT_CALL(mockHorizontalAxisCtrl, MoveToAbsolutPosition(0.0f)).Times(1).WillOnce(Return(kOk));
            }
            scannerCtrl.Update();
        }
    }

    ASSERT_TRUE(scannerCtrl.GetMode() == kModeInactive);
}
*/
TEST(ScannerCtrlTestSuite, test_scanning_set_horizontal_start_pos)
{
    constexpr float increment = 0.225;
    MockStepGen mockStepGen;
    MockAxisCtrl mockHorizontalAxisCtrl(mockStepGen);
    MockAxisCtrl mockVerticalAxisCtrl(mockStepGen);
    MockLidar mockLidar;
    ScannerCtrl<MockLidar> scannerCtrl(mockLidar, mockVerticalAxisCtrl, mockHorizontalAxisCtrl);
    scannerCtrl.SetHorizontalIncrement(increment);
    scannerCtrl.SetVerticalIncrement(increment);

    int i;
    int horizontal_iterations = (int)((kDefaultHorizontalEndPosition - 30.0f)/increment);
  
    // precondition - set a new start pos at current pos 30
    EXPECT_CALL(mockHorizontalAxisCtrl, GetPosition()).Times(1).WillOnce(Return(30.0f));
    EXPECT_CALL(mockHorizontalAxisCtrl, SetHome(0.0)).Times(1);
    scannerCtrl.SetHorizontalStartPosition();

    // start test
    EXPECT_CALL(mockHorizontalAxisCtrl, MoveToAbsolutPosition(kDefaultHorizontalStartPosition)).Times(1);
    EXPECT_CALL(mockVerticalAxisCtrl, MoveToAbsolutPosition(kDefaultVerticalStartPosition)).Times(1);
    scannerCtrl.SetMode(kModeScanning);
    
    // one horizontal rev...
    for (i = 0; i < horizontal_iterations; i++)
    {
        InSequence seq;
        EXPECT_CALL(mockHorizontalAxisCtrl, GetStatus()).Times(1).WillOnce(Return(kIdle));
        EXPECT_CALL(mockVerticalAxisCtrl, GetStatus()).Times(1).WillOnce(Return(kIdle));

        // from scan()
        EXPECT_CALL(mockHorizontalAxisCtrl, GetPosition()).Times(1);
        EXPECT_CALL(mockVerticalAxisCtrl, GetPosition()).Times(1);
        //////////////

        ExpectedMoveToPos(mockHorizontalAxisCtrl, (i+1)*increment);
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

        ExpectedMoveToPos(mockVerticalAxisCtrl, kDefaultVerticalStartPosition + increment);
        EXPECT_CALL(mockHorizontalAxisCtrl, MoveToAbsolutPosition(0.0f)).Times(1).WillOnce(Return(kOk));
        scannerCtrl.Update();
    }

    ASSERT_TRUE(scannerCtrl.GetMode() == kModeScanning);
}

TEST(ScannerCtrlTestSuite, test_scanning_set_horizontal_end_pos)
{
    MockStepGen mockStepGen;
    MockAxisCtrl mockHorizontalAxisCtrl(mockStepGen);
    MockAxisCtrl mockVerticalAxisCtrl(mockStepGen);
    MockLidar mockLidar;
    ScannerCtrl<MockLidar> scannerCtrl(mockLidar, mockVerticalAxisCtrl, mockHorizontalAxisCtrl);

    int i;
    int horizontal_iterations = (int)((90.0f)/kDefaultHorizontalIncrement);
  
    // precondition - set a new end pos
    EXPECT_CALL(mockHorizontalAxisCtrl, GetPosition()).Times(1).WillOnce(Return(90.0f));
    scannerCtrl.SetHorizontalEndPosition();

    EXPECT_CALL(mockHorizontalAxisCtrl, MoveToAbsolutPosition(kDefaultHorizontalStartPosition)).Times(1);
    EXPECT_CALL(mockVerticalAxisCtrl, MoveToAbsolutPosition(kDefaultVerticalStartPosition)).Times(1);
    scannerCtrl.SetMode(kModeScanning);
    
    // one horizontal rev...
    for (i = 0; i < horizontal_iterations; i++)
    {
        InSequence seq;
        EXPECT_CALL(mockHorizontalAxisCtrl, GetStatus()).Times(1).WillOnce(Return(kIdle));
        EXPECT_CALL(mockVerticalAxisCtrl, GetStatus()).Times(1).WillOnce(Return(kIdle));

        // from scan()
        EXPECT_CALL(mockHorizontalAxisCtrl, GetPosition()).Times(1);
        EXPECT_CALL(mockVerticalAxisCtrl, GetPosition()).Times(1);
        //////////////

        ExpectedMoveToPos(mockHorizontalAxisCtrl, (i+1)*kDefaultHorizontalIncrement);
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

        ExpectedMoveToPos(mockVerticalAxisCtrl, kDefaultVerticalStartPosition + kDefaultVerticalIncrement);
        EXPECT_CALL(mockHorizontalAxisCtrl, MoveToAbsolutPosition(0.0f)).Times(1).WillOnce(Return(kOk));
        scannerCtrl.Update();
    }

    ASSERT_TRUE(scannerCtrl.GetMode() == kModeScanning);
}

//negative start, then the end pos will remain as 
TEST(ScannerCtrlTestSuite, test_horizontal_negative_start_pos)
{
    MockStepGen mockStepGen;
    MockAxisCtrl mockHorizontalAxisCtrl(mockStepGen);
    MockAxisCtrl mockVerticalAxisCtrl(mockStepGen);
    MockLidar mockLidar;
    ScannerCtrl<MockLidar> scannerCtrl(mockLidar, mockVerticalAxisCtrl, mockHorizontalAxisCtrl);

    int i;
    int horizontal_iterations = (int)(kDefaultHorizontalEndPosition/kDefaultHorizontalIncrement);
  
    // precondition - set a new start pos at current pos -30
    EXPECT_CALL(mockHorizontalAxisCtrl, GetPosition()).Times(1).WillOnce(Return(-30.0f));
    EXPECT_CALL(mockHorizontalAxisCtrl, SetHome(0.0)).Times(1);
    scannerCtrl.SetHorizontalStartPosition();

    // start test
    EXPECT_CALL(mockHorizontalAxisCtrl, MoveToAbsolutPosition(kDefaultHorizontalStartPosition)).Times(1);
    EXPECT_CALL(mockVerticalAxisCtrl, MoveToAbsolutPosition(kDefaultVerticalStartPosition)).Times(1);
    scannerCtrl.SetMode(kModeScanning);
    
    // one horizontal rev...
    for (i = 0; i < horizontal_iterations-1; i++)
    {
        InSequence seq;
        EXPECT_CALL(mockHorizontalAxisCtrl, GetStatus()).Times(1).WillOnce(Return(kIdle));
        EXPECT_CALL(mockVerticalAxisCtrl, GetStatus()).Times(1).WillOnce(Return(kIdle));

        // from scan()
        EXPECT_CALL(mockHorizontalAxisCtrl, GetPosition()).Times(1);
        EXPECT_CALL(mockVerticalAxisCtrl, GetPosition()).Times(1);
        //////////////

        ExpectedMoveToPos(mockHorizontalAxisCtrl, (i+1)*kDefaultHorizontalIncrement);
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

        ExpectedMoveToPos(mockVerticalAxisCtrl, kDefaultVerticalStartPosition + kDefaultVerticalIncrement);
        EXPECT_CALL(mockHorizontalAxisCtrl, MoveToAbsolutPosition(0.0f)).Times(1).WillOnce(Return(kOk));
        scannerCtrl.Update();
    }

    ASSERT_TRUE(scannerCtrl.GetMode() == kModeScanning);
}

TEST(ScannerCtrlTestSuite, test_horizontal_negative_end_pos)
{
    MockStepGen mockStepGen;
    MockAxisCtrl mockHorizontalAxisCtrl(mockStepGen);
    MockAxisCtrl mockVerticalAxisCtrl(mockStepGen);
    MockLidar mockLidar;
    ScannerCtrl<MockLidar> scannerCtrl(mockLidar, mockVerticalAxisCtrl, mockHorizontalAxisCtrl);

    int i;
    int horizontal_iterations = (int)((330.0f)/kDefaultHorizontalIncrement);
  
    // precondition - set a new end pos
    EXPECT_CALL(mockHorizontalAxisCtrl, GetPosition()).Times(1).WillOnce(Return(-30.0f)); // should be interpreted as 330
    scannerCtrl.SetHorizontalEndPosition();

    EXPECT_CALL(mockHorizontalAxisCtrl, MoveToAbsolutPosition(kDefaultHorizontalStartPosition)).Times(1);
    EXPECT_CALL(mockVerticalAxisCtrl, MoveToAbsolutPosition(kDefaultVerticalStartPosition)).Times(1);
    scannerCtrl.SetMode(kModeScanning);
    
    // one horizontal rev...
    for (i = 0; i < horizontal_iterations; i++)
    {
        InSequence seq;
        EXPECT_CALL(mockHorizontalAxisCtrl, GetStatus()).Times(1).WillOnce(Return(kIdle));
        EXPECT_CALL(mockVerticalAxisCtrl, GetStatus()).Times(1).WillOnce(Return(kIdle));

        // from scan()
        EXPECT_CALL(mockHorizontalAxisCtrl, GetPosition()).Times(1);
        EXPECT_CALL(mockVerticalAxisCtrl, GetPosition()).Times(1);
        //////////////

        ExpectedMoveToPos(mockHorizontalAxisCtrl, (i+1)*kDefaultHorizontalIncrement);
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

        ExpectedMoveToPos(mockVerticalAxisCtrl, kDefaultVerticalStartPosition + kDefaultVerticalIncrement);
        EXPECT_CALL(mockHorizontalAxisCtrl, MoveToAbsolutPosition(0.0f)).Times(1).WillOnce(Return(kOk));
        scannerCtrl.Update();
    }

    ASSERT_TRUE(scannerCtrl.GetMode() == kModeScanning);
}

TEST(ScannerCtrlTestSuite, test_vertical_limits)
{
    MockStepGen mockStepGen;
    MockAxisCtrl mockHorizontalAxisCtrl(mockStepGen);
    MockAxisCtrl mockVerticalAxisCtrl(mockStepGen);
    MockLidar mockLidar;
    ScannerCtrl<MockLidar> scannerCtrl(mockLidar, mockVerticalAxisCtrl, mockHorizontalAxisCtrl);
    int j;
    int i;
    int vertical_iterations = (int)((20.0f)/kDefaultVerticalIncrement);
    int horizontal_iterations = (int)((10.0f)/kDefaultHorizontalIncrement);
  
    // prepare - smaller horizontal range to speed things up
    EXPECT_CALL(mockHorizontalAxisCtrl, GetPosition()).Times(1).WillOnce(Return(10.0f));
    scannerCtrl.SetHorizontalEndPosition();

    // precondition - set a new vertical start/end pos
    EXPECT_CALL(mockVerticalAxisCtrl, GetPosition()).Times(1).WillOnce(Return(15.0f));
    scannerCtrl.SetVerticalEndPosition();
    EXPECT_CALL(mockVerticalAxisCtrl, GetPosition()).Times(1).WillOnce(Return(-5.0f));
    scannerCtrl.SetVerticalStartPosition();

    EXPECT_CALL(mockHorizontalAxisCtrl, MoveToAbsolutPosition(kDefaultHorizontalStartPosition)).Times(1);
    EXPECT_CALL(mockVerticalAxisCtrl, MoveToAbsolutPosition(-5.0f)).Times(1);
    scannerCtrl.SetMode(kModeScanning);
    
    for(j = 0; j <= vertical_iterations; j++)
    {
        // one horizontal rev...
        for (i = 0; i < horizontal_iterations; i++)
        {
            InSequence seq;
            EXPECT_CALL(mockHorizontalAxisCtrl, GetStatus()).Times(1).WillOnce(Return(kIdle));
            EXPECT_CALL(mockVerticalAxisCtrl, GetStatus()).Times(1).WillOnce(Return(kIdle));

            // from scan()
            EXPECT_CALL(mockHorizontalAxisCtrl, GetPosition()).Times(1);
            EXPECT_CALL(mockVerticalAxisCtrl, GetPosition()).Times(1);
            //////////////

            ExpectedMoveToPos(mockHorizontalAxisCtrl, (i+1)*kDefaultHorizontalIncrement);
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
            if (j != vertical_iterations)
            {
                ExpectedMoveToPos(mockVerticalAxisCtrl, -5.0f+(j+1)*kDefaultVerticalIncrement);
                EXPECT_CALL(mockHorizontalAxisCtrl, MoveToAbsolutPosition(0.0f)).Times(1).WillOnce(Return(kOk));
            }
            
            scannerCtrl.Update();
        }
    }

    ASSERT_TRUE(scannerCtrl.GetMode() == kModeInactive);
}


TEST(ScannerCtrlTestSuite, test_scanning_both_ways)
{
    MockStepGen mockStepGen;
    MockAxisCtrl mockHorizontalAxisCtrl(mockStepGen);
    MockAxisCtrl mockVerticalAxisCtrl(mockStepGen);
    MockLidar mockLidar;
    ScannerCtrl<MockLidar> scannerCtrl(mockLidar, mockVerticalAxisCtrl, mockHorizontalAxisCtrl);
    int j;
    int i;
    int vertical_iterations = (int)((20.0f)/kDefaultVerticalIncrement);
    int horizontal_iterations = (int)((10.0f)/kDefaultHorizontalIncrement);
  
    // prepare - smaller horizontal range to speed things up
    EXPECT_CALL(mockHorizontalAxisCtrl, GetPosition()).Times(1).WillOnce(Return(10.0f));
    scannerCtrl.SetHorizontalEndPosition();

    // precondition - set a new vertical start/end pos
    EXPECT_CALL(mockVerticalAxisCtrl, GetPosition()).Times(1).WillOnce(Return(15.0f));
    scannerCtrl.SetVerticalEndPosition();
    EXPECT_CALL(mockVerticalAxisCtrl, GetPosition()).Times(1).WillOnce(Return(-5.0f));
    scannerCtrl.SetVerticalStartPosition();

    EXPECT_CALL(mockHorizontalAxisCtrl, MoveToAbsolutPosition(kDefaultHorizontalStartPosition)).Times(1);
    EXPECT_CALL(mockVerticalAxisCtrl, MoveToAbsolutPosition(-5.0f)).Times(1);
    scannerCtrl.SetMode(kModeScanning);
    
    for(j = 0; j <= vertical_iterations; j++)
    {
        // one horizontal rev...
        for (i = 0; i < horizontal_iterations; i++)
        {
            InSequence seq;
            EXPECT_CALL(mockHorizontalAxisCtrl, GetStatus()).Times(1).WillOnce(Return(kIdle));
            EXPECT_CALL(mockVerticalAxisCtrl, GetStatus()).Times(1).WillOnce(Return(kIdle));

            // from scan()
            EXPECT_CALL(mockHorizontalAxisCtrl, GetPosition()).Times(1);
            EXPECT_CALL(mockVerticalAxisCtrl, GetPosition()).Times(1);
            //////////////

            ExpectedMoveToPos(mockHorizontalAxisCtrl, (i+1)*kDefaultHorizontalIncrement);
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
            if (j != vertical_iterations)
            {
                ExpectedMoveToPos(mockVerticalAxisCtrl, -5.0f+(j+1)*kDefaultVerticalIncrement);
                EXPECT_CALL(mockHorizontalAxisCtrl, MoveToAbsolutPosition(0.0f)).Times(1).WillOnce(Return(kOk));
            }
            
            scannerCtrl.Update();
        }
    }

    ASSERT_TRUE(scannerCtrl.GetMode() == kModeInactive);
}


}