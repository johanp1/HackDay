 #ifndef __C_BUFFER_H__
#define __C_BUFFER_H__

#include "event.h"
#include "event_listner.h"

#define BUFFER_SIZE 20

class C_Buffer {
 
  public:

    // constructor 
   C_Buffer() 
   {
      byte i;      
      pushIdx = 0;
      popIdx = 0;
   };

   void push(const C_Event& e) 
   {
      noInterrupts();    // dissable INT interrupts while sending

      buffer[pushIdx] = e;

//Serial.print("pushing: ");
//buffer[pushIdx].who();

      pushIdx++;
      if(pushIdx > BUFFER_SIZE-1)
      {
         pushIdx = 0;
      }
       
      interrupts();       // restore interrupts

      l_p->handleEvent(e);
   };

   // returns true if data was poped
   C_Event* pop(void)
   {
      bool bufferEmpty = isEmpty();
      C_Event* e_p = 0;
      
      if(!bufferEmpty)
      {
         e_p = &buffer[popIdx];

//Serial.print("poping: ");Serial.print(popIdx);
//e_p->who();

         popIdx++;
         if(popIdx > BUFFER_SIZE-1)
         {
            popIdx = 0;
         }
      }

      return e_p;
   };
   
   bool isEmpty()
   {
      return popIdx == pushIdx;
   };
   
   void addEventListner(C_EventListner* lp)
   {
     l_p = lp;
   }
   
   private:
  
   C_Event buffer[BUFFER_SIZE];
   C_EventListner* l_p;
   byte popIdx;
   byte pushIdx;
};

#endif // __BUFFER_H__

