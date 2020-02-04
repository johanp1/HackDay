#include "controller.h"
#include <iostream>
using namespace std;

Controller::Controller(int period) : speedCtrl(period)
{
   refSpeed = 0;
   PIDParameters p(2, // K, 
                                   1, // Ti
                                   1, // Td 
                                   1, // N 
                                   1, // Tr
                                   1); // beta
   speedCtrl.setPar(p);
   refSpeed = period;
   currSpeed = 0;
}

void Controller::setSpeedRef(int s)
{
   refSpeed = s;
}

void Controller::setSpeed(int s)
{
   currSpeed = s;
}

int Controller::run(void)
{
   return speedCtrl.step(currSpeed, refSpeed);
}   

PIDController::PIDController(int period)
{
   PIDParameters p;
   PIDController(period, p);
}  

PIDController::PIDController(int period, PIDParameters &p)
{
   PIDController(period, p, 0, 2000);
}  

PIDController::PIDController(int period, PIDParameters &p, int _min, int _max)
{
   h = period;
   setPar(p);
   min = _min;
   max = _max;
   v = 0;
   D = 0;
   I = 0;
   yPrev = 0;
   cout << "PIDController constr: " << "period: " << h << " min: " << min << " max: " << max << "\n";
}

void PIDController::setPar(PIDParameters &p)
{
   par.setPar(p);
}  

int PIDController::step(int y, int yRef)
{
   return calcOutput(y, yRef);
}   

int PIDController::saturate(int in)
{
   int out = in;
/*   cout << "in: " << in << "\n";
   if (out <= min)
   {
  		out = min;
      cout << "out <= min\n";
   }
  	if (out >= max)
   {
  		out = max;
      cout << "out >= max\n";
   }*/
cout << "saturate: " << "in: " << in << " out: " << out << "\n";
  	return out;
}   

int PIDController::calcOutput(int y, int yRef)
{
   int u; //output from actuator
   int e = yRef - y;

   if (par.Td != 0)
   {  // only update D if Td not zero
		D = (par.Td*D)/(par.Td+par.N*h) - (par.K*par.Td*par.N)/(par.Td + par.N*h)*(y - yPrev);
      cout << "D: " << D << "\n";
  	}
   v = par.K*(par.beta*yRef-y) + I + D;
   u = saturate(v);

   cout << "v: " << v << " u: " << u << "\n";

   cout << "I: " << I << "\n";
   I = I + (par.K*h*e)/par.Ti + (h*(u-v))/par.Tr;
   cout << "par.K: " << par.K << "\n";
   cout << "h: " << h << "\n";
   cout << "e: " << e << "\n";
   cout << "par.K: " << par.K << "\n";
   cout << "(par.K*h*e)" << (par.K*h*e) << "\n";
   cout << "(par.K*h*e)/par.Ti: " << (par.K*h*e)/par.Ti << "\n";
   cout << " (h*(u-v))/par.Tr: " <<  (h*(u-v))/par.Tr << "\n";
   cout << "updated I: " << I << "\n";
  	yPrev = y;
   
  	return  u;
}

PIDParameters::PIDParameters()
{
   setPar(0, 0, 0, 0, 0, 0);
}

PIDParameters::PIDParameters(int _K, int _Ti, int _Td, int pN, int _Tr, int _beta)
{
   K = _K;
   Ti = _Ti;
   Td = _Td;
   N = pN;
   Tr = _Tr;
   beta = _beta;

   cout << "par constr:" << "K: " << K << ", Ti: " << Ti << ", Td: " <<  Td << ", N: " << N << ", Tr: " << Tr << ", beta: " << beta << "\n";
}

void PIDParameters::setPar(int _K, int _Ti, int _Td, int pN, int _Tr, int _beta)
{
   K = _K;
   Ti = _Ti;
   Td = _Td;
   N = pN;
   Tr = _Tr;
   beta = _beta;

   cout << "setPar1:" << "K: " << K << ", Ti: " << Ti << ", Td: " <<  Td << ", N: " << N << ", Tr: " << Tr << ", beta: " << beta << "\n";
}

void PIDParameters::setPar(PIDParameters &p)
{
   K = p.K;
   Ti = p.Ti;
   Td = p.Td;
   N = p.N;
   Tr = p.Tr;
   beta = p.beta;

   cout << "setPar2:" << "K: " << K << ", Ti: " << Ti << ", Td: " <<  Td << ", N: " << N << ", Tr: " << Tr << ", beta: " << beta << "\n";
}