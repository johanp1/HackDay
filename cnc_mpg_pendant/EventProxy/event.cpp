#include "event.h"

//   public:
C_Event::C_Event() : source(""), data(0) {}
C_Event::C_Event(String& str, unsigned int argData) : source(str), data(argData) {}
    
String C_Event::serialize(void)
{
  String retStr = String(source);
  
  retStr.append("_");
  retStr.append(to_string((int)data));
  return retStr;
}

