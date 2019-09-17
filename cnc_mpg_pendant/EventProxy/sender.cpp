#include "sender.h"
//#include <string>

//  public:
void C_Sender::handleEvent(C_Event& e)
{
   sendEvent(e);
}

void C_Sender::sendEvent(C_Event& e)
{
   String glue = "_";

   Serial.print(e.getSource());
   Serial.print(glue);
   Serial.println((int)e.getData());
}
