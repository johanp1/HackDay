 #ifndef __C_TIME_SERVER_H__
#define __C_TIME_SERVER_H__

#include <Arduino.h>
#include "event_generator.h"

class TimeServer : public EventGenerator
{
   public:
   TimeServer(const String& eventName, const byte eventPeriodisity);
   //void start(void);
   //void stop(void);
   void scan();

   private:
   int periodisity;
};

#endif // __TIME_SERVER_H__