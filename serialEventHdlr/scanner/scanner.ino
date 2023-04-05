// full-step 400 steps/rev for motor 1:4 ratio for axis => 1600 steps/rev => 0.225 degrees/step
#include "scanner.h"
#include "receiver.h"
#include "step_gen.h"

static void SetMotor1Direction(int i);
static void SetMotor2Direction(int i);
static void timer2Init( void );
static void stepEventWrapper(String& str, StepGen* stepGen);

// defines pins numbers
constexpr int motor1_stepPin = 5; // x-axis step
constexpr int motor1_dirPin = 2;  // x-axis dir

constexpr int motor2_stepPin = 6;  // y-axis step
constexpr int motor2_dirPin = 3;   // y-axis dir

constexpr milli_sec t_on = 2;
constexpr milli_sec t_off = 3;

const int stepEnable = 8;

StepGen stepGen1(motor1_stepPin, t_on, t_off);
StepGen stepGen2(motor2_stepPin, t_on, t_off);
static Receiver receiver(String("rec"));
static EventParser eventParser;

void setup() {

/*  SetPulsPerSecCommandHandler* pulsPerSec1CommandHandler = new SetPulsPerSecCommandHandler(stepGen1, String{"pps1"});
  SetPulsPerSecCommandHandler* pulsPerSec2CommandHandler = new SetPulsPerSecCommandHandler(stepGen2, String{"pps2"});
  SetRampingCommandHandler* ramping1CommandHandler = new SetRampingCommandHandler(stepGen1, String{"ramp1"});
  SetRampingCommandHandler* ramping2CommandHandler = new SetRampingCommandHandler(stepGen2, String{"ramp2"});
*/  
  //EventHandler<void (&)(int)>* h1 = new EventHandler<void (&)(int)>(SetMotor1Direction, String{"dir1"});
  EventHandler<void (&)(String&, StepGen*), StepGen>* step1EventHandler = new EventHandler<void (&)(String&, StepGen*), StepGen>(String{"step1"}, stepEventWrapper, &stepGen1);
  EventHandler<void (&)(String&, StepGen*), StepGen>* step2EventHandler = new EventHandler<void (&)(String&, StepGen*), StepGen>(String{"step2"}, stepEventWrapper, &stepGen2);
  //EventHandler<void (&)(int), StepGen>* h1 = new EventHandler<void (&)(int), StepGen>(String{"dir1"}, SetMotor1Direction, &stepGen1);
  //EventHandler<void (&)(int), StepGen>* h2 = new EventHandler<void (&)(int), StepGen>(String{"dir2"}, SetMotor2Direction, &stepGen2);

  //cli();
  timer2Init();
  //sei();

  Serial.begin(38400);  // opens serial port
  Serial.setTimeout(500);

  pinMode(motor1_dirPin, OUTPUT);
  pinMode(motor2_dirPin, OUTPUT);
  pinMode(stepEnable, OUTPUT);
  digitalWrite(stepEnable, LOW);
  
  Serial.println("scanner::setup()"); // tell server setup is done

  receiver.addEventListner(&eventParser);
  
  eventParser.AddAcceptedHandler(*step1EventHandler);
  eventParser.AddAcceptedHandler(*step2EventHandler);
/*  eventParser.AddAcceptedHandler(*pulsPerSec1CommandHandler);
  eventParser.AddAcceptedHandler(*pulsPerSec2CommandHandler);
  eventParser.AddAcceptedHandler(*ramping1CommandHandler);
  eventParser.AddAcceptedHandler(*ramping2CommandHandler); 
  eventParser.AddAcceptedHandler(*h1);
  eventParser.AddAcceptedHandler(*h2);*/
 
}

void loop() {

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

static void SetMotor1Direction(int i)
{
  digitalWrite(motor1_dirPin, i > 0 ? HIGH : LOW);
}

static void SetMotor2Direction(int i)
{
  digitalWrite(motor2_dirPin, i > 0 ? HIGH : LOW);
}

static void stepEventWrapper(String& str, StepGen* stepGen)
{
  stepGen->Step(str.toInt());
}