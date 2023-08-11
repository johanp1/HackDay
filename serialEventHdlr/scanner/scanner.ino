// full-step 400 steps/rev for motor 1:4 ratio for axis => 1600 steps/rev => 0.225 degrees/step
#include "scanner.h"
#include "receiver.h"
#include "event_generator.h"
#include "src/step_gen.h"
#include "src/axis_ctrl.h"
#include "Arduino.h"
#include "src/scanner_ctrl.h"
#include <Wire.h>
#include "LIDARLite.h"

constexpr int motor1_step_pin = 5; // x-axis step
constexpr int motor1_dir_pin = 2;  // x-axis dir
constexpr int motor2_step_pin = 6;  // y-axis step
constexpr int motor2_dir_pin = 3;   // y-axis dir
constexpr int enable_pin = 8;

constexpr milli_sec t_on = 2; //2;
constexpr milli_sec t_off = 2; //3;

static void timer2Init( void );

static void stepWrapper(String& str, StepGen* stepGen);
static void axisMoveWrapper(String& str, AxisCtrl* axisCtrl);
static void axisMoveHomeWrapper(AxisCtrl* axisCtrl);
static void setUnitsPerSecWrapper(String& str, AxisCtrl* axisCtrl);
static void modeWrapper(String& str, ScannerCtrl<LIDARLite>* ctrl);
static void setLimitWrapper(String& str, ScannerCtrl<LIDARLite>* ctrl);

static StepGen stepGen1(motor1_step_pin, motor1_dir_pin, t_on, t_off);
static StepGen stepGen2(motor2_step_pin, motor2_dir_pin, t_on, t_off, true);
AxisCtrl horizontalAxisCtrl(stepGen1);
AxisCtrl verticalAxisCtrl(stepGen2);
LIDARLite lidar;
ScannerCtrl<LIDARLite> scannerCtrl(lidar, verticalAxisCtrl, horizontalAxisCtrl);

static Receiver receiver(String("rec"));
static EventParser eventParser;

void setup() {  
  lidar.begin(0, true); // Set configuration to default and I2C to 400 kHz
  lidar.configure(0); // Change this number to try out alternate configurations

  EventHandler<void (&)(String&, StepGen*), StepGen>* step1Handler = new EventHandler<void (&)(String&, StepGen*), StepGen>(String{"step1"}, stepWrapper, &stepGen1);
  EventHandler<void (&)(String&, StepGen*), StepGen>* step2Handler = new EventHandler<void (&)(String&, StepGen*), StepGen>(String{"step2"}, stepWrapper, &stepGen2);
  EventHandler<void (&)(String&, AxisCtrl*), AxisCtrl>* horizontalMoveHandler = new EventHandler<void (&)(String&, AxisCtrl*), AxisCtrl>(String{"hor"}, axisMoveWrapper, &horizontalAxisCtrl);
  EventHandler<void (&)(String&, AxisCtrl*), AxisCtrl>* verticalMoveHandler = new EventHandler<void (&)(String&, AxisCtrl*), AxisCtrl>(String{"ver"}, axisMoveWrapper, &verticalAxisCtrl);
  EventHandlerNoArg<void (&)(AxisCtrl*), AxisCtrl>* horizontalMoveHomeHandler = new EventHandlerNoArg<void (&)(AxisCtrl*), AxisCtrl>(String{"hhome"}, axisMoveHomeWrapper, &horizontalAxisCtrl);
  EventHandlerNoArg<void (&)(AxisCtrl*), AxisCtrl>* verticalMoveHomeHandler = new EventHandlerNoArg<void (&)(AxisCtrl*), AxisCtrl>(String{"vhome"}, axisMoveHomeWrapper, &verticalAxisCtrl);
  EventHandler<void (&)(String&, AxisCtrl*), AxisCtrl>* setHorizontalUPSHandler = new EventHandler<void (&)(String&, AxisCtrl*), AxisCtrl>(String{"hups"}, setUnitsPerSecWrapper, &horizontalAxisCtrl);
  EventHandler<void (&)(String&, AxisCtrl*), AxisCtrl>* setVerticalUPSHandler = new EventHandler<void (&)(String&, AxisCtrl*), AxisCtrl>(String{"vups"}, setUnitsPerSecWrapper, &verticalAxisCtrl);
  EventHandler<void (&)(String&, ScannerCtrl<LIDARLite>*), ScannerCtrl<LIDARLite>>* modeHandler = new EventHandler<void (&)(String&, ScannerCtrl<LIDARLite>*), ScannerCtrl<LIDARLite>>(String{"mode"}, modeWrapper, &scannerCtrl);
  EventHandler<void (&)(String&, ScannerCtrl<LIDARLite>*), ScannerCtrl<LIDARLite>>* setLimitHandler = new EventHandler<void (&)(String&, ScannerCtrl<LIDARLite>*), ScannerCtrl<LIDARLite>>(String{"set"}, setLimitWrapper, &scannerCtrl);
  
  cli();
  timer2Init();
 
  Serial.begin(9600);  // opens serial port
  Serial.setTimeout(500);

  pinMode(enable_pin, OUTPUT);
  digitalWrite(enable_pin, LOW);
  
  Serial.println("scanner::setup()"); // tell server setup is done

  receiver.addEventListner(&eventParser);
  eventParser.AddAcceptedHandler(*step1Handler);
  eventParser.AddAcceptedHandler(*step2Handler);
  eventParser.AddAcceptedHandler(*horizontalMoveHandler);
  eventParser.AddAcceptedHandler(*verticalMoveHandler);
  eventParser.AddAcceptedHandler(*horizontalMoveHomeHandler);
  eventParser.AddAcceptedHandler(*verticalMoveHomeHandler);
  eventParser.AddAcceptedHandler(*setHorizontalUPSHandler);
  eventParser.AddAcceptedHandler(*setVerticalUPSHandler);
  eventParser.AddAcceptedHandler(*modeHandler);
  eventParser.AddAcceptedHandler(*setLimitHandler);

  horizontalAxisCtrl.SetScale(2.0f*4.0f*200.0f/360.0f); // steps/unit (degrees) #microsteps*ratio*(steps/rev)/unit
  verticalAxisCtrl.SetScale(4.0f*400.0f/360.0f); // steps/unit (degrees) #microsteps*(steps/rev)/unit

  sei();
}

void loop() {
  scannerCtrl.Update();  
  delay(5); 
}

static void timer2Init( void )
{
  TIMSK2 = (1<<OCIE2A);                    // enable Timer2 Output Compare Match A Interrupt Enable
  TCCR2A = (1<<WGM21);                     // enable CTC mode, OCR2A as TOP
  TCCR2B = (1<<CS22)|(1<<CS21)|(1<<CS20);  // prescaler 1024
  OCR2A = 15;                              // compare match every Xth milli-sec. @20MHz => 77 = 5ms, 38 = 2.5ms, 15 = 1ms
}

ISR( TIMER2_COMPA_vect  )
{ 
  stepGen1.Update();
  stepGen2.Update();
}

void serialEvent()
{
  receiver.scan();
}

static void stepWrapper(String& str, StepGen* stepGen)
{
  auto steps = str.toInt();
  stepGen->SetDirection(steps > 0 ? direction_forward : direction_reverse);
  stepGen->Step(abs(steps));
}

static void axisMoveWrapper(String& str, AxisCtrl* axisCtrl)
{
  auto pos = str.toFloat();
  axisCtrl->MoveToRelativePosition(pos);
}

static void axisMoveHomeWrapper(AxisCtrl* axisCtrl)
{
  axisCtrl->MoveToAbsolutPosition(0);
}

static void modeWrapper(String& str, ScannerCtrl<LIDARLite>* ctrl)
{
  Mode mode = static_cast<Mode>(str.toInt());
  ctrl->SetMode(mode);
}

static void setUnitsPerSecWrapper(String& str, AxisCtrl* axisCtrl)
{
  auto ups = str.toFloat(); 
  axisCtrl->SetSpeed(ups);
}

static void setLimitWrapper(String& str, ScannerCtrl<LIDARLite>* ctrl)
{
  if (str.compareTo("vs") == 0)
  {
    ctrl->SetVerticalStartPosition();
  }
  if (str.compareTo("ve") == 0)
  {
    ctrl->SetVerticalEndPosition();
  }
  if (str.compareTo("hs") == 0)
  {
    ctrl->SetHorizontalStartPosition();
  }
  if (str.compareTo("he") == 0)
  {
    ctrl->SetHorizontalEndPosition();
  }
}
