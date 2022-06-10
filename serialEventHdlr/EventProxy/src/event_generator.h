#ifndef __C_EVENT_GENERATOR_H__
#define __C_EVENT_GENERATOR_H__

#include "event_listner.h"

constexpr auto kMaxNbrOfListners = 4; 

class EventGenerator {
 
   public:
   EventGenerator(const String& argName) : name(argName) {Init();};
   virtual ~EventGenerator() {};
   
   virtual void scan(void) = 0;

   template<typename T>
   void generateEvent(const T& t);

   template<typename T>
   void generateEvent(const String& event_name, const T& t);

   void addEventListner(EventListner* h);
   String& getName();   
   
   private:
   void Init();
   byte NextFree();
   void Dispatch(C_Event& e);

   EventListner* handler_p[kMaxNbrOfListners];
   String name;
};

template<typename T>
void EventGenerator::generateEvent(const T& t)
{
   C_Event e = C_Event(name, t);
   Dispatch(e);
};

template<typename T>
void EventGenerator::generateEvent(const String& event_name, const T& t)
{
   C_Event e = C_Event(event_name, t);
   Dispatch(e);
};

#endif // __EVENT_GENERATOR_H__
