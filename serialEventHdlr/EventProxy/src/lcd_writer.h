#ifndef __C_LCD_WRITER_H__
#define __C_LCD_WRITER_H__

#include <Arduino.h>
#include "event_parser.h"

using Position = float;
using Speed = int;
using Row = byte;
enum Axis {axis_x, axis_y};

class Observer
{
   public:
   Observer(){};
   virtual void Update(){};
};

class Model
{
   public:
   Model(){x_pos_ = 0.0f, y_pos_ = 0.0f, spindle_speed_ = 0; active_axis_ = axis_x;};

   void Attach(Observer* o){registry = o;};
   void Detach(Observer* o)
   {
      if (registry == o)
      {
         registry = nullptr;
      }
   };

   void SetX(Position p){x_pos_ = p; Notify();};
   void SetY(Position p){y_pos_ = p; Notify();};
   void SetSpindleSpeed(Speed s){spindle_speed_ = s; Notify();};
   void SetActiveAxis(Axis a){active_axis_ = a;Notify();};

   Position GetX(){return x_pos_;};
   Position GetY(){return y_pos_;};
   Speed GetSpindleSpeed(){return spindle_speed_;};
   Axis GetActiveAxis(){return active_axis_;};

   protected:
   virtual void Notify(){registry->Update();};

   private:
   Position x_pos_;
   Position y_pos_;
   Speed spindle_speed_;
   Axis active_axis_;
   Observer* registry;
};

template <class Lcd>
class LcdView : public Observer
{
   public:
   LcdView(Lcd& lcd, Model& model) : myLcd(lcd), myModel(model) {myModel.Attach(this);};
   virtual ~LcdView(){myModel.Detach(this);};
   virtual void Update(){this->Draw();};
   virtual void Draw();

   protected:
   Lcd& myLcd;
   Model& myModel;
};

template <class Lcd>
void LcdView<Lcd>::Draw()
{
   myLcd.clear();
   myLcd.setCursor(0, 0);
   myLcd.print(String("hej"));
};

template <class Lcd>
class AxisView : public LcdView<Lcd> 
{
   public:
   AxisView(Lcd& lcd, Model& model) : LcdView<Lcd>(lcd, model){};

   void Draw() override;
};

template <class Lcd>
void AxisView<Lcd>::Draw()
{
   String row1 = String(" x: ");
   String row2 = String(" y: ");

   row1.concat(this->myModel.GetX());
   row2.concat(this->myModel.GetY());
   
   // indicate the jogged/active axis with a  '*'
   row1.setCharAt(0, this->myModel.GetActiveAxis() == axis_x ? '*' : ' ');
   row2.setCharAt(0, this->myModel.GetActiveAxis() == axis_y ? '*' : ' ');

   this->myLcd.clear()
   this->myLcd.setCursor(0, 0);
   this->myLcd.print(row1);
   this->myLcd.setCursor(0, 1);
   this->myLcd.print(row2);
};

template <class Lcd>
class SpindleView : public LcdView<Lcd> 
{
   public:
   SpindleView(Lcd& lcd, Model& model) : LcdView<Lcd>(lcd, model){};

   void Draw() override;
};

template <class Lcd>
void SpindleView<Lcd>::Draw()
{
   String row1 = String(" spindle speed:");
   String row2 = String(" ");

   row2.concat(this->myModel.GetSpindleSpeed());
   row2.concat(String(" rpm"));

   this->myLcd.clear()
   this->myLcd.setCursor(0, 0);
   this->myLcd.print(row1);
   this->myLcd.setCursor(0, 1);
   this->myLcd.print(row2);
};

template <class Lcd>
class LcdWriter
{
public:
   LcdWriter(Lcd& lcd /*, uint8_t cols, uint8_t rows*/)  : myLcd(lcd)
   {
      LcdView<Lcd>* myView = new AxisView<Lcd>(myLcd, myModel);

      // for some reason this didn't work?. Client needs to 
      // do begin and setBacklight
      //myLcd.begin(16, 2);
      //myLcd.setBacklight(200);
   };
   ~LcdWriter(){};

   void SetX(Position p) {myModel.SetX(p);};
   void SetY(Position p) {myModel.SetY(p);};
   void SetSpindleSpeed(Speed s) {myModel.SetSpindleSpeed(s);};
   void SetActiveAxis(Axis a) {myModel.SetActiveAxis(a);};
   void SetAxisView()
   {
      delete myView;

      myView = new AxisView<Lcd>(myLcd, myModel);
      myView->Draw();
   };
   void SetSpindleView()
   {
      delete myView;

      myView = new SpindleView<Lcd>(myLcd, myModel);
      myView->Draw();
   };

   Model myModel;

private:
   Lcd& myLcd;
   LcdView<Lcd>* myView;
   
};

#endif // __C_LCD_WRITER_H__