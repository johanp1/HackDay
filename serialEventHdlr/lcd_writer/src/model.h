#ifndef __MODEL_H__
#define __MODEL_H__

constexpr auto k_maxNbrOfObservers = 4;

using Position = float;
using Speed = int;
//using Row = byte;
enum Axis {axis_x, axis_z};

class Observer
{
   public:
   Observer(){};
   virtual ~Observer(){};
   virtual void Update(){};
};

class Model
{
   public:
   Model();

   void Attach(Observer* o);
   void Detach(Observer* o);

   void SetX(Position p) {x_pos_ = p; Notify();};
   void SetY(Position p) {y_pos_ = p; Notify();};
   void SetSpindleSpeed(Speed s) {spindle_speed_ = s; Notify();};
   void SetActiveAxis(Axis a) {active_axis_ = a;Notify();};

   Position GetX() {return x_pos_;};
   Position GetZ() {return z_pos_;};
   Speed GetSpindleSpeed() {return spindle_speed_;};
   Axis GetActiveAxis() {return active_axis_;};

   protected:
   virtual void Notify();

   private:
   Position x_pos_;
   Position z_pos_;
   Speed spindle_speed_;
   Axis active_axis_;
   Observer* registry_[k_maxNbrOfObservers];
};

#endif // __MODEL_H__