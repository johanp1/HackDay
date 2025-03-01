class Encoder:
  def __init__(self):
    self.pos = 0

  def update(self):
    self.pos = 1

#void RotaryEncoder::update(void) 
#{
#   digitalRead(dtPin) ? position++ : position--;
#   generateEvent((unsigned int)position);
#}