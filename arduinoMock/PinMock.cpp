#include "PinMock.h"

/*
   MockDigitalPin
*/
MockDigitalPin::MockDigitalPin()
{
   mockPinMode = std::make_unique<PinModeInput>();  // as per data-sheet, arudino's pins defaults as inputs
   pwmDuty = 0;
}

MockDigitalPin::~MockDigitalPin() 
{
   //delete mockPinMode;
}

void MockDigitalPin::SetMode(const PinMode _mode)
{
   mockPinMode->SetMode(this, _mode);
}

void MockDigitalPin::DigitalWrite(const PinState _state)
{
   mockPinMode->SetState(this, _state);
}

void MockDigitalPin::AnalogWrite(int duty)
{
	pwmDuty = duty;
}

PinState MockDigitalPin::DigitalRead(void)
{
   return mockPinMode->GetState();
}

void MockDigitalPin::MockSetDigitalRead(const PinState _state)
{
   mockPinMode->SetState(_state);
}

PinState MockDigitalPin::MockGetDigitalWrite()
{
   return mockPinMode->GetState();
}

PinMode MockDigitalPin::MockGetMode()
{
   return mockPinMode->GetMode();
}

int MockDigitalPin::MockGetAnalogWrite()
{
   return pwmDuty;
}

/*
   MockPinMode
*/
MockPinMode::MockPinMode()
{
   state = PinState_Low;
}

void MockPinMode::SetState(const PinState _state) 
{
   state = _state;
}

/*
   PinModeOutput
*/
PinModeOutput::PinModeOutput()
{
}

PinModeOutput::~PinModeOutput()
{
}

void PinModeOutput::SetMode(MockDigitalPin *mockedPin, const PinMode _mode)
{
   if(_mode == PinMode_Input)
   {
      mockedPin->mockPinMode = std::make_unique<PinModeInput>();
      //mockedPin->mockPinMode = new PinModeInput();
      //delete this;
   }
   if(_mode == PinMode_InputPullUp)
   {
      mockedPin->mockPinMode = std::make_unique<PinModeInputPullUp>(); //new PinModeInputPullUp();
      //delete this;
   }
}

PinMode PinModeOutput::GetMode(void)
{
   return mode;
}

void PinModeOutput::SetState(MockDigitalPin *mockedPin, const PinState _state) 
{
   if (mockedPin == nullptr) {} // dummy, mockedPin unused

   state = _state;
}

PinState PinModeOutput::GetState(void)
{
   return state;
}

/*
   PinModeInput
*/
PinModeInput::PinModeInput()
{
}

PinModeInput::PinModeInput(const PinState _state)
{
   state = _state;
   PinModeInput();
}

PinModeInput::~PinModeInput()
{
}

void PinModeInput::SetMode(MockDigitalPin *mockedPin, const PinMode _mode)
{
   if(_mode == PinMode_InputPullUp)
   {
      mockedPin->mockPinMode = std::make_unique<PinModeInputPullUp>(); //new PinModeInputPullUp();
      //delete this;
   }
   if(_mode == PinMode_Output)
   {
      mockedPin->mockPinMode = std::make_unique<PinModeOutput>(); //new PinModeOutput();
      //delete this;
   }
}

PinMode PinModeInput::GetMode(void)
{
   return mode;
}

// when writing to a Input pin, the internal pull up is enabled
void PinModeInput::SetState(MockDigitalPin *mockedPin, const PinState _state) 
{
   if (_state == PinState_High)
   {
      mockedPin->mockPinMode = std::make_unique<PinModeInputPullUp>(); //new PinModeInputPullUp();
      //delete this;
   }
}

PinState PinModeInput::GetState(void)
{
   return state;
}

/*
   PinModeInputPullUp
*/
PinModeInputPullUp::PinModeInputPullUp()
{
   state = PinState_High;
}

PinModeInputPullUp::~PinModeInputPullUp()
{
}

void PinModeInputPullUp::SetMode(MockDigitalPin *mockedPin, const PinMode _mode)
{
   if(_mode == PinMode_Input)
   {
      mockedPin->mockPinMode = std::make_unique<PinModeInput>(); //new PinModeInput();
      //delete this;
   }
   if(_mode == PinMode_Output)
   {
      mockedPin->mockPinMode = std::make_unique<PinModeOutput>(); //new PinModeOutput();
      //delete this;
   }
}

PinMode PinModeInputPullUp::GetMode(void)
{
   return mode;
}

void PinModeInputPullUp::SetState(MockDigitalPin *mockedPin, const PinState _state) 
{
   if (_state == PinState_Low)
   {
      mockedPin->mockPinMode = std::make_unique<PinModeInput>(PinState_Low); //new PinModeInput(PinState_Low);
      delete this;
   }
}

PinState PinModeInputPullUp::GetState(void)
{
   return state;
}
