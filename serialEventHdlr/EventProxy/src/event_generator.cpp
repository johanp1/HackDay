#include "event_generator.h"

void EventGenerator::Init()
{
   for (byte i = 0; i < kMaxNbrOfListners; i++)
   {
      handler_p[i] = nullptr;
   }
}

byte EventGenerator::NextFree()
{
   byte retVal = 0;

   for (byte i = 0; i < kMaxNbrOfListners; i++)
   {
      if(handler_p[i] == nullptr)
      {
         retVal = i;
      }
   }

   return retVal;
}

void EventGenerator::Dispatch(C_Event& e)
{
   for (byte i = 0; i < kMaxNbrOfListners; i++)
   {
      if (handler_p[i] != 0)
      {
         handler_p[i]->HandleEvent(e);
      }
   }
}

//   public:
void EventGenerator::addEventListner(EventListner* h)
{
   handler_p[NextFree()] = h;
}

String& EventGenerator::getName()
{
  return name;
}
