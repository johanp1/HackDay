#include "controller.h"
#include <iostream>
using namespace std;

Controller::Controller(int period) : speedCtrl(period)
{
   refSpeed = 0;
   PIDParameters p(2, // K, 
                                   100, // Ti
                                   100, // Td 
                                   10, // N 
                                   1, // Tr
                                   1); // beta
  
   speedCtrl.setPar(p);

   refSpeed = 0;
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
  h=period;
  min = 0;
  max = 2000;
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

  if (out <= min){
    out = min;
    cout << "out <= min\n";
  }
  if (out >= max){
    out = max;
    cout << "out >= max\n";
  }

  return out;
}   

int PIDController::calcOutput(int y, int yRef)
{
  cout << "\ncalculate output:\n";
   int u; //output from actuator
   int e = yRef - y;

   if (par.Td != 0)
   {  // only update D if Td not zero
     D = (par.Td*D)/(par.Td+par.N*h) - (par.K*par.Td*par.N)/(par.Td + par.N*h)*(y - yPrev);
   }
   
   v = par.K*(par.beta*yRef-y) + I + D;
   u = saturate(v);
   cout << "P: " << par.K*(par.beta*yRef-y) << ", ";
   cout << "I: " << I << ", ";
   cout << "D: " << D << ", ";
   I = I + (par.K*h*e)/par.Ti + (h*(u-v))/par.Tr;
   cout << "h: " << h << ", ";
   cout << "e: " << e << ", ";
   cout << "par.K: " << par.K << "\n";
   cout << "\t(par.K*h*e)=" << (par.K*h*e) << "\n";
   cout << "\t(par.K*h*e)/par.Ti=: " << (par.K*h*e)/par.Ti << "\n";
   cout << "\t(h*(u-v))/par.Tr= " <<  (h*(u-v))/par.Tr << "\n";
   cout << "updated I: " << I << "\n\n";
   cout << "v: " << v << " u: " << u << "\n";
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
}

void PIDParameters::setPar(int _K, int _Ti, int _Td, int pN, int _Tr, int _beta)
{
   K = _K;
   Ti = _Ti;
   Td = _Td;
   N = pN;
   Tr = _Tr;
   beta = _beta;
}

void PIDParameters::setPar(PIDParameters &p)
{
   K = p.K;
   Ti = p.Ti;
   Td = p.Td;
   N = p.N;
   Tr = p.Tr;
   beta = p.beta;

   //cout << "setPar2:" << "K: " << K << ", Ti: " << Ti << ", Td: " <<  Td << ", N: " << N << ", Tr: " << Tr << ", beta: " << beta << "\n";
}
