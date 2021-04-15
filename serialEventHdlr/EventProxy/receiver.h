#ifndef __C_RECEIVER_H__
#define __C_RECEIVER_H__

#include <Arduino.h>
#include "event_generator.h"

class Receiver : public EventGenerator {
 
   public:
   // constructor 
   Receiver(const String& argName);
  
   void scan(void);

   private:
   void serialEvent(void);
   String recCmd;
};

#endif // __C_RECEIVER_H__