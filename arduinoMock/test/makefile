#---------
#
# CppUTest Examples Makefile
#
#----------

#Set this to @ to keep the makefile quiet
ifndef SILENCE
	SILENCE = @
endif

#--- Inputs ----#
COMPONENT_NAME = ArduinoMockTests
CPPUTEST_HOME = /usr/local/cpputest-3.7dev

CPPUTEST_USE_EXTENSIONS = Y
CPPUTEST_PEDANTIC_ERRORS = N
CPP_PLATFORM = Gcc -std=c++11

# This line is overriding the default new macros.  This is helpful
# when using std library includes like <list> and other containers
# so that memory leak detection does not conflict with stl.
#CPPUTEST_MEMLEAK_DETECTOR_NEW_MACRO_FILE = -include ApplicationLib/ExamplesNewOverrides.h
SRC_DIRS = \
	..\

TEST_SRC_DIRS = \
	.

INCLUDE_DIRS =\
  .\
  ..\
  $(CPPUTEST_HOME)/include/CppUTest\
  
  
include $(CPPUTEST_HOME)/build/MakefileWorker.mk


