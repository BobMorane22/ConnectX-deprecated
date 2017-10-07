#--------------------------------------------------------------------------------------------------#
#
# @file    Makefile
# @author  Eric Poirier
# @date    April 2017
# @version 1
#
# This makefile defines how the cxbase library example code is built.
#
# To use this makefile, you need at least these tools installed on your
# machine:
#
#    1. GNU make (tested with)
#    2. gcc compiler (g++ is used)
#    3. cxbase library
#
#--------------------------------------------------------------------------------------------------#


include $(CX_SRC_ROOT)/init.mk

CPPFLAGS = $(OPT_FLAGS) $(DEBUG_FLAGS) $(STANDARD_FLAGS) \
           $(WARN_AS_ERRORS_FLAGS)

# Source files, headers, etc.:
MAKEFILE_LOC = $(CX_SRC_ROOT)/cxbase/doc/doxygen/examples
OBJ_DIR      = $(CX_SRC_ROOT)/cxbase/doc/doxygen/examples/out
OUT_DIR      = $(CX_SRC_ROOT)/cxbase/doc/doxygen/examples/out
INCLUDES     = -I$(CX_SRC_ROOT)/cxbase/include\
               -I$(CX_SRC_ROOT)
LIBINCLUDES  = -L$(CX_BUILD_ROOT)/connectx/libs
VPATH        = examples

SRCS      = main.cpp

OBJS      = main.o

OBJS     := $(addprefix $(OBJ_DIR)/,$(OBJS))

LIBS      = -lcxbase\
            -lcxutil

# Product:
MAIN = connect4-nw.out # Connect X, no window version

all: $(MAIN)
	@echo $(MAIN) has been compiled and linked!

$(MAIN): $(OBJS)
	@echo Invoquing GCC...
	g++ $(CPPFLAGS) $(LIBINCLUDES) -o $(OUT_DIR)/$(MAIN) $(OBJS) $(LIBS)
	@echo $(MAIN) created!

$(OBJ_DIR)/%.o: %.cpp
	@echo Invoquing GCC...
	$(CPPC) $(CPPFLAGS) $(INCLUDES) -c $< -o $@
	@echo Object files created!

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
