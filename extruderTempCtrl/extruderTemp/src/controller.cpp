#include "controller.h"
#include "Arduino.h"

#define DEBUG 0
#define debug_print(x)   if(debug){Serial.print(#x); Serial.print(": "); Serial.println(x);}

PIDController::PIDController(int period)
{
   PIDParameters p;

   SetPar(p);

   h = period;
   min = 0;
   max = 2000;
   D = 0;
   I = 0;
   v = 0;
   yRef = 0;
   yPrev = 0;
   enabled = false;
   debug = 0;
}  

PIDController::PIDController(int period, PIDParameters const& p, int _min, int _max)
{
   SetPar(p);
   
   h = period;
   min = _min;
   max = _max;
   D = 0;
   I = 0;
   v = 0;
   yRef = 0;
   yPrev = 0;
   enabled = false;
   debug = 0;
}

void PIDController::SetPar(PIDParameters const& p)
{
   par.Set(p);
}  

void PIDController::SetRef(int yRef_)
{
   yRef = yRef_;
}  

PIDParameters const& PIDController::GetPar() const
{
   return par;
}

void PIDController::SetEnable(bool e)
{
   enabled = e;
}

void PIDController::Step(int y)
{
   if (enabled == true)
   {
      v = CalcOutput(y, yRef);
   } 
}   

int PIDController::GetOut(void)
{
   return v;
}

void PIDController::SetDebug(bool d)
{
  debug = d;
  debug_print(debug);
}

int PIDController::Saturate(int in)
{
  int out = in;

  if (out < min)
  {
    out = min;
  }
  if (out > max)
  {
    out = max;
  }

  return out;
}   

int PIDController::CalcOutput(int y, int yRef)
{
  //cout << "\ncalculate output:\n";
  int I_term1;
  int I_term2;
  int u; //output from actuator (saturated v)
  int e = yRef - y;
  debug_print(y);
  debug_print(yRef);
  debug_print(e);

  if (par.Td != 0)
  {  // only update D if Td not zero
    D = (par.Td*D)/(par.Td+par.N*h) - ((par.K*par.Td*par.N)*(y - yPrev))/(par.Td + par.N*h);
    debug_print(D);
  }
   
  v = par.K*(par.beta*yRef-y) + I + D; // v(t) = K*e(t) + I(t-1) + D(t)
  u = Saturate(v);
  debug_print(v);
  debug_print(u);
 
  I_term1 = (int)((long)par.K*(long)h*(long)e)/par.Ti;
  I_term2 = (int)((long)h*(long)(u-v))/par.Tr;
  debug_print(I_term1);
  debug_print(I_term2);
  I = I + I_term1 + I_term2;
  debug_print(I);

  yPrev = y;
   
  return  u;
}

PIDParameters::PIDParameters()
{
  Set(0, 0, 0, 0, 0, 0);
}

PIDParameters::PIDParameters(int _K, int _Ti, int _Td, int pN, int _Tr, int _beta)
{
   Set(_K, _Ti, _Td, pN, _Tr, _beta);
}

PIDParameters::PIDParameters(PIDParameters const& p)
{
   Set(p);
}


void PIDParameters::Set(int _K, int _Ti, int _Td, int pN, int _Tr, int _beta)
{
   K = _K;
   Ti = _Ti;
   Td = _Td;
   N = pN;
   Tr = _Tr;
   beta = _beta;
}

void PIDParameters::Set(PIDParameters const& p)
{
   K = p.K;
   Ti = p.Ti;
   Td = p.Td;
   N = p.N;
   Tr = p.Tr;
   beta = p.beta;
}

bool PIDParameters::operator==(PIDParameters const& p) const
{
   return ((K == p.K) &&  (Ti == p.Ti) && (Td == p.Td) && (N == p.N) && (Tr == p.Tr) && (beta == p.beta));
}

bool PIDParameters::operator!=(PIDParameters const& p) const
{
   return ((K != p.K) || (Ti != p.Ti) || (Td != p.Td) || (N != p.N) || (Tr != p.Tr) || (beta != p.beta));
}
