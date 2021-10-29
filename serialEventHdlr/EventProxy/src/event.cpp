#include "event.h"

//   public:
C_Event::C_Event() : source(""), data(0) {}

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

