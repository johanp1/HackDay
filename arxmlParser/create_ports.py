#! /usr/bin/python

import DbcParser
import ArxmlParser
import RteRenderer
import StubRenderer
import ComponentRenderer

""" main script """
def main():
   ldc_name = 'StateEstimationCtrl'
   swc_name = 'StateEstimation'

   ap = ArxmlParser.ArxmlParser()
   ap.parse('http://autosar.org/schema/r4.0', \
            'arxml/StateEstimation.arxml', \
            'arxml/PortInterfaces.arxml', \
            'arxml/DataTypes.arxml')

   dp = DbcParser.DbcParser()
   dp.parse('can/CAN01-T3_1.9.0.dbc', 'can01')
   dp.parse('can/CAN02-T3_1.9.0.dbc', 'can02')
   dp.parse('can/CAN03-T3_1.9.0.dbc', 'can03')
   dp.parse('can/CAN04-T3_1.9.0.dbc', 'can04')
   dp.parse('can/CAN05-T3_1.9.0.dbc', 'can05')
   dp.parse('can/CAN06-T3_1.9.0.dbc', 'can06')
   dp.parse('can/CAN32-T3_1.9.0.dbc', 'can32')
   
   rr = RteRenderer.RteRenderer('Se_rteData', ldc_name, swc_name)
   sr = StubRenderer.StubRenderer('cunit_se_stubs', ldc_name, swc_name)
   cr = ComponentRenderer.ComponentRenderer(ldc_name)

   # find offset and scale
   for port in ap.port_array:
      # get scale and offset from can-db
      scale = '1'
      offset = '0'

      for sig_key in dp.signal_dict:
         if sig_key.startswith(port.signal_name):
            scale = dp.signal_dict[sig_key].scale
            offset = dp.signal_dict[sig_key].offset

            port.scale = scale
            port.offset = offset
            port.comment = dp.signal_dict[sig_key].net_name

      rr.render(port)
      sr.render(port, ap.type_dict[port.type])
      cr.render(port, ap.type_dict[port.type])

if __name__ == '__main__':
   main()
