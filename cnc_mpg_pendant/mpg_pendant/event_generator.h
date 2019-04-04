 #ifndef __C_EVENT_GENERATOR_H__
#define __C_EVENT_GENERATOR_H__
#include "buffer.h"

class C_EventGenerator {
 
   public:
   C_EventGenerator(C_Buffer* b) : buf(b) {};
   
   void generateEvent(const C_Event& e)
   {
//      Serial.print("generate event: ");
//      e.who();
      buf->push(e);
   };
   
   private:
   C_Buffer* buf;
   
};

#endif // __EVENT_GENERATOR_H__

