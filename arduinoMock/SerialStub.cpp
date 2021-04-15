#include "SerialStub.h"

Serial_stub Serial;

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
/*
const String Serial_stub::readStringUntil(const char ch)
{
   int idx = -1;
   string str;
   String retString;

   idx = recData.indexOf(ch);

   str = recData.s.substr(0, (size_t)idx);
   //cout << "index " << idx << "\n";
   //cout << "substr " << str << "\n";

   retString = String(str);
   return retString;
   //return recData;
}
*/
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

void Serial_stub::print(const char *s)
{
   string str = string(s);

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

void Serial_stub::println(const char *s)
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