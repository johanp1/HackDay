#include "controller.h"
#include <iostream>
using namespace std;

Controller::Controller(int period) : speedCtrl(period)
{
   refSpeed = 0;
   PIDParameters p(2, // K, 
                                   1000, // Ti, rule of thumb h/Ti = 0.1-0.3 
                                   100, // Td 
                                   10, // N 
                                   300, // Tr, rule of thumb Tr = sqrt(Ti*Td)
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
   PIDParameters p;

   setPar(p);

   h=period;
   min = 0;
   max = 2000;
   v = 0;
   D = 0;
   I = 0;
   yPrev = 0;

   cout << "PIDController constr: " << "period: " << h << " min: " << min << " max: " << max << "\n";
}  

PIDController::PIDController(int period, PIDParameters &p, int _min, int _max)
{
   setPar(p);
   
   h = period;
   min = _min;
   max = _max;
   v = 0;
   D = 0;
   I = 0;
   yPrev = 0;

   cout << "PIDController constr2: " << "period: " << h << " min: " << min << " max: " << max << "\n";
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
      cout << "\t(par.Td*D)=" << (par.Td*D) << "\n";
      cout << "\t(par.Td+par.N*h)=" << (par.Td+par.N*h) << "\n";
      cout << "\t(par.K*par.Td*par.N)=" << (par.K*par.Td*par.N) << "\n";
      cout << "\t(y - yPrev)=" << (y - yPrev) << "\n";
      cout << "\t(par.Td + par.N*h)=" << (par.Td + par.N*h) << "\n";
      D = (par.Td*D)/(par.Td+par.N*h) - ((par.K*par.Td*par.N)*(y - yPrev))/(par.Td + par.N*h);
      cout << "\tupdated D: " << D << "\n";
   }
   
   v = par.K*(par.beta*yRef-y) + I + D;
   u = saturate(v);
   cout << "P: " << par.K*(par.beta*yRef-y) << ", ";
   cout << "I: " << I << ", ";
   cout << "D: " << D << ", ";
   cout << "min: " << min << " max: " << max << "\n";
   I = I + (par.K*h*e)/par.Ti + (h*(u-v))/par.Tr;
   cout << "h: " << h << ", ";
   cout << "e: " << e << "\n";
   cout << "\t(par.K*h*e)=" << (par.K*h*e) << "\n";
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
