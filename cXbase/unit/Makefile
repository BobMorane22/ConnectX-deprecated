#--------------------------------------------------------------------------------------------------#
#
# @file    Makefile
# @author  Eric Poirier
# @date    March 2017
# @version 1
#
# This makefile defines how the unit tests for cXbase are built.
#
# To use this makefile, you need at least these tools installed on your
# machine:
#
#    1. GNU make (tested with)
#    2. gcc compiler (g++ is used)
#    3. Google Tests
#
#--------------------------------------------------------------------------------------------------#

# Compiler:
CPPFLAGS = $(OPT_FLAGS) $(DEBUG_FLAGS) $(STANDARD_FLAGS) \
           $(WARN_AS_ERRORS_FLAGS)

# Source files, headers, etc.:
OBJ_DIR      = $(CX_BUILD_ROOT)/tests/unit
OUT_DIR      = $(CX_BUILD_ROOT)/tests/unit
INCLUDES     = -I$(CX_SRC_ROOT)/cXbase
LIBINCLUDES  = -L$(CX_BUILD_ROOT)/connectx/libs
VPATH        = tests

SRCS      = cxUnitTests.cpp\
            test_Player.cpp\
            test_Name.cpp\
            test_Game.cpp\
            test_GameBoard.cpp\
            test_Disc.cpp\
            test_Color.cpp\
            test_AsciiColorCode.cpp\

OBJS      = test_Player.o\
            test_Name.o\
            test_Game.o\
            test_GameBoard.o\
            test_Disc.o\
            test_Color.o\
            test_AsciiColorCode.o\
            
OBJS := $(addprefix $(OBJ_DIR)/,$(OBJS))

LIBS      = -lgtest\
            -lgtest_main\
            -lpthread\
            -lcXbase
 
# Product:
MAIN = cxUnitTests.out


all: make_dir make_log $(MAIN)

$(MAIN): $(OBJS)
	@echo Invoquing GCC...
	$(CPPC) $(LIBINCLUDES) -o $(OUT_DIR)/$(MAIN) $(OBJS) $(LIBS)
	@echo $(MAIN) has been compiled and linked!

$(OBJ_DIR)/%.o: %.cpp
	@echo Invoquing GCC...
	$(CPPC) $(CPPFLAGS) $(INCLUDES) -c $< -o $@
	@echo Object files created!

make_dir:
	mkdir -p $(OBJ_DIR)
	mkdir -p $(OUT_DIR)

make_log:
	mkdir -p $(OUT_DIR)/log
	touch $(OUT_DIR)/log/unitTests.log

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
