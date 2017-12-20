#--------------------------------------------------------------------------------------------------#
#
# @file    Makefile
# @author  Eric Poirier
# @date    March 2017
# @version 1
#
# This makefile defines the build process for the entire Connect X project. Every part is
# built from a submakefile using recursive make calls. More precisely, this makefile:
#
#    1. Builds libcXbase.a
#    2. Builds AND RUNS all unit tests on libcXbase.a
#    3. Builds the libcXbase.a Doxygen documentation.
#    4. Builds the C++ programming norm documentation.
#
# To use this makefile, you need at least these tools installed on your
# machine:
#
#    1. GNU make (tested with)
#    2. gcc compiler (g++ is used)
#    3. Google test
#    4. Python
#    5. Doxygen
#    6. TeXLive
#    7. Latexmke
#
#--------------------------------------------------------------------------------------------------#


include init.mk

TESTS_RUNNER            = $(SRC_ROOT)/cxscripts/python/RunUnitTests.py

CXUTIL_UNIT_TESTS_EXEC  = -t $(BIN_ROOT)/tests/unit/cxutilTest.out
CXBASE_UNIT_TESTS_EXEC  = -t $(BIN_ROOT)/tests/unit/cxbaseTest.out

CXUTIL_UNIT_TESTS_LOG   = -l $(BIN_ROOT)/tests/unit/log/cxutilUnitTests.log
CXBASE_UNIT_TESTS_LOG   = -l $(BIN_ROOT)/tests/unit/log/cxbaseUnitTests.log


MAIN     = connectx
TARGETS  += cxutil     \
            cxutiltest \
            cxbase     \
            cxbasetest \
            cxutildoc  \
            cxbasedoc  \
            cxcppnorm

.PHONY: cxutil cxbase

all: $(MAIN)

$(MAIN): $(TARGETS)

cxutil:
	$(MAKE) -C cxutil

cxutiltest:
	$(MAKE) -C cxutil/test
	python $(TESTS_RUNNER) $(CXUTIL_UNIT_TESTS_EXEC) $(CXUTIL_UNIT_TESTS_LOG)

cxbase:
	$(MAKE) -C cxbase

cxbasetest:
	$(MAKE) -C cxbase/test
	python $(TESTS_RUNNER) $(CXBASE_UNIT_TESTS_EXEC) $(CXBASE_UNIT_TESTS_LOG)

cxutildoc:
	$(MAKE) -C cxutil/doc

cxbasedoc:
	$(MAKE) -C cxbase/doc

cxcppnorm:
	$(MAKE) -C cx_cpp_norme

mrproper:
	@echo Cleaning ConnectX...
	cd cxutil && make mrproper
	cd cxutil/test && mrproper
	cd cxbase && make mrproper
	cd cxbase/test && make mrproper
	cd cxutil/doc && make mrproper
	cd cXbase/doc && make mrproper
	cd cx_cpp_norme && make mrproper
	@echo ConnectX cleaned!

clean:
	@echo Removing object files...
	cd cxutil && make clean
	cd cxutil/test && make clean
	cd cxbase && make clean
	cd cxbase/test && make clean
	cd cxutil/doc && make clean
	cd cxbase/doc && make clean
	cd cx_cpp_norme && make clean
	@echo Object files removed!
