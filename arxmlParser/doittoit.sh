#!/bin/bash
python3 port_test.py
python3 create_ports.py
diff Se_rteData.h ref/Se_rteData.h
diff StateEstimationCtrl.xml ref/StateEstimationCtrl.xml
diff cunit_se_stubs.c ref/cunit_se_stubs.c
diff cunit_se_stubs.h ref/cunit_se_stubs.h