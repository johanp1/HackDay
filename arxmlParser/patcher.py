#! /usr/bin/python

import xml.etree.ElementTree as ET
import sys

_ignore_list = []

def _matching_name(ref_port, port):
    return ref_port.attrib['Name'] not in _ignore_list \
        and ref_port.attrib['Name'] == port.attrib['Name']

def _unstub(ref_p, p):
    # found in reference, we can "de-stub" it
    if 'Stub' in p.attrib:
        p.attrib.pop('Stub','') # remove attribute from dictionary

    # do not eveluate port with this name again for this reference
    _ignore_list.append(ref_p.attrib['Name'])
    #print('adding ' + p.attrib['Name'] + ' to ignore list')

def patch(port, ref_tree):
    """Patch the component-xml, removing stub etc"""
    root = ref_tree.getroot()

    ns = {'default_ns': 'http://schemas.volvo.com/gtt/adapt/ModuleConfig'}

    component_tag = '{' + ns['default_ns']+ '}' + 'Component'
    for ref_component in root.iter(component_tag):
        port_tag = '{' + ns['default_ns']+ '}' + 'Port'

        #loop each port in ref-component looking for the patchee-port
        for ref_port in ref_component.iter(port_tag):
            if _matching_name(ref_port, port):
                #if signal name differ, take the reference's signal name
                if 'Signal' in ref_port.attrib and 'Signal' in port.attrib and ref_port.attrib['Direction'] == port.attrib['Direction']:
                    if ref_port.attrib['Signal'] != port.attrib['Signal']:
                        print(ref_port.attrib['Name'] + ' different signal names: ' + ref_port.attrib['Signal'] + ' != ' + port.attrib['Signal'])
                        #port.attrib['Signal'] = ref_port.attrib['Signal']

                if ref_port.attrib['Direction'] == 'Receive' and port.attrib['Direction'] == 'Receive':
                    # if the reference-port contains SenderComponent, lets steal it
                    if 'SenderComponent' in ref_port.attrib:
                        port.attrib['SenderComponent'] = ref_port.attrib['SenderComponent']
                        port.attrib['SenderPort'] = ref_port.attrib['SenderPort']

                # if patchee-port receives from reference component/port
                if ref_port.attrib['Direction'] == 'Send' and port.attrib['Direction'] == 'Receive':
                    port.attrib['SenderComponent'] = ref_component.attrib['Name']
                    port.attrib['SenderPort'] = ref_port.attrib['Name']

                #port found in ref, un-stub
                _unstub(ref_port, port)

def main():
    """CLI entrypoint"""
    ref_tree = ET.parse(sys.argv[2])
    tree = ET.parse(sys.argv[1])
 
    root = tree.getroot()

    for port in root.iter('Port'):
        patch(port, ref_tree)

    tree.write(sys.argv[3])


if __name__ == '__main__':
   main()
