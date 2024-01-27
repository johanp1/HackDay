#include "src/controller.h"
#include "event_parser.h"
#include "receiver.h"
#include "src/extruder.h"

template<typename F, typename O>
class EventHandler : public EventFunctor
{
  public:
    EventHandler(String const &event_name, F f, O* o) : EventFunctor{event_name}, f_(f), o_(o) {};

    void operator()(String& parsed_data)
    {
      f_(parsed_data, o_);
    };
    
    O* o_;
    F f_;
};

template<typename O>
static void setEnableWrapper(String& s, O* o);

static void setRefTempWrapper(String& s, PIDController* c);

template<typename O>
static void setDebugWrapper(String& s, O* o);

// defines pins numbers
const int pwmPin = 5;
const int tempPin = A4;
int refTemp = 1000; // reference temperature in [0.1 degrees], i.e 250 = 25 degrees

PIDParameters p(2,    // K,
                12000, // Ti, rule of thumb h/Ti = 0.1-0.3 (h=period)
                0,     // Td
                10,    // N
                3000,  // Tr, rule of thumb Tr = sqrt(Ti*Td)
                1);    // beta

PIDController tempCtrl(1000, p, 0, 200);
Extruder extruder(tempPin, pwmPin);
Receiver receiver(String("rec"));
EventParser ep;

void setup() {
  Serial.begin(38400);  // opens serial port, sets data rate to 38400 bps
  Serial.setTimeout(500);
  // Sets the two pins as Outputs

  pinMode(pwmPin, OUTPUT);
  pinMode(tempPin, INPUT);  // analog read pin

  analogWrite(pwmPin, 0);

  receiver.addEventListner(&ep);

  ep.AddAcceptedHandler(*(new EventHandler<void (&)(String&, PIDController*), PIDController>(String{"en"}, setEnableWrapper, &tempCtrl)));
  ep.AddAcceptedHandler(*(new EventHandler<void (&)(String&, Extruder*), Extruder>(String{"en"}, setEnableWrapper, &extruder)));
  ep.AddAcceptedHandler(*(new EventHandler<void (&)(String&, PIDController*), PIDController>(String{"sp"}, setRefTempWrapper, &tempCtrl)));
  ep.AddAcceptedHandler(*(new EventHandler<void (&)(String&, PIDController*), PIDController>(String{"debug"}, setDebugWrapper, &tempCtrl)));
  ep.AddAcceptedHandler(*(new EventHandler<void (&)(String&, Extruder*), Extruder>(String{"debug"}, setDebugWrapper, &extruder)));

  Serial.println("setup done"); // tell server setup is done
}

void loop()
{
  int currTemp;

  if (extruder.IsEnabled())
  {
    currTemp = extruder.ReadTemp();
    tempCtrl.Step(currTemp);  // temp in [0.1 degrees] 
    Serial.print("mv_");
    Serial.println((int)(currTemp/10));
    
    extruder.SetTempPwmDuty(tempCtrl.GetOut());
  }
  else
  {
    extruder.SetTempPwmDuty(0);
  }

  
  delay(1000); // One second delay
}

void serialEvent()
{
  receiver.scan();
}

template<typename O>
static void setEnableWrapper(String& s, O* o)
{
  o->SetEnabled(s.toInt() > 0 ? true : false);
}

static void setRefTempWrapper(String& s, PIDController* c)
{
  c->SetRef(s.toInt()*10); // convert to 0.1 degrees unit
}

template<typename O>
static void setDebugWrapper(String& s, O* o)
{
  o->SetDebug(s.toInt() > 0 ? true : false);
}