from ArxmlParser import RPort, PPort, ValueSignal, StructSignal, StructSignalElement

class PPortVisitor:
    def __init__(self, renderer):
        self.renderer = renderer
        self.port_name = ''

    def renderValueSignal(self, signal):
        self.renderer._collect_stub_struct_elements(self.port_name, signal)
        self.renderer._collect_pport_stub_value_signals(self.port_name, signal)
        self.renderer._collect_pport_stub_check_value_signals(self.port_name, signal)

    def renderStructSignal(self, signal):
        self.renderer._collect_stub_struct_elements(self.port_name, signal)
        self.renderer._collect_pport_stub_struct_signals(self.port_name, signal)
        self.renderer._collect_pport_stub_check_stuct_signals(self.port_name, signal)

    def renderStructElement(self, element):
        pass

class RPortVisitor:
    def __init__(self, renderer):
        self.renderer = renderer
        self.port_name = ''

    def renderValueSignal(self, signal):
        self.renderer._collect_stub_struct_elements(self.port_name, signal)
        self.renderer._collect_rport_stub_value_signals(self.port_name, signal)
        self.renderer._collect_rport_stub_set_signals(self.port_name, signal)

    def renderStructSignal(self, signal):
        self.renderer._collect_stub_struct_elements(self.port_name, signal)
        self.renderer._collect_rport_stub_struct_signals(self.port_name, signal)
        self.renderer._collect_rport_stub_set_signals(self.port_name, signal)

    def renderStructElement(self, element):
        pass

class StubRenderer:
    def __init__(self, module, ldc, swc):
        f_template = open('template/template.h', 'r')
        self.f_header = open('out/' + module + '.h', 'w')
        self.f_source = open('out/' + module + '.c', 'w')

        self.pport_visitor = PPortVisitor(self)
        self.rport_visitor = RPortVisitor(self)

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

    def renderPPort(self, port):
        self.pport_visitor.port_name = port.port_name
        for signal in port.signal_array:
            signal.accept(self.pport_visitor)

    def renderRPort(self, port):
        self.rport_visitor.port_name = port.port_name
        for signal in port.signal_array:
            signal.accept(self.rport_visitor)

    def _collect_stub_struct_elements(self, port_name, signal):
        self.signal_struct_elements += '\tstruct\n'
        self.signal_struct_elements += '\t{\n'
        self.signal_struct_elements += '\t\t' + signal.type + ' ' + 'par;\n'
        self.signal_struct_elements += '\t\t' + 'Std_ReturnType ret;\n'
        self.signal_struct_elements += '\t}' + ' ' + 'Rte_' + port_name + '_' + signal.name + ';\n\n'

    def _collect_pport_stub_value_signals(self, port_name, signal):
        port_signal = port_name + '_' + signal.name
        self.stub_signals += 'Std_ReturnType Rte_Write_' + port_signal \
            + '(' + signal.type + ' par)\n'
        self.stub_signals += '{\n'
        self.stub_signals += '\tp.Rte_' + port_signal + '.par = par;\n'
        self.stub_signals += '\treturn p.Rte_' + port_signal + '.ret;\n'
        self.stub_signals += '}\n\n'

    def _collect_pport_stub_struct_signals(self ,port_name, signal):
        port_signal = port_name + '_' + signal.name
        self.stub_signals += 'Std_ReturnType Rte_Write_' + port_signal \
            + '(' + signal.type + ' const*' + ' par)\n'
        self.stub_signals += '{\n'
        self.stub_signals += '\tp.Rte_' + port_signal + '.par = ' + '*' + 'par;\n'
        self.stub_signals += '\treturn p.Rte_' + port_signal + '.ret;\n'
        self.stub_signals += '}\n\n'

    def _collect_rport_stub_value_signals(self, port_name, signal):
        port_signal = port_name + '_' + signal.name
        self.stub_signals += 'Std_ReturnType Rte_Read_' + port_signal \
            + '(' + signal.type + '* par)\n'
        self.stub_signals += '{\n'
        self.stub_signals += '\t*par = p.Rte_' + port_signal + '.par;\n'
        self.stub_signals += '\treturn p.Rte_' + port_signal + '.ret;\n'
        self.stub_signals += '}\n\n'

    def _collect_rport_stub_struct_signals(self ,port_name, signal):
        port_signal = port_name + '_' + signal.name
        self.stub_signals += 'Std_ReturnType Rte_Read_' + port_signal \
            + '(' + signal.type + '* par)\n'
        self.stub_signals += '{\n'
        self.stub_signals += '\t*par = p.Rte_' + port_signal + '.par;\n'
        self.stub_signals += '\treturn p.Rte_' + port_signal + '.ret;\n'
        self.stub_signals += '}\n\n'

    def _collect_rport_stub_set_signals(self ,port_name, signal):
        port_signal = port_name + '_' + signal.name
        function_prototype = 'void stubs_set_' + port_signal + '(' +  signal.type + ' par)'

        self.stub_set_functions += function_prototype + '\n'
        self.stub_set_functions += '{\n'
        self.stub_set_functions += '\tp.Rte_' + port_signal + '.par = par;\n'
        self.stub_set_functions += '}\n\n'

        self.stub_set_function_prototypes += function_prototype + ';\n'

    def _collect_pport_stub_check_value_signals(self, port_name, signal):
        port_signal = port_name + '_' + signal.name
        function_define = '#define stubs_check_' + port_signal + '(expected) _stubs_check_' \
            + port_signal + '(expected, __FILE__, __FUNCTION__, __LINE__);'
        function_prototype = 'void _stubs_check_' + port_signal + '(' +  signal.type \
            + ' expected, const char *file, const char *function, const int line)'
        self.stub_check_functions += function_prototype + '\n'
        self.stub_check_functions += '{\n'
        self.stub_check_functions += '\tif (p.Rte_' + port_signal + '.par != expected)\n'
        self.stub_check_functions += '\t{\n'
        self.stub_check_functions += '\t\tprintf(\"%s in %s on line: %d, ' + port_signal \
            + ': expected %d but was %d\\n\", file, function, line, expected, p.Rte_' \
            + port_signal + '.par);\n'
        self.stub_check_functions += '\t}\n'
        self.stub_check_functions += '\tCU_ASSERT_TRUE_FATAL(p.Rte_' + port_signal \
            + '.par == expected);\n'
        self.stub_check_functions += '}\n\n'

        self.stub_check_function_prototypes += function_define + '\n' + function_prototype + ';\n\n'

    def _collect_pport_stub_check_stuct_signals(self, port_name, signal):
        port_signal = port_name + '_' + signal.name
        function_define = '#define stubs_check_' + port_signal + '(expected) _stubs_check_' \
            + port_signal + '(expected, __FILE__, __FUNCTION__, __LINE__);'
        function_prototype = 'void _stubs_check_' + port_signal + '(' +  signal.type \
            + '* expected, const char *file, const char *function, const int line)'

        self.stub_check_functions += function_prototype + '\n'
        self.stub_check_functions += '{\n'
        for element in signal.element_array:
            self.stub_check_functions += '\tif (p.Rte_' + port_signal + '.par.' + element.name \
                + ' != expected->' + element.name + ')\n'
            self.stub_check_functions += '\t{\n'
            self.stub_check_functions += '\t\tprintf(\"%s in %s on line: %d, ' + element.name \
                + ': expected %d but was %d\\n\", file, function, line, expected->' + element.name\
                + ', p.Rte_' + port_signal + '.par.' + element.name + ');\n'
            self.stub_check_functions += '\t}\n'
            self.stub_check_functions += '\tCU_ASSERT_TRUE_FATAL(p.Rte_' + port_signal + '.par.' \
                + element.name + ' == expected->' + element.name + ');\n'
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
