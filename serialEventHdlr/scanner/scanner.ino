// full-step 400 steps/rev for motor 1:4 ratio for axis => 1600 steps/rev => 0.225 degrees/step
#include "scanner.h"
#include "receiver.h"
#include "src/step_gen.h"

static void timer2Init( void );
static void stepEventWrapper(String& str, StepGen* stepGen);
static void stepsPerSecEventWrapper(String& str, StepGen* stepGen);
static void useRampingEventWrapper(String& str, StepGen* stepGen);

// defines pins numbers
constexpr int motor1_step_pin = 5; // x-axis step
constexpr int motor1_dir_pin = 2;  // x-axis dir

constexpr int motor2_step_pin = 6;  // y-axis step
constexpr int motor2_dir_pin = 3;   // y-axis dir

constexpr milli_sec t_on = 2;
constexpr milli_sec t_off = 3;

const int enable_pin = 8;

static StepGen stepGen1(motor1_step_pin, motor1_dir_pin, t_on, t_off);
static StepGen stepGen2(motor2_step_pin, motor2_dir_pin, t_on, t_off);
static Receiver receiver(String("rec"));
static EventParser eventParser;

void setup() {  
  EventHandler<void (&)(String&, StepGen*), StepGen>* step1EventHandler = new EventHandler<void (&)(String&, StepGen*), StepGen>(String{"step1"}, stepEventWrapper, &stepGen1);
  EventHandler<void (&)(String&, StepGen*), StepGen>* step2EventHandler = new EventHandler<void (&)(String&, StepGen*), StepGen>(String{"step2"}, stepEventWrapper, &stepGen2);
  EventHandler<void (&)(String&, StepGen*), StepGen>* stepsPerSec1EventHandler = new EventHandler<void (&)(String&, StepGen*), StepGen>(String{"sps1"}, stepsPerSecEventWrapper, &stepGen1);
  EventHandler<void (&)(String&, StepGen*), StepGen>* stepsPerSec2EventHandler = new EventHandler<void (&)(String&, StepGen*), StepGen>(String{"sps2"}, stepsPerSecEventWrapper, &stepGen2);
  EventHandler<void (&)(String&, StepGen*), StepGen>* useRamping1EventHandler = new EventHandler<void (&)(String&, StepGen*), StepGen>(String{"ramp1"}, useRampingEventWrapper, &stepGen1);
  EventHandler<void (&)(String&, StepGen*), StepGen>* useRamping2EventHandler = new EventHandler<void (&)(String&, StepGen*), StepGen>(String{"ramp2"}, useRampingEventWrapper, &stepGen2);

  cli();
  timer2Init();
  sei();

  Serial.begin(38400);  // opens serial port
  Serial.setTimeout(500);

  pinMode(motor1_dir_pin, OUTPUT);
  pinMode(motor2_dir_pin, OUTPUT);
  pinMode(enable_pin, OUTPUT);
  digitalWrite(enable_pin, LOW);
  
  Serial.println("scanner::setup()"); // tell server setup is done

  receiver.addEventListner(&eventParser);
  
  eventParser.AddAcceptedHandler(*step1EventHandler);
  eventParser.AddAcceptedHandler(*step2EventHandler);
  eventParser.AddAcceptedHandler(*stepsPerSec1EventHandler);
  eventParser.AddAcceptedHandler(*stepsPerSec2EventHandler);
  eventParser.AddAcceptedHandler(*useRamping1EventHandler);
  eventParser.AddAcceptedHandler(*useRamping2EventHandler); 
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

static void stepEventWrapper(String& str, StepGen* stepGen)
{
  auto steps = str.toInt();
  stepGen->SetDirection(steps > 0 ? direction_forward : direction_reverse);
  stepGen->Step(steps);
}

static void stepsPerSecEventWrapper(String& str, StepGen* stepGen)
{
  stepGen->SetStepsPerSec(str.toInt());
}

static void useRampingEventWrapper(String& str, StepGen* stepGen)
{
  stepGen->SetUseRamping(str.toInt() > 0 ? true : false);
}