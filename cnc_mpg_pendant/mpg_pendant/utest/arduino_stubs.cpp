#include "Arduino.h"

C_Serial_stub Serial;
C_Arduino_stub ArduinoStub;

void noInterrupts(void)
{
}

void interrupts(void)
{
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
  int l_pin = pin;
  l_pin = 0;
  return l_pin;  return 0;
}

unsigned long millis(void)
{
  return 0;
}

void C_Serial_stub::print(string& str)
{
  string l_str = str;
}

void C_Serial_stub::print(int val)
{
  int l_val = val;
  
  if(l_val != val)
  {
  }
}

void C_Serial_stub::println(string& str)
{
  string l_str = str;
}

void C_Serial_stub::println(int val)
{
  int l_val = val;
  if(l_val != val) {
  }
}

C_Arduino_stub::C_Arduino_stub()
{
  reset();
}

void C_Arduino_stub::setMode(int pin, int dir)
{
  pinModes[pin] = dir;
}

int C_Arduino_stub::getMode(int pin)
{
  return pinModes[pin];
}

void C_Arduino_stub::digitalWrite(int pin, int w)
{
  digitalWrites[pin] = w;
}

int C_Arduino_stub::getDigitalWrite(int pin)
{
  return digitalWrites[pin];
}

void C_Arduino_stub::setDigitalRead(int pin, int data)
{
  digitalReads[pin] = data;
}

int C_Arduino_stub::digitalRead(int pin)
{
  return digitalReads[pin];
}

void C_Arduino_stub::reset()
{
  for(int i = 0; i < 9; i++)
  {
    pinModes[i] = OUTPUT;
    digitalWrites[i] = LOW;
    digitalReads[i] = LOW;
  }
}
