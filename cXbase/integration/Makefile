#--------------------------------------------------------------------------------------------------#
#
# @file    Makefile
# @author  Eric Poirier
# @date    April 2017
# @version 1
#
# This makefile defines how the integration tests for cXbase are built.
#
# To use this makefile, you need at least these tools installed on your
# machine:
#
#    1. GNU make (tested with)
#    2. gcc compiler (g++ is used)
#    3. cxbase library
#
#--------------------------------------------------------------------------------------------------#


CPPFLAGS = $(OPT_FLAGS) $(DEBUG_FLAGS) $(STANDARD_FLAGS) \
           $(WARN_AS_ERRORS_FLAGS)

# Source files, headers, etc.:
MAKEFILE_LOC = $(CX_SRC_ROOT)/cXbase/integration
OBJ_DIR      = $(CX_BUILD_ROOT)/tests/integration
OUT_DIR      = $(CX_BUILD_ROOT)/tests/integration
INCLUDES     = -I$(CX_SRC_ROOT)/cXbase/publicAPI
LIBINCLUDES  = -L$(CX_BUILD_ROOT)/connectx/libs
VPATH        = integration

SRCS      = main.cpp

OBJS      = main.o

OBJS := $(addprefix $(OBJ_DIR)/,$(OBJS))

LIBS      = -lcXbase

# Product:
MAIN = connect4-nw.out # Connect X, no window version

all: make_dir $(MAIN) doc
	@echo $(MAIN) has been compiled and linked!

$(MAIN): $(OBJS)
	@echo Invoquing GCC...
	$(CPPC) $(LIBINCLUDES) -o $(OUT_DIR)/$(MAIN) $(OBJS) $(LIBS)
	@echo $(MAIN) created!

$(OBJ_DIR)/%.o: %.cpp
	@echo Invoquing GCC...
	$(CPPC) $(CPPFLAGS) $(INCLUDES) -c $< -o $@
	@echo Object files created!

make_dir:
	mkdir -p $(OBJ_DIR)
	mkdir -p $(OUT_DIR)

doc:
	@echo Copying documentation files...
	python ../../cxPythonTools/CreateCopy.py main.cpp ../doc/doxygen/examples/
	python ../../cxPythonTools/CreateCopy.py Connect4Game.h ../doc/doxygen/examples/
	python ../../cxPythonTools/CreateCopy.py output_tie ../doc/doxygen/examples/
	python ../../cxPythonTools/CreateCopy.py output_win ../doc/doxygen/examples/
	@echo documentation files created!

clean:
	@echo Removing object files...
	$(RM) $(OBJ_DIR)/*.o
	@echo Object files removed!

mrproper: clean
	@echo Cleaning project...
	$(RM) $(OUT_DIR)/$(MAIN)
	@echo Project cleaned!

depend: $(SRCS)
	@echo Finding dependencies...
	makedepend $(INCLUDES) $^
	@echo Dependencies found!
