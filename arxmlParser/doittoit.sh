#!/bin/bash
function compare {
	if cmp -s $1 $2; then
		echo  $1 OK
	else
		diff $1 $2 | head
	fi
}

python3 port_test.py
python3 parser_test.py

if python3 create_ports.py --port_arxml=arxml/PortInterfaces.arxml\
						   --types_arxml=arxml/DataTypes.arxml\
						   --swc_arxml=arxml/StateEstimation.arxml\
						   --ldc_name=StateEstimationCtrl\
						   --swc_name=StateEstimation\
						   --ecu=VCM\
						   --can_db=can/CAN01-T3_1.9.0.dbc\
						   --can_db=can/CAN02-T3_1.9.0.dbc\
						   --can_db=can/CAN03-T3_1.9.0.dbc\
						   --can_db=can/CAN04-T3_1.9.0.dbc\
						   --can_db=can/CAN05-T3_1.9.0.dbc\
						   --can_db=can/CAN06-T3_1.9.0.dbc\
						   --can_db=can/CAN32-T3_1.9.0.dbc; then
	echo "create_ports succeeded"

	# get default values for parameters in the stubbed rte 
	python param_default.py arxml/StateEstimationCtrl.ldcxml out/cunit_stubs.h out/cunit_stubs_def.h 
	rm out/cunit_stubs.h
	mv out/cunit_stubs_def.h out/cunit_stubs.h

	# compare with saved references
	compare out/rte_data.h ref/rte_data.h
	compare out/StateEstimationCtrl.xml ref/StateEstimationCtrl.xml
	compare out/cunit_stubs.c ref/cunit_stubs.c
	compare out/cunit_stubs.h ref/cunit_stubs.h
else
	echo "create_ports failed"
fi	
