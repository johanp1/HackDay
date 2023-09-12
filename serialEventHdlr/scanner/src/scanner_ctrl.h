#ifndef __C_SCANNER_CTRL_H__
#define __C_SCANNER_CTRL_H__

#include "axis_ctrl.h"
#include "Arduino.h"

enum Mode {kModeNotHomed, kModeInactive, kModeScanning};

constexpr float kDegreesPerRev = 360;

constexpr float kHorizontalIncrement = 0.45f;
constexpr float kVerticalIncrement = 0.45f;

constexpr float kDefaultHorizontalStartPosition = 0.0f;
constexpr float kDefaultVerticalStartPosition = -45.0f;

constexpr float kDefaultHorizontalEndPosition = 360.0f - kHorizontalIncrement;
constexpr float kDefaultVerticalEndPosition = 45.0f;

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
  void SetVerticalHomePosition();
  
  private:
  bool IsAtTargetPos(float actual, float expected, float tol = 0.2f);
  void Scan();

  Mode mode_ = kModeNotHomed;
  float horizontal_target_position_ = kDefaultHorizontalStartPosition;
  float vertical_target_position_ = kDefaultVerticalStartPosition;
  float horizontal_end_position_ = kDefaultHorizontalEndPosition;
  float vertical_end_position_ = kDefaultVerticalEndPosition;
  float vertical_start_position_ = kDefaultVerticalStartPosition;

  Lidar& lidar_;
  AxisCtrl& verticalAxisCtrl_;
  AxisCtrl& horizontalAxisCtrl_;
};

template <class Lidar>
void ScannerCtrl<Lidar>::SetMode(Mode m)
{
  if ((m == kModeNotHomed) && (m != mode_))
  {
    mode_ = kModeNotHomed;
  }

  if ((m == kModeInactive) && (m != mode_))
  {
    mode_ = kModeInactive;
  }

  if ((m == kModeScanning) && (m != mode_))
  {
    // if current position passed 360, reset to current pos modulo 360
    float h_pos = fmod(horizontalAxisCtrl_.GetPosition(), kDegreesPerRev);
    horizontalAxisCtrl_.SetHome(h_pos);
    
    horizontal_target_position_ = kDefaultHorizontalStartPosition;
    vertical_target_position_ = kDefaultVerticalStartPosition;

    horizontalAxisCtrl_.MoveToAbsolutPosition(horizontal_target_position_);
    verticalAxisCtrl_.MoveToAbsolutPosition(vertical_target_position_);

    mode_ = kModeScanning;
  }

  cli();  // serial.send seems to be upset by interrupts...
  Serial.print("mode_");
  Serial.println(mode_);
  sei();
};

template <class Lidar>
void ScannerCtrl<Lidar>::Update()
{
  static int apa;
  if (mode_ == kModeScanning)
  {
    if ((horizontalAxisCtrl_.GetStatus() == kIdle) && (verticalAxisCtrl_.GetStatus() == kIdle))
    {
      // measure distance
      Scan();
      
      // set next target, if increment makes us pass the end-pos let's consider this rev done
      if (horizontal_target_position_ + kHorizontalIncrement <= horizontal_end_position_)
      {
        if (horizontalAxisCtrl_.MoveToAbsolutPosition(horizontal_target_position_ + kHorizontalIncrement) == kOk)
        {
          // the move was possible, save it as new target
          horizontal_target_position_ += kHorizontalIncrement;
        }
      }
      else
      {
        if (vertical_target_position_ + kVerticalIncrement<= vertical_end_position_)
        {
          if (verticalAxisCtrl_.MoveToAbsolutPosition(vertical_target_position_ + kVerticalIncrement) == kOk)
          {
            float h_pos = horizontalAxisCtrl_.GetPosition();

            // the move was possible, save it as new target
            vertical_target_position_ += kVerticalIncrement;
            //cout << apa++ << " " << vertical_target_position_ << " " << vertical_end_position_ << endl;
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
  // re-calc end pos. end pos should be a absolut pos, not an offset to start
  vertical_start_position_ = verticalAxisCtrl_.GetPosition();
 
  String sendStr{"start pos "};
  sendStr.concat(vertical_start_position_);
  cli();  // serial.send seems to be upset by interrupts...
  Serial.println(sendStr);
  sei();
};

template <class Lidar>
void ScannerCtrl<Lidar>::SetVerticalEndPosition()
{
  float pos = fmod(verticalAxisCtrl_.GetPosition(), kDegreesPerRev);

  if (pos > vertical_start_position_)
  {
    vertical_end_position_ = pos;
  
    String sendStr{"end pos "};
    sendStr.concat(vertical_end_position_);
    cli();  // serial.send seems to be upset by interrupts...
    Serial.println(sendStr);
    sei();
  }
};

template <class Lidar>
void ScannerCtrl<Lidar>::SetVerticalHomePosition()
{
  String sendStr{"curr pos "};
  sendStr.concat(verticalAxisCtrl_.GetPosition());
  sendStr.concat(" is now 0");
  cli();  // serial.send seems to be upset by interrupts...
  Serial.println(sendStr);
  sei();

  verticalAxisCtrl_.SetHome(0.0f);
  SetMode(kModeInactive);
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