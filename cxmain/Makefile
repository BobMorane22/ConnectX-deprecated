#--------------------------------------------------------------------------------------------------#
#
# @file    Makefile
# @author  Éric Poirier
# @date    August, 2018
# @version 1
#
# This makefile defines how the Connect X executable should be built.
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
MAKEFILE_LOC = $(SRC_ROOT)/cxmain
OBJ_DIR      = $(BIN_ROOT)/connectx/objects/cxmain
OUT_DIR      = $(BIN_ROOT)/connectx
LIBS_OUT     = $(BIN_ROOT)/connectx/libs
LIBS_INCLUDE = -L$(LIBS_OUT)
INCLUDES     = -I$(SRC_ROOT)
VPATH        = $(MAKEFILE_LOC)

SRCS     = main.cpp

OBJS     = $(OBJ_DIR)/main.o

LIBS = -lcxexec \
       -lcxgui  \
       -lcxbase \
       -lcxutil \


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
	$(CPPC) $(CPPFLAGS) $(INCLUDES) `pkg-config gtkmm-3.0 --cflags` -c $< -o $@
	@echo Object files created!

make_dir:
	mkdir -p $(OBJ_DIR)
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

