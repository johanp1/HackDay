#ifndef __ARDUINO_SERIAL_STUB_H_
#define __ARDUINO_SERIAL_STUB_H_

#include "String.h"

class SerialStub
{
public:
   SerialStub();

   char available();
   void setRecData(String& str);
   //const String readStringUntil(const char ch);
   int read();

   void print(String& str);
   void print(int val);
   void print(const char* str);

   void println(String& str);
   void println(int val);
   void println(const char* str);
   
   void begin(int val);
   void setTimeout(int val);
   void clear();
   const std::string getData();
   
private:
   std::string sendData;
   String recData;
};

extern SerialStub Serial;

#endif /* __ARDUINO_SERIAL_STUB_H_ */