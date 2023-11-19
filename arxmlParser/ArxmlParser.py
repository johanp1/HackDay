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
        return 'Signal name: ' + self.name + ' type: ' + repr(self.type)

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

        for element_name, element_type in signal_type.element_dict.items():
            self.element_array.append(StructSignalElement(element_name, element_type))

    def __repr__(self):
        #my_repr = super().__repr__() + '\n'
        my_repr = 'Signal name: ' + self.name + ' type: ' + self.type.name + '\n'
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
        return '\t\tStructSignalElement name: ' + self.name + ' type: ' + repr(self.type) \
         + ' scale: ' + self.scale + ' offset: ' + self.offset + '\n'

    def accept(self, visitor):
        """visitor method"""
        visitor.renderStructElement(self)

class ArraySignal(Signal):
    """representation of a AUTOSAR-array-signal"""
    def __init__(self, name, type_, scale = '1', offset = '0'):
        super().__init__(name, type_)
        self.scale = scale
        self.offset = offset

    def __repr__(self):
        my_repr = super().__repr__() + '\n'
        my_repr += repr(self.type)
        my_repr += ' scale: ' + self.scale + ' offset: ' + self.offset + '\n'
        return '\tArraySignal ' + my_repr

    def accept(self, visitor):
        """visitor method"""
        visitor.renderArraySignal(self)

class Type:
    """representation of a generic AUTOSAR-type"""
    def __init__(self, name_):
        self.name = name_

    def __repr__(self):
        return self.name

    def create_signal(self, signal_name):
        """factory method, to be overridden by child class"""

class ValueType(Type):
    """representation of a AUTOSAR-value-type"""
    def __init__(self, name, compu_method = None):
        super().__init__(name)
        self.compu_method = compu_method

    def __repr__(self):
        super_repr = super().__repr__()
        compu_method_str = '' if self.compu_method is None else ' compu_method: ' + repr(self.compu_method)
        return '\tValueType ' + super_repr + compu_method_str + '\n'

    def create_signal(self, signal_name):
        """factory method for value signal"""
        return ValueSignal(signal_name, self)

class ArrayType(Type):
    """representation of a AUTOSAR-array-type"""
    def __init__(self, name, size, element_type):
        super().__init__(name)
        self.size = size
        self.element_type = element_type

    def __repr__(self):
        super_repr = super().__repr__()
        return '\tArrayType ' + super_repr + ' size: ' + self.size + ' element type: '\
            + repr(self.element_type) + '\n'

    def create_signal(self, signal_name):
        """factory method for array signal"""
        return ArraySignal(signal_name, self)

class StructType(Type):
    """representation of a AUTOSAR-struct-type"""
    def __init__(self, name):
        super().__init__(name)
        self.element_dict = {}

    def __repr__(self):
        my_repr = super().__repr__() + '\n'
        for key, element in self.element_dict.items():
            my_repr += '\t element name: ' + key + repr(element)
        return '\tStructSignal ' + my_repr

    def add_element(self, name, type_):
        """add struct element"""
        self.element_dict[name] = type_

    def create_signal(self, signal_name):
        """factory method for value signal"""
        return StructSignal(signal_name, self)

class CompuMethod:
    """representation of scale-linear compu-method"""
    def __init__(self, name, scale = '1', offset = '0'):
        self.name = name
        self.scale = scale
        self.offset = offset

    def __repr__(self):
        return '\t\tCompu.method name: ' + self.name\
         + ' scale: ' + self.scale + ' offset: ' + self.offset + '\n'

class ArxmlParser:
    """ArxmlParser"""
    def __init__(self):
        self.port_array = []
        self.cal_array = []
        self.signal_dict = {}
        self.type_array = []
        self.appl_type_array = []
        self.compu_method_dict = {}
        self.mapping_dict = {}
        self._ns = ''

    def parse(self, namespace, swc_arxml, port_arxml, types_arxml):
        """Parse arxml files"""
        ET.register_namespace('', namespace)
        #ET.register_namespace('xsi', 'http://www.w3.org/2001/XMLSchema-instance')

        self._ns = {'default_ns':namespace}
        self._get_r_ports(swc_arxml) #get component's r-ports
        self._get_p_ports(swc_arxml) #get component's p-ports
        self._get_c_ports(swc_arxml) #get component's c-ports
        self._get_compu_methods(types_arxml) #get all "SCALE_LINEAR" compu-methods in types_arxml
        self._get_impl_types(types_arxml) #get all implementation data types in types_arxml
        self._get_appl_types(types_arxml) #get all application data types in types_arxml
        self._get_type_mapping(types_arxml) #get impl<->appl type mapping

        self._get_signals(port_arxml) #get signal- and type of all sender/receiver port-if's in port_arxml
        self._get_parameter_if(port_arxml) #get type of all c-port-if's in port_arxml

        self._assign_scaling()

        #substitute appl-type for impl-type and add scaling
        self._substitute_appl_types()

        #sender-receiver port mangling:
        for port in self.port_array:
            if port.port_if in self.signal_dict:
                port.signal_array.append(self.signal_dict[port.port_if])

        #calibration port mangling:
        for port in self.cal_array:
            if port.port_if in self.signal_dict:
                port.signal_array.append(self.signal_dict[port.port_if])
        #print(self.port_array)

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

            for t in self.type_array:
                if signal_type == t.name:
                    self.signal_dict[port_if_name] = t.create_signal(signal_name)

            for t in self.appl_type_array:
                if signal_type == t.name:
                    self.signal_dict[port_if_name] = t.create_signal(signal_name)

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

            for t in self.type_array:
                if prototype_type == t.name:
                    self.signal_dict[par_if_name] = t.create_signal(prototype_name)

            for t in self.appl_type_array:
                if prototype_type == t.name:
                    self.signal_dict[par_if_name] = t.create_signal(prototype_name)

            f_log.write('port-if: ' + par_if_name + ' prototype_name: ' + prototype_name + ' prototype_type: ' + prototype_type + '\n')

        f_log.close()

    def _get_impl_types(self, types_arxml):
        tree = ET.parse(types_arxml)
        root = tree.getroot()
        f_log = open('./logs/types.txt', 'w', encoding="utf-8")

        #first, find all value types
        tag = '{' + self._ns['default_ns'] + '}' + 'IMPLEMENTATION-DATA-TYPE'
        for data_type in root.iter(tag):
            data_type_name = data_type.find('default_ns:SHORT-NAME', self._ns).text
            data_type_category = data_type.find('default_ns:CATEGORY', self._ns).text # find out if it is a struct data type or a value

            if data_type_category == 'VALUE' or data_type_category == 'TYPE_REFERENCE':
                self.type_array.append(ValueType(data_type_name))

                f_log.write('value_data_type_name ' + data_type_name + '\n')

        #find all struct types
        #this has to be done in steps in order to support nested structs
        #find all struct types
        struct_array = []
        tag = '{' + self._ns['default_ns'] + '}' + 'IMPLEMENTATION-DATA-TYPE'
        for data_type in root.iter(tag):
            data_type_name = data_type.find('default_ns:SHORT-NAME', self._ns).text
            data_type_category = data_type.find('default_ns:CATEGORY', self._ns).text # find out if it is a struct data type or a value

            if data_type_category == 'STRUCTURE':
                struct_array.append(StructType(data_type_name))

        #then populate the struct elements
        for struct_type in struct_array:
            tag = '{' + self._ns['default_ns'] + '}' + 'IMPLEMENTATION-DATA-TYPE'
            for data_type in root.iter(tag):
                data_type_name = data_type.find('default_ns:SHORT-NAME', self._ns).text
                data_type_category = data_type.find('default_ns:CATEGORY', self._ns).text # find out if it is a struct data type or a value

                if data_type_category == 'STRUCTURE' and struct_type.name == data_type_name:
                    #find all the elements
                    struct_tag =  '{' + self._ns['default_ns']+ '}' + 'IMPLEMENTATION-DATA-TYPE-ELEMENT'
                    for struct_data_type in data_type.iter(struct_tag):
                        element_name = struct_data_type.find('default_ns:SHORT-NAME', self._ns).text # get struct element name

                        type_ref_tag =  '{' + self._ns['default_ns']+ '}' + 'IMPLEMENTATION-DATA-TYPE-REF'
                        for data_def_props in struct_data_type.iter(type_ref_tag):
                            element_type = data_def_props.text.split('/')[-1]

                            found = False
                            for t in self.type_array:
                                if element_type == t.name:
                                    found = True
                                    struct_type.add_element(element_name, t)
                                    break

                            if found:
                                f_log.write('struct_data_type_name ' + data_type_name + ' element name ' + element_name + ' element_type ' + element_type + '\n')
                                self.type_array.append(struct_type)
                            else:
                                print(element_type + ' not found')
                                
        #find all array types
        tag = '{' + self._ns['default_ns'] + '}' + 'IMPLEMENTATION-DATA-TYPE'
        for data_type in root.iter(tag):
            data_type_name = data_type.find('default_ns:SHORT-NAME', self._ns).text
            data_type_category = data_type.find('default_ns:CATEGORY', self._ns).text # find out if it is a struct data type or a value

            if data_type_category == 'ARRAY':
                elements = data_type.find('default_ns:SUB-ELEMENTS', self._ns)
                element = elements.find('default_ns:IMPLEMENTATION-DATA-TYPE-ELEMENT', self._ns)
                array_size = element.find('default_ns:ARRAY-SIZE', self._ns).text

                props = element.find('default_ns:SW-DATA-DEF-PROPS', self._ns)
                variants = props.find('default_ns:SW-DATA-DEF-PROPS-VARIANTS', self._ns)
                conditional = variants.find('default_ns:SW-DATA-DEF-PROPS-CONDITIONAL', self._ns)
                element_type = conditional.find('default_ns:IMPLEMENTATION-DATA-TYPE-REF', self._ns).text.split('/')[-1]

                found = False
                for t in self.type_array:
                    if element_type == t.name:
                        found = True
                        self.type_array.append(ArrayType(data_type_name, array_size, t))
                        break

                if found:
                    f_log.write('array_data_type_name ' + data_type_name + ' array size: ' + array_size + ' element_type ' + element_type + '\n')
                else:
                    print(element_type + ' not found')


        f_log.close()

    def _get_appl_types(self, types_arxml):
        tree = ET.parse(types_arxml)
        root = tree.getroot()
        f_log = open('./logs/appl_types.txt', 'w', encoding="utf-8")

        #first pick out the "value" data types
        tag = '{' + self._ns['default_ns'] + '}' + 'APPLICATION-PRIMITIVE-DATA-TYPE'
        for data_type in root.iter(tag):
            data_type_name = data_type.find('default_ns:SHORT-NAME', self._ns).text

            sw_props = data_type.find('default_ns:SW-DATA-DEF-PROPS', self._ns)
            sw_props_variant = sw_props.find('default_ns:SW-DATA-DEF-PROPS-VARIANTS', self._ns)
            sw_props_conditional = sw_props_variant.find('default_ns:SW-DATA-DEF-PROPS-CONDITIONAL', self._ns)
            
            compu_method = sw_props_conditional.find('default_ns:COMPU-METHOD-REF', self._ns)
            if compu_method is not None:
                compu_method_name = compu_method.text.split('/')[-1]
                if compu_method_name in self.compu_method_dict:
                    self.appl_type_array.append(ValueType(data_type_name, self.compu_method_dict[compu_method_name]))
                    f_log.write('value_data_type_name ' + data_type_name + ' compu-method ' + compu_method_name + '\n')
                else:
                    print('could not add type: ' + data_type_name + ', compum-method: ' + compu_method_name + ' not found')
            else:
                self.appl_type_array.append(ValueType(data_type_name))
                f_log.write('value_data_type_name ' + data_type_name)

        #pick out the array data types
        tag = '{' + self._ns['default_ns'] + '}' + 'APPLICATION-ARRAY-DATA-TYPE'
        for data_type in root.iter(tag):
            data_type_name = data_type.find('default_ns:SHORT-NAME', self._ns).text

            element = data_type.find('default_ns:ELEMENT', self._ns)
            element_name = element.find('default_ns:SHORT-NAME', self._ns).text
            element_type = element.find('default_ns:TYPE-TREF', self._ns).text.split('/')[-1]
            nbr_of_elements = element.find('default_ns:MAX-NUMBER-OF-ELEMENTS', self._ns).text


            found = False
            for t in self.appl_type_array:
                if element_type == t.name:
                    found = True
                    self.appl_type_array.append(ArrayType(data_type_name, nbr_of_elements, t))
                    break

            if found:
                f_log.write('array_data_type_name ' + data_type_name + ' array size: ' + nbr_of_elements + ' element_type ' + element_type + '\n')
            else:
                print(element_type + ' not found')

        #pick out the "struct" data types
        struct_array = []
        tag = '{' + self._ns['default_ns'] + '}' + 'APPLICATION-RECORD-DATA-TYPE'
        for data_type in root.iter(tag):
            data_type_name = data_type.find('default_ns:SHORT-NAME', self._ns).text
            struct_array.append(StructType(data_type_name))

        for struct_type in struct_array:
            tag = '{' + self._ns['default_ns'] + '}' + 'APPLICATION-RECORD-DATA-TYPE'
            for data_type in root.iter(tag):
                data_type_name = data_type.find('default_ns:SHORT-NAME', self._ns).text
                
                struct_tag =  '{' + self._ns['default_ns']+ '}' + 'APPLICATION-RECORD-ELEMENT'
                for struct_data_type in data_type.iter(struct_tag):
                    element_name = struct_data_type.find('default_ns:SHORT-NAME', self._ns).text # get struct element name

                    type_ref_tag =  '{' + self._ns['default_ns']+ '}' + 'TYPE-TREF'
                    for data_def_props in struct_data_type.iter(type_ref_tag):
                        element_type = data_def_props.text.split('/')[-1]
                        
                        found = False
                        for t in self.appl_type_array:
                            if element_type == t.name:
                                found = True
                                struct_type.add_element(element_name, t)
                                break

                        if found:
                            f_log.write('struct_data_type_name ' + data_type_name + ' element name ' + element_name + ' element_type ' + element_type + '\n')
                            self.appl_type_array.append(struct_type)
                        else:
                            print(element_type + ' not found')

        f_log.close()

    def _get_compu_methods(self, types_arxml):
        """ creates dictionary with SCALE_LINEAR compu methods, dict-key is the compu-method name"""
        tree = ET.parse(types_arxml)
        root = tree.getroot()
        f_log = open('./logs/compu.txt', 'w', encoding="utf-8")

        tag = '{' + self._ns['default_ns'] + '}' + 'COMPU-METHOD'
        for compu_method in root.iter(tag):
            compu_method_name = compu_method.find('default_ns:SHORT-NAME', self._ns).text
            compu_method_category = compu_method.find('default_ns:CATEGORY', self._ns).text

            if compu_method_category == 'SCALE_LINEAR':
                
                compu_internal_to_phys = compu_method.find('default_ns:COMPU-INTERNAL-TO-PHYS', self._ns)
                compu_scales = compu_internal_to_phys.find('default_ns:COMPU-SCALES', self._ns)
                compu_scale = compu_scales.find('default_ns:COMPU-SCALE', self._ns)
                coeffs = compu_scale.find('default_ns:COMPU-RATIONAL-COEFFS', self._ns)
                numerator = coeffs.find('default_ns:COMPU-NUMERATOR', self._ns)
                scale_offset = numerator.findall('default_ns:V', self._ns)
                offset = scale_offset[0].text
                scale = scale_offset[1].text
                                
                self.compu_method_dict[compu_method_name] = CompuMethod(compu_method_name, scale, offset)
                f_log.write('compu_method_name ' + compu_method_name + ' scale ' + scale + ' offset ' + offset + '\n')
            else:
                self.compu_method_dict[compu_method_name] = CompuMethod(compu_method_name)
                f_log.write('compu_method_name ' + compu_method_name)


    def _get_type_mapping(self, types_arxml):
        """ creates dictionary with application-type to implementation-type mappings"""
        tree = ET.parse(types_arxml)
        root = tree.getroot()
        f_log = open('./logs/mapping.txt', 'w', encoding="utf-8")

        tag = '{' + self._ns['default_ns'] + '}' + 'DATA-TYPE-MAP'
        for type_map in root.iter(tag):
            appl_type = type_map.find('default_ns:APPLICATION-DATA-TYPE-REF', self._ns).text.split('/')[-1]
            impl_type = type_map.find('default_ns:IMPLEMENTATION-DATA-TYPE-REF', self._ns).text.split('/')[-1]
            self.mapping_dict[appl_type] = impl_type

            f_log.write('appl_type: ' + appl_type + ' maps to impl_type: ' + impl_type + '\n')

    def _assign_scaling(self):
        pass #for key, value in self.signal_dict.items():


    def _substitute_appl_types(self):
        pass
