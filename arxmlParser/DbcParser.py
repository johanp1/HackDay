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
        return 'net_name: ' + self.net_name + '\tframe_name: ' + self.frame_name \
            + '\tsignal name: ' + self.signal_name + '\tsize: ' + str(self.size) \
            + '\tscale: ' + self.scale + '\toffset: ' + self.offset \
            + '\tdirection: ' + self.direction + '\n'

class DbcParser:
    """CAN db parser"""
    def __init__(self):
        self.signal_dict = {}
        self.f_log = open('./logs/can_log.txt', 'w', encoding="utf-8")

    def parse(self, dbc_file, net_name, ecu):
        """Parse input file appending internal dictionary"""
        f_dbc = open(dbc_file, 'r', encoding="utf-8")
        dbc_line = f_dbc.readline()
        frame_name = ''
        while dbc_line:
            # pick out frame
            if dbc_line.startswith('BO_'):
                frame_name = dbc_line.split(' ')[2].strip(':').lower()

                signals_in_frame_array = []
                # pick out each signal in frame
                while dbc_line != '\n':
                    if dbc_line.startswith(' SG_') and '_UB' not in dbc_line:
                        signals_in_frame_array.append(dbc_line)

                    dbc_line = f_dbc.readline()

                if signals_in_frame_array:
                    self._parse_signal_description(signals_in_frame_array, net_name, frame_name, ecu)

            dbc_line = f_dbc.readline()

    def _parse_signal_description(self, sig_array, net_name, frame_name, ecu):
        """pick out size, scale and offset from one line/signal in the dbc-file"""
        for signal in sig_array:
            signal_description_array = signal.split(' ')
            name = signal_description_array[2]
            size = self._find_signal_size(signal_description_array[4])
            scale = self._find_signal_scale(signal_description_array[5])
            offset = self._find_signal_offset(signal_description_array[5])
            direction = 'required' if signal_description_array[-1].strip('\n').find(ecu) != -1 else 'provided'
            self.signal_dict[name] = CANSignal(net_name, frame_name, name, size, scale, offset, direction)
            self.f_log.write('net_name: ' + net_name + '\tframe_name: ' + frame_name + '\tsignal name: ' + name + '\tsize: ' + size + '\tscale: ' + scale + '\toffset: ' + offset + '\tdirection: ' + direction + '\n')

    def _find_signal_scale(self, s):
        scale = s.strip(r'\(').strip(r'\)').split(',')[0]
        return scale

    def _find_signal_offset(self, signal_string):
        offset = signal_string.strip(r'\(').strip(r'\)').split(',')[-1]
        return offset

    def _find_signal_size(self, signal_string):
        pattern = r"\|(.*?)\@"
        substring = re.search(pattern, signal_string).group(1)
        return substring
