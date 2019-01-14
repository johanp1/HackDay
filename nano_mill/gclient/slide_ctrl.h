#if !defined(C_SLIDECTRL_DEF)
#define C_SLIDECTRL_DEF


#include <Servo.h>
#include <Arduino.h>

class C_SlideCtrl
{
	public:
		C_SlideCtrl();
		
		// config parameters
		int a;  // length of arm attached to servo [10um]
		int b;  // length of arm attached to sliding part [10um]
	  
		int max_angle;  // [100urad]
		int min_angle;
		int pw_max_angle; // [us]
		int pw_min_angle;  
	  String name;
    
		//internal parameters used for calculations
		long y1_minus_kx1;
		long dx;
		long dy;
	  
		Servo servo;

		void init(String name, byte pin, int a, int b, int max_angle, int min_angle, int pw_max, int pw_min);
		void run(int x);
		void setPWM(int pwm);
		void setDebugFlag(byte f);
    void debug_dump();
    
	private:
		int calcServoPw(int angle);
		int calcAngle(int x);
		byte debug_flag;
};

#endif
