#ifndef __ARDUINO_PIN_MOCK_H_
#define __ARDUINO_PIN_MOCK_H_

#include <memory>

#define INPUT PinMode_Input
#define INPUT_PULLUP PinMode_InputPullUp
#define OUTPUT PinMode_Output

#define LOW PinState_Low
#define HIGH PinState_High

typedef enum{
   PinMode_Input = 0,
   PinMode_InputPullUp = 1,
   PinMode_Output = 2,
   PinMode_PwmOutput = 3
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
   virtual PinMode GetMode(void) = 0;
   virtual void SetState(MockDigitalPin *mockedPin, const PinState _state) = 0;
   void SetState(const PinState _state);
   virtual PinState GetState(void) = 0;

   protected:
   PinState state;
};

class PinModeOutput : public MockPinMode  //this is one of the concrete state classes
{
public:
   PinModeOutput();
   ~PinModeOutput();

   void SetMode(MockDigitalPin *mockedPin, const PinMode _mode);
   PinMode GetMode(void);
   void SetState(MockDigitalPin *mockedPin, const PinState _state);
   PinState GetState(void);

   private:
   const PinMode mode = PinMode_Output;
};

class PinModeInput : public MockPinMode  //this is one of the concrete state classes
{
public:
   PinModeInput();
   PinModeInput(const PinState _state);
   ~PinModeInput();

   void SetMode(MockDigitalPin *mockedPin, const PinMode mode);
   PinMode GetMode(void);
   void SetState(MockDigitalPin *mockedPin, const PinState _state);
   PinState GetState(void);
   
   private:
   const PinMode mode = PinMode_Input;
};

class PinModeInputPullUp : public MockPinMode  //this is one of the concrete state classes
{
public:
   PinModeInputPullUp();
   ~PinModeInputPullUp();

   void SetMode(MockDigitalPin *mockedPin, const PinMode mode);
   PinMode GetMode(void);
   void SetState(MockDigitalPin *mockedPin, const PinState _state);
   PinState GetState(void);
   
   private:
   const PinMode mode = PinMode_InputPullUp;
};

class MockDigitalPin  // the context class in state pattern
{
public:
   MockDigitalPin();
   ~MockDigitalPin();

   void SetMode(const PinMode mode);
   void DigitalWrite(const PinState state);
   void AnalogWrite(int duty);
   PinState DigitalRead(void);

   void MockSetDigitalRead(const PinState state);
   PinState MockGetDigitalWrite();
   PinMode MockGetMode();
   int MockGetAnalogWrite();
   
   std::unique_ptr<MockPinMode> mockPinMode;

   int pwmDuty;
};

#endif /* __ARDUINO_PIN_MOCK_H_ */