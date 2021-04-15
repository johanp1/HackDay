#include "PinMock.h"

/*
   MockDigitalPin
*/
MockDigitalPin::MockDigitalPin()
{
   mockPinMode = new PinModeInput();  // as per data-sheet, arudino's pins defaults as inputs
}

MockDigitalPin::~MockDigitalPin() 
{
   delete mockPinMode;
}

void MockDigitalPin::setMode(const PinMode _mode)
{
   mockPinMode->SetMode(this, _mode);
}

void MockDigitalPin::digitalWrite(const PinState state)
{
   mockPinMode->SetState(state);
}

PinState MockDigitalPin::digitalRead(void)
{
   return mockPinMode->GetState();
}

void MockDigitalPin::mockSetDigitalRead(const PinState _state)
{
   mockPinMode->SetState(_state);
}

PinState MockDigitalPin::mockGetDigitalWrite()
{
   return mockPinMode->GetState();
}

PinMode MockDigitalPin::mockGetMode()
{
   return mockPinMode->GetMode();
}

/*
   MockPinMode
*/
MockPinMode::MockPinMode()
{
   state = PinState_Low;
}

PinMode MockPinMode::GetMode(void)
{
   return mode;
}

/*
   PinModeOutput
*/
PinModeOutput::PinModeOutput()
{
   mode = PinMode_Output;
}

PinModeOutput::~PinModeOutput()
{
}

void PinModeOutput::SetMode(MockDigitalPin *mockedPin, const PinMode _mode)
{
   if(_mode == PinMode_Input)
   {
      mockedPin->mockPinMode = new PinModeInput();
   }
   delete this;
}

void PinModeOutput::SetState(/*MockDigitalPin *mockedPin,*/ const PinState _state) 
{
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
   mode = PinMode_Input;
}

PinModeInput::~PinModeInput()
{
}

void PinModeInput::SetMode(MockDigitalPin *mockedPin, const PinMode _mode)
{
   if(_mode != PinMode_Input)
   {
      mockedPin->mockPinMode = new PinModeOutput();
   }
   delete this;
}

// when writing to a Input pin, the internal pull up is enabled
void PinModeInput::SetState(/*MockDigitalPin *mockedPin,*/ const PinState _state) 
{
   state = _state;
}

PinState PinModeInput::GetState(void)
{
   return state;
}