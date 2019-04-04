 #ifndef __C_SENDER_H__
#define __C_SENDER_H__
#include "event_listner.h"

class C_Sender : public C_EventListner {
 
  public:
    void handleEvent(const C_Event& e)
    {
      String tmp_str = e.getSource();
      byte data = e.getData();
      Serial.print("handleEvent:");
      Serial.print(tmp_str);
      Serial.println(data);
    };
    
      
   private:
   
};

#endif // __C_SENDER_H__

