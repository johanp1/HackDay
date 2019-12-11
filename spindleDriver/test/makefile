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
COMPONENT_NAME = spindleDriverTests
CPPUTEST_HOME = /usr/local/cpputest-3.7dev
SIMPLEMOTION_HOME = /home/johan/git_clones/SimpleMotionV2

CPPUTEST_USE_EXTENSIONS = Y
CPPUTEST_PEDANTIC_ERRORS = N
CPP_PLATFORM = Gcc -std=c++11

#CXXFLAGS = -L../lib
#LIBS = simpleMotion.a -lpthread
#LDFLAGS = -L../lib -llibsimplemotionv2.a

# This line is overriding the default new macros.  This is helpful
# when using std library includes like <list> and other containers
# so that memory leak detection does not conflict with stl.
#CPPUTEST_MEMLEAK_DETECTOR_NEW_MACRO_FILE = -include ApplicationLib/ExamplesNewOverrides.h
SRC_DIRS = \
	.. \
	$(SIMPLEMOTION_HOME)

TEST_SRC_DIRS = \
	.

INCLUDE_DIRS =\
  .\
  ..\
  $(CPPUTEST_HOME)/include/CppUTest\
  $(SIMPLEMOTION_HOME) \
  $(SIMPLEMOTION_HOME)/utils

include $(CPPUTEST_HOME)/build/MakefileWorker.mk


