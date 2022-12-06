from ArxmlParser import RPort, PPort, ValueSignal, StructSignal, StructSignalElement

class PPortVisitor:
   def __init__(self, renderer):
      self.renderer = renderer
      self.port_name = ''
      self.stubbed = True

   def renderValueSignal(self, signal):
      self.renderer.render_value_signal(self.port_name, 'Send', signal, self.stubbed)

   def renderStructSignal(self, signal):
      self.renderer.render_struct_signal(self.port_name, 'Send', signal, self.stubbed)

class RPortVisitor:
   def __init__(self, renderer):
      self.renderer = renderer
      self.port_name = ''

   def renderValueSignal(self, signal):
      self.renderer.render_value_signal(self.port_name, 'Receive', signal, self.stubbed)

   def renderStructSignal(self, signal):
      self.renderer.render_struct_signal(self.port_name, 'Receive', signal, self.stubbed)

class ComponentRenderer:
   def __init__(self, ldc):
      self.ldc = ldc
      self.f_out = open('out/' + ldc + '.xml', 'w')

      self.pport_visitor = PPortVisitor(self)
      self.rport_visitor = RPortVisitor(self)

      s = '<Component Name="' + self.ldc + '">\n'
      s += '\t<SenderReceiverPorts>\n'

      self.f_out.write(s)

   def __del__(self):
      s = '\t</SenderReceiverPorts>\n'
      s += '</Component>\n'
      self.f_out.write(s)

      self.f_out.close()

   def renderPPort(self, port):
      self.pport_visitor.port_name = port.port_name
      self.pport_visitor.stubbed = port.stubbed
      for signal in port.signal_array:
         signal.accept(self.pport_visitor)

   def renderRPort(self, port):
      self.rport_visitor.port_name = port.port_name
      self.rport_visitor.stubbed = port.stubbed
      for signal in port.signal_array:
         signal.accept(self.rport_visitor)

   def render_value_signal(self, port_name, direction, signal, stubbed):
      is_stubbed = ' Stub="true"' if stubbed == True else ''
      s = '\t\t<Port Name="' + port_name + '" Direction="' + direction + '" Signal="' + port_name + '"' + is_stubbed + ' />\n' #the can signal name is assumed to be the same as the port name
      self.f_out.write(s)

   def render_struct_signal(self, port_name, direction, signal, stubbed):
      is_stubbed = ' Stub="true"' if stubbed == True else ''
      s = '\t\t<Port Name="' + port_name + '" Direction="' + direction + '" Signal="' + port_name + '"' + is_stubbed + ' >\n'
      s += '\t\t\t<Signals>\n'

      for element in signal.element_array:
         s += '\t\t\t\t<Signal Name="' + port_name + '_' + element.name + '" Element="' + element.name + '" />\n'
      
      s += '\t\t\t</Signals>\n'
      s += '\t\t</Port>\n'

      self.f_out.write(s)
