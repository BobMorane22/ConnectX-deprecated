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
#    8. Gtkmm3
#
#--------------------------------------------------------------------------------------------------#


include init.mk

TESTS_RUNNER            = $(SRC_ROOT)/cxscripts/python/RunUnitTests.py

CXUTIL_UNIT_TESTS_EXEC  = -t $(BIN_ROOT)/tests/unit/cxutilTest.out
CXBASE_UNIT_TESTS_EXEC  = -t $(BIN_ROOT)/tests/unit/cxbaseTest.out
CXGUI_UNIT_TESTS_EXEC   = -t $(BIN_ROOT)/tests/unit/cxguiTest.out
CXEXEC_UNIT_TESTS_EXEC      = -t $(BIN_ROOT)/tests/unit/cxexecTest.out

CXUTIL_UNIT_TESTS_LOG   = -l $(BIN_ROOT)/tests/unit/log/cxutilUnitTests.log
CXBASE_UNIT_TESTS_LOG   = -l $(BIN_ROOT)/tests/unit/log/cxbaseUnitTests.log
CXGUI_UNIT_TESTS_LOG    = -l $(BIN_ROOT)/tests/unit/log/cxguiUnitTests.log
CXEXEC_UNIT_TESTS_LOG       = -l $(BIN_ROOT)/tests/unit/log/cxexecUnitTests.log


MAIN     = connectx

TARGETS  += cxutil     \
            cxutiltest \
            cxutildoc  \
            cxbase     \
            cxbasetest \
            cxbasedoc  \
            cxgui      \
            cxguitest  \
            cxguidoc   \
            cxexec     \
            cxexectest \
            cxexecdoc  \
            cxcppnorm


.PHONY: cxutil cxbase cxgui cxexec cxmain

all: $(MAIN)

$(MAIN): $(TARGETS)

cxutil:
	$(MAKE) -C cxutil

cxutiltest:
	$(MAKE) -C cxutil/test
	python $(TESTS_RUNNER) $(CXUTIL_UNIT_TESTS_EXEC) $(CXUTIL_UNIT_TESTS_LOG)

cxutildoc:
	$(MAKE) -C cxutil/doc

cxbase:
	$(MAKE) -C cxbase

cxbasetest:
	$(MAKE) -C cxbase/test
	python $(TESTS_RUNNER) $(CXBASE_UNIT_TESTS_EXEC) $(CXBASE_UNIT_TESTS_LOG)

cxbasedoc:
	$(MAKE) -C cxbase/doc

cxgui:
	$(MAKE) -C cxgui

cxguitest:
	$(MAKE) -C cxgui/test
	python $(TESTS_RUNNER) $(CXGUI_UNIT_TESTS_EXEC) $(CXGUI_UNIT_TESTS_LOG)

cxguidoc:
	$(MAKE) -C cxgui/doc

cxexec:
	$(MAKE) -C cxexec

cxexectest:
	$(MAKE) -C cxexec/test
	python $(TESTS_RUNNER) $(CXEXEC_UNIT_TESTS_EXEC) $(CXEXEC_UNIT_TESTS_LOG)

cxexecdoc:
	$(MAKE) -C cxexec/doc

cxmain:
	$(MAKE) -C cxmain

cxcppnorm:
	$(MAKE) -C cx_cpp_norme

mrproper:
	@echo Cleaning Connect X...
	$(MAKE) mrproper -C cxutil
	$(MAKE) mrproper -C cxutil/test
	$(MAKE) mrproper -C cxutil/doc
	$(MAKE) mrproper -C cxbase
	$(MAKE) mrproper -C cxbase/test
	$(MAKE) mrproper -C cxbase/doc
	$(MAKE) mrproper -C cxgui
	$(MAKE) mrproper -C cxgui/test
	$(MAKE) mrproper -C cxgui/doc
	$(MAKE) mrproper -C cxexec
	$(MAKE) mrproper -C cxexec/test
	$(MAKE) mrproper -C cxexec/doc
	$(MAKE) mrproper -C cxmain
	$(MAKE) mrproper -C cx_cpp_norme
	@echo ConnectX cleaned!

clean:
	@echo Removing object files...
	$(MAKE) clean -C cxutil
	$(MAKE) clean -C cxutil/test
	$(MAKE) clean -C cxutil/doc
	$(MAKE) clean -C cxbase
	$(MAKE) clean -C cxbase/test
	$(MAKE) clean -C cxbase/doc
	$(MAKE) clean -C cxgui/test
	$(MAKE) clean -C cxgui/doc
	$(MAKE) clean -C cxexec
	$(MAKE) clean -C cxexec/test
	$(MAKE) clean -C cxexec/doc
	$(MAKE) mrproper -C cxmain
	$(MAKE) clean -C cx_cpp_norme
	@echo Object files removed!
