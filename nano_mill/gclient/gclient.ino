// Client for parsing G-code commands sent over serial line
// controlls RC-servos
//
// By Johan Pettersson

#include <Servo.h>

#define MAX_TRAVERSE_FEED 1000  // default G0 feed rate, fastest possible

#define X_MAX 2000 //[10 mico meter unit]
#define X_MIN -2000
#define Y_MAX 2000
#define Y_MIN -2000
#define Z_MAX 2000
#define Z_MIN -2000
#define MIN_100MS_MOVEMENT 5  // 5 [10um] = 0.05mm
#define MIN_FEED 60

// defines used for caculating servo control pulse width from requested angle
#define DEGRES_TO_100URAD(a)  (long)((long)(a)*175)/10    // (a)*pi/180*1000 *10/10 
#define MAX_SERVO_ANGLE DEGRES_TO_100URAD(180)
#define MIN_SERVO_ANGLE DEGRES_TO_100URAD(0)
#define SERVO_PW_MAX_ANGLE 2300 // [us]
#define SERVO_PW_MIN_ANGLE 700  // [us]
#define KX1_PLUS_Y1 ((SERVO_PW_MAX_ANGLE - SERVO_PW_MIN_ANGLE)*MIN_SERVO_ANGLE)/(MAX_SERVO_ANGLE - MIN_SERVO_ANGLE) + SERVO_PW_MIN_ANGLE;

// y = (y2- y1)/(x2-x1)(x-x1)+y1
// re-organised to y = ((y2 - y1)*x)/(x2 - x1) - ((y2 - y1)*x1)/(x2 - x1) + y1
// y1 is always 0, y2 is the max angle, gives:
// y = y2*x/dx - kx1 where dx = (x2-x1) and kx1 = y2*x1/dx
#define CALC_PW_FROM_ANGLE(a) ((long)(SERVO_PW_MAX_ANGLE - SERVO_PW_MIN_ANGLE)*(long)(a))/(long)(MAX_SERVO_ANGLE - MIN_SERVO_ANGLE) + KX1_PLUS_Y1;

#define debug_print(x)  if(debug_flag) {Serial.print(#x); Serial.print(": "); Serial.println(x);}

typedef enum
{
  Idle,
  Moving,
  Test
} state_T;

typedef struct 
{
   //config parameters
   int spindle_speed;   // rpm
   
   int cutting_feed;    // mm/minute
   int curr_feed; // the current feed rate 10um/100ms
      
   int curr_x;          //[10 mico meter unit]
   int curr_y;
   int curr_z;
   
   int ref_x;
   int ref_y;
   int ref_z;

   state_T state;
} mill_T;

typedef struct
{
  // config parameters
  int max_angle;  // [100urad]
  int pw_max_angle; // [us]
  int pw_min_angle;
  byte pin;  // servo connection pin  
  
  //internal parameters used for calculations
  long k_x1;
  long dx;
} servo_T;

typedef struct
{
  // position calculation parameters
  int a;
  int b;

  servo_T servo;
} slide_ctrl_T;

// global variables ////////////////////////

Servo xServo;
Servo yServo;
//Servo zServo;

mill_T myMill;
byte debug_flag = 1;

void setup() {
  int angle_x;   // [100urad]
  int angle_y;   // [100urad]
  int pw_x;      // [us]
  int pw_y;
  
  myMill.state = Idle;
  myMill.spindle_speed = 100;
  myMill.cutting_feed = 180; //MIN_FEED;  // default cutting feed rate
  myMill.curr_feed = 180;    //MIN_FEED;    // current cutting feed rate [mm/minut]
  myMill.curr_x = 0;
  myMill.ref_x = 0;
  myMill.curr_y = 0;
  myMill.ref_y = 0;
  
	Serial.begin(9600);	// opens serial port, sets data rate to 9600 bps

	xServo.attach(9);
	xServo.writeMicroseconds(1500);

  Serial.setTimeout(500);

  angle_x = calcAngle(myMill.curr_x);
  angle_y = calcAngle(myMill.curr_y);
    
  pw_x = calcServoPw(angle_x);
  pw_y = calcServoPw(angle_y);

  xServo.writeMicroseconds(pw_x);
  yServo.writeMicroseconds(pw_y);

  debug_dump();
}

void loop() {
	char ser_in[20];	// for incoming serial data
  char in_len;
  long tmpD;
  int D, dD, n, dx, dy;
  bool done = 0;
  int angle_x;   // [100urad]
  int angle_y;   // [100urad]
  int pw_x;      // [us]
  int pw_y;
  
	// send data only when you receive data:
	if (Serial.available() > 0) {
		// read the incoming byte:
		in_len = Serial.readBytes(ser_in, 20);

    parseCmdLn(ser_in, in_len);
	}
 
  if ((myMill.curr_x != myMill.ref_x) || (myMill.curr_y != myMill.ref_y))
  {
    myMill.state = Moving;
    
    // control error, distance between ref and current position
    tmpD = (long)(myMill.ref_x - myMill.curr_x) * (long)(myMill.ref_x - myMill.curr_x);
    tmpD += (long)(myMill.ref_y - myMill.curr_y) * (long)(myMill.ref_y - myMill.curr_y);
    D = (int)sqrt(tmpD);
    
    dD = myMill.curr_feed / 6;  // travel per 100ms, [mm/minut] = 100*[10um]/60*10[100ms]   
    
    // calculate number of 100ms iterations it will require to travel distance D.
    // n will be rounded.
    n = (int)(D/dD + 0.5);           // number of 100ms to move distance D
    if (n == 0)                 // if distance to travel takes lesser than 100 ms
    {
      n = 1;                    // travel that distace in 100 ms anyway
    }

    debug_print(D);
    debug_print(n);
    
    // if this is the last iteration to reach target, then set curr to target
    // in the casees where n was smaller/bigger than 1 and rounded to 1, 
    // this construction will make the last travle slightly slower/faster than feed_rate
    if (n == 1)
    {
      myMill.curr_x = myMill.ref_x;
      myMill.curr_y = myMill.ref_y;
      done = 1;
    }
    else
    {
      // calculate x and y distance to move this iteration 
      dx = abs(myMill.ref_x - myMill.curr_x)/n;
      if (myMill.curr_x < myMill.ref_x)  // do the move with correct direction
      {
        myMill.curr_x += dx;
      }
      else
      {
        myMill.curr_x -= dx;
      }
        
      dy = abs(myMill.ref_y - myMill.curr_y)/n;
      if (myMill.curr_y < myMill.ref_y)
      {
        myMill.curr_y += dy;
      }
      else
      {
        myMill.curr_y -= dy;
      }
    }

    debug_print(myMill.curr_x);
    debug_print(myMill.curr_y);
  }

  if(myMill.state == Moving)
  {
    //calc servo angle..... based on curr_x and curr_y
    angle_x = calcAngle(myMill.curr_x);
    angle_y = calcAngle(myMill.curr_y);
    debug_print(angle_x);
    debug_print(angle_y);
    
    //convert to servo control signal
    pw_x = calcServoPw(angle_x);
    pw_y = calcServoPw(angle_y);
    debug_print(pw_x);
    debug_print(pw_y);

    Serial.println("");

    xServo.writeMicroseconds(pw_x);
    yServo.writeMicroseconds(pw_y);
  }

  if (done)
  {
    myMill.state = Idle;
    Serial.println("done");
    done = 0;
  }
  
  delay(100);                       // waits 100ms
}

//parse command line and execute each command
void parseCmdLn(char* cmd_ln, byte len)
{
  byte i = 0;
  bool done = 0;
  int tmp_int;
  
  //temp debug ////////////////
  String tmp_str = cmd_ln;
  tmp_str.remove(len);
  debug_print(tmp_str);
  /////////////////////////////

  //traverse the command line looking for individual commands
  while((!done) && (i < len-1)) //len-1 because a command must be followed by a number
  {
    if (cmd_ln[i] == 'G')
    {
      handleG(cmd_ln[i+1]);
    }
    else if (cmd_ln[i] == 'X')
    {
      // hopefully the next few positions in cmd_ln contains our x-coordinate
      tmp_int = snipInt(cmd_ln, i+1, len);

      myMill.ref_x = saturate(tmp_int, X_MAX, X_MIN);
    }
    else if (cmd_ln[i] == 'Y')
    {
      // hopefully the next few positions in cmd_ln contains our y-coordinate
      tmp_int = snipInt(cmd_ln, i+1, len);

      myMill.ref_y = saturate(tmp_int, Y_MAX, Y_MIN);
    }
    else if (cmd_ln[i] == 'F')
    {
      // hopefully the next few positions in cmd_ln contains our y-coordinate
      tmp_int = snipInt(cmd_ln, i+1, len);
      
      if (tmp_int < MIN_FEED)
      {
        tmp_int = MIN_FEED;
      }
      
      myMill.cutting_feed = tmp_int;
      myMill.curr_feed = myMill.cutting_feed;
    }
    else if (cmd_ln[i] == 'M')
    {
      // hopefully the next few positions in cmd_ln contains our y-coordinate
      tmp_int = snipInt(cmd_ln, i+1, len);

      // debug ////////////////////
      if ((tmp_int<=2550) && (tmp_int >= 650)) 
      {
        myMill.state = Test;
        xServo.writeMicroseconds(tmp_int);
      }
      if (tmp_int == 0)
      {
        myMill.state = Idle;
      }
      //////////////////////////////
    }
    else if (cmd_ln[i] == 'D')
    { 
      debug_flag = (cmd_ln[i+1] == '0' ? 0 : 1);
      debug_dump();
    }
    else
    {
      // throw away
    }
    
    i = i+1;
  }
}

// set the feed_rate
void handleG(char cmd)
{
  if (cmd == '1')
  {
    myMill.curr_feed = myMill.cutting_feed;
  }
  if (cmd == '0')
  {
    myMill.curr_feed = MAX_TRAVERSE_FEED;
  }
}

// dig out number from a string.
// the string is assumed to start with an integer
// if string does not contain integer, 0 is returned
int snipInt(char* str, byte pos, byte len)
{
  int retVal = 0;
  bool is_neg = 0;
  bool done = 0;
  String subStr;
  byte local_pos = pos;
  byte i = 0;
  
  if (str[local_pos] == '-')
  {
    is_neg = 1;
    local_pos += 1; 
  }

  i = local_pos;
  while ((!done) && (i < len))
  {
    if((str[i] <= '9') && (str[i] >= '0'))
    {
      subStr.concat(str[i]);
    }
    else
    {
      done = 1;
    }
    
    i++;
  }
  
  retVal = subStr.toInt();
  if ((retVal != 0) && is_neg)
  {
    retVal = -retVal;
  }

  return retVal;
}

int saturate(int in, int max_limit, int min_limit)
{
  int retVal = in;
  
  if (in > max_limit)
  {
    retVal = max_limit;
  }
  if (in < min_limit)
  {
    retVal = min_limit;
  }

  return retVal;
}

void debug_dump(void)
{
  debug_print(myMill.state);
  debug_print(myMill.spindle_speed);
  debug_print(myMill.cutting_feed);
  debug_print(myMill.curr_feed);
  debug_print(myMill.curr_x);
  debug_print(myMill.ref_x);
  debug_print(myMill.curr_y);
  debug_print(myMill.ref_y);
  debug_print(debug_flag);
}

// calculate servo pulse width to get servo angle
// angle in 100 urad unit
int calcServoPw(int angle)
{
  int pw;
  /*
  //test code.....
  int k_x1_plus_y1 = KX1_PLUS_Y1;
  long tmp;
  
  tmp = ((long)(SERVO_PW_MAX_ANGLE - SERVO_PW_MIN_ANGLE)*(long)angle);
  debug_print(tmp);
  pw = (int)(tmp/(MAX_SERVO_ANGLE - MIN_SERVO_ANGLE));
  debug_print(pw);
  pw += k_x1_plus_y1;
  debug_print(pw);
  */
  pw = CALC_PW_FROM_ANGLE(angle);
  return pw;
}

// calculate angle of servo given wanted coordinate using "cosinus satsen"
// angle =  acosd( (c*c+b*b-a*a)/(2*b*c) )
// returns angle in 100 micro radian units
int calcAngle(int x)
{
  long a = 4000; // 40mm = 4000 [10um]
  long b = 2000;
  long c = x+a;
  long num; //numerator
  long den; //denominator
  float tmp_angle;
  float ratio;
  int angle; 
    
  num = c*c;  //numerator
  num += b*b;
  num -= a*a;

  den = (2*b*c);  //denominator

  ratio = (float)((float)num/(float)den);
  
  tmp_angle = acos(ratio); // tmp_angle in radians
  angle = (int)(1000*tmp_angle);           // angle in 100 micro radians
  
  return angle;
}

