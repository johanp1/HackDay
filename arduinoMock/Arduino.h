#ifndef __ARDUINO_TEST_DOUBLE_H_
#define __ARDUINO_TEST_DOUBLE_H_
   
#include <string>

#define LOW 0
#define HIGH 1

#define INPUT 0
#define OUTPUT 1

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

class String
{
public:
   String(void);
   String(string& _s);
   String(const char* _c);
   String(int _i);
   String(size_t size, char ch);

   int indexOf(char ch);
   int indexOf(String& _s);

   void concat(string& _s);
   void concat(String& _s);
   void concat(const char* _c);
   void concat(int _i);
   void concat(const char ch);
   int compare(string& _s);
   int compare(String& _s);
   int compare(String _s);
   int compare(const char* _c);
   int compare(void);
   int compareTo(String& _s);
   int compareTo(string& _s);
   int length();
   String substring(int from);

   string s;
};

class Serial_stub
{
public:
   Serial_stub();

   char available();
   void setRecData(String& str);
   //const String readStringUntil(const char ch);
   int read();

   void print(String& str);
   void print(int val);
   void println(String& str);
   void println(int val);
   void println(char* str);
   void begin(int val);
   void setTimeout(int val);
   void clear();
   const string& getData();
   
private:
   string sendData;
   String recData;
};

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

extern Serial_stub Serial;
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
