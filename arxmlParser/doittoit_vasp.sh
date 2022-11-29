#!/bin/bash
cp ../../comp_vasp/vasp/SW_C/davinci/ComponentTypes/DacuVASPApp_Simulink_VASPComponentTypes.arxml arxml/DacuVASPApp_Simulink_VASPComponentTypes.arxml
cp ../../comp_vasp/vasp/SW_C/davinci/PortInterfaces.arxml arxml/PortInterfacesVasp.arxml
cp ../../comp_vasp/vasp/SW_C/davinci/DataTypes.arxml arxml/DataTypesVasp.arxml

python3 create_ports_vasp.py
cp out/DacuVaspApp.xml out/refDacuVaspApp.xml 
python3 patcher.py out/DacuVaspApp.xml arxml/Module.xml out/temp.xml
python3 patcher.py out/temp.xml arxml/Vcm.xml out/temp2.xml

mv out/temp2.xml out/DacuVaspApp.xml
cp out/DacuVaspApp.xml ../../comp_vasp/Adapt2/.
rm out/temp*

echo "number of stubbed signals:"
grep -i -n "stub" out/DacuVaspApp.xml |wc -l
