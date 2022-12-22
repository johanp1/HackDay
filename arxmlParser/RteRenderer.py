#from ArxmlParser import RPort, PPort, ValueSignal, StructSignal, StructSignalElement

class PPortVisitor:
    """PPortVisitor-class for RteRenderer"""
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
    """RPortVisitor-class for RteRenderer"""
    def __init__(self, renderer):
        self.renderer = renderer
        self.port_name = ''

    def renderValueSignal(self, signal):
        self.renderer.render_rport_signal(self.port_name, signal)

    def renderStructSignal(self, signal):
        self.renderer.render_rport_signal(self.port_name, signal)

    def renderStructElement(self, signal):
        pass

class RteRenderer:
    """Renders c functions in output file"""
    def __init__(self, module, ldc, swc):
        f_template = open('template/template.h', 'r')  # pylint: disable=unspecified-encoding
        self.f_out = open('out/' + module + '.h', 'w') # pylint: disable=unspecified-encoding

        self.pport_visitor = PPortVisitor(self)
        self.rport_visitor = RPortVisitor(self)

        # copy template until
        for line in f_template:
            if '@file' in line:
                self.f_out.write(line.replace('_', module + '.h', 1))
            elif '__C_module_H__' in line:
                self.f_out.write(line.replace('module', module.upper(), 1))
            elif 'swc' in line:
                self.f_out.write(line.replace('swc', swc, 1))
            elif 'ldc' in line:
                self.f_out.write(line.replace('ldc', ldc, 1))
            else:
                self.f_out.write(line)

        f_template.close()

        out_str = '#include \"Rte_' + swc + '.h\"\n\n'
        out_str += 'void ' + module + '(void)\n{\n'
        self.f_out.write(out_str)

    def __del__(self):
        self.f_out.write('};\n')
        self.f_out.write('#endif\n')
        self.f_out.close()

    def renderPPort(self, port):
        """Accept function (from Visitor-pattern) for P-Port"""
        self.pport_visitor.port_name = port.port_name
        for signal in port.signal_array:
            signal.accept(self.pport_visitor)

    def renderRPort(self, port):
        """Accept function (from Visitor-pattern) for R-Port"""
        self.rport_visitor.port_name = port.port_name
        for signal in port.signal_array:
            signal.accept(self.rport_visitor)

    def render_rport_signal(self, port_name, signal):
        """Renders Rte_Read_... function invocation in c-output file"""
        scale_str = '' if signal.scale == '1' else str(signal.scale) + '*'
        offset_str = '' if signal.offset == '0' else ' + (' + str(signal.offset) + ')'
        var_name = signal.name[0].lower() + signal.name[1:]

        out_str = "\t{"
        out_str += "#datatype #var_name;\n"
        out_str += "\t(void)Rte_Read_#port_name_#signal_name(&#var_name);\n"
        out_str += "\t/*dummy*/ rx->#var_name = " + scale_str + "#var_name" + offset_str + ";"
        out_str += "}\n\n"

        out_str = out_str.replace('#var_name', var_name)
        out_str = out_str.replace('#port_name', port_name)
        out_str = out_str.replace('#signal_name', signal.name)
        out_str = out_str.replace('#datatype', signal.type)

        self.f_out.write(out_str)

    def render_pport_value_signal(self, port_name, signal):
        """Renders Rte_Write_... function invocation in c-output file"""
        # pylint: disable=invalid-name
        write_data = 'tx->data'
        scale_str = '' if signal.scale == '1' else '/' + str(signal.scale)
        offset_str = '' if signal.offset == '0' else ' - (' + str(signal.offset) + scale_str + ')'
        arg_str = '(#dataType*)(&#write_data)'
        s = '\t(void)Rte_Write_#portName_#signalName(' + arg_str + scale_str + offset_str +');\n\n'

        s = s.replace('#portName', port_name)
        s = s.replace('#signalName', signal.name)
        s = s.replace('#dataType', signal.type)
        s = s.replace('#write_data', write_data)

        self.f_out.write(s)

    def render_pport_struct_signal(self, port_name, signal):
        """Renders Rte_Write_... function invocation in c-output file
           with struct-port as argument
        """
        # pylint: disable=invalid-name
        write_data = 'tx->data'
        arg_str = '(#dataType)(#write_data)'
        s = '\t(void)Rte_Write_#portName_#signalName('+ arg_str +');\n\n'

        s = s.replace('#portName', port_name)
        s = s.replace('#signalName', signal.name)
        s = s.replace('#dataType', signal.type)
        s = s.replace('#write_data', write_data)

        self.f_out.write(s)
