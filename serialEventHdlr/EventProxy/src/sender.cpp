#include "sender.h"

//  public:
void Sender::HandleEvent(C_Event& e)
{
  String s = e.serialize();
  send(s);
}

void Sender::send(String& str)
{
   Serial.println(str);
}

