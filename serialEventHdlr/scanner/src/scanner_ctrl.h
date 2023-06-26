#include "axis_ctrl.h"
#include "Arduino.h"

enum Mode { mode_inactive, mode_test, mode_scanning };

constexpr float start_position_ = 0.0f;

class ScannerCtrl
{
  public:
  ScannerCtrl(AxisCtrl& verticalAxisCtrl, AxisCtrl& horizontalAxisCtrl) : verticalAxisCtrl_(verticalAxisCtrl), horizontalAxisCtrl_(horizontalAxisCtrl){};
  void SetMode(Mode m)
  {
    if ((m != mode_inactive) && (m != mode_))
    {
      horizontalAxisCtrl_.SetAbsolutPosition(start_position_);
      horizontal_target_position_ = start_position_;
      horizontal_increment_ = (m == mode_test ? 10.0f : 1.0f);
      mode_ = m;
    }

    if ((m == mode_inactive) && (m != mode_))
    {
      mode_ = m;
    }

    Serial.print("mode ");
    Serial.println(mode_);
  };

  void Update()
  {
    if (mode_ == mode_test)
    {
      float pos = horizontalAxisCtrl_.GetPosition();
      if (isAtTargetPos(pos, horizontal_target_position_))
      {
        //measure...blocking...
        String sendStr{"h_"};
        sendStr.concat(pos);
        Serial.println(sendStr);

        //then move to next pos
        horizontal_target_position_ += horizontal_increment_;

        // set next target
        if (horizontal_target_position_ < horizontal_end_position_)
        {
          horizontalAxisCtrl_.SetAbsolutPosition(horizontal_target_position_);
        }
        else
        {
          // done
          SetMode(mode_inactive);
        }
      }
    }
  };

  Mode GetMode()
  {
    return mode_;
  };

  void SetHorizontalStartPosition()
  {
    // re-calc end pos. end pos should be a relative pos, not an offset to start
    horizontal_end_position_ -= horizontalAxisCtrl_.GetPosition();

    // set this pos as start
    horizontalAxisCtrl_.SetHome(0);
  };
  void SetHorizontalEndPosition()
  {
    horizontal_end_position_ = horizontalAxisCtrl_.GetPosition();
  };
  void SetVerticalStartPosition()
  {
    // re-calc end pos. end pos should be a relative pos, not an offset to start
    vertical_end_position_ -= verticalAxisCtrl_.GetPosition();

    // set this pos as start
    verticalAxisCtrl_.SetHome(0);
  };
  void SetVerticalEndPosition()
  {
    vertical_end_position_ = verticalAxisCtrl_.GetPosition();
  };
  
  //private:
  bool isAtTargetPos(float actual, float expected, float tol = 0.2)
  {
    return (actual <= expected + 0.2f) && (actual >= expected - 0.2f);
  };

  Mode mode_ = mode_inactive;
  float horizontal_target_position_ = 0.0f;
  float vertical_target_position_ = 0.0f;
  float horizontal_end_position_ = 360.0f;
  float vertical_end_position_ = 30.0f;
  float horizontal_increment_ = 1.0f;
  float vertical_increment_ = 1.0f;

  AxisCtrl& verticalAxisCtrl_;
  AxisCtrl& horizontalAxisCtrl_;
};