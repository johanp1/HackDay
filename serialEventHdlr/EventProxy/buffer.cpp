#include "buffer.h"
#include <Arduino.h>

//  public:

// constructor 
Buffer::Buffer() 
{      
   putIdx = 0;
   getIdx = 0;
   numberOfData = 0;
}

void Buffer::handleEvent(C_Event& e)
{
   put((const C_Event&)e);
}

void Buffer::put(const C_Event& e) 
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

bool Buffer::get(C_Event& e)
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
   
bool Buffer::isEmpty()
{
   return numberOfData == 0;
}

bool Buffer::isFull()
{
   return capacity() == numberOfData;
}

void Buffer::flush()
{
  getIdx = 0;
  putIdx = 0;
}

byte Buffer::capacity()
{
  return sizeof(buffer)/sizeof(C_Event);
}

byte Buffer::next(byte idx)
{
   byte outdex = (unsigned char)(idx + 1);
  
   if (outdex > capacity() - 1)
   {
      outdex = 0;
   }
   return outdex;
}
   