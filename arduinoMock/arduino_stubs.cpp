#include "Arduino.h"
#include <sstream>

#include <iostream>
using namespace std;

Serial_stub Serial;
Arduino_stub ArduinoStub;

byte TCCR1A = 0;  // Timer/Counter1 Control Register A
byte TCCR1B = 0;  // Timer/Counter1 Control Register B
int  TCNT1 = 0;   // Timer/Counter1

byte TIMSK2 = 0;  // enable overflow interrupt
byte TCCR2A = 0;  // Timer/Counter2 Control Register A
byte TCCR2B = 0;  // Timer/Counter2 Control Register A
byte OCR2A  = 0;  // compare match every 10th milli-sec @20MHz
byte TCNT2  = 0;  // clear timer2

std::string to__string(int& value)
{
  //create an output string stream
  std::ostringstream os ;
  
  //throw the value into the string stream
  os << value;
  
  //convert the string stream into a string and return
  return os.str() ;
}

String::String(void)
{
  s = string("");
}

String::String(string& _s)
{
  s = string(_s);
}

String::String(const char* _c) 
{
  s = string(_c);
}

String::String(int _i) 
{
  s = string(to__string(_i));
}

String::String(size_t size, char ch)
{
   s = string(size, ch);
}

int String::indexOf(char ch)
{
   return (int)s.find_first_of(ch);
}

void String::concat(string& _s)
{
  s.append(_s);
}

void String::concat(String& _s)
{
  s.append(_s.s);
}

void String::concat(const char* _c)
{
  s.append(_c);
}

void String::concat(const char ch)
{
   s.push_back(ch);
}

void String::concat(int _i)
{
  s.append(to__string(_i));
}

int String::compare(string& _s)
{
  return s.compare(_s);
}

int String::compare(String& _s)
{
  return s.compare(_s.s);
}

int String::compare(String _s)
{
  return s.compare(_s.s);
}

int String::compare(const char* _c)
{
  return s.compare(_c);
}

int String::compare(void)
{
  return s.compare("");
}

int String::compareTo(String& _s)
{
  return s.compare(_s.s);
}

int String::compareTo(string& _s)
{
  return s.compare(_s);
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
  return (unsigned long)ArduinoStub.getTime()/1000;  //convert us to ms
}

unsigned long micros(void)
{
  return (unsigned long)ArduinoStub.getTime();
}

Serial_stub::Serial_stub()
{
   // patch for allocating a larger string at startup. 
   // default seems to be an empty string with 15 chars allocated.
   // when appending the string and the size exceeds 15 it will automaticaly expand the string but will end up with a memory leak 
   sendData = string(100, '0');   
   recData = String(100, '0');
   clear();
}

char Serial_stub::available()
{
   return (char)recData.s.length();
}

void Serial_stub::setRecData(String& str)
{
   recData.s.append(str.s);
}

const String Serial_stub::readStringUntil(const char ch)
{
   int idx = -1;
   string str;
   String retString;

   idx = recData.indexOf(ch);

   str = recData.s.substr(0, (size_t)idx);
   /*cout << "index " << idx << "\n";
   cout << "substr " << str << "\n";*/

   retString = String(str);
   return retString;
   //return recData;
}

int Serial_stub::read()
{
   int retVal = (int)recData.s[0];
   //cout << "recData.length " << recData.s.length() << '\n';
   recData.s = recData.s.erase(0,1);
   
   return retVal;
}

void Serial_stub::clear()
{
   sendData.clear();
   recData.s.clear();
}

void Serial_stub::print(String& str)
{
   sendData.append(str.s);
}

void Serial_stub::print(int val)
{
   string str = to__string(val);

   sendData.append(str);
}

void Serial_stub::println(String& s)
{
   string str = s.s.append("\n");

   sendData.append(str);
}

void Serial_stub::println(int val)
{
   string str = to__string(val).append("\n");

   sendData.append(str);
}

void Serial_stub::println(char *s)
{
   string str = string(s).append("\n");

   sendData.append(str);
}

const string& Serial_stub::getData()
{
   return sendData;
}

void Serial_stub::begin(int val)
{
   if(val == 0){}
}

void Serial_stub::setTimeout(int val)
{
   if (val == 0) {}
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


