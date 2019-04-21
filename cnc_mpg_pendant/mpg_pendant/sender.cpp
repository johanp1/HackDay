#include "sender.h"
//  public:
void C_Sender::handleEvent(C_Event& e)
{
   sendEvent(e);
}

void C_Sender::sendEvent(C_Event& e)
{
   /*String tmp_str = e.getSource();
   unsigned int data = e.getData();
   Serial.print("handleEvent: ");
   Serial.print(tmp_str);
   Serial.print(", data: ");
   Serial.println(data);*/
   Serial.print(e.getSource());
   Serial.print("_");
   Serial.println(e.getData());
}
