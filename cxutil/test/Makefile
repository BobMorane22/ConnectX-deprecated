#--------------------------------------------------------------------------------------------------#
#
# @file    Makefile
# @author  Éric Poirier
# @date    July, 2017
# @version 1
#
# This makefile defines how the unit tests for cxutil are built.
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
INCLUDES     = -I$(SRC_ROOT)
LIBINCLUDES  = -L$(BIN_ROOT)/connectx/libs
VPATH        = unit

SRCS      = cxutilTest.cpp       \
            test_Color.cpp       \
            test_Date.cpp        \
            test_ISubject.cpp    \
            test_LineSegment.cpp \
            test_Logger.cpp      \
            test_Name.cpp        \
            test_narrow_cast.cpp \
            test_Point.cpp       \
            test_ReturnCode.cpp  \
            test_Time.cpp        \
            test_Vector.cpp

OBJS      = test_Date.o        \
            test_Color.o       \
            test_ISubject.o    \
            test_LineSegment.o \
            test_Logger.o      \
            test_Name.o        \
            test_Point.o       \
            test_narrow_cast.o \
            test_ReturnCode.o  \
            test_Time.o        \
            test_Vector.o

OBJS := $(addprefix $(OBJ_DIR)/,$(OBJS))

LIBS      = -lgtest      \
            -lgtest_main \
            -lpthread    \
            -lcxutil

# Product:
MAIN = cxutilTest.out

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
	touch $(OUT_DIR)/log/cxutilUnitTests.log

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

