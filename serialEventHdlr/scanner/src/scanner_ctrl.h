#ifndef __C_SCANNER_CTRL_H__
#define __C_SCANNER_CTRL_H__

#include "axis_ctrl.h"
#include "Arduino.h"

enum Mode { mode_inactive, mode_test, mode_scanning, mode_done };

constexpr float k_degrees_per_rev = 360;
constexpr float start_position_ = 0.0f;

static float my_fmod(float x, float denominator );

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
  float horizontal_increment_ = 0.9f;
  float vertical_increment_ = 0.9f;
  float horizontal_end_position_ = 360.0f - horizontal_increment_;
  float vertical_end_position_ = 90.0f;
  unsigned int watchdog = 0;

  Lidar& lidar_;
  AxisCtrl& verticalAxisCtrl_;
  AxisCtrl& horizontalAxisCtrl_;
};

template <class Lidar>
void ScannerCtrl<Lidar>::SetMode(Mode m)
{
  if ((m == mode_scanning) && (m != mode_))
  {
    // if current position passed 360, reset to current pos modulo 360
    float hpos = fmod(horizontalAxisCtrl_.GetPosition(), k_degrees_per_rev);
    horizontalAxisCtrl_.SetHome(hpos);
    
    horizontalAxisCtrl_.MoveToAbsolutPosition(start_position_);
    verticalAxisCtrl_.MoveToAbsolutPosition(start_position_);
    horizontal_target_position_ = start_position_;
    vertical_target_position_ = start_position_;
    horizontal_increment_ =  0.9f;
    vertical_increment_ =  0.9f;

    mode_ = mode_scanning;

    String sendStr{"start_"};
    sendStr.concat(hpos);
    sendStr.concat("_");
    sendStr.concat(horizontal_target_position_);
    sendStr.concat("_");
    sendStr.concat(vertical_target_position_);
    cli();  // serial.send seems to be upset by interrupts...
    Serial.println(sendStr);
    sei();

    watchdog = 0;
  }

  if ((m == mode_test) && (m != mode_))
  {
    // if current position passed 360, reset to current pos modulo 360
    float pos = fmod(horizontalAxisCtrl_.GetPosition(), k_degrees_per_rev);
    horizontalAxisCtrl_.SetHome(pos);

    horizontalAxisCtrl_.MoveToAbsolutPosition(start_position_);
    horizontal_target_position_ = start_position_;
    horizontal_increment_ =  9.9f;
    mode_ = mode_test;
  }

  if ((m == mode_inactive) && (m != mode_))
  {
    mode_ = mode_inactive;
  }

  if ((m == mode_done) && (m != mode_))
  {
    // go to start-pos (cw)
    horizontalAxisCtrl_.MoveToAbsolutPosition(360.0f);
    mode_ = mode_done;
  }

  cli();  // serial.send seems to be upset by interrupts...
  Serial.print("mode_");
  Serial.println(mode_);
  sei();
};

template <class Lidar>
void ScannerCtrl<Lidar>::Update()
{
  if (mode_ == mode_scanning)
  {
    watchdog++;
    float hpos = horizontalAxisCtrl_.GetPosition();
    float vpos = verticalAxisCtrl_.GetPosition();
    if ((isAtTargetPos(hpos, horizontal_target_position_, 0.05f)) && (isAtTargetPos(vpos, vertical_target_position_, 0.05f)))
    {
      watchdog = 0;
      // measure distance
      auto distance = lidar_.distance();
      
      String sendStr{"scan_"};
      sendStr.concat(hpos);
      sendStr.concat("_");
      sendStr.concat(vpos);
      sendStr.concat("_");
      sendStr.concat(distance);
      cli();  // serial.send seems to be upset by interrupts...
      Serial.println(sendStr);
      sei();

      //then move to next pos
      horizontal_target_position_ += horizontal_increment_;

      // set next target, if increment makes us pass the end-pos lets consider this done
      if (horizontal_target_position_ <= horizontal_end_position_ + 0.05) // adding random tolerance
      {
        horizontalAxisCtrl_.MoveToAbsolutPosition(horizontal_target_position_);
      }
      else
      {
        //move to next vertical pos
        vertical_target_position_ += vertical_increment_;
        if (vertical_target_position_ <= vertical_end_position_)
        {
          verticalAxisCtrl_.MoveToAbsolutPosition(vertical_target_position_); 

          // reset horizontal position. hpos should always be <= 360
          horizontalAxisCtrl_.SetHome(hpos - k_degrees_per_rev);
          horizontalAxisCtrl_.MoveToAbsolutPosition(0.0f);
          horizontal_target_position_ = 0.0f;
        }
        else
        {
          // done
          SetMode(mode_inactive);
        }
      }
    }
  }    

  if (watchdog > 1000)
  {
    String sendStr{"wd_"};
    sendStr.concat(hpos);
    sendStr.concat(" ");
    sendStr.concat(horizontal_target_position_);
    sendStr.concat("_");
    sendStr.concat(vpos);
    sendStr.concat(" ");
    sendStr.concat(vertical_target_position_);
    cli();  // serial.send seems to be upset by interrupts...
    Serial.println(sendStr);
    sei();

    watchdog = 0;
  }

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
        SetMode(mode_done);
      }
    }
  }    
};

template <class Lidar>
void ScannerCtrl<Lidar>::SetHorizontalStartPosition()
{
  // re-calc end pos. end pos should be a absolut pos, not an offset to start
  horizontal_end_position_ -= fmod(horizontalAxisCtrl_.GetPosition(), k_degrees_per_rev);

  // set this pos as start
  horizontalAxisCtrl_.SetHome(0.0f);
};

template <class Lidar>
void ScannerCtrl<Lidar>::SetHorizontalEndPosition()
{
  horizontal_end_position_ = fmod(horizontalAxisCtrl_.GetPosition(), k_degrees_per_rev);
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
  vertical_end_position_ -= fmod(verticalAxisCtrl_.GetPosition(), k_degrees_per_rev);

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
  vertical_end_position_ = fmod(verticalAxisCtrl_.GetPosition(), k_degrees_per_rev);

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
bool ScannerCtrl<Lidar>::isAtTargetPos(float actual, float expected, float tol)
{
  return (actual <= (expected + tol)) && (actual >= (expected - tol));
};

float my_fmod(float x, float denominator )
{
  float retval = fmod(abs(x), denominator);
  return (x >= 0) ? retval : -retval;
}

#endif