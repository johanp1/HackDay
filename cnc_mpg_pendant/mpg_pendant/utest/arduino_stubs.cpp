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
}

int digitalRead(int pin)
{
   return 0;
}

void digitalWrite(int pin, int dir)
{   
}

int analogRead(int pin)
{
   return 0;
}

unsigned long millis(void)
{
   return 0;
}

void C_Serial_stub::print(string& str)
{}

void C_Serial_stub::print(int val)
{}

void C_Serial_stub::println(string& str)
{}

void C_Serial_stub::println(int val)
{}
