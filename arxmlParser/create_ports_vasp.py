#! /usr/bin/python

import DbcParser
import ArxmlParser
#import RteRenderer
#from SignalVisitor import SignalVisitor
#import StubRenderer
import ComponentRenderer
import SignalVisitor

def main():
    """ main script """
    ldc_name = 'DacuVaspApp'

    ap = ArxmlParser.ArxmlParser()
    ap.parse('http://autosar.org/schema/r4.0', \
                'arxml/DacuVASPApp_Simulink_VASPComponentTypes.arxml', \
                'arxml/PortInterfacesVasp.arxml', \
                'arxml/DataTypesVasp.arxml')

    dp = DbcParser.DbcParser()
    dp.parse('can/CAN01-T3_1.9.0.dbc', 'can01', 'VCM')
    dp.parse('can/CAN02-T3_1.9.0.dbc', 'can02', 'VCM')
    dp.parse('can/CAN03-T3_1.9.0.dbc', 'can03', 'VCM')
    dp.parse('can/CAN04-T3_1.9.0.dbc', 'can04', 'VCM')
    dp.parse('can/CAN05-T3_1.9.0.dbc', 'can05', 'VCM')
    dp.parse('can/CAN06-T3_1.9.0.dbc', 'can06', 'VCM')
    dp.parse('can/CAN32-T3_1.9.0.dbc', 'can32', 'VCM')
    dp.parse('can/CAN20-T3.dbc', 'can20', 'VCM')
    dp.parse('can/CAN21-T3.dbc', 'can21', 'VCM')
    dp.parse('can/CAN23-T3.dbc', 'can23', 'VCM')
    
    #rr = RteRenderer.RteRenderer('Se_rteData', ldc_name, swc_name)
    #sr = StubRenderer.StubRenderer('cunit_se_stubs', ldc_name, swc_name)
    cr = ComponentRenderer.ComponentRenderer(ldc_name)

    # find offset and scale from parsed can-db
    sv = SignalVisitor.SignalVisitor(dp.signal_dict)
    for port in ap.port_array:
        port.accept(sv)

    for port in ap.port_array:
        #port.accept(rr)
        #port.accept(sr)
        port.accept(cr)

if __name__ == '__main__':
   main()
