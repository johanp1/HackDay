#include "event_generator.h"

constexpr auto cNbrOfButtons = 4;
constexpr auto cNbrOfSelectors = 1;

constexpr auto cButtonDebounceDelay = 50;
constexpr auto cSelectorDebounceDelay = 100;

constexpr auto cFuncButtonPin = 3;
constexpr auto cEStopButtonPin = 2;
constexpr auto cJogPosButtonPin = 4;
constexpr auto cJogNegButtonPin = 5;
constexpr auto cAxisSelectorPin1 = 6;
constexpr auto cAxisSelectorPin2 = 7;
constexpr auto cAxisSelectorPin3= 8;
constexpr auto cScaleSelectorPin = A2;

constexpr auto cLoopDelayTime = 10; //milli sec

class IsrFunctionoid
{
   public:
   IsrFunctionoid(EventGenerator *const generator) : handler_p(generator) {};
   IsrFunctionoid() {handler_p = nullptr;};
   
   void addEventGenerator(EventGenerator *const generator)  {if (generator != nullptr) handler_p = generator;};
   void execute() {if (handler_p != nullptr) handler_p->scan();};

   private:
   EventGenerator* handler_p;
};
