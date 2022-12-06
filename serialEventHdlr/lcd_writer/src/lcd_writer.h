#ifndef __C_LCD_WRITER_H__
#define __C_LCD_WRITER_H__

#include <Arduino.h>
#include "event_parser.h"
#include "model.h"

template <class Lcd>
class Controller;

template <class Lcd>
class LcdView : public Observer
{
   public:
   LcdView(Lcd& lcd, Model& model) : myLcd(lcd), myModel(model)
   {
      myModel.Attach(this); 
      enabled_ = false;
      myController = MakeController();
   };
   virtual ~LcdView(){myModel.Detach(this); if (myController != nullptr){delete myController;}};
   virtual void Update(){this->Draw();};
   virtual void Draw();
   //virtual void Initialize(){myController = MakeController();};

   // factory function for creating controller, maybe a view wants a special kind of controller
   virtual Controller<Lcd>* MakeController(){return new Controller<Lcd>(this);};

   virtual void SetEnabled(bool enabled);
   bool GetEnable(){return enabled_;}
   Controller<Lcd>* GetController(){return myController;};
   Model& myModel;

   protected:
   Lcd& myLcd;
   Controller<Lcd>* myController = nullptr;
   bool enabled_;
};

template <class Lcd>
void LcdView<Lcd>::Draw()
{
   myLcd.clear();
   myLcd.setCursor(0, 0);
   myLcd.print(String("hej"));
};

template <class Lcd>
void LcdView<Lcd>::SetEnabled(bool enabled)
{
   // if this view wasn't enabled before
   if (enabled && !enabled_)
   {
      myLcd.clear();
   }

   enabled_ = enabled;
   
   if(enabled_)
   {
      Draw();
   }
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
  if(this->enabled_)
  {
   String row1 = String(" x: ");
   String row2 = String(" z: ");

   row1.concat(this->myModel.GetX());
   row2.concat(this->myModel.GetZ());
   
   row1.concat("   "); //add some spaces to avoid doing clear between prints
   row2.concat("   ");

   // indicate the jogged/active axis with a  '*'
   row1.setCharAt(0, this->myModel.GetActiveAxis() == axis_x ? '*' : ' ');
   row2.setCharAt(0, this->myModel.GetActiveAxis() == axis_z ? '*' : ' ');

   this->myLcd.setCursor(0, 0);
   this->myLcd.print(row1);
   this->myLcd.setCursor(0, 1);
   this->myLcd.print(row2);
  }
};

template <class Lcd>
class SpindleView : public LcdView<Lcd> 
{
   public:
   SpindleView(Lcd& lcd, Model& model) : LcdView<Lcd>(lcd, model){};
   void SetEnabled(bool enabled); //override;
   void Draw() override;
};

template <class Lcd>
void SpindleView<Lcd>::SetEnabled(bool enabled)
{ 
   this->enabled_ = enabled;
   if(this->enabled_)
   {
      String row1 = String(" spindle speed:");

      this->myLcd.clear();

      this->myLcd.setCursor(0, 0);
      this->myLcd.print(row1);
  
      Draw();  
   }  
};

template <class Lcd>
void SpindleView<Lcd>::Draw()
{
  if(this->enabled_)
   {
    String row2 = String(" ");
   
    row2.concat(this->myModel.GetSpindleSpeed());
    row2.concat(String(" rpm    "));

    this->myLcd.setCursor(0, 1);
    this->myLcd.print(row2);
   }
};

// not used yet
template <class Lcd>
class Controller : public EventParser
{
   public:
   Controller(LcdView<Lcd>* view) : myView(view)
   {
      myModel = &myView->myModel;
   };
   virtual ~Controller(){};
   void AddEvent(EventFunctor &h){AddAcceptedHandler(h);};

   private:
   Model* myModel;
   LcdView<Lcd>* myView;
};

#endif // __C_LCD_WRITER_H__
