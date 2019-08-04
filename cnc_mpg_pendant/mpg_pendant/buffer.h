
#ifndef __C_BUFFER_H__
#define __C_BUFFER_H__

#include "event.h"
#include "event_listner.h"

#define BUFFER_SIZE 20

class C_Buffer : public C_EventListner {
 
public:

   // constructor 
   C_Buffer();

   void handleEvent(C_Event& e);
   void put(const C_Event& e); 
   bool get(C_Event& e);
   bool isEmpty();
   void flush();
   byte capacity();
   
private:
  
   C_Event buffer[BUFFER_SIZE];
   byte getIdx;
   byte putIdx;

   byte next(byte idx);
};

#endif // __BUFFER_H__
