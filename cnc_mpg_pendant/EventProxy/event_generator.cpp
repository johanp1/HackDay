#include "event_generator.h"

//   public:
   
void C_EventGenerator::generateEvent(unsigned int data)
{
   C_Event e = C_Event(name, data);
   if (handler_p != 0)
   {
      handler_p->handleEvent(e);
   }
}

void C_EventGenerator::addEventListner(C_EventListner* h)
{
   handler_p = h;
}

String& C_EventGenerator::getName()
{
  return name;
}

void C_EventGenerator::scan(void)
{
}