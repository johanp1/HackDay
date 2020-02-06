 #ifndef __CONTROLLER_H__
#define __CONTROLLER_H__


class PIDParameters
{
   public:
   PIDParameters();
   PIDParameters(PIDParameters &p);
   PIDParameters(int _K, int _Ti, int _Td, int pN, int _Tr, int _beta);
   void setPar(PIDParameters &p);
   void setPar(int _K, int _Ti, int _Td, int pN, int _Tr, int _beta);

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
   PIDController(int period, PIDParameters &p, int _min, int _max);
   void setPar(PIDParameters &p);
   int step(int y, int yRef); // y [rps], yRef [rps]
   
   private:
   int saturate(int in);
   int calcOutput(int y, int yRef);
   void updateState();
   
   class PIDParameters par;

   int h; //period [ms]
   int min;
   int max;
   int v; //output from controller
   int D;
   int I;
   int yPrev;
};

class Controller //: public C_EventListner
{
   public:
   Controller(int period);
   
//   void handleEvent(C_Event& e);
//   void setMode(byte m);
//   void setAngleRef(int a);
   void setSpeedRef(int s);
   void setSpeed(int s);
//   void setAngle(int a);
   int run(void);
   
   private:
   class PIDController speedCtrl;
   int refSpeed;
   int currSpeed;
};

#endif
