#include "Arduino.h"
#include "SerialStub.h"
#include <iostream>
#include <string>
using namespace std;

Arduino_stub ArduinoStub;

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
   ArduinoStub.incTime(val);
}

byte digitalPinToInterrupt(byte b)
{
   return b;
}

void attachInterrupt(byte pin, void(*cbf)(void), byte mode)
{
   ArduinoStub.setInterruptPin(pin);
   ArduinoStub.setISR(cbf);

   if(mode == 0){}
}

void pinMode(int pin, int dir)
{
  ArduinoStub.setMode(pin, dir);
}

int digitalRead(int pin)
{
  return ArduinoStub.digitalRead(pin);
}

void digitalWrite(int pin, int w)
{
  ArduinoStub.digitalWrite(pin, w);
}

int analogRead(int pin)
{
  return ArduinoStub.analogRead(pin);
}

unsigned long millis(void)
{
  return (unsigned long)ArduinoStub.getTime()/1000;  //convert us to ms
}

unsigned long micros(void)
{
  return (unsigned long)ArduinoStub.getTime();
}

Arduino_stub::Arduino_stub()
{
  reset();
}

void Arduino_stub::setMode(int pin, int dir)
{
  pinModes[pin] = dir;
}

int Arduino_stub::getMode(int pin)
{
  return pinModes[pin];
}

void Arduino_stub::digitalWrite(int pin, int w)
{
  digitalWrites[pin] = w;
}

int Arduino_stub::getDigitalWrite(int pin)
{
  return digitalWrites[pin];
}

void Arduino_stub::setDigitalRead(int pin, int data)
{
  digitalReads[pin] = data;
}

int Arduino_stub::digitalRead(int pin)
{
  return digitalReads[pin];
}

void Arduino_stub::setAnalogRead(int pin, int data)
{
  analogReads[pin] = data;
}

int Arduino_stub::analogRead(int pin)
{
  return analogReads[pin];
}

void Arduino_stub::reset()
{
  int i;

  for(i = 0; i < 9; i++)
  {
    pinModes[i] = OUTPUT;
    digitalWrites[i] = LOW;
    digitalReads[i] = LOW;
  }

  for(i = 0; i < 3; i++)
  {
	  analogReads[i] = 0;
  }

  time = 0;

  isr = NULL;
}

void Arduino_stub::incTime(unsigned long t)
{
  time += t;
}

void Arduino_stub::incTimeMs(unsigned long t)
{
  time += 1000*t;
}

unsigned long Arduino_stub::getTime()
{
  return time;
}

void Arduino_stub::setInterruptPin(byte pin)
{
   interruptPin = pin;
}

void Arduino_stub::setISR(void(*cbf)(void))
{
   isr = cbf;
}

void Arduino_stub::invokeInterrupt(unsigned int val)
{
  setDigitalRead(interruptPin, (int) val);

   if (isr != NULL)
   {
      isr();
   }
}
