#include "event.h"

//   public:
C_Event::C_Event() : source(""), data("") {}

const String C_Event::serialize(void)
{
   String retStr = String(source);
   
   // if no data, the event is just it's name
   if (data.compare("") != 0)
   {
      retStr.concat("_");
      retStr.concat(data);
   }
   return retStr;
}

String& C_Event::GetName(void)
{
   return source;
}

String& C_Event::GetData(void)
{
   return data;
}


