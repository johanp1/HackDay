#include "slide_ctrl.h"

#define debug_print(x)  if(debug_flag) {Serial.print(#x); Serial.print(": "); Serial.println(x);}
#define DEGRES_TO_100URAD(a)  (long)((long)(a)*175)/10    // (a)*pi/180*1000 *10/10 

C_SlideCtrl::C_SlideCtrl() {}

// local functions

// calculate servo pulse width to get servo angle
// angle in 100 urad unit
int C_SlideCtrl::calcServoPw(int angle)
{
  int pw;

  long tmp;
  
  tmp = (long) ((long)dy*(long)angle);
  pw = (int)(tmp/dx);
  pw += y1_minus_kx1;
 
  return pw;
}

// calculate angle of servo given wanted coordinate using "cosinus satsen"
// angle =  acosd( (c*c+b*b-a*a)/(2*b*c) )
// returns angle in 100 micro radian units
int C_SlideCtrl::calcAngle(int x)
{
  long c = (long)x + a;
  long num; //numerator
  long den; //denominator
  float tmp_angle;
  float ratio;
  int angle; 
    
  num = c*c;  //numerator
  num += (long)b*(long)b;
  num -= (long)a*(long)a;

  den = (2*b*c);  //denominator

  ratio = (float)((float)num/(float)den);
  
  tmp_angle = acos(ratio);         // tmp_angle in radians
  angle = (int)(1000*tmp_angle);   // angle in 100 micro radians
  
  return angle;
}



// global functions

void C_SlideCtrl::init(String str_name, byte pin, int a_in, int b_in, int max_ang, int min_ang, int pw_max, int pw_min)
{
  name = str_name;
  debug_flag = 1;
  // set config parameters
  a = a_in;  // length of arm attached to servo [10um]
  b = b_in;  // length of arm attached to sliding part [10um]
  
  max_angle = DEGRES_TO_100URAD(max_ang);  // [100urad]
  min_angle = DEGRES_TO_100URAD(min_ang);  // [100urad]
  pw_max_angle = pw_max; // [us]
  pw_min_angle = pw_min;
  
  // pre-calc internal parameters used for optimizing calculations
  // y = (y2- y1)/(x2-x1)(x-x1)+y1
  // re-organised to y = ((y2 - y1)*x)/dx - ((y2 - y1)*x1)/dx + y1
  // => y = dy*x/dx + y1_minus_kx1, where y1_minus_kx1 = y1 - dy*x1/dx  

  dx = (max_angle - min_angle);
  dy = (pw_max - pw_min);
  y1_minus_kx1 = pw_min - (int)((long)dy*(long)min_angle)/(long)dx;
  
  servo.attach(pin);
}

void C_SlideCtrl::run(int x)
{
	int ang;   // [100urad]
  int pw;      // [us]
    	
	//calc servo angle..... based on curr_x and curr_y
  ang = calcAngle(x); 
      
  //convert to servo control signal
  pw = calcServoPw(ang);
  
  debug_print(name);
  debug_print(ang);
  debug_print(pw)

  servo.writeMicroseconds(pw);
}

// used for testing
void C_SlideCtrl::setPWM(int pwm)
{
	if ((pwm <= 2350) && (pwm >= 650))
	{
		servo.writeMicroseconds(pwm);
    debug_print(name);
    debug_print(pwm)
	}
}

void C_SlideCtrl::setDebugFlag(byte f)
{
	debug_flag = f;
}

void C_SlideCtrl::debug_dump()
{
    debug_print(name);
    debug_print(a); 
    debug_print(b);    
    debug_print(max_angle);
    debug_print(min_angle);
    debug_print(pw_max_angle);
    debug_print(pw_min_angle);
    debug_print(y1_minus_kx1);
    debug_print(dx);
    debug_print(dy);
}
