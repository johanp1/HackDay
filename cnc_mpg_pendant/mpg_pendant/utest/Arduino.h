#ifndef __ARDUINO_TEST_DOUBLE_H_
#define __ARDUINO_TEST_DOUBLE_H_
   
#include <string>

#define LOW 0
#define HIGH 1

#define INPUT 0
#define OUTPUT 1

#define A2 0
#define A3 1

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

class C_Arduino_stub
{
 public:
  C_Arduino_stub();
  void setMode(int pin, int dir);
  int getMode(int pin);
  void digitalWrite(int pin, int dir);
  int getDigitalWrite(int pin);
  void setDigitalRead(int pin, int data);
  int digitalRead(int pin);
  void reset();
  
 private:
  int pinModes[9];
  int digitalWrites[9];
  int digitalReads[9];
};

void noInterrupts(void);
void interrupts(void);
void pinMode(int pin, int dir);
int digitalRead(int pin);
void digitalWrite(int pin, int w);
int analogRead(int pin);
unsigned long millis(void);

extern C_Serial_stub Serial;
extern C_Arduino_stub ArduinoStub;

#endif /* __ARDUINO_TEST_DOUBLE_H_ */
