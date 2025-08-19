// full-step 400 steps/rev for motor 1:4 ratio for axis => 1600 steps/rev => 0.225 degrees/step
#include "step_gen.h"

#define debug_print(x)   Serial.print(#x); Serial.print(": "); Serial.println(x);

// defines pins numbers
const int step_pin = 6; // x-axis step
const int dir_pin = 3;  // x-axis dir

const int step_enable = 8;

StepGen s(step_pin, dir_pin, 5000, 5000); // sets stepPin as output

void setup() {
  cli();
  timer2Init();
  sei();

  Serial.begin(9600);  // opens serial port, sets data rate to 9600 bps
  Serial.setTimeout(500);

  pinMode(step_enable, OUTPUT);
  digitalWrite(step_enable, LOW);

  Serial.println("hello"); // tell server setup is done
}

void loop() {
  char ser_in[20];  // for incoming serial data
  char in_len;
  byte dir = LOW;
  int step = 200;

  // send data only when you receive data:
  if (Serial.available() > 0)
  {
    // read the incoming byte:
    in_len = Serial.readBytes(ser_in, 20);

    step = parseCmdLn(ser_in, in_len);
    debug_print(step);
    if (step != 0)
    {
      if (step < 0)
      {
        s.SetDirection(direction_reverse);
      }
      else
      {
        s.SetDirection(direction_forward);
      }

      s.Step(step);      
    }
  }
}

int parseCmdLn(char* cmd, byte len)
{
  String tmpStr = cmd;

  tmpStr.remove(len);
  debug_print(tmpStr);

  return tmpStr.toInt();
}

void timer2Init( void )
{
  TIMSK2 = (1 << OCIE2A);                  // enable Timer2 Output Compare Match A Interrupt Enable
  TCCR2A = (1<<WGM21);                     // enable CTC mode, OCR2A as TOP
  TCCR2B = (1<<CS22)|(1<<CS21)|(1<<CS20);  // prescaler 1024
  OCR2A = 15;                              // compare match every Xth milli-sec. @20MHz 77 = 5ms, 38 = 2.5ms, 15 = 1ms
}

ISR( TIMER2_COMPA_vect  )
{ 
  s.Update();
}
