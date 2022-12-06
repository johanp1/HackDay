import re

class CANSignal:
   """representation of a CAN signal"""
   def __init__(self, net_name, frame_name, signal_name, size, scale, offset, direction):
      self.net_name = net_name
      self.frame_name = frame_name
      self.signal_name = signal_name
      self.size = size
      self.scale = scale
      self.offset = offset
      self.direction = direction
        
   def __repr__(self):
      return 'net_name: ' + self.net_name + '\tframe_name: ' + self.frame_name + '\tsignal name: ' + self.signal_name + '\tsize: ' + str(self.size) + '\tscale: ' + self.scale + '\toffset: ' + self.offset + '\tdirection: ' + self.direction + '\n'

class DbcParser:
   def __init__(self):
      self.signal_dict = {}
      self.f_log = open('./logs/can_log.txt', 'w')

   def parse(self, dbc_file, net_name, ecu):
      f_dbc = open(dbc_file, 'r')
      l = f_dbc.readline()
      frame_name = ''
      while l:
         # pick out frame
         if l.startswith('BO_'):
            frame_name = l.split(' ')[2].strip(':').lower()

            signals_in_frame_array = []
            # pick out each signal in frame
            while l != '\n':
               if l.startswith(' SG_') and '_UB' not in l:
                  signals_in_frame_array.append(l)
               l = f_dbc.readline()

            if signals_in_frame_array:
               self._parseSignalDescription(signals_in_frame_array, net_name, frame_name, ecu)
            
         l = f_dbc.readline()

   def _parseSignalDescription(self, sig_array, net_name, frame_name, ecu):
      """pick out size, scale and offset from one line/signal in the dbc-file"""
      for signal in sig_array:
         signal_description_array = signal.split(' ')
         name = signal_description_array[2]
         size = self._findSignalSize(signal_description_array[4])
         scale = self._findSignalScale(signal_description_array[5])
         offset = self._findSignalOffset(signal_description_array[5])
         direction = 'required' if signal_description_array[-1].strip('\n').find(ecu) != -1 else 'provided'
         self.signal_dict[name] = CANSignal(net_name, frame_name, name, size, scale, offset, direction)
         self.f_log.write('net_name: ' + net_name + '\tframe_name: ' + frame_name + '\tsignal name: ' + name + '\tsize: ' + size + '\tscale: ' + scale + '\toffset: ' + offset + '\tdirection: ' + direction + '\n')

   def _dbc2signalsInFrame(self, fHandle, frame):
      """get all lines/signals contained in <frame>.
      frames are separated with a blank line in the dbc-file"""
      sigDescr = fHandle.readline()
      while sigDescr != '\n':
         self._parseSignalDescription(sigDescr, frame)
        
      sigDescr = fHandle.readline()

   def _findSignalScale(self, s):
      scale = s.strip('\(').strip('\)').split(',')[0]
      return scale

   def _findSignalOffset(self, s):
      offset = s.strip('\(').strip('\)').split(',')[-1]
      return offset

   def _findSignalSize(self, s):
      pattern = "\|(.*?)\@"
      substring = re.search(pattern, s).group(1)
      return substring
