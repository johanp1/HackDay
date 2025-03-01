#! /usr/bin/python

class GpIo:
  def __init__(self):
    self.BOARD = 0
    self.IN = 0
    self.OUT = 1

  def setwarnings(self):
    pass

  def setmode(self, board):
    pass

  def setup(self, in_pin, direction):
    pass
  
GPIO = GpIo()