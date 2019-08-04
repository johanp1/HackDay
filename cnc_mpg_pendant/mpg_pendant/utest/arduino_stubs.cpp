#include "Arduino.h"
#include <sstream>
#include <iostream>   // std::cout
#include <string>     // std::string, std::to_string

C_Serial_stub Serial;
C_Arduino_stub ArduinoStub;


std::string tostring(int value)
{
      //create an output string stream
  std::ostringstream os ;
  
  //throw the value into the string stream
  os << value;
  
  //convert the string stream into a string and return
  return os.str() ;
}


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
  return (unsigned long)ArduinoStub.getTime();
}

void C_Serial_stub::print(string& str)
{
   ArduinoStub.writeSerialBuffer(str);
}

void C_Serial_stub::print(int val)
{
  string str = tostring(val);
   ArduinoStub.writeSerialBuffer(str);
}

void C_Serial_stub::println(string& str)
{
   ArduinoStub.writeSerialBuffer(str.append("\n"));
}

void C_Serial_stub::println(int val)
{
   string str = tostring(val).append("\n");
   ArduinoStub.writeSerialBuffer(str);
}

void C_Serial_stub::println(char *str)
{
   string s = string(str);
   ArduinoStub.writeSerialBuffer(s.append("\n"));
}

void C_Serial_stub::begin(int val)
{
   if(val == 0){}
}

void C_Serial_stub::setTimeout(int val)
{
   if (val == 0) {}
}

C_Arduino_stub::C_Arduino_stub()
{
  reset();
}

void C_Arduino_stub::Setup()
{
   setup();
}

void C_Arduino_stub::Loop()
{
   loop();
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

void C_Arduino_stub::setAnalogRead(int pin, int data)
{
  analogReads[pin] = data;
}

int C_Arduino_stub::analogRead(int pin)
{
  return analogReads[pin];
}

void C_Arduino_stub::writeSerialBuffer(string& str)
{
   serialBuffer.append(str);
}

string& C_Arduino_stub::getSerialBuffer()
{
   return serialBuffer;
}

void C_Arduino_stub::clearSerialBuffer()
{
   serialBuffer = "";
}

void C_Arduino_stub::reset()
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
  
  clearSerialBuffer();
}

void C_Arduino_stub::incTime(unsigned int t)
{
  time += t;
}

unsigned C_Arduino_stub::getTime()
{
  return time;
}

void C_Arduino_stub::setInterruptPin(byte pin)
{
   interruptPin = pin;
}

void C_Arduino_stub::setISR(void(*cbf)(void))
{
   isr = cbf;
}

void C_Arduino_stub::invokeInterrupt(unsigned int val)
{
  setDigitalRead(interruptPin, (int) val);

   if (isr != NULL)
   {
      isr();
   }
}
