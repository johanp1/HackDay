#import ArxmlParser
from ArxmlParser import Port

class RteRenderer:
   def __init__(self, module, ldc, swc):
      f_template = open('template/template.h', 'r')
      self.f_out = open(module + '.h', 'w')

      # copy template until
      for l in f_template:
         if '@file' in l:
            self.f_out.write(l.replace('_', module + '.h', 1))
         elif '__C_module_H__' in l:
            self.f_out.write(l.replace('module', module.upper(), 1))
         elif 'swc' in l:
            self.f_out.write(l.replace('swc', swc, 1))
         elif 'ldc' in l:
            self.f_out.write(l.replace('ldc', ldc, 1))            
         else:
            self.f_out.write(l)

      f_template.close()

      s = '#include \"Rte_' + swc + '.h\"\n\n'
      s += 'void ' + module + '(void)\n{\n'
      self.f_out.write(s)

   def __del__(self):
      self.f_out.write('};\n')
      self.f_out.write('#endif\n')
      self.f_out.close()

   def renderPPort(self, port):
      self._newWriteFunction(port.port_name, port.signal_name, port.type, port.scale, port.offset, port.is_struct_type, port.comment)

   def renderRPort(self, port):
      self._newReadFunction(port.port_name, port.signal_name, port.type, port.scale, port.offset, port.comment)

      
   def _newReadFunction(self, port_name, signal_name, datatype, scale = '1', offset = '0', comment = ''):
      scale_str = '' if scale == '1' else str(scale) + '*'
      offset_str = '' if offset == '0' else ' + (' + str(offset) + ')'
      comment_str = '  // ' + comment if comment != '' else ''
      var_name = signal_name[0].lower() + signal_name[1:]

      s = "\t{"
      s = s + "#datatype #var_name;\n"
      s = s + "\t(void)Rte_Read_#port_name_#signal_name(&#var_name);" + comment_str + "\n"
      s = s + "\t/*dummy*/ rx->#var_name = " + scale_str + "#var_name" + offset_str + ";"   
      s = s + "}\n\n"

      s = s.replace('#var_name', var_name)
      s = s.replace('#port_name', port_name)
      s = s.replace('#signal_name', signal_name)
      s = s.replace('#datatype', datatype)

      self.f_out.write(s)

   def _newWriteFunction(self, portName, signalName, datatype, scale, offset, use_const_ptr = False, comment = ''):     
      write_data = 'tx->data'
      scale_str = '' if scale == '1' else '/' + str(scale)
      offset_str = '' if offset == '0' else ' - (' + str(offset) + scale_str + ')'
      arg_str = '(#dataType)(#write_data' + scale_str + offset_str + ')' if use_const_ptr == False else '(#dataType*)(&#write_data)'
      comment_str = '  // ' + comment if comment != '' else ''
      s = '\t(void)Rte_Write_#portName_#signalName('+ arg_str +');' + comment_str + '\n\n'

      s = s.replace('#portName', portName)
      s = s.replace('#signalName', signalName)
      s = s.replace('#dataType', datatype)
      s = s.replace('#write_data', write_data)

      self.f_out.write(s)