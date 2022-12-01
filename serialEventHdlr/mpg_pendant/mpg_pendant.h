#include "event_generator.h"

constexpr auto kNbrOfButtons = 3;
constexpr auto kNbrOfSelectors = 2;
constexpr auto kNbrOfRotaryEncoders = 1;

constexpr auto kFuncButtonPin = 3;
constexpr auto kRunButtonPin = 6;
constexpr auto kEStopButtonPin = 8;
constexpr auto kButtonDebounceDelay = 50;

constexpr auto kAxisSelectorPin = A3;
constexpr auto kScaleSelectorPin = A2;
constexpr auto kSelectorDebounceDelay = 100;

constexpr auto kEncoderClockPin = 2;
constexpr auto kEncoderDirectionPin = 7;

constexpr auto kLoopDelayTime = 10; //milli sec

constexpr auto kHeartbeatPeriod = 2000; //2000ms

class IsrFunctor
{
public:
   IsrFunctor(EventGenerator *const generator) :handler_(generator){};
   IsrFunctor() :handler_(nullptr){};

   virtual void operator()() {if (handler_ != nullptr) handler_->scan();};

   void addEventGenerator(EventGenerator *const generator)  {if (generator != nullptr) handler_ = generator;};

private:
   EventGenerator* handler_;
};