 #ifndef __C_SENDER_H__
#define __C_SENDER_H__
#include "event_listner.h"
#include "Arduino.h"

class C_Sender : public C_EventListner {
 
  public:
    void handleEvent(C_Event& e);
    void sendEvent(C_Event& e);
   
};

#endif // __C_SENDER_H__

