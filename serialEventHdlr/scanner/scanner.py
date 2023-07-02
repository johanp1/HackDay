"""scanner main function"""

import threading
import time
import tkinter as tk
import serial
from serial.tools.list_ports import comports

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

        self.daemon=True

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

    def horizontal_jog_ccw(self):
        self._comm_hdlr.write_message('hor_-10')

    def horizontal_jog_cw(self):
        self._comm_hdlr.write_message('hor_10')

    def vertical_jog_up(self):
        self._comm_hdlr.write_message('ver_10')

    def vertical_jog_down(self):
        self._comm_hdlr.write_message('ver_-10')

    def set_selected_port(self, selected_port):
        print(selected_port)
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
        self._model.set_scanner_running(True)

    def test(self):
        self._comm_hdlr.write_message('mode_1')
        self._model.set_test_running(True)

    def stop(self):
        self._comm_hdlr.write_message('mode_0')
        self._model.set_scanner_running(False)
        self._model.set_test_running(False)
        
class Model:
    def __init__(self, available_ports):
        self._available_ports = available_ports
        self._observers = []
        self._test_runnig = False
        self._scanner_runnig = False

    def attatch(self, o):
        self._observers.append(o)
        
    def notify(self):
        for o in self._observers:
            o.update()

    def get_available_ports(self):
        return self._available_ports
    
    def set_test_running(self, is_runnig):
        if self._test_runnig != is_runnig:
            self._test_runnig = is_runnig
            self.notify()

    def set_scanner_running(self, is_runnig):
        if self._scanner_runnig != is_runnig:
            self._scanner_runnig = is_runnig
            self.notify()

class View:
    def __init__(self, model, comm_hdlr):
        self._model = model
        self._controller = Controller(comm_hdlr, model)
        self._model.attatch(self)

        self.window = tk.Tk()
        self.current_port = tk.StringVar()

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
        btn_start = tk.Button(master = ctrl_frame, text="Start", padx=5, pady=5, command=self._controller.start)
        btn_start.grid(row=0, column=0, padx=5, pady=5, sticky="n")

        btn_test = tk.Button(master=ctrl_frame, text="Test", padx=5, pady=5, command=self._controller.test)
        btn_test.grid(row=0, column=1, padx=5, pady=5, sticky="n")

        # config frame content
        available_ports = model.get_available_ports()
        if available_ports:
            self.current_port.set(available_ports[0])
        else:
            self.current_port.set('N/A')

        tk.Label(cfg_frame, text="File name:").grid(row=0, column=0, padx=5, pady=5)
        tk.Label(cfg_frame, text="Com port:").grid(row=1, column=0, padx=5, pady=5)
        port_option_menu = tk.OptionMenu(master = cfg_frame, variable = self.current_port, value = self.current_port.get(), command = self._controller.set_selected_port)
        port_option_menu.values = available_ports
        port_option_menu.grid(row=1, column=1, padx=5, pady=5, sticky="n")

    def start(self):
        self.window.mainloop()

    def update(self):
        print("update")

def message_handler(message):
    print(message)

def main():
    """main function"""
    comms = Comms(message_handler)
    model = Model(comms.get_available_ports())
    view = View(model, comms)

    view.start()



if __name__ == '__main__':
    main()
