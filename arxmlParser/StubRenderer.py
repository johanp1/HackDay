import ArxmlParser
from collections import namedtuple

class StubRenderer:
   def __init__(self, module, ldc, swc):
      f_template = open('template/template.h', 'r')
      self.f_header = open(module + '.h', 'w')
      self.f_source = open(module + '.c', 'w')

      # copy template to header file
      for l in f_template:
         if '@file' in l:
            self.f_header.write(l.replace('_', module + '.h', 1))
         elif '__C_module_H__' in l:
            self.f_header.write(l.replace('module', module.upper(), 1))
         elif 'swc' in l:
            self.f_header.write(l.replace('swc', swc, 1))
         elif 'ldc' in l:
            self.f_header.write(l.replace('ldc', ldc, 1))            
         else:
            self.f_header.write(l)

      f_template.close()

      s = '#include \"Rte_' + swc + '.h\"\n'
      s += '#include <CUnit/CUnit.h>\n\n'
      self.f_header.write(s)

      #add include statement to source
      s = '#define DISABLE_RTE_PTR2ARRAYBASETYPE_PASSING\n\n'
      s += '#include \"' + module + '.h\"\n\n'
      self.f_source.write(s)

   def __del__(self):
      self.f_header.write('#endif\n')
      self.f_header.close()

      self.f_source.close()

   def render(self, arxml_parser):
      self._write_stub_signal_struct(arxml_parser.port_array)
      self._write_stub_signals(arxml_parser.port_array)
      self._write_stub_set_signals(arxml_parser.port_array)
      self._write_stub_check_signals(arxml_parser.port_array, arxml_parser.type_dict)

   def _write_stub_signal_struct(self, port_array):
      s = 'typedef struct\n{'
      self.f_header.write(s)

      for port in port_array:
         s = '\tstruct\n'
         s += '\t{\n'
         s += '\t\t' + port.type + ' ' + 'par;\n'
         s += '\t\t' + 'Std_ReturnType ret;\n'
         s += '\t}' + ' ' + 'Rte_' + port.port_name + '_' + port.signal_name + ';\n\n'

         self.f_header.write(s)
      
      s += '} StubSignals_Type;\n\n'
      s += 'extern StubSignals_Type p;\n\n'
      self.f_header.write(s)

      s = 'StubSignals_Type p;\n\n'
      self.f_source.write(s)
   
   def _write_stub_signals(self, port_array):
      for port in port_array:
         port_signal = port.port_name + '_' + port.signal_name
         if port.direction == 'required':
            s = 'Std_ReturnType Rte_Read_' + port_signal + '(' + port.type + '* par)\n'
            s += '{\n'
            s += '\t*par = p.Rte_' + port_signal + '.par;\n'
            s += '\treturn p.Rte_' + port_signal + '.ret;\n'
            s += '}\n\n'
         if port.direction == 'provided':
            ptr_to_struct = ' const*' if port.is_struct_type == True else ''
            dereference_ptr = '*' if port.is_struct_type == True else ''
            s = 'Std_ReturnType Rte_Write_' + port_signal + '(' + port.type + ptr_to_struct + ' par)\n'
            s += '{\n'
            s += '\tp.Rte_' + port_signal + '.par = ' + dereference_ptr + 'par;\n'
            s += '\treturn p.Rte_' + port_signal + '.ret;\n'
            s += '}\n\n'
         self.f_source.write(s)

   def _write_stub_set_signals(self, port_array):
      for port in port_array:
         if port.direction == 'required':
            port_signal = port.port_name + '_' + port.signal_name
            function_prototype = 'void stubs_set_' + port_signal + '(' +  port.type + ' par)'

            s = function_prototype + '\n'
            s += '{\n'
            s += '\tp.Rte_' + port_signal + '.par = par;\n'
            s += '}\n\n'

            self.f_source.write(s)
            self.f_header.write(function_prototype + ';\n')
            
   def _write_stub_check_signals(self, port_array, type_dict):
      for port in port_array:
         if port.direction == 'provided':
            ptr_to_struct = '*' if port.is_struct_type == True else ''
            port_signal = port.port_name + '_' + port.signal_name
            function_define = '#define stubs_check_' + port_signal + '(expected) _stubs_check_' + port_signal + '(expected, __FILE__, __FUNCTION__, __LINE__);'
            function_prototype = 'void _stubs_check_' + port_signal + '(' +  port.type + ptr_to_struct + ' expected, const char *file, const char *function, const int line)'
 
            s = function_prototype + '\n'
            s += '{\n'
            if type_dict[port.type]:
               for element in type_dict[port.type]:
                  s += '\tif (p.Rte_' + port_signal + '.par.' + element.element_name + ' != expected->' + element.element_name + ')\n'
                  s += '\t{\n'
                  s += '\t\tprintf(\"%s in %s on line: %d, ' + element.element_name + ': expected %d but was %d\\n\", file, function, line, expected->' + element.element_name + ', p.Rte_' + port_signal + '.par.' + element.element_name + ');\n'
                  s += '\t}\n'
                  s += '\tCU_ASSERT_TRUE_FATAL(p.Rte_' + port_signal + '.par.' + element.element_name + ' == expected->' + element.element_name + ');\n'
            else:
               s += '\tif (p.Rte_' + port_signal + '.par != expected)\n'
               s += '\t{\n'
               s += '\t\tprintf(\"%s in %s on line: %d, ' + port_signal + ': expected %d but was %d\\n\", file, function, line, expected, p.Rte_' + port_signal + '.par);\n'
               s += '\t}\n'
               s += '\tCU_ASSERT_TRUE_FATAL(p.Rte_' + port_signal + '.par == expected);\n'

            s += '}\n\n'

            self.f_source.write(s)
            self.f_header.write(function_define + '\n' + function_prototype + ';\n\n')
