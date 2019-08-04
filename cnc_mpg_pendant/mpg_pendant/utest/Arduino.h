#ifndef __ARDUINO_TEST_DOUBLE_H_
#define __ARDUINO_TEST_DOUBLE_H_
   
#include <string>

#define LOW 0
#define HIGH 1

#define INPUT 0
#define OUTPUT 1

#define CHANGE 0

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
   void println(char* str);
   void begin(int val);
   void setTimeout(int val);
};

class C_Arduino_stub
{
   public:
   C_Arduino_stub();

   void Setup();
   void Loop();

   void setMode(int pin, int dir);
   int getMode(int pin);

   void digitalWrite(int pin, int dir);
   int getDigitalWrite(int pin);

   void setDigitalRead(int pin, int data);
   int digitalRead(int pin);

   void setAnalogRead(int pin, int val);
   int analogRead(int pin);
  
   void incTime(unsigned int t);
   unsigned int getTime();

   void writeSerialBuffer(string& str);
   string& getSerialBuffer();
   void clearSerialBuffer();

   void setInterruptPin(byte pin);
   void setISR(void(*cbf)(void));
   void invokeInterrupt(unsigned int val);

   void reset();

   private:
   int pinModes[9];
   int digitalWrites[9];
   int digitalReads[9];
   int analogReads[4];
   string serialBuffer;
   unsigned int time;
   void(*isr)(void);
   byte interruptPin;
};

void setup();
void loop();
void delay(unsigned int val);
byte digitalPinToInterrupt(byte b);
void attachInterrupt(byte pin, void(*cbf)(void), byte mode);
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
