#! /usr/bin/python

import sys
import DbcParser
import ArxmlParser
import RteRenderer
from SignalVisitor import SignalVisitor
import StubRenderer
import ComponentRenderer
import SignalVisitor
import getopt

class OptParser:
    def __init__(self, argv):
        self.namespace = 'http://autosar.org/schema/r4.0'
        self.port_arxml = 'PortInterfaces.arxml'
        self.types_arxml = 'DataTypes.arxml'
        self.swc_arxml = ''
        self.ldc_name = ''
        self.swc_name = ''
        self.debug = False
        self.ecu = ''
        self.can_db = []
        self.render_rte = True
        self.render_stubs = True

        self._get_options(argv)

    def _get_options(self, argv):
        try:
            opts, args = getopt.getopt(argv, "hd", ["namespace=", "port_arxml=", "types_arxml=", "swc_arxml=", "ldc_name=", "swc_name=", "can_db=", "ecu="])
        except getopt.GetoptError as err:
            # print help information and exit:
            print(err) # will print something like "option -a not recognized"
            sys.exit(2)

        ### parse input command line
        for o, a in opts:
            if o == "-h":
                self._usage()
                sys.exit()
            if o == "-d":
                self.debug = True
            elif o == "--namespace":
                self.namespace = a
            elif o == "--port_arxml":
                self.port_arxml = a
            elif o == "--types_arxml":
                self.types_arxml = a
            elif o == "--swc_arxml":
                self.swc_arxml = a
            elif o == "--ldc_name":
                self.ldc_name = a
            elif o == "--swc_name":
                self.swc_name = a
            elif o == "--can_db":
                self.can_db.append(a)
            elif o == "--ecu":
                self.ecu = a
            else:
                print (o, a)
                assert False, "unhandled option"

        if self.swc_name == '':
            self.render_rte = False
            self.render_stubs = False

        if not self.validate_input_files():
            self._usage()
            sys.exit(2)

    def validate_input_files(self):
        """checking that all required files are populated with actual file names"""
        return self.port_arxml != '' and self.port_arxml != '' and \
               self.types_arxml != '' and self.swc_arxml != '' and \
               self.ldc_name != '' and self.ecu != ''

    def _usage(self):
        print('usage')

def main():
    optParser = OptParser(sys.argv[1:])

    ap = ArxmlParser.ArxmlParser()
    ap.parse(optParser.namespace, \
             optParser.swc_arxml, \
             optParser.port_arxml, \
             optParser.types_arxml)

    dp = DbcParser.DbcParser()
    for can_db in optParser.can_db:
        dp.parse(can_db, can_db.split('.')[0], optParser.ecu)

    if optParser.render_rte:
        rr = RteRenderer.RteRenderer('rte_data', optParser.ldc_name, optParser.swc_name)

    if optParser.render_stubs:
        sr = StubRenderer.StubRenderer('cunit_stubs', optParser.ldc_name, optParser.swc_name)

    cr = ComponentRenderer.ComponentRenderer(optParser.ldc_name)

    # find offset and scale from parsed can-db
    sv = SignalVisitor.SignalVisitor(dp.signal_dict)
    for port in ap.port_array:
        port.accept(sv)

    for port in ap.port_array:
        if optParser.render_rte:
            port.accept(rr)
        if optParser.render_stubs:
            port.accept(sr)
        port.accept(cr)
    
    for port in ap.cal_array:
        if optParser.render_rte:
            port.accept(rr)

if __name__ == '__main__':
    main()
