#--------------------------------------------------------------------------------------------------#
#
# @file    Makefile
# @author  morane
# @date    December, 2017
# @version 1
#
# This makefile defines how the unit tests for cxgui are built.
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
OBJ_DIR       = $(BIN_ROOT)/tests/unit
OUT_DIR       = $(BIN_ROOT)/tests/unit
INCLUDES      = -I$(SRC_ROOT)
LIBS_INCLUDE  = -L$(BIN_ROOT)/connectx/libs
VPATH         = unit

SRCS      = cxguiTest.cpp           \
            test_RAIICairoPath.cpp

OBJS      = cxguiTest.o           \
            test_RAIICairoPath.o

OBJS := $(addprefix $(OBJ_DIR)/,$(OBJS))

LIBS      = -lcxutil     \
            -lcxbase     \
            -lcxgui      \
            -lgtest      \
            -lgtest_main \
            -lpthread

# Product:
MAIN = cxguiTest.out

all: make_dir make_log $(MAIN)

$(MAIN): $(OBJS)
	@echo Invoquing GCC...
	$(CPPC) $(LIBS_INCLUDE) $(INCLUDES) -o $(OUT_DIR)/$(MAIN) $(OBJS) $(LIBS) `pkg-config gtkmm-3.0 --libs`
	@echo $(MAIN) has been compiled and linked!

$(OBJ_DIR)/%.o: %.cpp
	@echo Invoquing GCC...
	$(CPPC) $(CPPFLAGS) $(INCLUDES) `pkg-config gtkmm-3.0 --cflags` -c $< -o $@
	@echo Object files created!

make_dir:
	mkdir -p $(OBJ_DIR)
	mkdir -p $(OUT_DIR)

make_log:
	mkdir -p $(OUT_DIR)/log
	touch $(OUT_DIR)/log/cxguiUnitTests.log

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

