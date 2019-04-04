 #ifndef __C_EVENT_H__
#define __C_EVENT_H__


class C_Event {
 
  public:
    C_Event() : source(""), data(0) {};
    C_Event(String& str, int argData) : source(str), data(argData) {};

    void who(void)
    {
      Serial.print("source: "); Serial.print(source); Serial.print(" data: "); Serial.println(data);
    }
    
    String& getSource(void)
    {
      return source;
    };

    int getData(void)
    {
      return data;
    }
    
  private:
      String source;
      int data;
   
};

#endif // __C_EVENT_H__

