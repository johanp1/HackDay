#ifndef __ARDUINO_TEST_DOUBLE_H_
#define __ARDUINO_TEST_DOUBLE_H_
   
#include <string>
#include "String.h"
#include "SerialStub.h"
#include "PinMock.h"

#define INPUT PinMode_Input
#define INPUT_PULLUP PinMode_InputPullUp
#define OUTPUT PinMode_Output

#define LOW PinState_Low
#define HIGH PinState_High

#define CHANGE 0
#define RISING 1

#define A2 0
#define A3 1

#define CS10 0
#define CS11 1
#define CS12 2
#define CS20 0
#define CS21 1
#define CS22 2
#define OCIE2A 1
#define WGM21 1

#define ISR(X) void interruptServiceRoutine(X)
#define TIMER2_COMPA_vect void

using namespace std;

typedef unsigned char byte;

class Arduino_stub
{
   public:
   Arduino_stub();

   void setMode(int pin, int dir);
   int getMode(int pin);

   void digitalWrite(int pin, int dir);
   int getDigitalWrite(int pin);

   void setDigitalRead(int pin, int data);
   int digitalRead(int pin);

   void setAnalogRead(int pin, int val);
   int analogRead(int pin);
  
   void incTimeMs(unsigned long t);
   void incTime(unsigned long t);
   unsigned long getTime();

   void setInterruptPin(byte pin);
   void setISR(void(*cbf)(void));
   void invokeInterrupt(unsigned int val);

   void reset();

   private:
   int pinModes[9];
   int digitalWrites[9];
   int digitalReads[9];

   int analogReads[4];

   unsigned long time;

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
unsigned long micros(void);

extern Arduino_stub ArduinoStub;

extern byte TCCR1A;  // Timer/Counter1 Control Register A
extern byte TCCR1B;  // Timer/Counter1 Control Register B
extern int  TCNT1;   // Timer/Counter1

extern byte TIMSK2;  // enable overflow interrupt
extern byte TCCR2A;  // Timer/Counter2 Control Register A
extern byte TCCR2B;  // Timer/Counter2 Control Register A
extern byte OCR2A;   // compare match every 10th milli-sec @20MHz
extern byte TCNT2;   // clear timer2

#endif /* __ARDUINO_TEST_DOUBLE_H_ */
