#include "Arduino.h"
#include "SerialStub.h"
#include <iostream>
#include <string>
using namespace std;

byte TCCR1A = 0;  // Timer/Counter1 Control Register A
byte TCCR1B = 0;  // Timer/Counter1 Control Register B
int TCNT1 = 0;   // Timer/Counter1

byte TIMSK2 = 0;  // enable overflow interrupt
byte TCCR2A = 0;  // Timer/Counter2 Control Register A
byte TCCR2B = 0;  // Timer/Counter2 Control Register A
byte OCR2A  = 0;  // compare match every 10th milli-sec @20MHz
byte TCNT2  = 0;  // clear timer2

void noInterrupts(void)
{
}

void interrupts(void)
{
}

void delay(unsigned int val)
{
   (ArduinoStub::GetInstance())->IncTime(val);// .IncTime(val);
}

byte digitalPinToInterrupt(byte b)
{
   return b;
}

void attachInterrupt(byte pin, void(*cbf)(void), InterruptMode mode)
{
   (ArduinoStub::GetInstance())->SetInterruptPin(pin);
   (ArduinoStub::GetInstance())->SetISR(cbf);

   if(mode == 0){}
}

void pinMode(int pin, int m)
{
   (ArduinoStub::GetInstance())->SetMode(pin, (PinMode)m);
}

int digitalRead(int pin)
{
  return (ArduinoStub::GetInstance())->DigitalRead(pin);
}

void digitalWrite(int pin, int w)
{
  (ArduinoStub::GetInstance())->DigitalWrite(pin, (PinState)w);
}

int analogRead(int pin)
{
  return (ArduinoStub::GetInstance())->AnalogRead(pin);
}

unsigned long millis(void)
{
  return (unsigned long)(ArduinoStub::GetInstance())->GetTime()/1000;  //convert us to ms
}

unsigned long micros(void)
{
  return (unsigned long)(ArduinoStub::GetInstance())->GetTime();
}

ArduinoStub::ArduinoStub()
{
   Reset();
}

ArduinoStub::~ArduinoStub()
{
   arduinoStub_.reset(); // clear the weak ptr
}

std::weak_ptr<ArduinoStub> ArduinoStub::arduinoStub_;

std::shared_ptr<ArduinoStub> ArduinoStub::GetInstance()
{
   if (auto existing_instance = arduinoStub_.lock())
   {
      return existing_instance;
   }
   else
   {
      std::shared_ptr<ArduinoStub> tmp_shared(new ArduinoStub());
      arduinoStub_ = tmp_shared;
      return tmp_shared;
   }
}

void ArduinoStub::SetMode(const int pin, const PinMode m)
{
  digitalPins[pin].SetMode(m);
}

int ArduinoStub::GetMode(const int pin)
{
   return digitalPins[pin].MockGetMode();
}

void ArduinoStub::DigitalWrite(const int pin, const PinState w)
{
  digitalPins[pin].DigitalWrite(w);
}

int ArduinoStub::GetDigitalWrite(const int pin)
{
  return digitalPins[pin].MockGetDigitalWrite();
}

void ArduinoStub::SetDigitalRead(const int pin, const PinState data)
{
  digitalPins[pin].MockSetDigitalRead(data);
}

int ArduinoStub::DigitalRead(const int pin)
{
   return digitalPins[pin].DigitalRead();
}

void ArduinoStub::SetAnalogRead(const int pin, const PinState data)
{
  analogReads[pin] = data;
}

int ArduinoStub::AnalogRead(const int pin)
{
  return analogReads[pin];
}

void ArduinoStub::Reset()
{
  int i;

  for(i = 0; i < 3; i++)
  {
	  analogReads[i] = 0;
  }

  time = 0;

  isr = NULL;
}

void ArduinoStub::IncTime(const unsigned long t)
{
  time += t;
}

void ArduinoStub::IncTimeMs(const unsigned long t)
{
  time += 1000*t;
}

unsigned long ArduinoStub::GetTime()
{
  return time;
}

void ArduinoStub::SetInterruptPin(byte pin)
{
   interruptPin = pin;
}

void ArduinoStub::SetISR(void(*cbf)(void))
{
   isr = cbf;
}

void ArduinoStub::InvokeInterrupt(const unsigned int val)
{
  SetDigitalRead(interruptPin, (PinState) val);

   if (isr != NULL)
   {
      isr();
   }
}
