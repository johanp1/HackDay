#ifndef __C_EVENT_GENERATOR_H__
#define __C_EVENT_GENERATOR_H__

#include "event_listner.h"

class EventGenerator {
 
   public:
   EventGenerator(const String& argName) : name(argName) {handler_p = 0;};
   virtual ~EventGenerator() {};
   
   virtual void scan(void) = 0;

   template<typename T>
   void generateEvent(const T& t)
   {
      C_Event e = C_Event(name, t);
      if (handler_p != 0)
      {
         handler_p->HandleEvent(e);
      }
   };

   void addEventListner(EventListner* h);
   String& getName();   
   
   private:
   EventListner* handler_p;
   String name;
};

#endif // __EVENT_GENERATOR_H__
