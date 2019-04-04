 #ifndef __C_EVENT_GENERATOR_H__
#define __C_BEVENT_GENERATOR_H__
#include "buffer.h"

class C_EventGenerator {
 
   public:
   C_EventGenerator(C_Buffer* b) : buf(b) {};
   
   void generateEvent(const byte e)
   {
      //Serial.print("generate event: ");
      //Serial.println(e);
      buf->push(e);
   };
   
   private:
   C_Buffer* buf;
   
};

#endif // __EVENT_GENERATOR_H__

