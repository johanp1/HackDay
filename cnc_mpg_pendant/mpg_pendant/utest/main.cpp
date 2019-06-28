#include "buffer.h"

int main(void)
{
   C_Button buttons[NBR_OF_BUTTONS] = { C_Button("rth", 3, 50), C_Button("run", 6, 50), C_Button("est", 8, 50)} ;
   C_RotaryEncoder encoder("jog", 2, 7);
   C_Selector selectors[NBR_OF_SELECTORS] = {C_Selector("sela", A3, 100), C_Selector("sels", A2, 100)};
   C_Sender sender;
   C_Buffer buffer;
}