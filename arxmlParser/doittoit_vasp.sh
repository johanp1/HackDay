#!/bin/bash

if python3 create_ports.py --port_arxml=../../comp_vasp/vasp/SW_C/davinci/PortInterfaces.arxml\
						   --types_arxml=../../comp_vasp/vasp/SW_C/davinci/DataTypes.arxml\
						   --swc_arxml=../../comp_vasp/vasp/SW_C/davinci/ComponentTypes/DacuVASPApp_Simulink_VASPComponentTypes.arxml\
						   --ldc_name=DacuVaspApp\
						   --ecu=VCM\
						   --can_db=can/CAN01-T3_1.9.0.dbc\
						   --can_db=can/CAN02-T3_1.9.0.dbc\
						   --can_db=can/CAN03-T3_1.9.0.dbc\
						   --can_db=can/CAN04-T3_1.9.0.dbc\
						   --can_db=can/CAN05-T3_1.9.0.dbc\
						   --can_db=can/CAN06-T3_1.9.0.dbc\
						   --can_db=can/CAN32-T3_1.9.0.dbc\
						   --can_db=can/CAN20-T3.dbc\
						   --can_db=can/CAN21-T3.dbc\
						   --can_db=can/CAN23-T3.dbc; then
	echo "create_ports succeeded"
	cp out/DacuVaspApp.xml out/refDacuVaspApp.xml 
	python3 patcher.py out/DacuVaspApp.xml ../../comp_vasp/Adapt2/Module.xml out/temp.xml
	python3 patcher.py out/temp.xml arxml/Vcm.xml out/temp2.xml


	mv out/temp2.xml out/DacuVaspApp.xml
	cp out/DacuVaspApp.xml ../../comp_vasp/Adapt2/.
	rm out/temp*

	echo "number of stubbed signals before patching:"
	grep "Stub=\"true\"" out/refDacuVaspApp.xml |wc -l
	echo "number of stubbed signals after patching:"
	grep "Stub=\"true\"" out/DacuVaspApp.xml |wc -l
else
	echo "create_ports failed"
fi	
