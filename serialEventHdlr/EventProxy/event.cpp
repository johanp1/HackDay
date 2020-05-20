#include "event.h"

//   public:
C_Event::C_Event() : source(""), data(0) {}
C_Event::C_Event(String& str, unsigned int argData) : source(str)
{
   data.concat((int)argData);
}

C_Event::C_Event(String& str, String& argData) : source(str), data(argData) {}

String C_Event::serialize(void)
{
   String retStr = String(source);
   
   retStr.concat("_");
   retStr.concat(data);

   return retStr;
}

String C_Event::serializeData(void)
{
   String retStr = String(data);  
   return retStr;
}

