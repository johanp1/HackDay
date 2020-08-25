#include "receiver.h"
#include "event_parser.h"
#include <avr/wdt.h>

class HeartbeatFunctionoid : public ParserFunctionoid
{
  public:
  void execute() { wdt_reset(); };
};

boolean send = false;
byte cnt = 0;
unsigned int currSpeed;
  
Receiver receiver(String("rec"));
EventParser ep;
HeartbeatFunctionoid heartbeatFunct;
  
void setup() {
  String heartbeatCmd = String("hb");
   
  cli();
  timer1Init();
  timer2Init();
  sei();
  
  //  wdInit();
  wdt_enable(WDTO_2S);
  
  pinMode(5, INPUT);

  ep.addAcceptedCmd(heartbeatCmd, heartbeatFunct);

  Serial.begin(38400);  // opens serial port
  Serial.setTimeout(500);
  Serial.println("hej");
}

void loop() {
  if(send)
  {
    Serial.print("pos_");
    Serial.println(currSpeed);
    send=0;
  }
}

void serialEvent()
{
  receiver.scan();
}

void timer1Init( void )
{
  TCCR1A = 0;
  TCCR1B |= (1<<CS10)|(1<<CS11)|(1<<CS12);  // enable external clock source & rising edge on pin T1 i.e. D5
  TCNT1   = 0;                // clear timer1
}

void timer2Init( void )
{
  TIMSK2 = (1 << OCIE2A);                   // enable overflow interrupt
  TCCR2A = (1<<WGM21);                      // enable CTC mode, OCR2A as TOP
  TCCR2B |= (1<<CS22)|(1<<CS21)|(1<<CS20);  // prescaler 1024
  OCR2A = 77;                              // compare match every 5th milli-sec @20MHz
  TCNT2   = 0;                              // clear timer2
}


void wdInit(void)
{
   wdr();
   // Start timed equence
   WDTCSR |= (1<<WDCE) | (1<<WDE);
   // Set new prescaler(time-out) value = 256K cycles (~2 s)
   WDTCSR = (1<<WDE) | (1<<WDP2) | (1<<WDP1) | (1<<WDP0);
}


ISR( TIMER2_COMPA_vect  )
{ 
  cnt++;
  if (cnt == 10)
  {
    send = true;
    currSpeed = TCNT1; // TCNT1 contains #counts_per_50ms
    TCNT1 = 0;
    cnt = 0;  
  }
}
