#--------------------------------------------------------------------------------------------------#
#
# @file    Makefile
# @author  morane
# @date    December, 2017
# @version 1
#
# This makefile defines how cxgui should be built. The following
# build step is done from here:
#
#    1. Build libcxgui.a
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
MAKEFILE_LOC = $(SRC_ROOT)/cxgui
OBJ_DIR      = $(BIN_ROOT)/connectx/objects/cxgui
OUT_DIR      = $(BIN_ROOT)/connectx
LIBS_OUT     = $(BIN_ROOT)/connectx/libs
INCLUDES     = -I$(SRC_ROOT)
VPATH        = src

SRCS     = About.cpp          \
           Credits.cpp        \
           Disc.cpp           \
           GeometricShape.cpp \
           Help.cpp           \
           License.cpp        \
           MessageBox.cpp     \
           RAIICairoPath.cpp  \
           SectionTitle.cpp   \
           util.cpp           \
           Window.cpp

OBJS     = $(OBJ_DIR)/About.o          \
		   $(OBJ_DIR)/Credits.o        \
           $(OBJ_DIR)/Disc.o           \
           $(OBJ_DIR)/GeometricShape.o \
           $(OBJ_DIR)/Help.o           \
           $(OBJ_DIR)/License.o        \
           $(OBJ_DIR)/MessageBox.o     \
           $(OBJ_DIR)/RAIICairoPath.o  \
           $(OBJ_DIR)/SectionTitle.o   \
           $(OBJ_DIR)/util.o           \
           $(OBJ_DIR)/Window.o

LIBS = -lcxbase \
       -lcxutil

# Build output:

# Product:
MAIN = libcxgui.a # static library


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

