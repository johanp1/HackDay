from ArxmlParser import RPort, PPort, ValueSignal, StructSignal, StructSignalElement
from DbcParser import CANSignal

class SignalVisitor:
   def __init__(self, signal_dict):
      self.signal_dict = signal_dict

   def renderPPort(self, port):
      for signal in port.signal_array:
         signal.accept(self)

   def renderRPort(self, port):
      for signal in port.signal_array:
         signal.accept(self)

   def renderValueSignal(self, signal):
      for sig_key in self.signal_dict:
         if sig_key.startswith(signal.name):
            signal.scale = self.signal_dict[sig_key].scale
            signal.offset = self.signal_dict[sig_key].offset
      
   def renderStructSignal(self, signal):
      for element in signal.element_array:
         element.accept(self)

   def renderStructElement(self, element):
      for sig_key in self.signal_dict:
         if sig_key.startswith(element.name):
            element.scale = self.signal_dict[sig_key].scale
            element.offset = self.signal_dict[sig_key].offset


