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

export ROOT_DIR = $(CURDIR)

SHELL := /bin/bash
TESTS_RUNNER            = $(ROOT_DIR)/cxPythonTools/RunUnitTests.py
CXBASE_UNIT_TESTS_EXEC  = -t $(ROOT_DIR)/cXbase/unit/cxUnitTests
CXBASE_UNIT_TESTS_LOG   = -l $(ROOT_DIR)/cXbase/unit/log/unitTests.log

MAIN     = connectx
TARGETS  += cxbase \
            cxbaseunit \
            cxbasedoc \
            cxcppnorm

all: $(MAIN)

$(MAIN): $(TARGETS)

cxbase:
	$(MAKE) -C cXbase

cxbaseunit:
	$(MAKE) -C cXbase/unit
	$(shell $(TESTS_RUNNER) $(CXBASE_UNIT_TESTS_EXEC) $(CXBASE_UNIT_TESTS_LOG) > /dev/null 2>&1)

cxbasedoc:
	$(MAKE) -C cXbase/doc

cxcppnorm:
	$(MAKE) -C cx_cpp_norme

mrproper:
	@echo Cleaning ConnectX...
	cd cXbase && make mrproper
	cd cXbase/doc && make mrproper
	cd cXbase/unit && make mrproper
	cd cx_cpp_norme && make mrproper
	@echo ConnectX cleaned!

clean:
	@echo Removing object files...
	cd cXbase && make clean
	cd cXbase/doc && make clean
	cd cXbase/unit && make clean
	cd cx_cpp_norme && make clean
	@echo Object files removed!
