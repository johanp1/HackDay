#include "buffer.h"
#include <Arduino.h>

//  public:

// constructor 
C_Buffer::C_Buffer() 
{      
   putIdx = 0;
   getIdx = 0;
   numberOfData = 0;
}

void C_Buffer::handleEvent(C_Event& e)
{
   put((const C_Event&)e);
}

void C_Buffer::put(const C_Event& e) 
{
   noInterrupts();    // dissable INT interrupts while sending

   if (!isFull())
   {
      buffer[putIdx] = e;
      numberOfData++;
      putIdx = next(putIdx);
   }

   interrupts();       // restore interrupts
}

bool C_Buffer::get(C_Event& e)
{
   bool notEmpty = !isEmpty();
      
   if(notEmpty)
   {
      e = buffer[getIdx];
      numberOfData--;
      getIdx = next(getIdx);
   }

   return notEmpty;
}
   
bool C_Buffer::isEmpty()
{
   return numberOfData == 0;
}

bool C_Buffer::isFull()
{
   return capacity() == numberOfData;
}

void C_Buffer::flush()
{
  getIdx = 0;
  putIdx = 0;
}

byte C_Buffer::capacity()
{
  return sizeof(buffer)/sizeof(C_Event);
}

byte C_Buffer::next(byte idx)
{
   byte outdex = idx + 1;
  
   if (outdex > capacity() - 1)
   {
      outdex = 0;
   }
   return outdex;
}
   