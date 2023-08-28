#ifndef __C_SCANNER_CTRL_H__
#define __C_SCANNER_CTRL_H__

#include "axis_ctrl.h"
#include "Arduino.h"

enum Mode { kModeInactive, kModeTest, kModeScanning, kModeDone };

constexpr float kDegreesPerRev = 360;
constexpr float kStartPosition = 0.0f;

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
  bool IsAtTargetPos(float actual, float expected, float tol = 0.2f);
  void Scan();

  Mode mode_ = kModeInactive;
  float horizontal_target_position_ = 0.0f;
  float vertical_target_position_ = 0.0f;
  float horizontal_increment_ = 0.45f;
  float vertical_increment_ = 0.45f;
  float horizontal_end_position_ = 360.0f - horizontal_increment_;
  float vertical_end_position_ = 90.0f;

  Lidar& lidar_;
  AxisCtrl& verticalAxisCtrl_;
  AxisCtrl& horizontalAxisCtrl_;
};

template <class Lidar>
void ScannerCtrl<Lidar>::SetMode(Mode m)
{
  if ((m == kModeScanning) && (m != mode_))
  {
    // if current position passed 360, reset to current pos modulo 360
    float h_pos = fmod(horizontalAxisCtrl_.GetPosition(), kDegreesPerRev);
    horizontalAxisCtrl_.SetHome(h_pos);
    
    horizontalAxisCtrl_.MoveToAbsolutPosition(kStartPosition);
    verticalAxisCtrl_.MoveToAbsolutPosition(kStartPosition);
    horizontal_target_position_ = kStartPosition;
    vertical_target_position_ = kStartPosition;
    horizontal_increment_ =  0.45f;
    vertical_increment_ =  0.45f;

    mode_ = kModeScanning;
  }

  if ((m == kModeTest) && (m != mode_))
  {
    // if current position passed 360, reset to current pos modulo 360
    float pos = fmod(horizontalAxisCtrl_.GetPosition(), kDegreesPerRev);
    horizontalAxisCtrl_.SetHome(pos);

    horizontalAxisCtrl_.MoveToAbsolutPosition(kStartPosition);
    horizontal_target_position_ = kStartPosition;
    horizontal_increment_ =  9.9f;
    mode_ = kModeTest;
  }

  if ((m == kModeInactive) && (m != mode_))
  {
    mode_ = kModeInactive;
  }

  if ((m == kModeDone) && (m != mode_))
  {
    // go to start-pos (cw)
    horizontalAxisCtrl_.MoveToAbsolutPosition(360.0f);
    mode_ = kModeDone;
  }

  cli();  // serial.send seems to be upset by interrupts...
  Serial.print("mode_");
  Serial.println(mode_);
  sei();
};

template <class Lidar>
void ScannerCtrl<Lidar>::Update()
{
  if (mode_ == kModeScanning)
  {
    if ((horizontalAxisCtrl_.GetStatus() == kIdle) && (verticalAxisCtrl_.GetStatus() == kIdle))
    {
      // measure distance
      Scan();
      
      // set next target, if increment makes us pass the end-pos let's consider this rev done
      if (horizontal_target_position_ + horizontal_increment_ <= horizontal_end_position_)
      {
        if (horizontalAxisCtrl_.MoveToAbsolutPosition(horizontal_target_position_ + horizontal_increment_) == kOk)
        {
          // the move was possible, save it as new target
          horizontal_target_position_ += horizontal_increment_;
        }
      }
      else
      {
        if (vertical_target_position_ + vertical_increment_<= vertical_end_position_)
        {
          if (verticalAxisCtrl_.MoveToAbsolutPosition(vertical_target_position_ + vertical_increment_) == kOk)
          {
            float h_pos = horizontalAxisCtrl_.GetPosition();

            // the move was possible, save it as new target
            vertical_target_position_ += vertical_increment_;
            
            // reset horizontal position. hpos should always be <= 360
            horizontalAxisCtrl_.SetHome(h_pos - kDegreesPerRev);
            horizontalAxisCtrl_.MoveToAbsolutPosition(0.0f);
            horizontal_target_position_ = 0.0f;
          }
        }
        else
        {
          // scan done
          SetMode(kModeInactive);
        }
      }
    }
  }

  if (mode_ == kModeDone)
  {
    float pos = horizontalAxisCtrl_.GetPosition();
    if (IsAtTargetPos(pos, 360.0f, 0.2f))
    {
      float new_home = pos-360.0f;
      horizontalAxisCtrl_.SetHome(new_home); // reset current position to 0
      String sendStr{"done_"};
      sendStr.concat(new_home);
      cli();  // serial.send seems to be upset by interrupts...
      Serial.println(sendStr);
      sei();

      SetMode(kModeInactive);
    } 
  }

  if (mode_ == kModeTest)
  {
    float pos = horizontalAxisCtrl_.GetPosition();
    if (IsAtTargetPos(pos, horizontal_target_position_, 0.25f))
    {
      // measure distance
      auto distance = lidar_.distance();
  
      String sendStr{"scan_"};
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
        SetMode(kModeDone);
      }
    }
  }    
};

template <class Lidar>
void ScannerCtrl<Lidar>::SetHorizontalStartPosition()
{
  // re-calc end pos. end pos should be a absolut pos, not an offset to start
  horizontal_end_position_ -= fmod(horizontalAxisCtrl_.GetPosition(), kDegreesPerRev);

  // set this pos as start
  horizontalAxisCtrl_.SetHome(0.0f);
};

template <class Lidar>
void ScannerCtrl<Lidar>::SetHorizontalEndPosition()
{
  horizontal_end_position_ = fmod(horizontalAxisCtrl_.GetPosition(), kDegreesPerRev);
};

template <class Lidar>
void ScannerCtrl<Lidar>::SetVerticalStartPosition()
{
  String sendStr{"current pos "};
  sendStr.concat(verticalAxisCtrl_.GetPosition());
  sendStr.concat("\n");
  sendStr.concat("old end ");
  sendStr.concat(vertical_end_position_);
  sendStr.concat("\n");
  
  // re-calc end pos. end pos should be a absolut pos, not an offset to start
  vertical_end_position_ -= fmod(verticalAxisCtrl_.GetPosition(), kDegreesPerRev);

  sendStr.concat("new end ");
  sendStr.concat(vertical_end_position_);
  sendStr.concat("\n");
  
  // set this pos as start
  verticalAxisCtrl_.SetHome(0.0f);

  sendStr.concat("new curr ");
  sendStr.concat(verticalAxisCtrl_.GetPosition());
  cli();  // serial.send seems to be upset by interrupts...
  Serial.println(sendStr);
  sei();
};

template <class Lidar>
void ScannerCtrl<Lidar>::SetVerticalEndPosition()
{
  vertical_end_position_ = fmod(verticalAxisCtrl_.GetPosition(), kDegreesPerRev);

  String sendStr{"end pos "};
  sendStr.concat(vertical_end_position_);
  sendStr.concat("\n");
  sendStr.concat("curr pos ");
  sendStr.concat(verticalAxisCtrl_.GetPosition());
  cli();  // serial.send seems to be upset by interrupts...
  Serial.println(sendStr);
  sei();
};

template <class Lidar>
bool ScannerCtrl<Lidar>::IsAtTargetPos(float actual, float expected, float tol)
{
  return (actual <= (expected + tol)) && (actual >= (expected - tol));
};

template <class Lidar>
void ScannerCtrl<Lidar>::Scan()
{
  auto distance = lidar_.distance();
  auto horizontal_pos = horizontalAxisCtrl_.GetPosition();
  auto vertical_pos = verticalAxisCtrl_.GetPosition();
  String sendStr{"scan_"};

  sendStr.concat(horizontal_pos);
  sendStr.concat("_");
  sendStr.concat(vertical_pos);
  sendStr.concat("_");
  sendStr.concat(distance);
  cli();  // serial.send seems to be upset by interrupts...
  Serial.println(sendStr);
  sei();
};

#endif