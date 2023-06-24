// full-step 400 steps/rev for motor 1:4 ratio for axis => 1600 steps/rev => 0.225 degrees/step
#include "scanner.h"
#include "receiver.h"
#include "event_generator.h"
#include "src/step_gen.h"
#include "src/axis_ctrl.h"
#include "Arduino.h"
#include "src/scanner_ctrl.h"

constexpr int motor1_step_pin = 5; // x-axis step
constexpr int motor1_dir_pin = 2;  // x-axis dir
constexpr int motor2_step_pin = 6;  // y-axis step
constexpr int motor2_dir_pin = 3;   // y-axis dir
constexpr int enable_pin = 8;

constexpr milli_sec t_on = 5;//2;
constexpr milli_sec t_off = 5;//3;

static void timer2Init( void );
static void axisMoveWrapper(String& str, AxisCtrl* axisCtrl);
//static void stepEventWrapper(String& str, StepGen* stepGen);
static void modeWrapper(String& str, ScannerCtrl* ctrl);
static void setVerticalStartWrapper(ScannerCtrl* ctrl);
static void setVerticalEndWrapper(ScannerCtrl* ctrl);
static void setHorizontalStartWrapper(ScannerCtrl* ctrl);
static void setHorizontalEndWrapper(ScannerCtrl* ctrl);

static StepGen stepGen1(motor1_step_pin, motor1_dir_pin, t_on, t_off);
static StepGen stepGen2(motor2_step_pin, motor2_dir_pin, t_on, t_off);
AxisCtrl horizontalAxisCtrl(stepGen1);
AxisCtrl verticalAxisCtrl(stepGen2);

static Receiver receiver(String("rec"));
static EventParser eventParser;

static ScannerCtrl scannerCtrl(verticalAxisCtrl, horizontalAxisCtrl);

void setup() {  
  EventHandler<void (&)(String&, AxisCtrl*), AxisCtrl>* horizontalMoveHandler = new EventHandler<void (&)(String&, AxisCtrl*), AxisCtrl>(String{"hor"}, axisMoveWrapper, &horizontalAxisCtrl);
  EventHandler<void (&)(String&, AxisCtrl*), AxisCtrl>* verticalMoveHandler = new EventHandler<void (&)(String&, AxisCtrl*), AxisCtrl>(String{"ver"}, axisMoveWrapper, &verticalAxisCtrl);
  //EventHandler<void (&)(String&, StepGen*), StepGen>* step1EventHandler = new EventHandler<void (&)(String&, StepGen*), StepGen>(String{"step1"}, stepEventWrapper, &stepGen1);
  //EventHandler<void (&)(String&, StepGen*), StepGen>* step2EventHandler = new EventHandler<void (&)(String&, StepGen*), StepGen>(String{"step2"}, stepEventWrapper, &stepGen2);

  EventHandler<void (&)(String&, ScannerCtrl*), ScannerCtrl>* modeHandler = new EventHandler<void (&)(String&, ScannerCtrl*), ScannerCtrl>(String{"mode"}, modeWrapper, &scannerCtrl);
  EventHandlerNoArg<void (&)(ScannerCtrl*), ScannerCtrl>* setVerticalStartHandler = new EventHandlerNoArg<void (&)(ScannerCtrl*), ScannerCtrl>(String{"vs"}, setVerticalStartWrapper, &scannerCtrl);
  EventHandlerNoArg<void (&)(ScannerCtrl*), ScannerCtrl>* setVerticalEndHandler = new EventHandlerNoArg<void (&)(ScannerCtrl*), ScannerCtrl>(String{"ve"}, setVerticalEndWrapper, &scannerCtrl);
  EventHandlerNoArg<void (&)(ScannerCtrl*), ScannerCtrl>* setHorizontalStartHandler = new EventHandlerNoArg<void (&)(ScannerCtrl*), ScannerCtrl>(String{"hs"}, setHorizontalStartWrapper, &scannerCtrl);
  EventHandlerNoArg<void (&)(ScannerCtrl*), ScannerCtrl>* setHorizontalEndHandler = new EventHandlerNoArg<void (&)(ScannerCtrl*), ScannerCtrl>(String{"he"}, setHorizontalEndWrapper, &scannerCtrl);

  cli();
  timer2Init();
  sei();

  Serial.begin(9600);  // opens serial port
  Serial.setTimeout(500);

  pinMode(enable_pin, OUTPUT);
  digitalWrite(enable_pin, LOW);
  
  Serial.println("scanner::setup()"); // tell server setup is done

  receiver.addEventListner(&eventParser);
  eventParser.AddAcceptedHandler(*horizontalMoveHandler);
  eventParser.AddAcceptedHandler(*verticalMoveHandler);
  //eventParser.AddAcceptedHandler(*step1EventHandler);
  //eventParser.AddAcceptedHandler(*step2EventHandler);
  eventParser.AddAcceptedHandler(*modeHandler);
  eventParser.AddAcceptedHandler(*setVerticalStartHandler);
  eventParser.AddAcceptedHandler(*setVerticalEndHandler);
  eventParser.AddAcceptedHandler(*setHorizontalStartHandler);
  eventParser.AddAcceptedHandler(*setHorizontalEndHandler);

}

void loop() {
  scannerCtrl.Update();
  delay(5);
}


static void timer2Init( void )
{
  TIMSK2 = (1 << OCIE2A);                  // enable Timer2 Output Compare Match A Interrupt Enable
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

static void axisMoveWrapper(String& str, AxisCtrl* axisCtrl)
{
  auto pos = str.toFloat();
  axisCtrl->SetRelativePosition(pos);
}

/*static void stepEventWrapper(String& str, StepGen* stepGen)
{
  auto steps = str.toInt();
  stepGen->SetDirection(steps > 0 ? direction_forward : direction_reverse);
  stepGen->Step(steps);
}*/

static void modeWrapper(String& str, ScannerCtrl* ctrl)
{
  Mode mode = static_cast<Mode>(str.toInt());
  ctrl->SetMode(mode);
}

static void setVerticalStartWrapper(ScannerCtrl* ctrl)
{
  scannerCtrl.SetVerticalStartPosition();
}

static void setVerticalEndWrapper(ScannerCtrl* ctrl)
{
  scannerCtrl.SetVerticalEndPosition();
}

static void setHorizontalStartWrapper(ScannerCtrl* ctrl)
{
  scannerCtrl.SetHorizontalStartPosition();
}

static void setHorizontalEndWrapper(ScannerCtrl* ctrl)
{
  scannerCtrl.SetHorizontalEndPosition();
}