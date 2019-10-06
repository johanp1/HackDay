#include "sender.h"
#include <string>

//  public:
void C_Sender::handleEvent(C_Event& e)
{
  String s = e.serialize();
  send(s);
}

void C_Sender::send(String& str)
{
   Serial.println(str);
}

