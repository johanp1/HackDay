#ifndef __C_EVENT_GENERATOR_H__
#define __C_EVENT_GENERATOR_H__

#include "event_listner.h"

class C_EventGenerator {
 
   public:
   C_EventGenerator(const String& argName) : name(argName) {handler_p = 0;};
   virtual ~C_EventGenerator() {};
   
   virtual void scan(void) = 0;

   void generateEvent(unsigned int data);
   void addEventListner(C_EventListner* h);
   String& getName();   
   
   private:
   C_EventListner* handler_p;
   String name;
};

#endif // __EVENT_GENERATOR_H__
