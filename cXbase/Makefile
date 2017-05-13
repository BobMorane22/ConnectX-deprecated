#--------------------------------------------------------------------------------------------------#
#
# @file    makefile
# @author  Eric Poirier
# @date    March 2017
# @version 1
#
# This makefile defines how cXbase.lib should be built. Both the following
# build steps are done from here:
#
#    1. Build libcXbase.a
#    2. Build the cXbase library Doxygen documentation.
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
MAKEFILE_LOC = $(CX_SRC_ROOT)/cXbase
OBJ_DIR      = $(CX_BUILD_ROOT)/connectx
OUT_DIR      = $(CX_BUILD_ROOT)/connectx
LIBS_OUT     = $(CX_BUILD_ROOT)/connectx/libs
INCLUDES     = -I$(MAKEFILE_LOC)/source -I$(MAKEFILE_LOC)/publicAPI
VPATH        = source

SRCS     = AsciiColorCode.cpp\
           Color.cpp\
           ContractException.cpp\
           Disc.cpp\
           Game.cpp\
           GameBoard.cpp\
           Name.cpp\
           Player.cpp\
           Position.cpp

OBJS     = $(OBJ_DIR)/AsciiColorCode.o\
           $(OBJ_DIR)/Color.o\
           $(OBJ_DIR)/ContractException.o\
           $(OBJ_DIR)/Disc.o\
           $(OBJ_DIR)/Game.o\
           $(OBJ_DIR)/GameBoard.o\
           $(OBJ_DIR)/Name.o\
           $(OBJ_DIR)/Player.o\
           $(OBJ_DIR)/Position.o

LIBS =

# Build output:

# Product:
MAIN = libcXbase.a # static library


all: make_dir $(MAIN)
	@echo $(MAIN) has been compiled!

$(MAIN): $(OBJS)
	@echo Invoquing GCC Archiver...
	ar -r $(LIBS_OUT)/$(MAIN) $(OBJS) $(LIBS)
	@echo Static library $(MAIN) created!

$(OBJ_DIR)/%.o: %.cpp
	@echo Invoquing GCC...
	$(CPPC) $(CPPFLAGS) $(INCLUDES) -c $< -o $@
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
	$(RM) $(OUT_DIR)/$(MAIN)
	@echo Project cleaned!

depend: $(SRCS)
	@echo Finding dependencies...
	makedepend $(INCLUDES) $^
	@echo Dependencies found!
