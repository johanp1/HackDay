#include "sender.h"
#include <string>

//  public:
void C_Sender::handleEvent(C_Event& e)
{
   sendEvent(e);
}

void C_Sender::sendEvent(C_Event& e)
{

   string glue = "_";
   /*   string end = "\n";
   string sendString = "ap";// string(e.getSource());
   string data = "10";

   sendString.append(glue);
   //sendString.append(to_string((int)e.getData()));
   sendString.append(data);
   sendString.append(end);

   Serial.print(sendString);
*/

   Serial.print(e.getSource());
   Serial.print(glue);
   Serial.println((int)e.getData());
}
