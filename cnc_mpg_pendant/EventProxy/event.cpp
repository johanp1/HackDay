#include "event.h"
#include <sstream>
#include <string>     // std::string


std::string to_string(int value)
{
  //create an output string stream
  std::ostringstream os ;
  
  //throw the value into the string stream
  os << value;
  
  //convert the string stream into a string and return
  return os.str() ;
}


//   public:
C_Event::C_Event() : source(""), data(0) {}
C_Event::C_Event(String& str, unsigned int argData) : source(str), data(argData) {}
    
/*String& C_Event::getSource(void)
{
   return source;
}

unsigned int C_Event::getData(void)
{
   return data;
}
*/
String C_Event::serialize(void)
{
  String retStr = String(source);
  
  retStr.append("_");
  retStr.append(to_string((int)data));
  return retStr;
}

