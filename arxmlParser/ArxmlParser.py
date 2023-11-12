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

class CPort(Port):
    """representation of a AUTOSAR-calibration-port"""
    def __repr__(self):
        str_ = super().__repr__()
        for sig in self.signal_array:
            str_ += repr(sig)
        return 'c-port: ' + str_  + '\n'

    def accept(self, visitor):
        visitor.renderCPort(self)


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
        self.cal_array = []
        self.signal_dict = {}
        self.type_dict = {}
        self.appl_type_dict = {}
        self.compu_method_dict = {}
        self._ns = ''

    def parse(self, namespace, swc_arxml, port_arxml, types_arxml):
        """Parse arxml files"""
        ET.register_namespace('', namespace)
        #ET.register_namespace('xsi', 'http://www.w3.org/2001/XMLSchema-instance')

        self._ns = {'default_ns':namespace}
        self._get_r_ports(swc_arxml) #get component's r-ports
        self._get_p_ports(swc_arxml) #get component's p-ports
        self._get_c_ports(swc_arxml) #get component's c-ports
        self._get_signals(port_arxml) #get signal- and type of all sender/receiver port-if's in port_arxml
        self._get_parameter_if(port_arxml) #get type of all c-port-if's in port_arxml
        self._get_impl_types(types_arxml) #get all implementation data types in types_arxml
        self._get_appl_types(types_arxml) #get all application data types in types_arxml
        self._get_compu_methods(types_arxml) #get all "SCALE_LINEAR" compu-methods in types_arxml

        #sender-receiver port mangling:
        for port in self.port_array:
            if port.port_if in self.signal_dict:
                port.signal_name = self.signal_dict[port.port_if].name
                port.type = self.signal_dict[port.port_if].type

                type_key = self.signal_dict[port.port_if].type

                if type_key in self.type_dict:
                    if self.type_dict[type_key][0].element_name != '': #
                        port.signal_array.append(StructSignal(self.signal_dict[port.port_if].name, self.signal_dict[port.port_if].type))
                        for element in self.type_dict[type_key]:
                            port.signal_array[-1].element_array.append(StructSignalElement(element.element_name, element.element_type))
                    else:
                        port.signal_array.append(ValueSignal(self.signal_dict[port.port_if].name, self.signal_dict[port.port_if].type))

                if type_key in self.appl_type_dict:
                    if self.appl_type_dict[type_key][0].element_name != '':
                        port.signal_array.append(StructSignal(self.signal_dict[port.port_if].name, self.signal_dict[port.port_if].type))
                        for element in self.appl_type_dict[type_key]:
                            port.signal_array[-1].element_array.append(StructSignalElement(element.element_name, element.element_type))
                    else:
                        port.signal_array.append(ValueSignal(self.signal_dict[port.port_if].name, self.signal_dict[port.port_if].type))

        #calibration port mangling:
        for port in self.cal_array:
            if port.port_if in self.signal_dict:
                port.signal_name = self.signal_dict[port.port_if].name
                port.type = self.signal_dict[port.port_if].type

                type_key = self.signal_dict[port.port_if].type

                if type_key in self.appl_type_dict:
                    port.signal_array.append(ValueSignal(self.signal_dict[port.port_if].name, self.signal_dict[port.port_if].type))
                    
                    #assign scale and offset from compu-method
                    compu_method_name = self.appl_type_dict[type_key][0].compu
                    if compu_method_name != '':
                        if compu_method_name in self.compu_method_dict:
                            port.signal_array[-1].scale = self.compu_method_dict[compu_method_name].scale
                            port.signal_array[-1].offset = self.compu_method_dict[compu_method_name].offset

    def _get_r_ports(self, swc_arxml):
        tree = ET.parse(swc_arxml)
        root = tree.getroot()
        f_log = open('./logs/rport_log.txt', 'w', encoding="utf-8")

        tag = '{{{}}}{}'.format(self._ns['default_ns'], 'R-PORT-PROTOTYPE')
        for required_port in root.iter(tag):
            name = required_port.find('default_ns:SHORT-NAME', self._ns).text

            if_tref = required_port.find('default_ns:REQUIRED-INTERFACE-TREF', self._ns)
            if if_tref.attrib['DEST'] == 'SENDER-RECEIVER-INTERFACE':
                port_if = if_tref.text.split('/')[-1]
                self.port_array.append(RPort(name, port_if))
                f_log.write('port name: ' + name + ' port-if: ' + port_if + '\n')

        f_log.close()

    def _get_p_ports(self, swc_arxml):

        tree = ET.parse(swc_arxml)
        root = tree.getroot()
        f_log = open('./logs/pport_log.txt', 'w', encoding="utf-8")

        tag = '{{{}}}{}'.format(self._ns['default_ns'], 'P-PORT-PROTOTYPE')
        for provided_port in root.iter(tag):
            name = provided_port.find('default_ns:SHORT-NAME', self._ns).text
            port_if = provided_port.find('default_ns:PROVIDED-INTERFACE-TREF', self._ns).text.split('/')[-1]
            self.port_array.append(PPort(name, port_if))
            f_log.write('port name: ' + name + ' port-if: ' + port_if + '\n')

        f_log.close()

    def _get_c_ports(self, swc_arxml):
        tree = ET.parse(swc_arxml)
        root = tree.getroot()
        f_log = open('./logs/cport_log.txt', 'w', encoding="utf-8")

        tag = '{{{}}}{}'.format(self._ns['default_ns'], 'R-PORT-PROTOTYPE')
        for required_port in root.iter(tag):
            name = required_port.find('default_ns:SHORT-NAME', self._ns).text

            if_tref = required_port.find('default_ns:REQUIRED-INTERFACE-TREF', self._ns)
            if if_tref.attrib['DEST'] == 'PARAMETER-INTERFACE':
                port_if = if_tref.text.split('/')[-1]
                self.cal_array.append(CPort(name, port_if))
                f_log.write('port name: ' + name + ' port-if: ' + port_if + '\n')

        f_log.close()

    def _get_signals(self, port_arxml):
        tree = ET.parse(port_arxml)
        root = tree.getroot()
        f_log = open('./logs/port_type.txt', 'w', encoding="utf-8")

        tag = '{{{}}}{}'.format(self._ns['default_ns'], 'SENDER-RECEIVER-INTERFACE')
        for port_if in root.iter(tag):
            port_if_name = port_if.find('default_ns:SHORT-NAME', self._ns).text # get port_if name
            data_elements = port_if.find('default_ns:DATA-ELEMENTS', self._ns)
            variable_data_prototype = data_elements.find('default_ns:VARIABLE-DATA-PROTOTYPE', self._ns)

            # get port_if name
            signal_name = variable_data_prototype.find('default_ns:SHORT-NAME', self._ns).text 
            signal_type = variable_data_prototype.find('default_ns:TYPE-TREF', self._ns).text.split('/')[-1]

            SignalTuple = namedtuple("Signal", ["name", "type"])
            self.signal_dict[port_if_name] = SignalTuple(signal_name, signal_type)

            f_log.write('port-if: ' + port_if_name + ' signal_name: ' + signal_name + ' signal_type: ' + signal_type + '\n')

        f_log.close()

    def _get_parameter_if(self, port_arxml):
        tree = ET.parse(port_arxml)
        root = tree.getroot()
        f_log = open('./logs/cport_type.txt', 'w', encoding="utf-8")

        tag = '{{{}}}{}'.format(self._ns['default_ns'], 'PARAMETER-INTERFACE')
        for par_if in root.iter(tag):
            par_if_name = par_if.find('default_ns:SHORT-NAME', self._ns).text # get port_if name
            parameters = par_if.find('default_ns:PARAMETERS', self._ns)
            parameter_data_prototype = parameters.find('default_ns:PARAMETER-DATA-PROTOTYPE', self._ns)

            # get port_if name
            prototype_name = parameter_data_prototype.find('default_ns:SHORT-NAME', self._ns).text 
            prototype_type = parameter_data_prototype.find('default_ns:TYPE-TREF', self._ns).text.split('/')[-1]

            ParameterTuple = namedtuple("Parameter", ["name", "type"])
            self.signal_dict[par_if_name] = ParameterTuple(prototype_name, prototype_type)

            f_log.write('port-if: ' + par_if_name + ' prototype_name: ' + prototype_name + ' prototype_type: ' + prototype_type + '\n')

        f_log.close()

    def _get_impl_types(self, types_arxml):
        tree = ET.parse(types_arxml)
        root = tree.getroot()
        f_log = open('./logs/types.txt', 'w', encoding="utf-8")

        tag = '{' + self._ns['default_ns'] + '}' + 'IMPLEMENTATION-DATA-TYPE'
        for data_type in root.iter(tag):
            data_type_name = data_type.find('default_ns:SHORT-NAME', self._ns).text
            data_type_category = data_type.find('default_ns:CATEGORY', self._ns).text # find out if it is a struct data type or a value

            self.type_dict[data_type_name] = []
            Element = namedtuple("Element", ["element_name", "element_type", "compu"])
            self.type_dict[data_type_name].append(Element('', '', ''))
         
            if data_type_category == 'STRUCTURE':
                struct_tag =  '{' + self._ns['default_ns']+ '}' + 'IMPLEMENTATION-DATA-TYPE-ELEMENT'
                
                for struct_data_type in data_type.iter(struct_tag):
                    element_name = struct_data_type.find('default_ns:SHORT-NAME', self._ns).text # get struct element name

                    type_ref_tag =  '{' + self._ns['default_ns']+ '}' + 'IMPLEMENTATION-DATA-TYPE-REF'
                    for data_def_props in struct_data_type.iter(type_ref_tag):
                        element_type = data_def_props.text.split('/')[-1]

                        Element = namedtuple("Element", ["element_name", "element_type", "compu"])
                        self.type_dict[data_type_name].append(Element(element_name, element_type, ''))

                        f_log.write('data_type_name ' + data_type_name + ' element name ' + element_name + ' element_type ' + element_type + '\n')

        f_log.close()

    def _get_appl_types(self, types_arxml):
        tree = ET.parse(types_arxml)
        root = tree.getroot()
        f_log = open('./logs/appl_types.txt', 'w', encoding="utf-8")

        #first pick out the "value" data types
        tag = '{' + self._ns['default_ns'] + '}' + 'APPLICATION-PRIMITIVE-DATA-TYPE'
        for data_type in root.iter(tag):
            data_type_name = data_type.find('default_ns:SHORT-NAME', self._ns).text
            
            self.appl_type_dict[data_type_name] = []

            sw_props = data_type.find('default_ns:SW-DATA-DEF-PROPS', self._ns)
            sw_props_variant = sw_props.find('default_ns:SW-DATA-DEF-PROPS-VARIANTS', self._ns)
            sw_props_conditional = sw_props_variant.find('default_ns:SW-DATA-DEF-PROPS-CONDITIONAL', self._ns)
            
            compu_method = sw_props_conditional.find('default_ns:COMPU-METHOD-REF', self._ns)
            if compu_method is not None:
                compu_method_name = compu_method.text.split('/')[-1]
                Element = namedtuple("Element", ["element_name", "element_type", "compu"])
                
                self.appl_type_dict[data_type_name].append(Element('', '', compu_method_name))
                f_log.write('data_type_name ' + data_type_name + ' compu-method ' + compu_method_name + '\n')

        #pick out the array data types
        tag = '{' + self._ns['default_ns'] + '}' + 'APPLICATION-ARRAY-DATA-TYPE'
        for data_type in root.iter(tag):
            data_type_name = data_type.find('default_ns:SHORT-NAME', self._ns).text

            self.appl_type_dict[data_type_name] = []

            element = data_type.find('default_ns:ELEMENT', self._ns)
            element_name = element.find('default_ns:SHORT-NAME', self._ns).text
            element_type = element.find('default_ns:TYPE-TREF', self._ns).text.split('/')[-1]
            nbr_of_elements = element.find('default_ns:MAX-NUMBER-OF-ELEMENTS', self._ns).text

            Element = namedtuple("Element", ["element_name", "element_type", "compu"])
            self.appl_type_dict[data_type_name].append(Element(element_name, element_type, ''))

            f_log.write('data_type_name ' + data_type_name + ' element name ' + element_name + ' element_type ' + element_type + ' nbr_of_elements ' + nbr_of_elements + '\n')

        #pick out the "struct" data types
        tag = '{' + self._ns['default_ns'] + '}' + 'APPLICATION-RECORD-DATA-TYPE'
        for data_type in root.iter(tag):
            data_type_name = data_type.find('default_ns:SHORT-NAME', self._ns).text

            self.appl_type_dict[data_type_name] = []

            struct_tag =  '{' + self._ns['default_ns']+ '}' + 'APPLICATION-RECORD-ELEMENT'
            for struct_data_type in data_type.iter(struct_tag):
                element_name = struct_data_type.find('default_ns:SHORT-NAME', self._ns).text # get struct element name

                type_ref_tag =  '{' + self._ns['default_ns']+ '}' + 'TYPE-TREF'
                for data_def_props in struct_data_type.iter(type_ref_tag):
                    element_type = data_def_props.text.split('/')[-1]

                    Element = namedtuple("Element", ["element_name", "element_type", "compu"])
                    self.appl_type_dict[data_type_name].append(Element(element_name, element_type, ''))

                    f_log.write('data_type_name ' + data_type_name + ' element name ' + element_name + ' element_type ' + element_type + '\n')

        f_log.close()

    def _get_compu_methods(self, types_arxml):
        tree = ET.parse(types_arxml)
        root = tree.getroot()
        f_log = open('./logs/compu.txt', 'w', encoding="utf-8")

        tag = '{' + self._ns['default_ns'] + '}' + 'COMPU-METHOD'
        for compu_method in root.iter(tag):
            compu_method_category = compu_method.find('default_ns:CATEGORY', self._ns).text
            if compu_method_category == 'SCALE_LINEAR':
                compu_method_name = compu_method.find('default_ns:SHORT-NAME', self._ns).text
                
                compu_internal_to_phys = compu_method.find('default_ns:COMPU-INTERNAL-TO-PHYS', self._ns)
                compu_scales = compu_internal_to_phys.find('default_ns:COMPU-SCALES', self._ns)
                compu_scale = compu_scales.find('default_ns:COMPU-SCALE', self._ns)
                coeffs = compu_scale.find('default_ns:COMPU-RATIONAL-COEFFS', self._ns)
                numerator = coeffs.find('default_ns:COMPU-NUMERATOR', self._ns)
                scale_offset = numerator.findall('default_ns:V', self._ns)
                offset = scale_offset[0].text
                scale = scale_offset[1].text
                #print(compu_method_name + ' ' + scale + ' ' + offset)
                CompuMethod = namedtuple("CompuMethod", ["scale", "offset"])
                self.compu_method_dict[compu_method_name] = CompuMethod(scale, offset)

                f_log.write('compu_method_name ' + compu_method_name + ' scale ' + scale + ' offset ' + offset + '\n')