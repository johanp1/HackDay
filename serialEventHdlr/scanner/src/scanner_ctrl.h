#ifndef __C_SCANNER_CTRL_H__
#define __C_SCANNER_CTRL_H__

#include "axis_ctrl.h"
#include "Arduino.h"

enum Mode { mode_inactive, mode_test, mode_scanning, mode_done };

constexpr float start_position_ = 0.0f;

template <class Lidar>
class ScannerCtrl
{
  public:
  ScannerCtrl(Lidar& lidar, AxisCtrl& verticalAxisCtrl, AxisCtrl& horizontalAxisCtrl) : lidar_(lidar), verticalAxisCtrl_(verticalAxisCtrl), horizontalAxisCtrl_(horizontalAxisCtrl)
  {
    lidar_ = lidar;
  };

  void SetMode(Mode m);
  void Update();
  Mode GetMode() {return mode_; };

  void SetHorizontalStartPosition();
  void SetHorizontalEndPosition();
  void SetVerticalStartPosition();
  void SetVerticalEndPosition();
  
  private:
  bool isAtTargetPos(float actual, float expected, float tol = 0.2f);

  Mode mode_ = mode_inactive;
  float horizontal_target_position_ = 0.0f;
  float vertical_target_position_ = 0.0f;
  float horizontal_end_position_ = 360.0f;
  float vertical_end_position_ = 30.0f;
  float horizontal_increment_ = 1.0f;
  float vertical_increment_ = 1.0f;

  Lidar& lidar_;
  AxisCtrl& verticalAxisCtrl_;
  AxisCtrl& horizontalAxisCtrl_;
};

template <class Lidar>
void ScannerCtrl<Lidar>::SetMode(Mode m)
{
  if ((m == mode_test) && (m != mode_))
  {
    horizontalAxisCtrl_.MoveToAbsolutPosition(start_position_);
    horizontal_target_position_ = start_position_;
    horizontal_increment_ =  9.9f;
    mode_ = m;
  }

  if ((m == mode_inactive) && (m != mode_))
  {
    mode_ = m;
  }

  if ((m == mode_done) && (m != mode_))
  {
    // go to start-pos (cw)
    horizontalAxisCtrl_.MoveToAbsolutPosition(360.0f);
    mode_ = m;
  }

  cli();  // serial.send seems to be upset by interrupts...
  Serial.print("mode_");
  Serial.println(mode_);
  sei();
};

template <class Lidar>
void ScannerCtrl<Lidar>::Update()
{
  if (mode_ == mode_done)
  {
    float pos = horizontalAxisCtrl_.GetPosition();
    if (isAtTargetPos(pos, 360.0f, 0.2f))
    {
      float new_home = pos-360.0f;
      horizontalAxisCtrl_.SetHome(new_home); // reset current position to 0
      String sendStr{"done_"};
      sendStr.concat(new_home);
      cli();  // serial.send seems to be upset by interrupts...
      Serial.println(sendStr);
      sei();

      SetMode(mode_inactive);
    } 
  }

  if (mode_ == mode_test)
  {
    float pos = horizontalAxisCtrl_.GetPosition();
    if (isAtTargetPos(pos, horizontal_target_position_, 0.25f))
    {
      // measure distance
      auto distance = lidar_.distance();
      
      String sendStr{"h_"};
      sendStr.concat(pos);
      sendStr.concat(" ");
      sendStr.concat(distance);
      cli();  // serial.send seems to be upset by interrupts...
      Serial.println(sendStr);
      sei();

      //then move to next pos
      horizontal_target_position_ += horizontal_increment_;

      // set next target, if increment makes us pass the end-pos lets consider this done
      if (horizontal_target_position_ <= horizontal_end_position_)
      {
        horizontalAxisCtrl_.MoveToAbsolutPosition(horizontal_target_position_);
      }
      else
      {
        // done
        SetMode(mode_done);
      }
    }
  }    
};

template <class Lidar>
void ScannerCtrl<Lidar>::SetHorizontalStartPosition()
{
  // re-calc end pos. end pos should be a absolut pos, not an offset to start
  horizontal_end_position_ -= horizontalAxisCtrl_.GetPosition();
  if (horizontal_end_position_ > 360)
  {
    horizontal_end_position_ = 360;
  }

  // set this pos as start
  horizontalAxisCtrl_.SetHome(0);
};

template <class Lidar>
void ScannerCtrl<Lidar>::SetHorizontalEndPosition()
{
  horizontal_end_position_ = horizontalAxisCtrl_.GetPosition();
};


template <class Lidar>
void ScannerCtrl<Lidar>::SetVerticalStartPosition()
{
  // re-calc end pos. end pos should be a absolut pos, not an offset to start
  vertical_end_position_ -= verticalAxisCtrl_.GetPosition();
  if (vertical_end_position_ > 360)
  {
    vertical_end_position_ = 360;
  }
  // set this pos as start
  verticalAxisCtrl_.SetHome(0);
};

template <class Lidar>
void ScannerCtrl<Lidar>::SetVerticalEndPosition()
{
  vertical_end_position_ = verticalAxisCtrl_.GetPosition();
};

template <class Lidar>
bool ScannerCtrl<Lidar>::isAtTargetPos(float actual, float expected, float tol)
{
  return (actual <= (expected + tol)) && (actual >= (expected - tol));
};

#endif