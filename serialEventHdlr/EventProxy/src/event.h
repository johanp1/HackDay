#ifndef __C_EVENT_H__
#define __C_EVENT_H__

#include <Arduino.h>

class C_Event {
   
 public:
   C_Event();
   
   template<typename T>
   C_Event(const String& str, const T&  argData) : source(str)
   {
      data.concat(argData);
   };

   const String serialize(void);

   String& GetName(void);
   String& GetData(void);

 private:
   String source;
   String data;
};

#endif // __C_EVENT_H__
