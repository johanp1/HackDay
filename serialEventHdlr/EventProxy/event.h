#ifndef __C_EVENT_H__
#define __C_EVENT_H__

#include <Arduino.h>

class C_Event {
   
 public:
  C_Event();
  C_Event(String& str, unsigned int argData);
  C_Event(String& str, String& argData);

  String serialize(void);
  String serializeData(void);
  
 private:
  String source;
  String data;
};

#endif // __C_EVENT_H__
