#! /usr/bin/python

import sys
import getopt
import xml.etree.ElementTree as ET

def usage():
    print 'usage luber.py --input=<in-file> --debug=[01]'

def update(tree, parName, value):
    """update parameter in xml-tree"""
    root = tree.getroot()

    for param in root.iter('parameter'):
        if param.attrib['name'] == parName:
            param.attrib['value'] = str(value)
            break

def main():
    paramDict = {}
    debug = 0
    in_file = ''

    try:
        opts, args = getopt.getopt(sys.argv[1:], "h", ["input=", "debug="])
    except getopt.GetoptError as err:
        # print help information and exit:
        print(err) # will print something like "option -a not recognized"
        sys.exit(2)

    for o, a in opts:
        if o == "-h":
            usage()
            sys.exit()
        elif o == "--input":
            in_file = a
        elif o == "--debug":
            debug = a
        else:
            print o
            assert False, "unhandled option"

    tree = ET.parse('luber.xml')
    root = tree.getroot()

    for param in root.iter('parameter'):
        print param.attrib['name'], param.attrib['value'] 
        paramDict[param.attrib['name']] = int(param.attrib['value'])

    update(tree, 'totalDistance', paramDict['totalDistance']+1)

    tree.write('luber.xml')

if __name__ == '__main__':
   main()