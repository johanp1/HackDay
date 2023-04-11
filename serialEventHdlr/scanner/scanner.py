"""scanner main function"""

import tkinter as tk
import serial
from serial.tools.list_ports import comports

def increase():
    """button press callback"""
    serial_port.write(''.join('dir1_0').encode('utf-8', 'ignore'))
    serial_port.write(''.join('step1_10').encode('utf-8', 'ignore'))
    print('+')

def decrease():
    """button press callback"""
    serial_port.write(''.join('dir1_1').encode('utf-8', 'ignore'))
    serial_port.write(''.join('step1_10').encode('utf-8', 'ignore'))
    print('-')

def open_port(selected_port):
    """helper for opening com-port"""
    serial_port.port = selected_port
    serial_port.baudrate = 9600
    serial_port.parity = 'N'
    serial_port.bytesize = 8
    serial_port.stopbits = 1
    serial_port.xonxoff = False       # disable software flow control
    serial_port.timeout = 0.05

    try:
        serial_port.open()
        print('opening port')
    except serial.SerialException:
        print('unable to open port...')

    print(serial_port)

def set_selected_port(selected_port):
    """callback for optinMenu change event"""
    #print(selected_port)
    try:
        serial_port.port = selected_port
    except serial.SerialException:
        print('unable to change port...')

    print(serial_port)

serial_port = serial.Serial()

def main():
    """main function"""
    # get available ports
    available_ports = []
    for port in comports():
        available_ports.append(port.device)
    print(available_ports)

    window = tk.Tk()

    window.rowconfigure([0, 1], minsize=50, weight=1)
    window.columnconfigure([0, 1], minsize=50, weight=1)

    btn_decrease = tk.Button(master=window, text="jog-", command=decrease)
    btn_decrease.grid(row=0, column=0, sticky="nsew")

    btn_increase = tk.Button(master=window, text="jog+", command=increase)
    btn_increase.grid(row=0, column=1, sticky="nsew")

    current_port = tk.StringVar()
    current_port.set(available_ports[0])
    port_option_menu = tk.OptionMenu(window, current_port, *available_ports, command = set_selected_port)
    port_option_menu.grid(row=1, column=0, sticky="nsew")

    open_port(current_port.get())

    window.mainloop()

if __name__ == '__main__':
    main()
