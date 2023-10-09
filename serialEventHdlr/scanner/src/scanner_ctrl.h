#ifndef __C_SCANNER_CTRL_H__
#define __C_SCANNER_CTRL_H__

#include "axis_ctrl.h"
#include "Arduino.h"

enum Mode {kModeNotHomed, kModeInactive, kModeScanning};

constexpr float kHorizontalIncrement = 0.45f;
constexpr float kVerticalIncrement = 0.45f;

constexpr float kDefaultHorizontalStartPosition = 0.0f;
constexpr float kDefaultVerticalStartPosition = -45.0f;

constexpr float kDefaultHorizontalEndPosition = 360.0f - kHorizontalIncrement;
constexpr float kDefaultVerticalEndPosition = 45.0f;

constexpr int kLidarBiasCorrectionInterval = 100;

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
  float horizontal_start_position_ = kDefaultHorizontalStartPosition;
  float vertical_end_position_ = kDefaultVerticalEndPosition;
  float vertical_start_position_ = kDefaultVerticalStartPosition;

  int lidar_bias_correction_counter_ = 0;

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
    float h_pos = horizontalAxisCtrl_.GetPosition();
  
    horizontal_target_position_ = horizontal_start_position_;
    vertical_target_position_ = vertical_start_position_;

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
        if (vertical_target_position_ + kVerticalIncrement <= vertical_end_position_)
        {
          if (verticalAxisCtrl_.MoveToAbsolutPosition(vertical_target_position_ + kVerticalIncrement) == kOk)
          {
            float h_pos = horizontalAxisCtrl_.GetPosition();

            // the move was possible, save it as new target
            vertical_target_position_ += kVerticalIncrement;
          
            // reset horizontal position. hpos should always be <= 360
            //horizontalAxisCtrl_.SetHome(h_pos - kDegreesPerRev);
            horizontalAxisCtrl_.MoveToAbsolutPosition(horizontal_start_position_);
            horizontal_target_position_ = horizontal_start_position_;
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
  auto pos = horizontalAxisCtrl_.GetPosition();

  // re-calc end pos. end pos should be a absolut pos, not an offset to start
  horizontal_end_position_ -= pos;

  if (horizontal_end_position_ > kDegreesPerRev - kHorizontalIncrement)
  {
    horizontal_end_position_ = kDegreesPerRev - kHorizontalIncrement;
  }

  // set this pos as start
  horizontalAxisCtrl_.SetHome(0.0f);
};

template <class Lidar>
void ScannerCtrl<Lidar>::SetHorizontalEndPosition()
{
  auto pos = horizontalAxisCtrl_.GetPosition();

  if (pos < 0)
  {
    pos = pos + kDegreesPerRev;
  }

  horizontal_end_position_ = pos;
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
  float pos = verticalAxisCtrl_.GetPosition();

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
  bool bias_correction_flag = (lidar_bias_correction_counter_ == 0 ? true : false);
  int distance;
  auto horizontal_pos = horizontalAxisCtrl_.GetPosition();
  auto vertical_pos = verticalAxisCtrl_.GetPosition();
  String sendStr{"scan_"};

  if (++lidar_bias_correction_counter_ >= kLidarBiasCorrectionInterval)
  {
    lidar_bias_correction_counter_ = 0;
  }

  distance = lidar_.distance(bias_correction_flag);

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