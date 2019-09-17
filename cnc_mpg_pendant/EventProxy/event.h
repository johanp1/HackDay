#ifndef __C_EVENT_H__
#define __C_EVENT_H__

#include <Arduino.h>

class C_Event {
   
   public:
    C_Event();
    C_Event(String& str, unsigned int argData);
    
   String& getSource(void);
   unsigned int getData(void);
    
   private:
      String source;
      unsigned int data;
};

#endif // __C_EVENT_H__

