"""scanner main function"""
import sys
import getopt
from datetime import datetime
import threading
import time
import tkinter as tk
import serial
from serial.tools.list_ports import comports
import test_comms

class Comms(threading.Thread):
    """rs232 port"""

    def __init__(self, msg_handler):
        threading.Thread.__init__(self)
        self.serial = serial.Serial()
        self.serial.baudrate = 9600
        self.serial.parity = 'N'
        self.serial.bytesize = 8
        self.serial.stopbits = 1
        self.serial.xonxoff = False       # disable software flow control
        self.serial.timeout = 0.05
        self.msg_hdlr = msg_handler

        self.daemon = True

        self.ports = self.get_available_ports()
        if self.ports:
            self.serial.port = self.ports[0]
            self.open()  #open the com-port

        self.start()  # start the thread

    def run(self):
        while True:
            if self.data_ready():
                self.read_messages()

            time.sleep(0.05)

    def get_available_ports(self):    # get available ports
        available_ports = []
        for port in comports():
            available_ports.append(port.device)
        #print(available_ports)
        return available_ports

    def open(self):
        try:
            self.serial.open()
            #print 'comms::opening port'
            print(self.serial)
        except serial.SerialException:
            print('unable to open port...')

    def close(self):
        self.serial.close()
        #print 'comms::closing port'

    def data_ready(self):
        if self.is_open():
            return self.serial.in_waiting     
        else:
            return False

    def read_messages(self):
        """reads serial port"""
        while self.data_ready():
            msg_str = self._read().strip('\n')
            self.msg_hdlr(msg_str)

    def write_message(self, s):
        self._write(s + '\n')

    def is_open(self):
        return self.serial.is_open

    def set_port(self, port):
        self.close()

        try:
            self.serial.port = port
        except serial.SerialException:
            print('unable to change port...')

        self.open()

    def _write(self, s):
        if self.is_open() == True:
            #serial expects a byte-array and not a string
            self.serial.write(''.join(s).encode('utf-8', 'ignore'))

    def _read(self):
        """ returns string read from serial port """
        b = ''
        if self.is_open() is True:
            b = self.serial.read_until() #blocks until '\n' received or timeout

        return b.decode('utf-8', 'ignore')        #convert byte array to string

class Controller:
    def __init__(self, comm_hdlr, model):
        self._comm_hdlr = comm_hdlr
        self._model = model
        self._model.attatch(self)

    def horizontal_jog_ccw(self):
        self._comm_hdlr.write_message('hor_-10')

    def horizontal_jog_cw(self):
        self._comm_hdlr.write_message('hor_10')

    def vertical_jog_up(self):
        self._comm_hdlr.write_message('ver_10')

    def vertical_jog_down(self):
        self._comm_hdlr.write_message('ver_-10')

    def set_selected_port(self, selected_port):
        self._comm_hdlr.set_port(selected_port)

    def vertical_start(self):
        self._comm_hdlr.write_message('vs')

    def vertical_end(self):
        self._comm_hdlr.write_message('ve')

    def horizontal_start(self):
        self._comm_hdlr.write_message('hs')

    def horizontal_end(self):
        self._comm_hdlr.write_message('he')

    def start(self):
        self._comm_hdlr.write_message('mode_2')

    def test(self):
        self._comm_hdlr.write_message('mode_1')

    def stop(self):
        self._comm_hdlr.write_message('mode_0')

    def update(self):
        pass

    def handle_mode_event(self, mode):
        """gets serialized data from event brooker"""
        try:
            self._model.set_scanner_mode(int(mode))
        except ValueError:
            pass
        
        
class Model:
    def __init__(self, available_ports):
        self._available_ports = available_ports
        self._observers = []
        self._mode = 0
        self._file_name = 'apa.txt'

    def attatch(self, o):
        self._observers.append(o)
        
    def notify(self):
        for o in self._observers:
            o.update()

    def get_available_ports(self):
        return self._available_ports
    
    def set_scanner_mode(self, mode):
        if self._mode != mode:
            self._mode = mode
            self.notify()

    def get_scanner_mode(self):
        return self._mode

    def set_file_name(self, file_name):
        self._file_name = file_name

    def get_file_name(self):
        return self._file_name

class View:
    def __init__(self, model, comm_hdlr):
        self._model = model
        self._controller = Controller(comm_hdlr, model)
        self._model.attatch(self)

        self.window = tk.Tk()
        self.current_port = tk.StringVar()
        self._file_name=tk.StringVar()
        self._file_name.set(model.get_file_name())

        #the top level frames
        vertical_ctrl_frame = tk.Frame(self.window, relief=tk.GROOVE, borderwidth=3)
        vertical_ctrl_frame.grid(row=0, column=0, padx=5, pady=5)

        horizontal_ctrl_frame = tk.Frame(self.window, relief=tk.GROOVE, borderwidth=3)
        horizontal_ctrl_frame.grid(row=0, column=1, padx=5, pady=5, sticky="nw")

        ctrl_frame = tk.Frame(self.window, relief=tk.GROOVE, borderwidth=3)
        ctrl_frame.grid(row=1, column=0, padx=5, pady=5, sticky="nw")

        cfg_frame = tk.Frame(self.window, relief=tk.GROOVE, borderwidth=3)
        cfg_frame.grid(row=1, column=1, padx=5, pady=5, sticky="nw")

        # Vertical control frame content
        tk.Label(vertical_ctrl_frame, text="Vertical control:").grid(row=0, column=0, padx=5, pady=5)

        btn_jog_up = tk.Button(master=vertical_ctrl_frame, text="jog up", padx=5, pady=5, command=self._controller.vertical_jog_up)
        btn_jog_up.grid(row=1, column=0, padx=5, pady=5, sticky="nw")

        btn_jog_down = tk.Button(master = vertical_ctrl_frame, text="jog down", padx=5, pady=5, command=self._controller.vertical_jog_down)
        btn_jog_down.grid(row=2, column=0, padx=5, pady=5, sticky="nw")

        btn_set_upper = tk.Button(master=vertical_ctrl_frame, text="upper limit", padx=5, pady=5, command=self._controller.vertical_start)
        btn_set_upper.grid(row=1, column=1, padx=5, pady=5, sticky='nw')

        btn_set_lower = tk.Button(master = vertical_ctrl_frame, text="set lower limit", padx=5, pady=5, command=self._controller.vertical_end)
        btn_set_lower.grid(row=2, column=1, padx=5, pady=5, sticky="nw")

        # horizontal control frame content
        tk.Label(horizontal_ctrl_frame, text="Horizontal control:").grid(row=0, column=0, padx=5, pady=5)

        btn_jog_ccw = tk.Button(master = horizontal_ctrl_frame, text="jog ccw", padx=5, pady=5, command=self._controller.horizontal_jog_ccw)
        btn_jog_ccw.grid(row=1, column=0, padx=5, pady=5, sticky="nw")

        btn_jog_cw = tk.Button(master=horizontal_ctrl_frame, text="jog cw", padx=5, pady=5, command=self._controller.horizontal_jog_cw)
        btn_jog_cw.grid(row=1, column=1, padx=5, pady=5, sticky="nw")

        btn_jog_ccw = tk.Button(master = horizontal_ctrl_frame, text="set as start ", padx=5, pady=5, command=self._controller.horizontal_start)
        btn_jog_ccw.grid(row=2, column=0, padx=5, pady=5, sticky="nw")

        btn_jog_cw = tk.Button(master=horizontal_ctrl_frame, text="set as end", padx=5, pady=5, command=self._controller.horizontal_end)
        btn_jog_cw.grid(row=2, column=1, padx=5, pady=5, sticky="nw")

        # horizontal control frame content
        self.btn_start = tk.Button(master = ctrl_frame, text="Start", padx=5, pady=5, command=self._controller.start)
        self.btn_start.grid(row=0, column=0, padx=5, pady=5, sticky="n")

        self.btn_test = tk.Button(master=ctrl_frame, text="Test", padx=5, pady=5, command=self._controller.test)
        self.btn_test.grid(row=0, column=1, padx=5, pady=5, sticky="n")

        # config frame content
        available_ports = model.get_available_ports()
        if not available_ports:
            available_ports.append('N/A')
        self.current_port.set(available_ports[0])

        vcmd = (cfg_frame.register(self.validate), '%P')
        tk.Label(cfg_frame, text="File name:").grid(row=0, column=0, padx=5, pady=5)
        self.filename_entry = tk.Entry(cfg_frame, textvariable=self._file_name, validatecommand=vcmd, validate='key').grid(row=0, column=1, padx=5, pady=5)

        tk.Label(cfg_frame, text="Com port:").grid(row=1, column=0, padx=5, pady=5)
        port_option_menu = tk.OptionMenu(cfg_frame, self.current_port, available_ports[0], *available_ports, command = self._controller.set_selected_port)
        port_option_menu.grid(row=1, column=1, padx=5, pady=5, sticky="n")

    def validate(self, file_name):
        self._model.set_file_name(file_name)
        return True

    def update(self):
        if self._model.get_scanner_mode() == 0:
            self.btn_start.config(text="Start", command=self._controller.start, state="normal")
            self.btn_test.config(text="Test", command=self._controller.test, state="normal")
        if self._model.get_scanner_mode() == 1: #test mode
            self.btn_start.config(state="disabled")
            self.btn_test.config(text="Stop", command=self._controller.stop, state="normal")
        if self._model.get_scanner_mode() == 2: #scanning mode
            self.btn_start.config(text = "Stop", command=self._controller.stop, state="normal")
            self.btn_test.config(state = "disabled")

    def start(self):
        self.window.mainloop()


class MessageBroker:
   def __init__(self):
      self.brokee_dict = {}

   def attach_handler(self, event_name, handler):
      self.brokee_dict[event_name] = handler

   def message_handler(self, message):
        print(message)
        de_serialized_message = message.split('_')
        event_name = de_serialized_message[0]
        event_data = de_serialized_message[1:]
        if event_name in self.brokee_dict:  
            try:          
                self.brokee_dict[event_name](*event_data)
            except TypeError:
                pass
                #print('unable to invoke handler, too manny args supplied')


class OutputFileHandler:
    def __init__(self, model):
        self._model = model
        self._model.attatch(self)

    def print_scan(self, angle):
        if not self.f_log.closed:
            self.f_log.write(angle + '\n')

    def update(self):
        if self._model.get_scanner_mode() == 1:
            self.f_log = open(self._model.get_file_name(), 'a', encoding="utf-8")
            dt_string = datetime.now().strftime("%Y-%m-%d %H:%M:%S")
            self.f_log.write('start scanning ' + dt_string + '\n')

        if self._model.get_scanner_mode() == 0:
            dt_string = datetime.now().strftime("%Y-%m-%d %H:%M:%S")
            self.f_log.write('scanning done ' + dt_string + '\n')
            self.f_log.close()

def main():
    use_test_comms = False

    try:
        opts, args = getopt.getopt(sys.argv[1:], "t", ["test"])
    except getopt.GetoptError as err:
        # print help information and exit:
        print(err) # will print
    
    for o, a in opts:
        if o in ("-t", "--test"):
            use_test_comms = True

    message_broker = MessageBroker()

    if use_test_comms == True:
        comms = test_comms.TestComms(message_broker.message_handler)
    else:
        comms = Comms(message_broker.message_handler)
 
    model = Model(comms.get_available_ports())
    view = View(model, comms)
    output_file_handler = OutputFileHandler(model)

    message_broker.attach_handler('mode', view._controller.handle_mode_event)
    message_broker.attach_handler('h', output_file_handler.print_scan)

    view.start()

if __name__ == '__main__':
    main()
