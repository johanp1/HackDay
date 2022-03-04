import ArxmlParser

class ComponentRenderer:
    def __init__(self, ldc):
        self.ldc = ldc
        self.f_out = open(ldc + '.xml', 'w')

    def render(self, arxml_parser):
        s = '<Component Name="' + self.ldc + '">\n'
        s += '\t<SenderReceiverPorts>\n'
        self.f_out.write(s)

        for port in arxml_parser.port_array:
            direction = 'Receive' if port.direction == 'required' else 'Send'

            if arxml_parser.type_dict[port.type]:
                s = '\t\t<Port Name="' + port.port_name + '" Direction="' + direction + '" Stub="true" >\n'
                s += '\t\t\t<Signals>\n'
                for element in arxml_parser.type_dict[port.type]:
                    s += '\t\t\t\t<Signal Name="' + port.port_name + '_' + element.element_name + '" Element="' + element.element_name + '" />\n'
                s += '\t\t\t</Signals>\n'
                s += '\t\t</Port>\n'
            else:
                s = '\t\t<Port Name="' + port.port_name + '" Direction="' + direction + '" Signal="' + port.signal_name + '" Stub="true" />\n'
            self.f_out.write(s)

        s = '\t</SenderReceiverPorts>\n'
        s += '</Component>\n'
        self.f_out.write(s)
