#ifndef __ARDUINO_TEST_DOUBLE_H_
#define __ARDUINO_TEST_DOUBLE_H_
   
#include <string>

#define LOW 0
#define HIGH 1

#define INPUT 0

using namespace std;

typedef string String;  
typedef unsigned char byte;

class C_Serial_stub
{
   public:
   void print(string& str);
   void print(int val);
   void println(string& str);
   void println(int val);
   
   private:
   string send_str;
};

void noInterrupts(void);
void interrupts(void);
void pinMode(int pin, int dir);
int digitalRead(int pin);
void digitalWrite(int pin, int dir);
int analogRead(int pin);
unsigned long millis(void);

extern C_Serial_stub Serial;


#endif /* __ARDUINO_TEST_DOUBLE_H_ */