from ArxmlParser import RPort, PPort, ValueSignal, StructSignal, StructSignalElement

class PPortVisitor:
   def __init__(self, renderer):
      self.renderer = renderer
      self.port_name = ''

   def renderValueSignal(self, signal):
      self.renderer.render_pport_value_signal(self.port_name, signal)

   def renderStructSignal(self, signal):
      self.renderer.render_pport_struct_signal(self.port_name, signal)
      
   def renderStructElement(self, element):
      pass

class RPortVisitor:
   def __init__(self, renderer):
      self.renderer = renderer
      self.port_name = ''

   def renderValueSignal(self, signal):
      self.renderer.render_value_signal(self.port_name, signal)
      
   def renderStructSignal(self, signal):
      self.renderer.render_value_signal(self.port_name, signal)

   def renderStructElement(self, signal):
      self.renderer.render_struct_signal(self.port_name, signal)

class RteRenderer:
   def __init__(self, module, ldc, swc):
      f_template = open('template/template.h', 'r')
      self.f_out = open('out/' + module + '.h', 'w')

      self.pport_visitor = PPortVisitor(self)
      self.rport_visitor = RPortVisitor(self)

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
      self.pport_visitor.port_name = port.port_name
      for signal in port.signal_array:
         signal.accept(self.pport_visitor)

   def renderRPort(self, port):
      self.rport_visitor.port_name = port.port_name
      for signal in port.signal_array:
         signal.accept(self.rport_visitor)

   def render_value_signal(self, port_name, signal):
      scale_str = '' if signal.scale == '1' else str(signal.scale) + '*'
      offset_str = '' if signal.offset == '0' else ' + (' + str(signal.offset) + ')'
      var_name = signal.name[0].lower() + signal.name[1:]

      s = "\t{"
      s = s + "#datatype #var_name;\n"
      s = s + "\t(void)Rte_Read_#port_name_#signal_name(&#var_name);\n"
      s = s + "\t/*dummy*/ rx->#var_name = " + scale_str + "#var_name" + offset_str + ";"   
      s = s + "}\n\n"

      s = s.replace('#var_name', var_name)
      s = s.replace('#port_name', port_name)
      s = s.replace('#signal_name', signal.name)
      s = s.replace('#datatype', signal.type)

      self.f_out.write(s)

   def render_pport_value_signal(self, port_name, signal): 
      write_data = 'tx->data'
      scale_str = '' if signal.scale == '1' else '/' + str(signal.scale)
      offset_str = '' if signal.offset == '0' else ' - (' + str(signal.offset) + scale_str + ')'
      arg_str = '(#dataType*)(&#write_data)'
      s = '\t(void)Rte_Write_#portName_#signalName('+ arg_str +');\n\n'

      s = s.replace('#portName', port_name)
      s = s.replace('#signalName', signal.name)
      s = s.replace('#dataType', signal.type)
      s = s.replace('#write_data', write_data)

      self.f_out.write(s)

   def render_pport_struct_signal(self, port_name, signal): 
      write_data = 'tx->data'
      #scale_str = '' if signal.scale == '1' else '/' + str(signal.scale)
      #offset_str = '' if offset == '0' else ' - (' + str(offset) + scale_str + ')'
      #arg_str = '(#dataType)(#write_data' + scale_str + offset_str + ')' 
      arg_str = '(#dataType)(#write_data)' 
      s = '\t(void)Rte_Write_#portName_#signalName('+ arg_str +');\n\n'

      s = s.replace('#portName', port_name)
      s = s.replace('#signalName', signal.name)
      s = s.replace('#dataType', signal.type)
      s = s.replace('#write_data', write_data)

      self.f_out.write(s)