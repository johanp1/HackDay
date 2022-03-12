#ifndef __CONTROLLER_H__
#define __CONTROLLER_H__


class PIDParameters
{
   public:
   PIDParameters();
   PIDParameters(PIDParameters const& p);
   PIDParameters(int _K, int _Ti, int _Td, int pN, int _Tr, int _beta);
   void Set(PIDParameters const& p);
   void Set(int _K, int _Ti, int _Td, int pN, int _Tr, int _beta);
   bool operator==(PIDParameters const& p) const;
   bool operator!=(PIDParameters const& p) const;

   int K; 
   int Ti;
   int Td;
   int N;
   int Tr;
   int beta;
};

class PIDController
{
   public:
   PIDController(int period); // [ms]
   PIDController(int period, PIDParameters const& p, int _min, int _max);

   void SetPar(PIDParameters const& p);
   void SetRef(int yRef_);
   void Step(int y);
   int GetOut(void);
   PIDParameters const& GetPar() const;
   void SetEnable(bool e);
   void SetDebug(bool d);
   
   private:
   int Saturate(int in);
   int CalcOutput(int y, int yRef);
   
   class PIDParameters par;

   int h; //period [ms]
   int min;
   int max;
   int D;
   int I;
   int yPrev;
   int yRef;
   int v; //output from controller
   bool enabled;
   bool debug;
};

#endif
