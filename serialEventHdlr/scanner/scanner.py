"""scanner main function"""

import tkinter as tk
import serial
from serial.tools.list_ports import comports

def increase():
    """button press callback"""
    if serial_port.is_open:
        serial_port.write(''.join('dir1_0').encode('utf-8', 'ignore'))
        serial_port.write(''.join('step1_10').encode('utf-8', 'ignore'))
    print('+')

def decrease():
    """button press callback"""
    if serial_port.is_open:
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

    vertical_ctrl_frame = tk.Frame(window, relief=tk.GROOVE, borderwidth=3)
    vertical_ctrl_frame.grid(row=0, column=0, padx=5, pady=5)

    horizontal_ctrl_frame = tk.Frame(window, relief=tk.GROOVE, borderwidth=3)
    horizontal_ctrl_frame.grid(row=0, column=1, padx=5, pady=5, sticky="nw")

    ctrl_frame = tk.Frame(window, relief=tk.GROOVE, borderwidth=3)
    ctrl_frame.grid(row=1, column=0, padx=5, pady=5, sticky="nw")

    cfg_frame = tk.Frame(window, relief=tk.GROOVE, borderwidth=3)
    cfg_frame.grid(row=1, column=1, padx=5, pady=5, sticky="nw")

    tk.Label(vertical_ctrl_frame, text="Vertical control:").grid(row=0, column=0, padx=5, pady=5)

    btn_jog_up = tk.Button(master=vertical_ctrl_frame, text="jog up", padx=5, pady=5, command=increase)
    btn_jog_up.grid(row=1, column=0, padx=5, pady=5, sticky="nw")

    btn_jog_down = tk.Button(master = vertical_ctrl_frame, text="jog down", padx=5, pady=5, command=decrease)
    btn_jog_down.grid(row=2, column=0, padx=5, pady=5, sticky="nw")

    tk.Label(horizontal_ctrl_frame, text="Horizontal control:").grid(row=0, column=0, padx=5, pady=5)

    btn_jog_ccw = tk.Button(master = horizontal_ctrl_frame, text="jog ccw", padx=5, pady=5)
    btn_jog_ccw.grid(row=1, column=0, padx=5, pady=5, sticky="nw")

    btn_jog_cw = tk.Button(master=horizontal_ctrl_frame, text="jog cw", padx=5, pady=5)
    btn_jog_cw.grid(row=1, column=1, padx=5, pady=5, sticky="nw")

    btn_start = tk.Button(master = ctrl_frame, text="Start", padx=5, pady=5)
    btn_start.grid(row=0, column=0, padx=5, pady=5, sticky="n")

    btn_test = tk.Button(master=ctrl_frame, text="Test", padx=5, pady=5)
    btn_test.grid(row=0, column=1, padx=5, pady=5, sticky="n")

    current_port = tk.StringVar()

    if available_ports:
        current_port.set(available_ports[0])
    else:
        current_port.set('N/A')

    tk.Label(cfg_frame, text="File name:").grid(row=0, column=0, padx=5, pady=5)
    tk.Label(cfg_frame, text="Com port:").grid(row=1, column=0, padx=5, pady=5)
    port_option_menu = tk.OptionMenu(master = cfg_frame, variable = current_port, value = current_port.get(), *available_ports, command = set_selected_port)
    port_option_menu.grid(row=1, column=1, padx=5, pady=5, sticky="n")

    if current_port.get() in available_ports:
        open_port(current_port.get())

    window.mainloop()

if __name__ == '__main__':
    main()
