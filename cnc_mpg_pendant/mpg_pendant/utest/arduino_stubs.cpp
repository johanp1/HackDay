#include "Arduino.h"

C_Serial_stub Serial;

void noInterrupts(void)
{
}

void interrupts(void)
{
}

void pinMode(int pin, int dir)
{
  int dummy_pin = pin;
  int dummy_dir = dir;
  
  if (dummy_pin == dummy_dir)
    {}
}

int digitalRead(int pin)
{
  int l_pin = pin;
  l_pin = 0;
  return l_pin;
}

void digitalWrite(int pin, int dir)
{
  int dummy_pin = pin;
  int dummy_dir = dir;

  if (dummy_pin == dummy_dir)
    {}
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
