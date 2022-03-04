#! /usr/bin/python

import DbcParser
import ArxmlParser
#import WriteDataRenderer
#import ReadDataRenderer
import RteRenderer
import StubRenderer
import ComponentRenderer

""" main script """
def main():
   ldc_name = 'StateEstimationCtrl'
   swc_name = 'StateEstimation'

   ap = ArxmlParser.ArxmlParser()
   ap.parse('http://autosar.org/schema/r4.0', \
            '../autosar4/StateEstimation.arxml', \
            '../../autosar4/PortInterfaces.arxml', \
            '../../autosar4/DataTypes.arxml')

   dp = DbcParser.DbcParser()
   dp.parse('can/CAN01-T3_1.9.0.dbc', 'can01')
   dp.parse('can/CAN02-T3_1.9.0.dbc', 'can02')
   dp.parse('can/CAN03-T3_1.9.0.dbc', 'can03')
   dp.parse('can/CAN04-T3_1.9.0.dbc', 'can04')
   dp.parse('can/CAN05-T3_1.9.0.dbc', 'can05')
   dp.parse('can/CAN06-T3_1.9.0.dbc', 'can06')
   dp.parse('can/CAN32-T3_1.9.0.dbc', 'can32')
   
   #wdr = WriteDataRenderer.WriteDataRenderer('Vmm_writeData', ldc_name, swc_name)
   #rdr = ReadDataRenderer.ReadDataRenderer('Vmm_readData', ldc_name, swc_name)
   rr = RteRenderer.RteRenderer('Se_rteData', ldc_name, swc_name)
   sr = StubRenderer.StubRenderer('cunit_se_stubs', ldc_name, swc_name)
   cr = ComponentRenderer.ComponentRenderer(ldc_name)

   # find offset and scale
   for port in ap.port_array:
         # get scale and offset from can-db
         found_in_dbc = False
         scale = '1'
         offset = '0'

         for sig_key in dp.signal_dict:
            if sig_key.startswith(port.signal_name):
               scale = dp.signal_dict[sig_key].scale
               offset = dp.signal_dict[sig_key].offset
               found_in_dbc = True

               port.scale = scale
               port.offset = offset
               port.comment = dp.signal_dict[sig_key].net_name

         #if port.direction == 'provided' and port.signal_name != '':
         #   wdr.newWriteFunction(port.port_name, port.signal_name, port.type, scale, offset, port.is_struct_type, found_in_dbc)

         #if port.direction == 'required' and port.signal_name != '':
         #   rdr.newReadFunction(port.port_name, port.signal_name, port.type, scale, offset, found_in_dbc)

   rr.render(ap)
   sr.render(ap)
   cr.render(ap)

if __name__ == '__main__':
   main()
