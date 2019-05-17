#!/usr/bin/python
import hal
import time
import serial
import getopt

def updatePin(str):
   """parses incomming cmd and update Pin data value accordingly
   input: command string, formated as: '<event>_<number>\n' 
   output: nothing.
   """
   val = 0
   cmd = str.split('_')
   if len(cmd) == 2:
      if is_number(cmd[1]):
         val = int(cmd[1]) 
      
   return val

def is_number(s):
    try:
        int(s)
        return True
    except ValueError:
        return False


try:
  opts, args = getopt.getopt(sys.argv[1:], "hp:d:c:", ["input=", "port=", "debug="])
except getopt.GetoptError as err:
  # print help information and exit:
  print(err) # will print something like "option -a not recognized"
  sys.exit(2)

### parse input command line
for o, a in opts:
  if o == "-h":
    usage()
    sys.exit()
  if o == "-c":
    name = a
  elif o == "--input":
    xml_file = a
  elif o in ("-p", "--port"):
    port = a
  elif o in ("-d", "--debug"):
   debug = a
  else:
    print o
    assert False, "unhandled option"
   
if xml_file == '':
   if len(sys.argv) < 2:
      usage()
      sys.exit(2)
   else:
      xml_file = sys.argv[-1]
   
if name == '':
   name = 'test' # default name


h = hal.component(name)

h.newpin("in", hal.HAL_FLOAT, hal.HAL_IN)
h.newpin("out", hal.HAL_FLOAT, hal.HAL_OUT)

h.ready()


### open serial port
# list available ports with 'python -m serial.tools.list_ports'
ser = serial.Serial()
ser.port = '/dev/ttyACM0'
ser.baudrate = 9600
ser.parity = 'N'
ser.bytesize = 8
ser.stopbits = 1
ser.xonxoff = False       # disable software flow control
#ser.rtscts = False       # disable hardware (RTS/CTS) flow control
#ser.dsrdtr = False       # disable hardware (DSR/DTR) flow control
#ser.writeTimeout = 2     # timeout for write
ser.timeout = 1           # 1 sec timeout

try:
   ser.open()
except serial.SerialException as e:
   print 'could not open srial port ' + ser.port 
   raise SystemExit

out_val = 0
try:
   while 1:
      while ser.in_waiting:
            b = ser.read_until() #blocks until '\n' received or timeout
            out_val = updatePin(b.decode('utf-8'))
            #print b
      h['out'] = out_val
      time.sleep(0.1)
 
except KeyboardInterrupt:
   raise SystemExit
