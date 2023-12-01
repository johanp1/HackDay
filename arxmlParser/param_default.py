import xml.etree.ElementTree as ET
import sys

def main():
    input_ldcxml = sys.argv[1]
    source_file = sys.argv[2]
    param_dict = {}
    out_file = sys.argv[3]

    tree = ET.parse(input_ldcxml)
    root = tree.getroot()

    # first create dictionary with all parameter and default values
    tag = 'Parameter'
    for parameter in root.iter(tag):
        doid = parameter.attrib['Name']
        default_value = ', '.join(parameter.attrib['Value'].split(' '))
        param_dict[doid] = default_value

    #assign default values to generated file
    f_hdlr = open(source_file, 'r', encoding="utf-8")
    out_hdlr = open(out_file, 'w', encoding="utf-8")
    lines = f_hdlr.readlines()

    for line in lines:
        if line.find('/*P') != -1 or line.find('/*X') != -1:
            doid = line.split('/*')[1].split('_')[0]

            if doid in param_dict:
                if len(line.split(' ')) == 2:
                    line = line.replace('0,', param_dict[doid] + ',')

                else:
                    replacee = line.split('},')
                    replacee[0] = '{' + param_dict[doid] + '}'
                    line = '\t' + ', '.join(replacee)

        out_hdlr.write(line)

if __name__ == '__main__':
    main()
