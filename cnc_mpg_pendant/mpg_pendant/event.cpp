#include "event.h"

//   public:
C_Event::C_Event() : source(""), data(0) {}
C_Event::C_Event(String& str, unsigned int argData) : source(str), data(argData) {}
    
String& C_Event::getSource(void)
{
   return source;
}

unsigned int C_Event::getData(void)
{
   return data;
}
 
