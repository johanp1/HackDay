#include "sender.h"

//  public:
void C_Sender::handleEvent(C_Event& e)
{
   sendEvent(e);
}

void C_Sender::sendEvent(C_Event& e)
{
  string glueString = string("_");
  
   Serial.print(e.getSource());
   Serial.print(glueString);
   Serial.println((int)e.getData());
}
