#--------------------------------------------------------------------------------------------------#
#
# @file    Makefile
# @author  morane
# @date    July, 2019
# @version 1
#
# This makefile defines how the unit tests for cxmath are built.
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
OBJ_DIR      = $(BIN_ROOT)/tests/unit
OUT_DIR      = $(BIN_ROOT)/tests/unit
INCLUDES     = -I$(SRC_ROOT)/cxmath -I$(SRC_ROOT)
LIBINCLUDES  = -L$(BIN_ROOT)/connectx/libs
VPATH        = unit

SRCS      = cxmathTest.cpp       \
            test_LineSegment.cpp \
            test_Point.cpp       \
            test_Vector.cpp

OBJS      = cxmathTest.o       \
            test_LineSegment.o \
            test_Point.o       \
            test_Vector.o

OBJS := $(addprefix $(OBJ_DIR)/,$(OBJS))

LIBS      = -lcxmath     \
            -lcxutil     \
            -lgtest      \
            -lgtest_main \
            -lpthread

# Product:
MAIN = cxmathTest.out

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
	touch $(OUT_DIR)/log/cxmathUnitTests.log

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

