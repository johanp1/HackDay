 #ifndef __C_EVENT_GENERATOR_H__
#define __C_EVENT_GENERATOR_H__

#include "event_listner.h"

class C_EventGenerator {
 
   public:
   C_EventGenerator(const String& argName) : name(argName) {handler_p = 0;};
   
   void generateEvent(int data)
   {
      C_Event e(name, data);

      if (handler_p != 0)
      {
        handler_p->handleEvent(e);
      }
   };

   void addEventListner(C_EventListner* h)
   {
      handler_p = h;
   };
   
   private:
   C_EventListner* handler_p;
   String name;
};

#endif // __EVENT_GENERATOR_H__

