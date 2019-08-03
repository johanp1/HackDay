#include "event_generator.h"

//   public:
   
void C_EventGenerator::generateEvent(unsigned int data)
{
   if (handler_p != 0)
   {
      handler_p->handleEvent(C_Event(name, data));
   }
}

void C_EventGenerator::addEventListner(C_EventListner* h)
{
   handler_p = h;
}