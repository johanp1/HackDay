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
//#include <iostream>

constexpr int motor1_step_pin = 5; // x-axis step
constexpr int motor1_dir_pin = 2;  // x-axis dir
constexpr int motor2_step_pin = 6;  // y-axis step
constexpr int motor2_dir_pin = 3;   // y-axis dir
constexpr int enable_pin = 8;

constexpr micro_sec t_on = 250;
constexpr micro_sec t_off = 250;

static void timer2Init( void );

static void stepWrapper(String& str, StepGen* stepGen);
static void axisRelMoveWrapper(String& str, AxisCtrl* axisCtrl);
static void axisAbsMoveWrapper(String& str, AxisCtrl* axisCtrl);
static void setUnitsPerSecWrapper(String& str, AxisCtrl* axisCtrl);
static void modeWrapper(String& str, ScannerCtrl<LIDARLite>* ctrl);
static void setLimitWrapper(String& str, ScannerCtrl<LIDARLite>* ctrl);
static void getPosWrapper(AxisCtrl* axisCtrl);
static void setRowFirstWrapper(String& str, ScannerCtrl<LIDARLite>* ctrl);
static void setHorizontalIncrementWrapper(String& str, ScannerCtrl<LIDARLite>* ctrl);
static void setVerticalIncrementWrapper(String& str, ScannerCtrl<LIDARLite>* ctrl);

static StepGen stepGen1(motor1_step_pin, motor1_dir_pin, t_on, t_off, false, 500, 60);
static StepGen stepGen2(motor2_step_pin, motor2_dir_pin, t_on, t_off, true, 500, 30);
RotaryAxisCtrl horizontalAxisCtrl(stepGen1);
AxisCtrl verticalAxisCtrl(stepGen2);
LIDARLite lidar;
ScannerCtrl<LIDARLite> scannerCtrl(lidar, verticalAxisCtrl, horizontalAxisCtrl);

static Receiver receiver(String("rec"));
static EventParser eventParser;

String vpos = String{"vpos"};
JogHandler verticalJogHandler(verticalAxisCtrl, vpos);
String hpos = String{"hpos"};
JogHandler horizontalJogHandler(horizontalAxisCtrl, hpos);

void setup() {    
  lidar.begin(0, true); // Set configuration to default and I2C to 400 kHz
  lidar.configure(0); // Change this number to try out alternate configurations

  EventHandler<void (&)(String&, StepGen*), StepGen>* step1Handler = new EventHandler<void (&)(String&, StepGen*), StepGen>(String{"step1"}, stepWrapper, &stepGen1);
  EventHandler<void (&)(String&, StepGen*), StepGen>* step2Handler = new EventHandler<void (&)(String&, StepGen*), StepGen>(String{"step2"}, stepWrapper, &stepGen2);
  EventHandler<void (&)(String&, AxisCtrl*), AxisCtrl>* horizontalMoveHomeHandler = new EventHandler<void (&)(String&, AxisCtrl*), AxisCtrl>(String{"ham"}, axisAbsMoveWrapper, &horizontalAxisCtrl);
  EventHandler<void (&)(String&, AxisCtrl*), AxisCtrl>* verticalMoveHomeHandler = new EventHandler<void (&)(String&, AxisCtrl*), AxisCtrl>(String{"vam"}, axisAbsMoveWrapper, &verticalAxisCtrl);
  EventHandler<void (&)(String&, AxisCtrl*), AxisCtrl>* setHorizontalUPSHandler = new EventHandler<void (&)(String&, AxisCtrl*), AxisCtrl>(String{"hups"}, setUnitsPerSecWrapper, &horizontalAxisCtrl);
  EventHandler<void (&)(String&, AxisCtrl*), AxisCtrl>* setVerticalUPSHandler = new EventHandler<void (&)(String&, AxisCtrl*), AxisCtrl>(String{"vups"}, setUnitsPerSecWrapper, &verticalAxisCtrl);
  EventHandler<void (&)(String&, ScannerCtrl<LIDARLite>*), ScannerCtrl<LIDARLite>>* modeHandler = new EventHandler<void (&)(String&, ScannerCtrl<LIDARLite>*), ScannerCtrl<LIDARLite>>(String{"mode"}, modeWrapper, &scannerCtrl);
  EventHandler<void (&)(String&, ScannerCtrl<LIDARLite>*), ScannerCtrl<LIDARLite>>* setLimitHandler = new EventHandler<void (&)(String&, ScannerCtrl<LIDARLite>*), ScannerCtrl<LIDARLite>>(String{"set"}, setLimitWrapper, &scannerCtrl);
  EventHandler<void (&)(String&, ScannerCtrl<LIDARLite>*), ScannerCtrl<LIDARLite>>* setRowFirstHandler = new EventHandler<void (&)(String&, ScannerCtrl<LIDARLite>*), ScannerCtrl<LIDARLite>>(String{"rf"}, setRowFirstWrapper, &scannerCtrl);
  EventHandler<void (&)(String&, ScannerCtrl<LIDARLite>*), ScannerCtrl<LIDARLite>>* setHorizontalIncrementHandler = new EventHandler<void (&)(String&, ScannerCtrl<LIDARLite>*), ScannerCtrl<LIDARLite>>(String{"hi"}, setHorizontalIncrementWrapper, &scannerCtrl);
  EventHandler<void (&)(String&, ScannerCtrl<LIDARLite>*), ScannerCtrl<LIDARLite>>* setVerticalIncrementHandler = new EventHandler<void (&)(String&, ScannerCtrl<LIDARLite>*), ScannerCtrl<LIDARLite>>(String{"vi"}, setVerticalIncrementWrapper, &scannerCtrl);
  EventHandler<void (&)(String&, JogHandler*), JogHandler>* horizontalJogHdlr = new EventHandler<void (&)(String&, JogHandler*), JogHandler>(String{"hjog"}, JogHandler::JogStartHandler, &horizontalJogHandler);
  EventHandler<void (&)(String&, JogHandler*), JogHandler>* verticalJogHdlr = new EventHandler<void (&)(String&, JogHandler*), JogHandler>(String{"vjog"}, JogHandler::JogStartHandler, &verticalJogHandler);
  //EventHandler<void (&)(String&, AxisCtrl*), AxisCtrl>* horizontalMoveHandler = new EventHandler<void (&)(String&, AxisCtrl*), AxisCtrl>(String{"hrm"}, axisRelMoveWrapper, &horizontalAxisCtrl);
  //EventHandler<void (&)(String&, AxisCtrl*), AxisCtrl>* verticalMoveHandler = new EventHandler<void (&)(String&, AxisCtrl*), AxisCtrl>(String{"vrm"}, axisRelMoveWrapper, &verticalAxisCtrl);
  //EventHandlerNoArg<void (&)(AxisCtrl*), AxisCtrl>* verticalGetHandler = new EventHandlerNoArg<void (&)(AxisCtrl*), AxisCtrl>(String{"getv"}, getPosWrapper, &verticalAxisCtrl);
  //EventHandlerNoArg<void (&)(AxisCtrl*), AxisCtrl>* horizontalGetHandler = new EventHandlerNoArg<void (&)(AxisCtrl*), AxisCtrl>(String{"geth"}, getPosWrapper, &horizontalAxisCtrl);
  //EventHandler<void (&)(String&, AxisCtrl*), AxisCtrl>* horizontalJogHandler = new EventHandler<void (&)(String&, AxisCtrl*), AxisCtrl>(String{"hjog"}, horizontalJogWrapper, &horizontalAxisCtrl);
  //EventHandler<void (&)(String&, AxisCtrl*), AxisCtrl>* verticalJogHandler = new EventHandler<void (&)(String&, AxisCtrl*), AxisCtrl>(String{"vjog"}, verticalJogWrapper, &verticalAxisCtrl);


  cli();
  timer2Init();
  sei();

  Serial.begin(57600);  // opens serial port
  Serial.setTimeout(500);

  pinMode(enable_pin, OUTPUT);
  digitalWrite(enable_pin, LOW);
  
  Serial.println("scanner::setup()"); // tell server setup is done

  receiver.addEventListner(&eventParser);
  eventParser.AddAcceptedHandler(*step1Handler);
  eventParser.AddAcceptedHandler(*step2Handler);
  //eventParser.AddAcceptedHandler(*horizontalMoveHandler);
  //eventParser.AddAcceptedHandler(*verticalMoveHandler);
  eventParser.AddAcceptedHandler(*horizontalMoveHomeHandler);
  eventParser.AddAcceptedHandler(*verticalMoveHomeHandler);
  eventParser.AddAcceptedHandler(*setHorizontalUPSHandler);
  eventParser.AddAcceptedHandler(*setVerticalUPSHandler);
  eventParser.AddAcceptedHandler(*modeHandler);
  eventParser.AddAcceptedHandler(*setLimitHandler);
  //eventParser.AddAcceptedHandler(*verticalGetHandler);
  //eventParser.AddAcceptedHandler(*horizontalGetHandler);
  eventParser.AddAcceptedHandler(*setRowFirstHandler);
  eventParser.AddAcceptedHandler(*setHorizontalIncrementHandler);
  eventParser.AddAcceptedHandler(*setVerticalIncrementHandler);
  eventParser.AddAcceptedHandler(*horizontalJogHdlr);
  eventParser.AddAcceptedHandler(*verticalJogHdlr);
 
  horizontalAxisCtrl.SetScale(2.0f*4.0f*400.0f/360.0f); // 8.8889 steps/unit (degrees) #microsteps*ratio*(steps/unit)
  verticalAxisCtrl.SetScale(8.0f*400.0f/360.0f); // 8.8889 steps/unit (degrees) #microsteps*(steps/unit)
  scannerCtrl.SetHorizontalIncrement(0.1125); // 1/horizontal_scale [units/step] minimum increment...
  scannerCtrl.SetVerticalIncrement(0.1125);
}

void loop() {
  scannerCtrl.Update();  
  //delay(1);
  delayMicroseconds(1000); 
}

static void timer2Init( void )
{
  TIMSK2 = (1<<OCIE2A);                    // enable Timer2 Output Compare Match A Interrupt Enable
  TCCR2A = (1<<WGM21);                     // enable CTC mode, OCR2A as TOP

  TCCR2B = (1<<CS22);                      // prescaler 64
  OCR2A = 62;                             // compare match every Xth milli-sec. @20MHz => 124 = 500us, 61 = 248us, 62 = 252u

  //TCCR2B = (1<<CS22)|(1<<CS20);          // prescaler 128
  //OCR2A = 124;                           // compare match every Xth milli-sec. @20MHz => 124 = 1000us

  //TCCR2B = (1<<CS21)|(1<<CS20);          // prescaler 32
  //OCR2A = 50;                            // compare match every Xth milli-sec. @20MHz => 50 = 100us

  //TCCR2B = (1<<CS22)|(1<<CS21)|(1<<CS20);  // prescaler 1024
  //OCR2A = 15;                              // compare match every Xth milli-sec. @20MHz => 77 = 5ms, 38 = 2.5ms, 15 = 1024us
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

static void axisRelMoveWrapper(String& str, AxisCtrl* axisCtrl)
{
  auto pos = str.toFloat();
  axisCtrl->MoveToRelativePosition(pos);
}

static void axisAbsMoveWrapper(String& str, AxisCtrl* axisCtrl)
{
  auto pos = str.toFloat();

  axisCtrl->MoveToAbsolutPosition(pos);
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
  if (str.compareTo("vh") == 0)
  {
    ctrl->SetVerticalHomePosition();
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

static void getPosWrapper(AxisCtrl* axisCtrl)
{
  String sendStr{"pos_"};
  sendStr.concat(axisCtrl->GetPosition());
  cli();  // serial.send seems to be upset by interrupts...
  Serial.println(sendStr);
  sei();
}

static void setRowFirstWrapper(String& str, ScannerCtrl<LIDARLite>* ctrl)
{
  ctrl->SetRowFirst(str.toInt() > 0 ? true : false);
}

static void setHorizontalIncrementWrapper(String& str, ScannerCtrl<LIDARLite>* ctrl)
{
   auto inc = str.toFloat();
   ctrl->SetHorizontalIncrement(inc);
}

static void setVerticalIncrementWrapper(String& str, ScannerCtrl<LIDARLite>* ctrl)
{
   auto inc = str.toFloat();
   ctrl->SetVerticalIncrement(inc);
}
