#include "event_generator.h"

//   public:
   
void EventGenerator::generateEvent(unsigned int data)
{
   C_Event e = C_Event(name, data);
   if (handler_p != 0)
   {
      handler_p->handleEvent(e);
   }
}

void EventGenerator::addEventListner(EventListner* h)
{
   handler_p = h;
}

String& EventGenerator::getName()
{
  return name;
}
