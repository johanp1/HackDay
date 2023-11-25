from ArxmlParser import RPort, PPort, ValueSignal, StructSignal, StructSignalElement

class PPortVisitor:
    def __init__(self, renderer):
        self.renderer = renderer
        self.port_name = ''

    def renderValueSignal(self, signal):
        self.renderer.collect_stub_struct_elements(self.port_name, signal)
        self.renderer.collect_pport_stub_value_signals(self.port_name, signal)
        self.renderer.collect_pport_stub_check_value_signals(self.port_name, signal)

    def renderStructSignal(self, signal):
        self.renderer.collect_stub_struct_elements(self.port_name, signal)
        self.renderer.collect_pport_stub_struct_signals(self.port_name, signal)
        self.renderer.collect_pport_stub_check_stuct_signals(self.port_name, signal)

    def renderStructElement(self, element):
        pass

class RPortVisitor:
    def __init__(self, renderer):
        self.renderer = renderer
        self.port_name = ''

    def renderValueSignal(self, signal):
        self.renderer.collect_stub_struct_elements(self.port_name, signal)
        self.renderer.collect_rport_stub_value_signals(self.port_name, signal)
        self.renderer.collect_rport_stub_set_signals(self.port_name, signal)

    def renderStructSignal(self, signal):
        self.renderer.collect_stub_struct_elements(self.port_name, signal)
        self.renderer.collect_rport_stub_struct_signals(self.port_name, signal)
        self.renderer.collect_rport_stub_set_signals(self.port_name, signal)

    def renderStructElement(self, element):
        pass

class CPortVisitor:
    def __init__(self, renderer):
        self.renderer = renderer
        self.port_name = ''

    def renderValueSignal(self, signal):
        self.renderer.collect_stub_config_struct_value_type(self.port_name, signal)
        self.renderer.collect_cport_stub_value_function(self.port_name, signal)

    def renderStructSignal(self, signal):
        self.renderer.collect_stub_config_struct_struct_type(self.port_name, signal)
        self.renderer.collect_cport_stub_struct_function(self.port_name, signal)

    def renderStructElement(self, element):
        pass

    def renderArraySignal(self, signal):
        self.renderer.collect_stub_config_struct_array_type(self.port_name, signal)
        self.renderer.collect_cport_stub_array_function(self.port_name, signal)

class StubRenderer:
    def __init__(self, module, ldc, swc):
        f_template = open('template/template.h', 'r')
        self.f_header = open('out/' + module + '.h', 'w')
        self.f_source = open('out/' + module + '.c', 'w')

        self.pport_visitor = PPortVisitor(self)
        self.rport_visitor = RPortVisitor(self)
        self.cport_visitor = CPortVisitor(self)

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

        self.config_struct = ''
        self.default_config = ''
        self.stub_config_functions = ''

    def __del__(self):
        self._write_stub_signal_struct()
        self._write_config_struct()
        self._write_stub_signals()
        self._write_stub_set_signals()
        self._write_stub_check_signals()
        self._write_config_stubs()

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

    def renderCPort(self, port):
        self.cport_visitor.port_name = port.port_name
        for signal in port.signal_array:
            signal.accept(self.cport_visitor)

    def collect_stub_struct_elements(self, port_name, signal):
        self.signal_struct_elements += '\tstruct\n'
        self.signal_struct_elements += '\t{\n'
        self.signal_struct_elements += '\t\t' + signal.type.name + ' ' + 'par;\n'
        self.signal_struct_elements += '\t\t' + 'Std_ReturnType ret;\n'
        self.signal_struct_elements += '\t}' + ' ' + 'Rte_' + port_name + '_' + signal.name + ';\n\n'

    def collect_stub_config_struct_value_type(self, port_name, signal):
        variable_name = port_name
        self.config_struct += '\t\t' + signal.type.name + ' ' + variable_name + ';\n'
        self.default_config += '\t0, /*' + variable_name + '*/\n'

    def collect_stub_config_struct_struct_type(self, port_name, signal):
        variable_name = port_name
        self.config_struct += '\t\t' + signal.type.name + ' ' + variable_name + ';\n'

        self.default_config += ', \{ /*' + variable_name + '*/\n'
        for element in signal.element_array:
            self.default_config += '\t\t0, /*' + element.name + '*/\n'
        self.default_config += '\}\n'

    def collect_stub_config_struct_array_type(self, port_name, signal):
        variable_name = port_name
        self.config_struct += '\t\t' + signal.type.name + ' ' + variable_name + ';\n'

        self.default_config += '\t{'
        for i in range(0, int(signal.type.size)-1):
            self.default_config += '0, '
        self.default_config += '0}, /*' + variable_name + '*/\n'

    def collect_cport_stub_value_function(self, port_name, signal):
        self.stub_config_functions += \
            signal.type.name + ' Rte_Prm_' + port_name + '_' + signal.name + '()\n'
        self.stub_config_functions += \
            '{\n\treturn c.' + port_name + ';\n}\n\n'
        
    def collect_cport_stub_struct_function(self, port_name, signal):
        self.stub_config_functions += \
            signal.type.name + '* Rte_Prm_' + port_name + '_' + signal.name + '()\n'
        self.stub_config_functions += \
            '{\n\treturn &c.' + port_name + ';\n}\n\n'

    def collect_cport_stub_array_function(self, port_name, signal):
        self.stub_config_functions += \
            signal.type.name + '* Rte_Prm_' + port_name + '_' + signal.name + '()\n'
        self.stub_config_functions += \
            '{\n\treturn &c.' + port_name + ';\n}\n\n'

    def collect_pport_stub_value_signals(self, port_name, signal):
        port_signal = port_name + '_' + signal.name
        self.stub_signals += 'Std_ReturnType Rte_Write_' + port_signal \
            + '(' + signal.type + ' par)\n'
        self.stub_signals += '{\n'
        self.stub_signals += '\tp.Rte_' + port_signal + '.par = par;\n'
        self.stub_signals += '\treturn p.Rte_' + port_signal + '.ret;\n'
        self.stub_signals += '}\n\n'

    def collect_pport_stub_struct_signals(self ,port_name, signal):
        port_signal = port_name + '_' + signal.name
        self.stub_signals += 'Std_ReturnType Rte_Write_' + port_signal \
            + '(' + signal.type.name + ' const*' + ' par)\n'
        self.stub_signals += '{\n'
        self.stub_signals += '\tp.Rte_' + port_signal + '.par = ' + '*' + 'par;\n'
        self.stub_signals += '\treturn p.Rte_' + port_signal + '.ret;\n'
        self.stub_signals += '}\n\n'

    def collect_rport_stub_value_signals(self, port_name, signal):
        port_signal = port_name + '_' + signal.name
        self.stub_signals += 'Std_ReturnType Rte_Read_' + port_signal \
            + '(' + signal.type.name + '* par)\n'
        self.stub_signals += '{\n'
        self.stub_signals += '\t*par = p.Rte_' + port_signal + '.par;\n'
        self.stub_signals += '\treturn p.Rte_' + port_signal + '.ret;\n'
        self.stub_signals += '}\n\n'

    def collect_rport_stub_struct_signals(self ,port_name, signal):
        port_signal = port_name + '_' + signal.name
        self.stub_signals += 'Std_ReturnType Rte_Read_' + port_signal \
            + '(' + signal.type.name + '* par)\n'
        self.stub_signals += '{\n'
        self.stub_signals += '\t*par = p.Rte_' + port_signal + '.par;\n'
        self.stub_signals += '\treturn p.Rte_' + port_signal + '.ret;\n'
        self.stub_signals += '}\n\n'

    def collect_rport_stub_set_signals(self ,port_name, signal):
        port_signal = port_name + '_' + signal.name
        function_prototype = 'void stubs_set_' + port_signal + '(' +  signal.type.name + ' par)'

        self.stub_set_functions += function_prototype + '\n'
        self.stub_set_functions += '{\n'
        self.stub_set_functions += '\tp.Rte_' + port_signal + '.par = par;\n'
        self.stub_set_functions += '}\n\n'

        self.stub_set_function_prototypes += function_prototype + ';\n'

    def collect_pport_stub_check_value_signals(self, port_name, signal):
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

    def collect_pport_stub_check_stuct_signals(self, port_name, signal):
        port_signal = port_name + '_' + signal.name
        function_define = '#define stubs_check_' + port_signal + '(expected) _stubs_check_' \
            + port_signal + '(expected, __FILE__, __FUNCTION__, __LINE__);'
        function_prototype = 'void _stubs_check_' + port_signal + '(' +  signal.type.name \
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

    def _write_config_struct(self):
        self.f_header.write('typedef struct\n{\n')
        self.f_header.write(self.config_struct)
        s = '} StubConfig_Type;\n\n'

        #s += 'extern StubConfig_Type c;\n\n'
        s += 'StubConfig_Type c = {\n'
        s += self.default_config
        s += '};\n\n'
    
        self.f_header.write(s)

        #self.f_source.write('StubConfig_Type c;\n\n')

    def _write_stub_signals(self):
        self.f_source.write(self.stub_signals)

    def _write_stub_set_signals(self):
        self.f_source.write(self.stub_set_functions)
        self.f_header.write(self.stub_set_function_prototypes)

    def _write_stub_check_signals(self):
        self.f_source.write(self.stub_check_functions)
        self.f_header.write(self.stub_check_function_prototypes)

    def _write_config_stubs(self):
        self.f_source.write(self.stub_config_functions)