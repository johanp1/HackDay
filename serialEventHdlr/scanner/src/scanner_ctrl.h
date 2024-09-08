#ifndef __C_SCANNER_CTRL_H__
#define __C_SCANNER_CTRL_H__

#include "axis_ctrl.h"
#include "Arduino.h"

enum Mode {kModeNotHomed, kModeInactive, kModeScanning};
enum ScanningDirection { kPositive, kNegative };

constexpr float kDefaultHorizontalIncrement = 0.225f;
constexpr float kDefaultVerticalIncrement = 0.225f;

constexpr Position kDefaultHorizontalStartPosition = 0.0f;
constexpr Position kDefaultVerticalStartPosition = -45.0f;

constexpr Position kDefaultHorizontalEndPosition = 360.0f - kDefaultHorizontalIncrement;
constexpr Position kDefaultVerticalEndPosition = 45.0f;

constexpr int kLidarBiasCorrectionInterval = 100;

struct AxisConfig
{
  Position target_position;
  Position end_position;
  Position start_position;
  float increment;
};


template <class Lidar>
class ScannerCtrl
{
  public:
  ScannerCtrl(Lidar& lidar, AxisCtrl& verticalAxisCtrl, AxisCtrl& horizontalAxisCtrl) : lidar_(lidar), verticalAxisCtrl_(verticalAxisCtrl), horizontalAxisCtrl_(horizontalAxisCtrl) {};

  void SetMode(Mode m);
  void Update();
  Mode GetMode() {return mode_; };
  float GetHorizontalIncrement() {return horizontal_increment_;};
  float GetVerticalIncrement() {return vertical_increment_;};

  void SetHorizontalStartPosition();
  void SetHorizontalEndPosition();
  void SetVerticalStartPosition();
  void SetVerticalEndPosition();
  void SetVerticalHomePosition();
  void SetHorizontalIncrement(float increment) {horizontal_increment_ = increment;};
  void SetVerticalIncrement(float increment) {vertical_increment_ = increment;};
  void SetRowFirst(bool rf);
  void SetBothWays(bool b);

  private:
  void Scan();
  Position NextTargetPos(AxisConfig& config, ScanningDirection direction = kPositive);
  bool IsPosInsideStartEnd(Position pos, AxisConfig& config, float tol = 0.1f);

  Mode mode_ = kModeNotHomed;
  ScanningDirection direction_ = kPositive;
  bool both_ways_ = false;

  Position horizontal_end_position_ = kDefaultHorizontalEndPosition;
  Position horizontal_start_position_ = kDefaultHorizontalStartPosition;
  Position vertical_end_position_ = kDefaultVerticalEndPosition;
  Position vertical_start_position_ = kDefaultVerticalStartPosition;

  float horizontal_increment_ = kDefaultHorizontalIncrement;
  float vertical_increment_ = kDefaultVerticalIncrement;

  bool row_first_ = true; // scanning row first then increment vertical axis
                          // if false, obviously, scanning will first move along vertical limits, then increment horizontally

  int lidar_bias_correction_counter_ = 0;

  Lidar& lidar_;
  AxisCtrl& verticalAxisCtrl_;
  AxisCtrl& horizontalAxisCtrl_;

  AxisCtrl* majorAxisCtrl_;
  AxisCtrl* minorAxisCtrl_;
  AxisConfig majorAxisConfig_;
  AxisConfig minorAxisConfig_;
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

    if (row_first_)
    {  // scan along horizontal axis first, then increment vertical axis
      majorAxisCtrl_ = &horizontalAxisCtrl_;
      minorAxisCtrl_ = &verticalAxisCtrl_;

      majorAxisConfig_.start_position = horizontal_start_position_;
      majorAxisConfig_.end_position = horizontal_end_position_;
      majorAxisConfig_.target_position = horizontal_start_position_;
      majorAxisConfig_.increment = horizontal_increment_;

      minorAxisConfig_.start_position = vertical_start_position_;
      minorAxisConfig_.end_position = vertical_end_position_;
      minorAxisConfig_.target_position = vertical_start_position_;
      minorAxisConfig_.increment = vertical_increment_;
    }
    else
    {   // scan along vertical axis first, then increment horizontal axis
      majorAxisCtrl_ = &verticalAxisCtrl_;
      minorAxisCtrl_ = &horizontalAxisCtrl_;

      majorAxisConfig_.start_position = vertical_start_position_;
      majorAxisConfig_.end_position = vertical_end_position_;
      majorAxisConfig_.target_position = vertical_start_position_;
      majorAxisConfig_.increment = vertical_increment_;

      minorAxisConfig_.start_position = horizontal_start_position_;
      minorAxisConfig_.end_position = horizontal_end_position_;
      minorAxisConfig_.target_position = horizontal_start_position_;
      minorAxisConfig_.increment = horizontal_increment_;
    }

    majorAxisCtrl_->MoveToAbsolutPosition(majorAxisConfig_.start_position);
    minorAxisCtrl_->MoveToAbsolutPosition(minorAxisConfig_.start_position);

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
      auto next_major_target = NextTargetPos(majorAxisConfig_, direction_);
      if (IsPosInsideStartEnd(next_major_target, majorAxisConfig_, 0.005f))
      {
        if (majorAxisCtrl_->MoveToAbsolutPosition(next_major_target) == kOk)
        {
          // the move was possible, save it as new target
          majorAxisConfig_.target_position = next_major_target;
        }
      }
      else
      {
        auto next_minor_target = NextTargetPos(minorAxisConfig_);
        if (next_minor_target <= minorAxisConfig_.end_position)
        {
          if (minorAxisCtrl_->MoveToAbsolutPosition(next_minor_target) == kOk)
          {
            // the move was possible, save it as new target
            minorAxisConfig_.target_position = next_minor_target;
          
            if (!both_ways_)
            {
              // return to major axis start pos
              majorAxisConfig_.target_position = majorAxisConfig_.start_position;
              majorAxisCtrl_->MoveToAbsolutPosition(majorAxisConfig_.target_position);
            }
            else
            {
              // flip direction
              direction_ = (direction_ == kPositive ? kNegative : kPositive);
            }

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

  if (horizontal_end_position_ > kDegreesPerRev - horizontal_increment_)
  {
    horizontal_end_position_ = kDegreesPerRev - horizontal_increment_;
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
  auto pos = verticalAxisCtrl_.GetPosition();

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
void ScannerCtrl<Lidar>::SetRowFirst(bool rf)
{
  row_first_ = rf;
  cli();  // serial.send seems to be upset by interrupts...
  Serial.print("rm_");
  Serial.println(row_first_);
  sei();
}

template <class Lidar>
void ScannerCtrl<Lidar>::SetBothWays(bool b)
{
  both_ways_ = b;
  cli();  // serial.send seems to be upset by interrupts...
  Serial.print("bw_");
  Serial.println(both_ways_);
  sei();
}

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
 
template <class Lidar>
Position ScannerCtrl<Lidar>::NextTargetPos(AxisConfig& config, ScanningDirection direction)
{
  return config.target_position + config.increment * (direction == kPositive ? 1: -1);
}

template <class Lidar>
bool ScannerCtrl<Lidar>::IsPosInsideStartEnd(Position pos, AxisConfig& config, float tol)
{
  return (pos <= config.end_position + tol) && (pos >= config.start_position - tol);
}

#endif