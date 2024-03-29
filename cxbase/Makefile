#--------------------------------------------------------------------------------------------------#
#
# @file    Makefile
# @author  Éric Poirier
# @date    July, 2017
# @version 1
#
# This makefile defines how cxbase should be built. The following
# build step is done from here:
#
#    1. Build libcxbase.a
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
MAKEFILE_LOC = $(SRC_ROOT)/cxbase
OBJ_DIR      = $(BIN_ROOT)/connectx/objects/cxbase
OUT_DIR      = $(BIN_ROOT)/connectx
LIBS_OUT     = $(BIN_ROOT)/connectx/libs
LIBS_INCLUDE = -static -L$(LIBS_OUT)
INCLUDES     = -I$(SRC_ROOT)
VPATH        = src

SRCS     = Disc.cpp      \
           Game.cpp      \
           GameBoard.cpp \
           Player.cpp    \
           Position.cpp


OBJS     = $(OBJ_DIR)/Disc.o      \
           $(OBJ_DIR)/Game.o      \
           $(OBJ_DIR)/GameBoard.o \
           $(OBJ_DIR)/Player.o    \
           $(OBJ_DIR)/Position.o

LIBS = -lcxutil

# Build output:

# Product:
MAIN = libcxbase.a # static library


all: make_dir $(MAIN)
	@echo $(MAIN) has been compiled!

$(MAIN): $(OBJS)
	@echo Invoquing GCC Archiver...
	ar -r $(LIBS_OUT)/$(MAIN) $(OBJS)
	@echo Static library $(MAIN) created!

$(OBJ_DIR)/%.o: %.cpp
	@echo Invoquing GCC...
	$(CPPC) $(CPPFLAGS) $(INCLUDES) $< -o $@ $(LIBS) $(LIBS_INCLUDE)
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

