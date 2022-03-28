import xml.etree.ElementTree as ET
from collections import namedtuple

class Port:
   """representation of a AUTOSAR-port"""
   def __init__(self, port_name, port_if, direction, signal_name = '', type = '', scale = '1', offset = '0', is_struct_type = False, comment = ''):
      self.port_name = port_name
      self.port_if = port_if
      self.signal_name = signal_name
      self.type = type
      self.scale = scale
      self.offset = offset
      self.direction = direction
      self.is_struct_type = is_struct_type
      self.comment = comment
      self.signal_array = []
        
   def __repr__(self):
      return 'port name: ' + self.port_name + '\tport if: ' + self.port_if + '\tsignal name: ' + self.signal_name + '\tdirection: ' + self.direction + '\ttype: ' + self.type +  '\tis_struct_type: ' + str(self.is_struct_type) + '\n'

   def accept(self, v):
      pass

class PPort(Port):
   def __init__(self, port_name, port_if, dummy = ''):
      super().__init__(port_name, port_if, 'provided')

   def accept(self, v):
      v.renderPPort(self)

class RPort(Port):
   def __init__(self, port_name, port_if, dummy = ''):
      super().__init__(port_name, port_if, 'required')

   def accept(self, v):
      v.renderRPort(self)

class Signal:
   def __init__(self, name, type):
       self.name = name
       self.type = type

   def accept(self, v):
      pass

class ValueSignal(Signal):
   def __init__(self, name, type, scale = '1', offset = '0'):
       super().__init__(name, type)
       self.scale = scale
       self.offset = offset

   def accept(self, v):
      v.renderValueSignal(self)

class StructSignal(Signal):
   def __init__(self, name, type):
       self.name = name
       self.type = type
       self.element_array = []

   def accept(self, v):
      v.renderStructSignal(self)

"""this might be the same as ValueSignal"""
class StructSignalElement:
   def __init__(self, name, type, scale = '1', offset = '0'):
       self.name = name
       self.type = type
       self.scale = scale
       self.offset = offset
       
   def accept(self, v):
      v.renderStructElement(self)

class ArxmlParser:
   def __init__(self):
      self.port_array = []
      self.signal_dict = {}
      self.type_dict = {}

   def parse(self, namespace, swc_arxml, port_arxml, types_arxml):
      self._getRPorts(namespace, swc_arxml)
      self._getPPorts(namespace, swc_arxml)
      self._getSignals(namespace, port_arxml)
      self._getTypes(namespace, types_arxml)

      for port in self.port_array:
         if port.port_if in self.signal_dict:
            if self.type_dict[port.type]:
               port.signal_array.append(StructSignal(self.signal_dict[port.port_if].name, self.signal_dict[port.port_if].type))
            else:
               port.signal_array.append(ValueSignal(self.signal_dict[port.port_if].name, self.signal_dict[port.port_if].type))
               
            port.signal_name = self.signal_dict[port.port_if].name
            port.type = self.signal_dict[port.port_if].type
            port.is_struct_type = True if self.type_dict[port.type] else False

   def _getRPorts(self, namespace, swc_arxml):
      tree = ET.parse(swc_arxml)
      root = tree.getroot()
      ns = {'default_ns':namespace}
      #f_log = open('./logs/rport_log.txt', 'w')

      tag = '{' + ns['default_ns']+ '}' + 'R-PORT-PROTOTYPE'
      for required_port in root.iter(tag):
         name = required_port.find('default_ns:SHORT-NAME', ns).text

         if_tref = required_port.find('default_ns:REQUIRED-INTERFACE-TREF', ns)
         if if_tref.attrib['DEST'] == 'SENDER-RECEIVER-INTERFACE':
            port_if = if_tref.text.split('/')[-1]
            self.port_array.append(RPort(name, port_if, 'required'))
            #f_log.write('port name: ' + name + ' port-if: ' + port_if + '\n')

      #f_log.close()

   def _getPPorts(self, namespace, swc_arxml):

      tree = ET.parse(swc_arxml)
      root = tree.getroot()
      ns = {'default_ns':namespace}
      #f_log = open('./logs/pport_log.txt', 'w')

      tag = '{' + ns['default_ns']+ '}' + 'P-PORT-PROTOTYPE'
      for provided_port in root.iter(tag):
         name = provided_port.find('default_ns:SHORT-NAME', ns).text
         port_if = provided_port.find('default_ns:PROVIDED-INTERFACE-TREF', ns).text.split('/')[-1]
         self.port_array.append(PPort(name, port_if, 'provided'))
         #f_log.write('port name: ' + name + ' port-if: ' + port_if + '\n')

      #f_log.close()

   def _getSignals(self, namespace, port_arxml):
      tree = ET.parse(port_arxml)
      root = tree.getroot()
      ns = {'default_ns':namespace}
      f_log = open('./logs/port_type.txt', 'w')

      tag = '{' + ns['default_ns']+ '}' + 'SENDER-RECEIVER-INTERFACE'
      for port_if in root.iter(tag):
         port_if_name = port_if.find('default_ns:SHORT-NAME', ns).text # get port_if name
         data_elements = port_if.find('default_ns:DATA-ELEMENTS', ns)
         variable_data_prototype = data_elements.find('default_ns:VARIABLE-DATA-PROTOTYPE', ns)
         signal_name = variable_data_prototype.find('default_ns:SHORT-NAME', ns).text # get port_if name
         signal_type = variable_data_prototype.find('default_ns:TYPE-TREF', ns).text.split('/')[-1]

         Signal = namedtuple("Signal", ["name", "type"])
         self.signal_dict[port_if_name] = Signal(signal_name, signal_type)
         
         f_log.write('port-if: ' + port_if_name + ' signal_name: ' + signal_name + ' signal_type: ' + signal_type + '\n')

      f_log.close()   

   def _getTypes(self, namespace, types_arxml):
      tree = ET.parse(types_arxml)
      root = tree.getroot()
      ns = {'default_ns':namespace}
      f_log = open('./logs/types.txt', 'w')

      tag = '{' + ns['default_ns']+ '}' + 'IMPLEMENTATION-DATA-TYPE'
      for data_type in root.iter(tag):
         data_type_name = data_type.find('default_ns:SHORT-NAME', ns).text
         data_type_category = data_type.find('default_ns:CATEGORY', ns).text # find out if it is a struct data type or a value
         
         #self.type_dict[data_type_name] = True if data_type_category == 'STRUCTURE' else False
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