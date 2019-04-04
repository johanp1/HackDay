 #ifndef __C_EVENT_LISTNER_H__
#define __C_EVENT_LISTNER_H__
#include "event.h"

class C_EventListner {
 
   public:
   virtual void handleEvent(const C_Event& e) = 0;
};

#endif // __EVENT_LISTNER_H__

