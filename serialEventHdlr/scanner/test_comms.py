
class TestComms:
    def __init__(self, msg_handler):
        self._msg_handler = msg_handler
    
    def write_message(self, s):
        self._msg_handler(s)

        if s == 'set_vh':
            self._msg_handler('mode_0')

        if s == 'mode_2':
            for angle in range(0, 360, 10):
                self._msg_handler('h_' + str(angle))
            self._msg_handler('mode_1')

    def get_available_ports(self):    # get available ports
        available_ports = ['COM5', 'COM6']
        return available_ports
    
    def set_port(self, selected_port):
        print('setting port ' + selected_port)