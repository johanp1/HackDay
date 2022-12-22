import xml.etree.ElementTree as ET
from collections import namedtuple

class Port:
    """representation of a AUTOSAR-port"""
    def __init__(self, port_name, port_if):
        self.port_name = port_name
        self.port_if = port_if
        self.signal_array = []
        self.stubbed = True

    def __repr__(self):
        return 'port name: ' + self.port_name + ', port if: ' + self.port_if + '\n'

    def accept(self, visitor):
        """to be overriden by child class"""

class PPort(Port):
    """representation of a provided AUTOSAR-port"""
    def __repr__(self):
        str_ = super().__repr__()
        for sig in self.signal_array:
            str_ += repr(sig)
        return 'p-port: ' + str_ + '\n'

    def accept(self, visitor):
        visitor.renderPPort(self)

class RPort(Port):
    """representation of a required AUTOSAR-port"""
    def __repr__(self):
        str_ = super().__repr__()
        for sig in self.signal_array:
            str_ += repr(sig)
        return 'r-port: ' + str_  + '\n'

    def accept(self, visitor):
        visitor.renderRPort(self)

class Signal:
    """representation of a generic AUTOSAR-signal"""
    def __init__(self, name_, type_):
        self.name = name_
        self.type = type_

    def __repr__(self):
        return 'Signal name: ' + self.name + ' type: ' + self.type

    def accept(self, visitor):
        """visitor method, to be overridden by child class"""

class ValueSignal(Signal):
    """representation of a AUTOSAR-value-signal"""
    def __init__(self, signal_name, signal_type, scale = '1', offset = '0'):
        super().__init__(signal_name, signal_type)
        self.scale = scale
        self.offset = offset

    def __repr__(self):
        super_repr = super().__repr__()
        return '\tValueSignal ' + super_repr + ' scale: ' + self.scale + ' offset: ' + self.offset + '\n'

    def accept(self, visitor):
        """visitor method"""
        visitor.renderValueSignal(self)

class StructSignal(Signal):
    """representation of a AUTOSAR-struct-signal"""
    def __init__(self, signal_name, signal_type):
        super().__init__(signal_name, signal_type)
        self.element_array = []

    def __repr__(self):
        my_repr = super().__repr__() + '\n'
        for element in self.element_array:
            my_repr += repr(element)
        return '\tStructSignal ' + my_repr

    def accept(self, visitor):
        """visitor method"""
        visitor.renderStructSignal(self)

class StructSignalElement:
    """this might be the same as ValueSignal"""
    def __init__(self, signal_name, signal_type, scale = '1', offset = '0'):
        self.name = signal_name
        self.type = signal_type
        self.scale = scale
        self.offset = offset

    def __repr__(self):
        return '\t\tStructSignalElement name: ' + self.name + ' type: ' + self.type \
         + ' scale: ' + self.scale + ' offset: ' + self.offset + '\n'

    def accept(self, visitor):
        """visitor method"""
        visitor.renderStructElement(self)

class ArxmlParser:
    """ArxmlParser"""
    def __init__(self):
        self.port_array = []
        self.signal_dict = {}
        self.type_dict = {}

    def parse(self, namespace, swc_arxml, port_arxml, types_arxml):
        """Parse arxml files"""
        self._get_r_ports(namespace, swc_arxml)
        self._get_p_ports(namespace, swc_arxml)
        self._get_signals(namespace, port_arxml)
        self._get_impl_types(namespace, types_arxml)
        self._get_appl_types(namespace, types_arxml)

        for port in self.port_array:
            if port.port_if in self.signal_dict:
                port.signal_name = self.signal_dict[port.port_if].name
                port.type = self.signal_dict[port.port_if].type

                type_key = self.signal_dict[port.port_if].type
                try:
                    if self.type_dict[type_key]:
                        port.signal_array.append(StructSignal(self.signal_dict[port.port_if].name, self.signal_dict[port.port_if].type))
                        for element in self.type_dict[type_key]:
                            port.signal_array[-1].element_array.append(StructSignalElement(element.element_name, element.element_type))
                    else:
                        port.signal_array.append(ValueSignal(self.signal_dict[port.port_if].name, self.signal_dict[port.port_if].type))
                except KeyError:
                    print("type: " + type_key + " not found in type_dict")

    def _get_r_ports(self, namespace, swc_arxml):
        tree = ET.parse(swc_arxml)
        root = tree.getroot()
        ns = {'default_ns':namespace}
        f_log = open('./logs/rport_log.txt', 'w', encoding="utf-8")

        tag = '{' + ns['default_ns']+ '}' + 'R-PORT-PROTOTYPE'
        for required_port in root.iter(tag):
            name = required_port.find('default_ns:SHORT-NAME', ns).text

            if_tref = required_port.find('default_ns:REQUIRED-INTERFACE-TREF', ns)
            if if_tref.attrib['DEST'] == 'SENDER-RECEIVER-INTERFACE':
                port_if = if_tref.text.split('/')[-1]
                self.port_array.append(RPort(name, port_if))
                f_log.write('port name: ' + name + ' port-if: ' + port_if + '\n')

        f_log.close()

    def _get_p_ports(self, namespace, swc_arxml):

        tree = ET.parse(swc_arxml)
        root = tree.getroot()
        ns = {'default_ns':namespace}
        f_log = open('./logs/pport_log.txt', 'w', encoding="utf-8")

        tag = '{' + ns['default_ns']+ '}' + 'P-PORT-PROTOTYPE'
        for provided_port in root.iter(tag):
            name = provided_port.find('default_ns:SHORT-NAME', ns).text
            port_if = provided_port.find('default_ns:PROVIDED-INTERFACE-TREF', ns).text.split('/')[-1]
            self.port_array.append(PPort(name, port_if))
            f_log.write('port name: ' + name + ' port-if: ' + port_if + '\n')

        f_log.close()

    def _get_signals(self, namespace, port_arxml):
        tree = ET.parse(port_arxml)
        root = tree.getroot()
        ns = {'default_ns':namespace}
        f_log = open('./logs/port_type.txt', 'w', encoding="utf-8")

        tag = '{' + ns['default_ns']+ '}' + 'SENDER-RECEIVER-INTERFACE'
        for port_if in root.iter(tag):
            port_if_name = port_if.find('default_ns:SHORT-NAME', ns).text # get port_if name
            data_elements = port_if.find('default_ns:DATA-ELEMENTS', ns)
            variable_data_prototype = data_elements.find('default_ns:VARIABLE-DATA-PROTOTYPE', ns)

            # get port_if name
            signal_name = variable_data_prototype.find('default_ns:SHORT-NAME', ns).text 
            signal_type = variable_data_prototype.find('default_ns:TYPE-TREF', ns).text.split('/')[-1]

            SignalTuple = namedtuple("Signal", ["name", "type"])
            self.signal_dict[port_if_name] = SignalTuple(signal_name, signal_type)

            f_log.write('port-if: ' + port_if_name + ' signal_name: ' + signal_name + ' signal_type: ' + signal_type + '\n')

        f_log.close()

    def _get_impl_types(self, namespace, types_arxml):
        tree = ET.parse(types_arxml)
        root = tree.getroot()
        ns = {'default_ns':namespace}
        f_log = open('./logs/types.txt', 'w', encoding="utf-8")

        tag = '{' + ns['default_ns']+ '}' + 'IMPLEMENTATION-DATA-TYPE'
        for data_type in root.iter(tag):
            data_type_name = data_type.find('default_ns:SHORT-NAME', ns).text
            data_type_category = data_type.find('default_ns:CATEGORY', ns).text # find out if it is a struct data type or a value

            self.type_dict[data_type_name] = []
         
            if data_type_category == 'STRUCTURE':
                struct_tag =  '{' + ns['default_ns']+ '}' + 'IMPLEMENTATION-DATA-TYPE-ELEMENT'
                for struct_data_type in data_type.iter(struct_tag):
                    element_name = struct_data_type.find('default_ns:SHORT-NAME', ns).text # get struct element name

                    type_ref_tag =  '{' + ns['default_ns']+ '}' + 'IMPLEMENTATION-DATA-TYPE-REF'
                    for data_def_props in struct_data_type.iter(type_ref_tag):
                        element_type = data_def_props.text.split('/')[-1]

                        Element = namedtuple("Element", ["element_name", "element_type"])
                        self.type_dict[data_type_name].append(Element(element_name, element_type))      

                        f_log.write('data_type_name ' + data_type_name + ' element name ' + element_name + ' element_type ' + element_type + '\n')

        f_log.close()

    def _get_appl_types(self, namespace, types_arxml):
        tree = ET.parse(types_arxml)
        root = tree.getroot()
        ns = {'default_ns':namespace}
        f_log = open('./logs/appl_types.txt', 'w', encoding="utf-8")

        #first pick out the "value" data types
        tag = '{' + ns['default_ns']+ '}' + 'APPLICATION-PRIMITIVE-DATA-TYPE'
        for data_type in root.iter(tag):
            data_type_name = data_type.find('default_ns:SHORT-NAME', ns).text

            self.type_dict[data_type_name] = []

        #pick out the "struct" data types
        tag = '{' + ns['default_ns']+ '}' + 'APPLICATION-RECORD-DATA-TYPE'
        for data_type in root.iter(tag):
            data_type_name = data_type.find('default_ns:SHORT-NAME', ns).text

            self.type_dict[data_type_name] = []

            struct_tag =  '{' + ns['default_ns']+ '}' + 'APPLICATION-RECORD-ELEMENT'
            for struct_data_type in data_type.iter(struct_tag):
                element_name = struct_data_type.find('default_ns:SHORT-NAME', ns).text # get struct element name

                type_ref_tag =  '{' + ns['default_ns']+ '}' + 'TYPE-TREF'
                for data_def_props in struct_data_type.iter(type_ref_tag):
                    element_type = data_def_props.text.split('/')[-1]

                    Element = namedtuple("Element", ["element_name", "element_type"])
                    self.type_dict[data_type_name].append(Element(element_name, element_type))      

                    f_log.write('data_type_name ' + data_type_name + ' element name ' + element_name + ' element_type ' + element_type + '\n')

        f_log.close()
