#--------------------------------------------------------------------------------------------------#
#
# @file    Makefile
# @author  morane
# @date    June, 2019
# @version 1
#
# This makefile defines how cxinv should be built. The following
# build step is done from here:
#
#    1. Build libcxinv.a
#
# To use this makefile, you need at least these tools installed on your
# machine:
#
#    1. GNU make (tested with)
#    2. gcc compiler (g++ is used)
#
#--------------------------------------------------------------------------------------------------#

# Compiler:
CPPFLAGS             = $(OPT_FLAGS) $(DEBUG_FLAGS) $(NO_LINKER_FLAGS) $(STANDARD_FLAGS) #\
                       #$(WARN_AS_ERRORS_FLAGS)

# Source files, headers, etc.:
MAKEFILE_LOC = $(SRC_ROOT)/cxinv
OBJ_DIR      = $(BIN_ROOT)/connectx/objects/cxinv
OUT_DIR      = $(BIN_ROOT)/connectx
LIBS_OUT     = $(BIN_ROOT)/connectx/libs
INCLUDES     = -I$(MAKEFILE_LOC)/src -I$(MAKEFILE_LOC)/include
VPATH        = src

SRCS     = assertion.cpp

OBJS     = $(OBJ_DIR)/assertion.o

# Build output:

# Product:
MAIN = libcxinv.a # static library


all: make_dir $(MAIN)
	@echo $(MAIN) has been compiled!

$(MAIN): $(OBJS)
	@echo Invoquing GCC Archiver...
	ar -r $(LIBS_OUT)/$(MAIN) $(OBJS)
	@echo Static library $(MAIN) created!

$(OBJ_DIR)/%.o: %.cpp
	@echo Invoquing GCC...
	$(CPPC) $(CPPFLAGS) $(INCLUDES) $< -o $@
	@echo Object files created!

make_dir:
	mkdir -p $(OBJ_DIR)
	mkdir -p $(LIBS_OUT)

clean:
	@echo Removing object files...
	$(RM) $(OBJ_DIR)/*.o
	@echo Object files removed!

mrproper:
	@echo Cleaning project...
	$(RM) $(OBJ_DIR)/*.o
	$(RM) $(LIBS_OUT)/$(MAIN)
	@echo Project cleaned!

depend: $(SRCS)
	@echo Finding dependencies...
	makedepend $(INCLUDES) $^
	@echo Dependencies found!

