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
ROOT     = $(ROOT_DIR)/cXbase
INCLUDES = -I$(ROOT)source -I$(ROOT)publicAPI
VPATH    = source

SRCS     = AsciiColorCode.cpp\
           Color.cpp\
           ContractException.cpp\
           Disc.cpp\
           Game.cpp\
           GameBoard.cpp\
           Name.cpp\
           Player.cpp\
           Position.cpp

OBJS     = AsciiColorCode.o\
           Color.o\
           ContractException.o\
           Disc.o\
           Game.o\
           GameBoard.o\
           Name.o\
           Player.o\
           Position.o

LIBS =

# Build output:

# Product:
MAIN = libcXbase.a # static library


all:	$(MAIN)
	@echo $(MAIN) has been compiled!

$(MAIN): $(OBJS)
	@echo Invoquing GCC Archiver...
	ar -r $(MAIN) $(OBJS) $(LIBS)
	@echo Static library $(MAIN) created!

.cpp.o:
	@echo Invoquing GCC...
	$(CPPC) $(CPPFLAGS) $(INCLUDES) -c $< -o $@
	@echo Object files created!

clean:
	@echo Removing object files...
	$(RM) *.o 
	@echo Object files removed!

mrproper:
	@echo Cleaning project...
	$(RM) *.o
	$(RM) *.a
	@echo Project cleaned!

depend: $(SRCS)
	@echo Finding dependencies...
	makedepend $(INCLUDES) $^
	@echo Dependencies found!
