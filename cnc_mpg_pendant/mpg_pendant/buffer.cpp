#include "buffer.h"

//  public:

// constructor 
C_Buffer::C_Buffer() 
{
   byte i;      
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

C_Event* C_Buffer::pop(void)
{
   bool bufferEmpty = isEmpty();
   C_Event* e_p = 0;
      
   if(!bufferEmpty)
   {
      e_p = &buffer[popIdx];

      popIdx++;
      if(popIdx > BUFFER_SIZE-1)
      {
         popIdx = 0;
      }
   }

   return e_p;
}
   
bool C_Buffer::isEmpty()
{
   return popIdx == pushIdx;
}

