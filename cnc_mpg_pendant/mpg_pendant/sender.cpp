#include "sender.h"

//  public:
void C_Sender::handleEvent(C_Event& e)
{
   sendEvent(e);
}

void C_Sender::sendEvent(C_Event& e)
{
   Serial.print(e.getSource());
   Serial.print((String)"_");
   Serial.println((int)e.getData());
}
