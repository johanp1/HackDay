#!/bin/bash

if python3 create_ports.py --port_arxml=../../comp_vasp_handlers/davinci/PortInterfaces.arxml\
						   --types_arxml=../../comp_vasp_handlers/davinci/DataTypes.arxml\
						   --swc_arxml=../../comp_vasp_handlers/davinci/ComponentTypes/DACU_Components_VASP.arxml\
						   --ldc_name=DACU_Components_VASP\
						   --ecu=VCM; then
	echo "create_ports succeeded"
	
	cp out/DACU_Components_VASP.xml out/refDACU_Components_VASP.xml
	python3 patcher.py out/refDACU_Components_VASP.xml ../../comp_vasp_handlers/Adapt2/Module.xml out/DACU_Components_VASP.xml
	
	cp out/DACU_Components_VASP.xml ../../comp_vasp_handlers/Adapt2/.
	
	echo "number of stubbed signals before patching:"
	grep "Stub=\"true\"" out/refDACU_Components_VASP.xml |wc -l
	echo "number of stubbed signals after patching:"
	grep "Stub=\"true\"" out/DACU_Components_VASP.xml |wc -l
else
	echo "create_ports failed"
fi	
