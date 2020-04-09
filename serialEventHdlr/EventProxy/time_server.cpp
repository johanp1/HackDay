#include "time_server.h"

TimeServer::TimeServer(const String& eventName,const byte eventPeriodisity) : EventGenerator(eventName), periodisity(eventPeriodisity)
{

}

void TimeServer::scan(void)
{
   // not used
}


ISR( TIMER2_COMPA_vect  )
{ 
   //generateEvent(1);
   /*cnt++;
   if (cnt == 10)
   {
      send=true;
      cnt=0;  
   }*/
  
}