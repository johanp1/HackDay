 #ifndef __C_BUFFER_H__
#define __C_BUFFER_H__

#define BUFFER_SIZE 20
class C_Buffer {
 
  public:

    // constructor 
   C_Buffer() 
   {
      byte i;
       
      for (i = 0; i<BUFFER_SIZE; i++)  
      {
         buffer[i] = 0;
      }
      pushIdx = 0;
      popIdx = 0;
   };

   void push(const byte data) 
   {
      noInterrupts();    // dissable INT interrupts while sending

      buffer[pushIdx] = data;

      pushIdx++;
      if(pushIdx > BUFFER_SIZE-1)
      {
         pushIdx = 0;
      }
       
      interrupts();       // restore interrupts
   };

   // returns true if data was poped
   bool pop(byte* data)
   {
      bool bufferEmpty = isEmpty();
      
      if(!bufferEmpty)
      {
         *data = buffer[popIdx];

         popIdx++;
         if(popIdx > BUFFER_SIZE-1)
         {
            popIdx = 0;
         }
      }
       
      return !bufferEmpty;
   };
   
   bool isEmpty()
   {
      return popIdx == pushIdx;
   };
   
   
   private:
  
   byte buffer[BUFFER_SIZE];
   byte popIdx;
   byte pushIdx;
};

#endif // __BUFFER_H__

