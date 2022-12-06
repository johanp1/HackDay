#include "event_generator.h"

constexpr auto kNbrOfButtons = 4;
constexpr auto kNbrOfSelectors = 2;

constexpr auto kButtonDebounceDelay = 50;
constexpr auto kSelectorDebounceDelay = 100;

constexpr unsigned int kSelectorStateVolts[4] = {0u, 256u, 512u, 768u};
constexpr byte kNbrOfSelectorStates = 4;
constexpr byte kSelectorStateValueUncertainty = 50;

constexpr auto kFuncButtonPin = 3;
constexpr auto kEStopButtonPin = 2;
constexpr auto kJogPosButtonPin = 5;
constexpr auto kJogNegButtonPin = 4;

constexpr auto kAxisSelectorPin = A1;
constexpr auto cScaleSelectorPin = A0;

constexpr auto kHeartbeatPeriod = 2000; //ms

constexpr auto kLoopDelayTime = 10; //milli sec
