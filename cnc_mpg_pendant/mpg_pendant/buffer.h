#ifndef __C_BUFFER_H__
#define __C_BUFFER_H__

#include <Arduino.h>
#include "event.h"
#include "event_listner.h"

#define BUFFER_SIZE 20

class C_Buffer : public C_EventListner {
 
public:

   // constructor 
   C_Buffer();

   void handleEvent(C_Event& e);
   void push(const C_Event& e); 
   C_Event* pop(void);
   bool isEmpty();
   
private:
  
   C_Event buffer[BUFFER_SIZE];
   byte popIdx;
   byte pushIdx;
};

#endif // __BUFFER_H__

