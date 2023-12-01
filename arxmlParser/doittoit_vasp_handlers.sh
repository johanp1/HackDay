#!/bin/bash

if python3 create_ports.py --port_arxml=../../vasp_classic/vasp_handlers/davinci/PortInterfaces.arxml\
						   --types_arxml=../../vasp_classic/vasp_handlers/davinci/DataTypes.arxml\
						   --swc_arxml=../../vasp_classic/vasp_handlers/davinci/ComponentTypes/DACU_Components_VASP.arxml\
						   --ldc_name=DACU_Components_VASP\
						   --ecu=VCM\
							--can_db=can/CAN01-T3_2.3.0-postfix.dbc\
						   --can_db=can/CAN02-T3_2.3.0-postfix.dbc\
						   --can_db=can/CAN03-T3_2.3.0-postfix.dbc\
						   --can_db=can/CAN04-T3_2.3.0-postfix.dbc\
						   --can_db=can/CAN05-T3_2.3.0-postfix.dbc\
						   --can_db=can/CAN06-T3_2.3.0-postfix.dbc\
						   --can_db=can/CAN32-T3_2.3.0.dbc\
						   --can_db=can/CAN20-T3.dbc\
						   --can_db=can/CAN21-T3.dbc\
						   --can_db=can/CAN23-T3.dbc; then
	echo "create_ports succeeded"
	
	cp out/DACU_Components_VASP.xml out/refDACU_Components_VASP.xml
	
    echo "patching with DacuVaspApp.xml"
	python3 patcher.py out/refDACU_Components_VASP.xml ../../vasp_classic/vasp/SW_C/autosar4/DacuVaspApp.xml out/temp.xml
	
	echo "patching with Vcm.xml"
	python3 patcher.py out/temp.xml arxml/Vcm.xml out/DACU_Components_VASP.xml
	
	cp out/DACU_Components_VASP.xml ../../vasp_classic/vasp_handlers/Adapt2/.
	rm out/temp*

	echo "number of stubbed signals before patching:"
	grep "Stub=\"true\"" out/refDACU_Components_VASP.xml |wc -l
	echo "number of stubbed signals after patching:"
	grep "Stub=\"true\"" out/DACU_Components_VASP.xml |wc -l
else
	echo "create_ports failed"
fi	
