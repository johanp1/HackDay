
boolean send = false;
byte cnt = 0;
unsigned int currSpeed;
  
void setup() {
  cli();
  timer1Init();
  timer2Init();
  sei();
  
  pinMode(5, INPUT);

  Serial.begin(38400);  // opens serial port
  Serial.setTimeout(500);
  Serial.println("hej");
}

void loop() {
/*  Serial.print("TCNT1: ");
  Serial.println((TCNT1*6)/5); // TCNT1 contains #counts_per_100ms => TCNT1*10*60/500 RPM
  
  TCNT1=0;
  dely(100); // waits 1000ms*/
  
  if(send)
  {
    Serial.print("pos_");
    Serial.println(currSpeed);
    send=0;
  }
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
