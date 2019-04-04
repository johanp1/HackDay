 #ifndef __C_EVENT_H__
#define __C_EVENT_H__


class C_Event {
 
  public:
    C_Event() : source(""), data(0) {};
    C_Event(String& str, byte argData) : source(str), data(argData) {};

    void who(void)
    {
      Serial.print("source: "); Serial.print(source); Serial.print(" data: "); Serial.println(data);
    }
    
    String& getSource(void)
    {
      return source;
    };

    byte getData(void)
    {
      return data;
    }
    
   private:
      String source;
      byte data;
   
};

#endif // __C_EVENT_H__

