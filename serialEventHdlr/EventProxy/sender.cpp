#include "sender.h"

//  public:
void Sender::handleEvent(C_Event& e)
{
  String s = e.serialize();
  send(s);
}

void Sender::send(String& str)
{
   Serial.println(str);
}

