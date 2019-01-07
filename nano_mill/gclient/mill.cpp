#include "mill.h"

#define debug_print(x)  if(debug_flag) {Serial.print(#x); Serial.print(": "); Serial.println(x);}

C_Mill::C_Mill() {}

void C_Mill::init()
{
  state = Idle;
  spindle_speed = 100;
  cutting_feed = 180; //MIN_FEED;  // default cutting feed rate
  curr_feed = 180;    //MIN_FEED;    // current cutting feed rate [mm/minut]
  curr_x = 0;
  ref_x = 0;
  curr_y = 0;
  ref_y = 0;
  
  debug_flag = 1;
  
//  x_slide_ctrl = new C_SlideCtrl();
//  x_slide_ctrl = new C_SlideCtrl();
  
  x_slide_ctrl.init("x", 9, 4000, 2000, 180, 0, 2300, 700);
  y_slide_ctrl.init("y", 10, 4000, 2000, 180, 0, 2300, 700);
}

void C_Mill::run()
{
  long tmpD;
  int D, dD, n, dx, dy;
  bool done = 0;
  
  if (((curr_x != ref_x) || (curr_y != ref_y)) && (state != Test))
  {
    state = Moving;
    
    // control error, distance between ref and current position
    tmpD = (long)(ref_x - curr_x) * (long)(ref_x - curr_x);
    tmpD += (long)(ref_y - curr_y) * (long)(ref_y - curr_y);
    D = (int)sqrt(tmpD);
    
    dD = curr_feed / 6;  // travel per 100ms, [mm/minut] = 100*[10um]/60*10[100ms]   
    
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
      curr_x = ref_x;
      curr_y = ref_y;
      done = 1;
    }
    else
    {
      // calculate x and y distance to move this iteration 
      dx = abs(ref_x - curr_x)/n;
      if (curr_x < ref_x)  // do the move with correct direction
      {
        curr_x += dx;
      }
      else
      {
        curr_x -= dx;
      }
        
      dy = abs(ref_y - curr_y)/n;
      if (curr_y < ref_y)
      {
        curr_y += dy;
      }
      else
      {
        curr_y -= dy;
      }
    }

    debug_print(curr_x);
    debug_print(curr_y);
  }

  if(state == Moving)
  {
    //calc servo angle..... based on curr_x and curr_y
/*    angle_x = calcAngle(this.curr_x);
    angle_y = calcAngle(this.curr_y);
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
	*/
	x_slide_ctrl.run(curr_x);
	y_slide_ctrl.run(curr_y);
  }

  if (done)
  {
    state = Idle;
    Serial.println("done");
    done = 0;
  }
}

void C_Mill::debug_dump()
{
  debug_print(state);
  debug_print(spindle_speed);
  debug_print(cutting_feed);
  debug_print(curr_feed);
  debug_print(curr_x);
  debug_print(ref_x);
  debug_print(curr_y);
  debug_print(ref_y);

  x_slide_ctrl.debug_dump();
  y_slide_ctrl.debug_dump();
}

void C_Mill::setDebugFlag(byte f)
{
	debug_flag = f;
	x_slide_ctrl.setDebugFlag(f);
	y_slide_ctrl.setDebugFlag(f);
}

void C_Mill::setRefX(int x)
{
  if ((state == Idle) || (state == Moving))
  {
	  ref_x = saturate(x, X_MAX, X_MIN);
  }
  
	if(state == Test)
	{
		if ((x <= 2350) && (x >= 650)) 
		{
			x_slide_ctrl.setPWM(x);
		}
	}
}

void C_Mill::setRefY(int y)
{
  if ((state == Idle) || (state == Moving))
  {
	  ref_y = saturate(y, Y_MAX, Y_MIN);
  }
  
	if(state == Test)
	{
		if ((y <= 2350) && (y >= 650)) 
		{
			y_slide_ctrl.setPWM(y);
		}
	}
}

void C_Mill::setSpindleSpeed(int s)
{
	spindle_speed = s;
}

void C_Mill::setCuttingFeed(int f)
{
	if (f < MIN_FEED)
    {
		cutting_feed = MIN_FEED;
    }
    else 
	{
		cutting_feed = f;
	}
}

void C_Mill::setLinInterCutFeed(void)
{
	curr_feed = cutting_feed;
}

void C_Mill::setLinInterTravFeed(void)
{
	curr_feed = MAX_TRAVERSE_FEED;
}

void C_Mill::setTestState(bool in)
{
	if (in)
	{
		state = Test;
	}
	else
	{
		state = Idle;
	}
}


int C_Mill::saturate(int in, int max_limit, int min_limit)
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
