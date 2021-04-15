#ifndef __ARDUINO_PIN_MOCK_H_
#define __ARDUINO_PIN_MOCK_H_
   
typedef enum{
   PinMode_Input = 0,
   PinMode_InputPullUp = 1,
   PinMode_Output = 2
} PinMode;

typedef enum{
   PinState_Low = 0,
   PinState_High = 1,
} PinState;

class MockDigitalPin;

class MockPinMode  // this is the state interface class
{
public:
   MockPinMode();
   virtual ~MockPinMode(){};

   virtual void SetMode(MockDigitalPin *mockedPin, const PinMode mode) = 0;
   PinMode GetMode(void);
   virtual void SetState(/*MockDigitalPin *mockedPin,*/ const PinState _state) = 0;
   virtual PinState GetState(void) = 0;

   protected:
   PinState state;
   PinMode mode;
};

class PinModeOutput : public MockPinMode  //this is one of the concrete state classes
{
public:
   PinModeOutput();
   ~PinModeOutput();

   void SetMode(MockDigitalPin *mockedPin, const PinMode mode);
   void SetState(/*MockDigitalPin *mockedPin,*/ const PinState _state);
   PinState GetState(void);
};

class PinModeInput : public MockPinMode  //this is one of the concrete state classes
{
public:
   PinModeInput();
   ~PinModeInput();

   void SetMode(MockDigitalPin *mockedPin, const PinMode mode);
   void SetState(/*MockDigitalPin *mockedPin,*/ const PinState _state);
   PinState GetState(void);
};

class MockDigitalPin  // the context class in state pattern
{
public:
   MockDigitalPin();
   ~MockDigitalPin();

   void setMode(const PinMode mode);
   void digitalWrite(/*MockPinMode *_mockPinMode,*/ const PinState state);
   PinState digitalRead(void);

   void mockSetDigitalRead(const PinState state);
   PinState mockGetDigitalWrite();
   PinMode mockGetMode();
   
   MockPinMode* mockPinMode;
};

#endif /* __ARDUINO_PIN_MOCK_H_ */