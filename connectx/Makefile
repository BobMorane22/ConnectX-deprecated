#--------------------------------------------------------------------------------------------------#
#
# @file    Makefile
# @author  morane
# @date    December, 2017
# @version 1
#
# This makefile defines how connectx should be built. The following
# build step is done from here:
#
#    1. Build libconnectx.a
#
# To use this makefile, you need at least these tools installed on your
# machine:
#
#    1. GNU make (tested with)
#    2. gcc compiler (g++ is used)
#
#--------------------------------------------------------------------------------------------------#

# Compiler:
CPPFLAGS = $(OPT_FLAGS) $(DEBUG_FLAGS) $(STANDARD_FLAGS) $(WARN_AS_ERRORS_FLAGS)

# Source files, headers, etc.:
MAKEFILE_LOC = $(SRC_ROOT)/connectx
OBJ_DIR      = $(BIN_ROOT)/connectx
OUT_DIR      = $(BIN_ROOT)/connectx
LIBS_OUT     = $(BIN_ROOT)/connectx/libs
LIBS_INCLUDE = -L$(LIBS_OUT)
INCLUDES     = -I$(MAKEFILE_LOC)/src -I$(MAKEFILE_LOC)/include
VPATH        = src

SRCS     = GameWindow.cpp \
           main.cpp

OBJS     = $(OBJ_DIR)/GameWindow.o \
           $(OBJ_DIR)/main.o

LIBS = -lcxbase   \
       -lcxutil

# Build output:

# Product:
MAIN = connectx


all: make_dir runtime_dependencies $(MAIN)
	@echo $(MAIN) has been compiled!

$(MAIN): $(OBJS)
	@echo Invoquing GCC...
	$(CPPC) $(CPPFLAGS) $(LIBS_INCLUDE) $(INCLUDES) -o $(OUT_DIR)/$(MAIN) $(OBJS) $(LIBS) `pkg-config gtkmm-3.0 --libs`
	@echo $(MAIN) program created!

$(OBJ_DIR)/%.o: %.cpp
	@echo Invoquing GCC...
	$(CPPC) $(CPPFLAGS) -c $(INCLUDES) $< -o $@ $(LIBS) $(LIBS_INCLUDE) `pkg-config gtkmm-3.0 --cflags`
	@echo Object files created!

make_dir:
	mkdir -p $(OBJ_DIR)
	mkdir -p $(LIBS_OUT)
	mkdir -p $(BIN_ROOT)/$(MAIN)/icons

runtime_dependencies:
	cp $(MAKEFILE_LOC)/img/icons/cxicon16.png $(BIN_ROOT)/$(MAIN)/icons
	cp $(MAKEFILE_LOC)/img/icons/cxicon32.png $(BIN_ROOT)/$(MAIN)/icons
	cp $(MAKEFILE_LOC)/img/icons/cxicon64.png $(BIN_ROOT)/$(MAIN)/icons
	cp $(MAKEFILE_LOC)/img/icons/cxicon128.png $(BIN_ROOT)/$(MAIN)/icons

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

