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

CXINV_UNIT_TESTS_EXEC   = -t $(BIN_ROOT)/tests/unit/cxinvTest.out
CXUTIL_UNIT_TESTS_EXEC  = -t $(BIN_ROOT)/tests/unit/cxutilTest.out
CXMATH_UNIT_TESTS_EXEC  = -t $(BIN_ROOT)/tests/unit/cxmathTest.out
CXLOG_UNIT_TESTS_EXEC   = -t $(BIN_ROOT)/tests/unit/cxlogTest.out
CXCMD_UNIT_TESTS_EXEC   = -t $(BIN_ROOT)/tests/unit/cxcmdTest.out
CXBASE_UNIT_TESTS_EXEC  = -t $(BIN_ROOT)/tests/unit/cxbaseTest.out
CXGUI_UNIT_TESTS_EXEC   = -t $(BIN_ROOT)/tests/unit/cxguiTest.out
CXEXEC_UNIT_TESTS_EXEC  = -t $(BIN_ROOT)/tests/unit/cxexecTest.out

CXINV_UNIT_TESTS_LOG    = -l $(BIN_ROOT)/tests/unit/log/cxinvUnitTests.log
CXUTIL_UNIT_TESTS_LOG   = -l $(BIN_ROOT)/tests/unit/log/cxutilUnitTests.log
CXMATH_UNIT_TESTS_LOG   = -l $(BIN_ROOT)/tests/unit/log/cxmathUnitTests.log
CXLOG_UNIT_TESTS_LOG    = -l $(BIN_ROOT)/tests/unit/log/cxlogUnitTests.log
CXCMD_UNIT_TESTS_LOG    = -l $(BIN_ROOT)/tests/unit/log/cxcmdUnitTests.log
CXBASE_UNIT_TESTS_LOG   = -l $(BIN_ROOT)/tests/unit/log/cxbaseUnitTests.log
CXGUI_UNIT_TESTS_LOG    = -l $(BIN_ROOT)/tests/unit/log/cxguiUnitTests.log
CXEXEC_UNIT_TESTS_LOG   = -l $(BIN_ROOT)/tests/unit/log/cxexecUnitTests.log


MAIN     = connectx


# Missing cxinvtest
TARGETS  += cxinv      \
            cxinvtest  \
            cxinvdoc   \
            cxutil     \
            cxutiltest \
            cxutildoc  \
            cxmath     \
            cxmathtest \
            cxmathdoc  \
            cxlog      \
            cxlogtest  \
            cxlogdoc   \
            cxcmd      \
            cxcmdtest  \
            cxcmddoc   \
            cxbase     \
            cxbasetest \
            cxbasedoc  \
            cxgui      \
            cxguitest  \
            cxguidoc   \
            cxexec     \
            cxexectest \
            cxexecdoc  \
            cxmain     \
            cxdoc


.PHONY:  cxinv cxmath cxlog cxcmd cxutil cxbase cxgui cxexec cxmain cxdoc

all: $(MAIN)

$(MAIN): $(TARGETS)

cxinv:
	$(MAKE) -C cxinv

cxinvtest:
	$(MAKE) -C cxinv/test
	python $(TESTS_RUNNER) $(CXINV_UNIT_TESTS_EXEC) $(CXINV_UNIT_TESTS_LOG)

cxinvdoc:
	$(MAKE) -C cxinv/doc

cxutil:
	$(MAKE) -C cxutil

cxutiltest:
	$(MAKE) -C cxutil/test
	python $(TESTS_RUNNER) $(CXUTIL_UNIT_TESTS_EXEC) $(CXUTIL_UNIT_TESTS_LOG)

cxutildoc:
	$(MAKE) -C cxutil/doc

cxmath:
	$(MAKE) -C cxmath

cxmathtest:
	$(MAKE) -C cxmath/test
	python $(TESTS_RUNNER) $(CXMATH_UNIT_TESTS_EXEC) $(CXMATH_UNIT_TESTS_LOG)

cxmathdoc:
	$(MAKE) -C cxmath/doc

cxlog:
	$(MAKE) -C cxlog

cxlogtest:
	$(MAKE) -C cxlog/test
	python $(TESTS_RUNNER) $(CXLOG_UNIT_TESTS_EXEC) $(CXLOG_UNIT_TESTS_LOG)

cxlogdoc:
	$(MAKE) -C cxlog/doc

cxcmd:
	$(MAKE) -C cxcmd

cxcmdtest:
	$(MAKE) -C cxcmd/test
	python $(TESTS_RUNNER) $(CXCMD_UNIT_TESTS_EXEC) $(CXCMD_UNIT_TESTS_LOG)

cxcmddoc:
	$(MAKE) -C cxcmd/doc

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

cxdoc:
	$(MAKE) -C cxdoc

mrproper:
	@echo Purging Connect X...
	$(MAKE) mrproper -C cxinv
	$(MAKE) mrproper -C cxinv/test
	$(MAKE) mrproper -C cxinv/doc
	$(MAKE) mrproper -C cxutil
	$(MAKE) mrproper -C cxutil/test
	$(MAKE) mrproper -C cxutil/doc
	$(MAKE) mrproper -C cxmath
	$(MAKE) mrproper -C cxmath/test
	$(MAKE) mrproper -C cxmath/doc
	$(MAKE) mrproper -C cxlog
	$(MAKE) mrproper -C cxlog/test
	$(MAKE) mrproper -C cxlog/doc
	$(MAKE) mrproper -C cxcmd
	$(MAKE) mrproper -C cxcmd/test
	$(MAKE) mrproper -C cxcmd/doc
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
	$(MAKE) mrproper -C cxdoc
	@echo Connect X purged!

clean:
	@echo Cleaning Connect X...
	$(MAKE) clean -C cxinv
	$(MAKE) clean -C cxinv/test
	$(MAKE) clean -C cxinv/doc
	$(MAKE) clean -C cxutil
	$(MAKE) clean -C cxutil/test
	$(MAKE) clean -C cxutil/doc
	$(MAKE) clean -C cxmath
	$(MAKE) clean -C cxmath/test
	$(MAKE) clean -C cxmath/doc
	$(MAKE) clean -C cxlog
	$(MAKE) clean -C cxlog/test
	$(MAKE) clean -C cxlog/doc
	$(MAKE) clean -C cxcmd
	$(MAKE) clean -C cxcmd/test
	$(MAKE) clean -C cxcmd/doc
	$(MAKE) clean -C cxbase
	$(MAKE) clean -C cxbase/test
	$(MAKE) clean -C cxbase/doc
	$(MAKE) clean -C cxgui
	$(MAKE) clean -C cxgui/test
	$(MAKE) clean -C cxgui/doc
	$(MAKE) clean -C cxexec
	$(MAKE) clean -C cxexec/test
	$(MAKE) clean -C cxexec/doc
	$(MAKE) clean -C cxmain
	$(MAKE) clean -C cxdoc
	@echo Connect X cleaned!
