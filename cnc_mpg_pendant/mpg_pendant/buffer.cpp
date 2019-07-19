#include "buffer.h"
#include <Arduino.h>

//  public:

// constructor 
C_Buffer::C_Buffer() 
{      
   pushIdx = 0;
   popIdx = 0;
}

void C_Buffer::handleEvent(C_Event& e)
{
   push((const C_Event&)e);
}

void C_Buffer::push(const C_Event& e) 
{
   noInterrupts();    // dissable INT interrupts while sending

   buffer[pushIdx] = e;

   pushIdx++;
   if(pushIdx > BUFFER_SIZE-1)
   {
      pushIdx = 0;
   }
       
   interrupts();       // restore interrupts
}

bool C_Buffer::pop(C_Event& e)
{
   bool bufferEmpty = isEmpty();
      
   if(!bufferEmpty)
   {
      e = buffer[popIdx];

      popIdx++;
      if(popIdx > BUFFER_SIZE-1)
      {
         popIdx = 0;
      }
   }

   return !bufferEmpty;
}
   
bool C_Buffer::isEmpty()
{
   return popIdx == pushIdx;
}

