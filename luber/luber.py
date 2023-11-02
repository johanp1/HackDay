#! /usr/bin/python

import sys
import getopt
import xml.etree.ElementTree as ET
import hal
import time
from collections import namedtuple

class Pin:
    """ Representation of a Pin and it's data"""
    def __init__(self, type, dir):
        self.val = 0    # current value of pin, e.g. 1 - on, 0 - off
        self.type = type  # type (string read from xml)
        self.dir = dir

    def __repr__(self):
        return 'val: ' + str(self.val) + '\ttype: ' + self.type + '\tdir: ' + self.dir

class HalAdapter:
    def __init__(self, name):
        self.h = hal.component(name) 
        self.h.newpin('x-vel', hal.HAL_FLOAT, hal.HAL_IN)
        self.h.newpin('y-vel', hal.HAL_FLOAT, hal.HAL_IN)
        self.h.newpin('z-vel', hal.HAL_FLOAT, hal.HAL_IN)
        self.h.newpin('lube-level-ok',hal.HAL_BIT, hal.HAL_IN)
        self.h.newpin('reset', hal.HAL_BIT, hal.HAL_IN)
        self.h.newpin('lube-ext-req', hal.HAL_BIT, hal.HAL_IN)
        self.h.newpin('lube-cmd', hal.HAL_BIT, hal.HAL_OUT)
        self.h.newpin('lube-level-alarm', hal.HAL_BIT, hal.HAL_OUT)
        self.h.newpin('accumulated-distance', hal.HAL_FLOAT, hal.HAL_OUT)
        self.h.ready()

    def __repr__(self):
        tmp_str = ''
        return tmp_str

    def is_lube_level_ok(self):
        return self.h['lube-level-ok']

    def is_reset(self):
        return self.h['reset']

    def is_lube_ext_req(self):
        return self.h['lube-ext-req']

    def get_velocities(self):
        velocities = namedtuple("velocities", ["x", "y", "z"])
        return velocities(
            self.h['x-vel'],
            self.h['y-vel'],
            self.h['z-vel'])

    def set_lube_on(self,  request):
        if request >= 1:
            self.h['lube-cmd'] = 1
        else:
            self.h['lube-cmd'] = 0

    def set_lube_level_alarm(self, level_ok):
        if level_ok >= 1:
            self.h['lube-level-alarm'] = 1
        else:
            self.h['lube-level-alarm'] = 0

    def set_accumulated_distance(self, d):
        self.h['accumulated-distance'] = d

class ParameterContainer:
    def __init__(self, xml_file):
        self.param_dict = {}
        self._xml_file = xml_file

        self.tree = ET.parse(self._xml_file)
        self._parse()

    def _parse(self):
        root = self.tree.getroot()
        for param in root.iter('parameter'):
            #print param.attrib['name'], param.attrib['value'] 
            self.param_dict[param.attrib['name']] = float(param.attrib['value'])

    def get_param(self, name):
        if name in self.param_dict:
            return self.param_dict[name]
        else:
            return None 

    def get_params(self):
        return self.param_dict

    def write_to_file(self):
        for key, value in self.param_dict.items():
            self._write_to_tree(key, value)

        self.tree.write(self._xml_file)

    def write_param(self, parName, value):
        if parName in self.param_dict:
            self.param_dict[parName] = value

    def _write_to_tree(self, parName, value):   
        """update parameter in xml-tree"""
        root = self.tree.getroot()
      
        for param in root.iter('parameter'):
            if param.attrib['name'] == parName:
                param.attrib['value'] = str(round(value, 2))
                break


class LubeControl:
    def __init__(self, lube_on_time, accumulated_distance, distance_threshold, number_of_lubings):
        self.lube_on_time = lube_on_time                 # [sec]
        self.total_distance = accumulated_distance       # [mm]
        self.distance_threshold = distance_threshold     # [mm]
        self.number_of_lubings = number_of_lubings

        self.state = 'OFF'
        self.lube_level_ok = True

        self.prev_time = time.time()
        self.timeout = self.prev_time

    def calc_dist_from_vel(self, v_x, v_y, v_z):
        current_time = time.time()
        time_delta = current_time - self.prev_time

        self.total_distance += abs(v_x) * time_delta
        self.total_distance += abs(v_y) * time_delta
        self.total_distance += abs(v_z) * time_delta

        self.prev_time = current_time

    def run_state_machine(self, ext_req):
        current_time = time.time()
        if self._transition_to_state_on(ext_req):
            self.state = 'ON'
            self.timeout = self.lube_on_time + current_time
            self.total_distance = 0
            self.number_of_lubings += 1

        if self._transition_to_state_off(current_time):
            self.state = 'OFF'

    def set_lube_level_ok(self, level_ok):
        self.lube_level_ok = level_ok

    def reset(self):
        self.total_distance = 0
        self.state = 'OFF'
        self.lube_level_ok = True

    def _transition_to_state_on(self, ext_req):
        return self.state == 'OFF' \
                and self.lube_level_ok \
                and (self.total_distance >= self.distance_threshold or ext_req == True)

    def _transition_to_state_off(self, current_time):
        return self.state == 'ON' \
                and (current_time > self.timeout or not self.lube_level_ok)

def _usage():
    """ print command line options """
    print("usage luber.py -h -c<name> <path/>in_file.xml\n"\
        "in_file         # input xml-file describing what knobs and/or button are on the pendant\n"\
        "-c <name>       # name of component in HAL. 'my-luber' default\n"\
        "-h              # Help test")

def main():
    xml_file = 'luber.xml'
    #xmlFile = ''
    name = 'my-luber'       # default name of component in HAL

    try:
        opts, args = getopt.getopt(sys.argv[1:], "hc:", ["input="])
    except getopt.GetoptError as err:
        # print help information and exit:
        print(err) # will print something like "option -a not recognized"
        sys.exit(2)

    for o, a in opts:
        if o == "-h":
            _usage()
            sys.exit()
        elif o == "-c":
            name = a
        elif o == "--input":
            xml_file = a
        else:
            assert False, "unhandled option"

    if xml_file == '':
        if len(sys.argv) < 2:
            _usage()
            sys.exit(2)
        else:
            xml_file = sys.argv[-1]

    p = ParameterContainer(xml_file)

    h = HalAdapter(name)

    lube_ctrl = LubeControl(p.get_param('lubePulseTime'),\
                            p.get_param('totalDistance'),\
                            p.get_param('distanceThreshold'),\
                            p.get_param('numberOfLubings'))

    try:
        while 1:
            if h.is_reset():
                lube_ctrl.reset()

            v = h.get_velocities()
            lube_ctrl.calc_dist_from_vel(v.x, v.y, v.z)
            lube_ctrl.set_lube_level_ok(h.is_lube_level_ok())
            lube_ctrl.run_state_machine(h.is_lube_ext_req())

            h.set_lube_on(lube_ctrl.state == 'ON')
            h.set_lube_level_alarm(lube_ctrl.lube_level_ok)
            h.set_accumulated_distance(lube_ctrl.total_distance)

            time.sleep(0.1)

    except KeyboardInterrupt:
        p.write_param('totalDistance', lube_ctrl.total_distance)
        p.write_param('numberOfLubings', lube_ctrl.number_of_lubings)
        p.write_to_file()
        raise SystemExit

if __name__ == '__main__':
    main()
