 #ifndef __C_EVENT_H__
#define __C_BEVENT_H__


class C_Event {
 
   public:
   C_Event() : source(""): data(0) {};
   C_Event(String& str, byte argData) : source(str): data(argData) {};
      
   private:
      String& source;
      byte data;
   
};

#endif // __C_EVENT_H__

