#include "Arduino.h"
#include <sstream>
//#include <iostream>   // std::cout
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

C_Serial_stub::C_Serial_stub()
{
   // patch for allocating a larger string at startup. 
   // default seems to be an empty string with 15 chars allocated.
   // when appending the string and the size exceeds 15 it will automaticaly expand the string but will end up with a memory leak 
   serialData = string(100, '0');   
   clear();
}

void C_Serial_stub::clear()
{
   serialData.clear();
}

void C_Serial_stub::print(string& str)
{
   serialData.append(str);

/*   cout << "capcity " << serialData.capacity() << "\n";
   cout << "length " << serialData.length() << "\n";
   cout << "max_size " << serialData.max_size() << "\n";
   cout << "serialData " << serialData << "\n";*/
}

void C_Serial_stub::print(int val)
{
   string str = tostring(val);

   serialData.append(str);
}

void C_Serial_stub::println(string& s)
{
   string str = s.append("\n");

   serialData.append(str);

/*   cout << "capcity " << serialData.capacity() << "\n";
   cout << "length " << serialData.length() << "\n";
   cout << "max_size " << serialData.max_size() << "\n";
   cout << "serialData " << serialData << "\n";*/
}

void C_Serial_stub::println(int val)
{
   string str = tostring(val).append("\n");

   serialData.append(str);
}

void C_Serial_stub::println(char *s)
{
   string str = string(s).append("\n");

   serialData.append(str);
}

const string& C_Serial_stub::getData()
{
   return serialData;
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
