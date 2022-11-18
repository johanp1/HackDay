#include "event_generator.h"

constexpr auto cNbrOfButtons = 4;
constexpr auto cNbrOfSelectors = 2;

constexpr auto cButtonDebounceDelay = 50;
constexpr auto cSelectorDebounceDelay = 100;

constexpr unsigned int cSelectorStateVolts[4] = {0u, 256u, 512u, 768u};
constexpr byte cNbrOfSelectorStates = 4;
constexpr byte cSelectorStateValueUncertainty = 50;

constexpr auto cFuncButtonPin = 3;
constexpr auto cEStopButtonPin = 2;
constexpr auto cJogPosButtonPin = 5;
constexpr auto cJogNegButtonPin = 4;

constexpr auto cAxisSelectorPin = A1;
constexpr auto cScaleSelectorPin = A0;

constexpr auto cLoopDelayTime = 10; //milli sec
