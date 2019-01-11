#--------------------------------------------------------------------------------------------------#
#
# @file    Makefile
# @author  Eric Poirier
# @date    August, 2018
# @version 1
#
# This makefile defines how cxexec should be built. The following
# build step is done from here:
#
#    1. Build libcxexec.a
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
MAKEFILE_LOC = $(SRC_ROOT)/cxexec
OBJ_DIR      = $(BIN_ROOT)/connectx/objects/cxexec
OUT_DIR      = $(BIN_ROOT)/connectx
LIBS_OUT     = $(BIN_ROOT)/connectx/libs
LIBS_INCLUDE = -static -L$(LIBS_OUT)
INCLUDES     = -I$(SRC_ROOT)
VPATH        = src

SRCS     = About.cpp          \
           Chip.cpp           \
           Credits.cpp        \
           GameBoard.cpp      \
           GameWindow.cpp     \
           GBDisc.cpp         \
           Help.cpp           \
           License.cpp        \
           MessageBox.cpp     \
           NDADisc.cpp        \
           NewGame.cpp        \
           NewPlayerRow.cpp   \
           NewPlayersList.cpp \
           util.cpp           \
           Window.cpp

OBJS     = $(OBJ_DIR)/About.o          \
           $(OBJ_DIR)/Chip.o           \
           $(OBJ_DIR)/Credits.o        \
           $(OBJ_DIR)/GameBoard.o      \
           $(OBJ_DIR)/GameWindow.o     \
           $(OBJ_DIR)/GBDisc.o         \
           $(OBJ_DIR)/Help.o           \
           $(OBJ_DIR)/License.o        \
           $(OBJ_DIR)/MessageBox.o     \
           $(OBJ_DIR)/NDADisc.o        \
           $(OBJ_DIR)/NewGame.o        \
           $(OBJ_DIR)/NewPlayerRow.o   \
           $(OBJ_DIR)/NewPlayersList.o \
           $(OBJ_DIR)/util.o           \
           $(OBJ_DIR)/Window.o

LIBS = -lcxutil \
       -lcxbase \
       -lcxgui

# Build output:

# Product:
MAIN = libcxexec.a # static library


all: make_dir $(MAIN)
	@echo $(MAIN) has been compiled!

$(MAIN): $(OBJS)
	@echo Invoquing GCC Archiver...
	ar -r $(LIBS_OUT)/$(MAIN) $(OBJS)
	@echo Static library $(MAIN) created!

$(OBJ_DIR)/%.o: %.cpp
	@echo Invoquing GCC...
	$(CPPC) $(CPPFLAGS) $(INCLUDES) -c $< -o $@ $(LIBS) $(LIBS_INCLUDE) `pkg-config gtkmm-3.0 --cflags`
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

