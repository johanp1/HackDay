#import ArxmlParser
from collections import namedtuple
from ArxmlParser import Port

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

      self.signal_struct_elements = ''
      self.stub_signals = ''
      self.stub_set_functions = ''
      self.stub_set_function_prototypes = ''
      self.stub_check_functions = ''
      self.stub_check_function_prototypes = ''

   def __del__(self):
      self._write_stub_signal_struct()   
      self._write_stub_signals()
      self._write_stub_set_signals()
      self._write_stub_check_signals()

      self.f_header.write('#endif\n')
      self.f_header.close()

      self.f_source.close()

   def render(self,port, port_type):
      self._collect_stub_struct_elements(port)
      self._collect_stub_signals(port)
      self._collect_stub_set_functions(port)
      self._collect_stub_check_functions(port, port_type)
      
   def renderPPort(self, port):
      self._collect_stub_struct_elements(port)
      self._collect_pport_stub_signals(port)
      #self._collect_stub_check_functions(port)

   def renderRPort(self, port):
      self._collect_stub_struct_elements(port)
      self._collect_rport_stub_signals(port)
      self._collect_stub_set_functions(port)

   def _collect_stub_struct_elements(self, port):
      self.signal_struct_elements += '\tstruct\n'
      self.signal_struct_elements += '\t{\n'
      self.signal_struct_elements += '\t\t' + port.type + ' ' + 'par;\n'
      self.signal_struct_elements += '\t\t' + 'Std_ReturnType ret;\n'
      self.signal_struct_elements += '\t}' + ' ' + 'Rte_' + port.port_name + '_' + port.signal_name + ';\n\n'
   
   def _collect_pport_stub_signals(self, port):
      port_signal = port.port_name + '_' + port.signal_name
      ptr_to_struct = ' const*' if port.is_struct_type == True else ''
      dereference_ptr = '*' if port.is_struct_type == True else ''
      self.stub_signals += 'Std_ReturnType Rte_Write_' + port_signal + '(' + port.type + ptr_to_struct + ' par)\n'
      self.stub_signals += '{\n'
      self.stub_signals += '\tp.Rte_' + port_signal + '.par = ' + dereference_ptr + 'par;\n'
      self.stub_signals += '\treturn p.Rte_' + port_signal + '.ret;\n'
      self.stub_signals += '}\n\n'

   def _collect_rport_stub_signals(self, port):
      port_signal = port.port_name + '_' + port.signal_name
      self.stub_signals += 'Std_ReturnType Rte_Read_' + port_signal + '(' + port.type + '* par)\n'
      self.stub_signals += '{\n'
      self.stub_signals += '\t*par = p.Rte_' + port_signal + '.par;\n'
      self.stub_signals += '\treturn p.Rte_' + port_signal + '.ret;\n'
      self.stub_signals += '}\n\n'

   def _collect_stub_set_functions(self, port):
      if port.direction == 'required':
         port_signal = port.port_name + '_' + port.signal_name
         function_prototype = 'void stubs_set_' + port_signal + '(' +  port.type + ' par)'

         self.stub_set_functions += function_prototype + '\n'
         self.stub_set_functions += '{\n'
         self.stub_set_functions += '\tp.Rte_' + port_signal + '.par = par;\n'
         self.stub_set_functions += '}\n\n'

         self.stub_set_function_prototypes += function_prototype + ';\n'

   def _collect_stub_check_functions(self, port, type_tuple):
      if port.direction == 'provided':
         ptr_to_struct = '*' if port.is_struct_type == True else ''
         port_signal = port.port_name + '_' + port.signal_name
         function_define = '#define stubs_check_' + port_signal + '(expected) _stubs_check_' + port_signal + '(expected, __FILE__, __FUNCTION__, __LINE__);'
         function_prototype = 'void _stubs_check_' + port_signal + '(' +  port.type + ptr_to_struct + ' expected, const char *file, const char *function, const int line)'

         self.stub_check_functions += function_prototype + '\n'
         self.stub_check_functions += '{\n'
         if type_tuple:
            for element in type_tuple:
               self.stub_check_functions += '\tif (p.Rte_' + port_signal + '.par.' + element.element_name + ' != expected->' + element.element_name + ')\n'
               self.stub_check_functions += '\t{\n'
               self.stub_check_functions += '\t\tprintf(\"%s in %s on line: %d, ' + element.element_name + ': expected %d but was %d\\n\", file, function, line, expected->' + element.element_name + ', p.Rte_' + port_signal + '.par.' + element.element_name + ');\n'
               self.stub_check_functions += '\t}\n'
               self.stub_check_functions += '\tCU_ASSERT_TRUE_FATAL(p.Rte_' + port_signal + '.par.' + element.element_name + ' == expected->' + element.element_name + ');\n'
         else:
            self.stub_check_functions += '\tif (p.Rte_' + port_signal + '.par != expected)\n'
            self.stub_check_functionss += '\t{\n'
            self.stub_check_functions += '\t\tprintf(\"%s in %s on line: %d, ' + port_signal + ': expected %d but was %d\\n\", file, function, line, expected, p.Rte_' + port_signal + '.par);\n'
            self.stub_check_functions += '\t}\n'
            self.stub_check_functions += '\tCU_ASSERT_TRUE_FATAL(p.Rte_' + port_signal + '.par == expected);\n'

         self.stub_check_functions += '}\n\n'

         self.stub_check_function_prototypes += function_define + '\n' + function_prototype + ';\n\n'

   def _write_stub_signal_struct(self):
      self.f_header.write('typedef struct\n{')
      self.f_header.write(self.signal_struct_elements)
      
      s = '} StubSignals_Type;\n\n'
      s += 'extern StubSignals_Type p;\n\n'
      self.f_header.write(s)

      self.f_source.write('StubSignals_Type p;\n\n')

   def _write_stub_signals(self):
      self.f_source.write(self.stub_signals)

   def _write_stub_set_signals(self):
      self.f_source.write(self.stub_set_functions)
      self.f_header.write(self.stub_set_function_prototypes)

   def _write_stub_check_signals(self):
      self.f_source.write(self.stub_check_functions)
      self.f_header.write(self.stub_check_function_prototypes)
