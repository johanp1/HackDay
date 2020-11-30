#include "event_generator.h"

//   public:
void EventGenerator::addEventListner(EventListner* h)
{
   handler_p = h;
}

String& EventGenerator::getName()
{
  return name;
}
