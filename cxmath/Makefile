#--------------------------------------------------------------------------------------------------#
#
# @file    Makefile
# @author  morane
# @date    July, 2019
# @version 1
#
# This makefile defines how cxmath should be built. The following
# build step is done from here:
#
#    1. Build libcxmath.a
#
# To use this makefile, you need at least these tools installed on your
# machine:
#
#    1. GNU make (tested with)
#    2. gcc compiler (g++ is used)
#
#--------------------------------------------------------------------------------------------------#

# Compiler:
CPPFLAGS             = $(OPT_FLAGS) $(DEBUG_FLAGS) $(NO_LINKER_FLAGS) $(STANDARD_FLAGS) \
                       $(WARN_AS_ERRORS_FLAGS)

# Source files, headers, etc.:
MAKEFILE_LOC = $(SRC_ROOT)/cxmath
OBJ_DIR      = $(BIN_ROOT)/connectx/objects/cxmath
OUT_DIR      = $(BIN_ROOT)/connectx
LIBS_OUT     = $(BIN_ROOT)/connectx/libs
LIBS_INCLUDE = -static -L$(LIBS_OUT)
INCLUDES     = -I$(SRC_ROOT)
VPATH        = src

# Every file so far is header only because of the templates. So there is nothing to compile here.
#SRCS     =

#OBJS     = $(OBJ_DIR)/

LIBS = -lcxutil

# Build output:

# Product:
MAIN = libcxmath.a # static library


all: make_dir $(MAIN)
	@echo $(MAIN) has been compiled!

$(MAIN): $(OBJS)
	@echo Invoquing GCC Archiver...
	ar -r $(LIBS_OUT)/$(MAIN) $(OBJS)
	@echo Static library $(MAIN) created!

$(OBJ_DIR)/%.o: %.cpp
	@echo Invoquing GCC...
	$(CPPC) $(CPPFLAGS) $(INCLUDES) -c $< -o $@ $(LIBS) $(LIBS_INCLUDE)
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

