#include "axis_ctrl.h"
#include "Arduino.h"

enum Mode { mode_inactive, mode_test, mode_scanning };

class ScannerCtrl
{
  public:
  ScannerCtrl(AxisCtrl& verticalAxisCtrl, AxisCtrl& horizontalAxisCtrl) : verticalAxisCtrl_(verticalAxisCtrl), horizontalAxisCtrl_(horizontalAxisCtrl){};
  void SetMode(Mode m)
  {
    if ((m != mode_inactive) && (m != mode_))
    {
        horizontalAxisCtrl_.SetAbsolutPosition(horizontal_start_position_);
        horizontal_target_position_ = horizontal_start_position_;
        horizontal_increment_ = (m == mode_test ? 10.0f : 1.0f);
    }

    mode_ = m;
  };

  void Update()
  {
    if (mode_ == mode_test)
    {
      if (horizontalAxisCtrl_.GetPosition() == horizontal_target_position_)
      {
        //measure...blocking...
        Serial.println("measure...");

        //then move to next pos
        horizontal_target_position_ += horizontal_increment_; 
        horizontalAxisCtrl_.SetAbsolutPosition(horizontal_target_position_);
      }
    }
  };

  void SetHorizontalStartPosition(float pos)
  {
    horizontal_start_position_ = pos;
  };
  void SetHorizontalEndPosition(float pos)
  {
    horizontal_end_position_ = pos;
  };
  void SetVerticalStartPosition(float pos)
  {
    vertical_start_position_ = pos;
  };
  void SetVerticalEndPosition(float pos)
  {
    vertical_end_position_ = pos;
  };
  
  //private:
  Mode mode_ = mode_inactive;
  float horizontal_target_position_ = 0.0f;
  float vertical_target_position_ = 0.0f;
  float horizontal_end_position_ = 360.0f;
  float vertical_end_position_ = 30.0f;
  float horizontal_start_position_ = 0.0f;
  float vertical_start_position_ = 0.0f;
  float horizontal_increment_ = 1.0f;
  float vertical_increment_ = 1.0f;

  AxisCtrl& verticalAxisCtrl_;
  AxisCtrl& horizontalAxisCtrl_;
};