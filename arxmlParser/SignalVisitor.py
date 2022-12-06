from ArxmlParser import RPort, PPort, ValueSignal, StructSignal, StructSignalElement
from DbcParser import CANSignal

# trying to extract scale and offset of signals from parsed can-db.
# if port-name exists in can-db, the port is considered "not stubbed"
class SignalVisitor:
   def __init__(self, signal_dict):
      self.signal_dict = signal_dict

   def renderPPort(self, port):
      for sig_key in self.signal_dict:
         if sig_key.startswith(port.port_name) and self.signal_dict[sig_key].direction == 'provided':  # should probably be signal group, not port name
            port.stubbed = False

      for signal in port.signal_array:
         signal.accept(self)

   def renderRPort(self, port):
      for sig_key in self.signal_dict:
         if sig_key.startswith(port.port_name) and self.signal_dict[sig_key].direction == 'required':  # should probably be signal group, not port name
            port.stubbed = False

      for signal in port.signal_array:
         signal.accept(self)

   def renderValueSignal(self, signal):
      for sig_key in self.signal_dict:
         if sig_key.startswith(signal.name):  # this might not be the best way of picking out a signal from the DB
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


