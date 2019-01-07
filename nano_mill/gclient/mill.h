#if !defined(C_MILL_DEF)
#define C_MILL_DEF

#include "slide_ctrl.h"
#include "cfg_params.h"
#include <Arduino.h>

typedef enum
{
  Idle,
  Moving,
  Test
} state_T;

class C_Mill
{
	public:
		C_Mill();
		
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

	   C_SlideCtrl x_slide_ctrl;
	   C_SlideCtrl y_slide_ctrl;
	   
	   state_T state;

		void init();
		void run();
		void debug_dump();
		void setRefX(int x);
		void setRefY(int y);
		void setSpindleSpeed(int s);
		void setCuttingFeed(int f);
		void setLinInterCutFeed(void);
		void setLinInterTravFeed(void);
		void setDebugFlag(byte f);
    void setTestState(bool in);
		
	private:
		byte debug_flag;
		int saturate(int in, int max_limit, int min_limit);
};

#endif
