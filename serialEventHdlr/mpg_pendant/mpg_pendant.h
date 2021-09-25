#include "event_generator.h"

constexpr auto kNbrOfButtons = 3;
constexpr auto kNbrOfSelectors = 2;

constexpr auto kButtonDebounceDelay = 50;
constexpr auto kSelectorDebounceDelay = 100;

constexpr auto kFuncButtonPin = 3;
constexpr auto kRunButtonPin = 6;
constexpr auto kEStopButtonPin = 8;

constexpr auto kAxisSelectorPin = A3;
constexpr auto kScaleSelectorPin = A2;

constexpr auto kEncoderClockPin = 2;
constexpr auto kEncoderDirectionPin = 7;

constexpr auto kLoopDelayTime = 10; //milli sec

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
