#--------------------------------------------------------------------------------------------------#
#
# @file    makefile
# @author  Eric Poirier
# @date    March 2017
# @version 1
#
# This makefile defines how the unit tests for cXbase are built.
#
# To use this makefile, you need at least these tools installed on your
# machine:
#
#    1. GNU make (tested with)
#    2. gcc compiler (g++ is used)
#    3. Google Tests
#
#--------------------------------------------------------------------------------------------------#

# Compilator:
CPPC                 = g++
STANDARD_FLAGS       = -std=c++0x
WARN_AS_ERRORS_FLAGS = -pedantic-errors\
                       -Wall\
                       -Wextra\
                       -Werror\
                       -Wconversion
DEBUG_FLAGS          = -g3
OPT_FLAGS            = -O0
CPPFLAGS             = $(OPT_FLAGS) $(DEBUG_FLAGS) $(STANDARD_FLAGS) \
                       $(WARN_AS_ERRORS_FLAGS)

# Source files, headers, etc.:
ROOT        = $(CURDIR)
INCLUDES    = -I$(ROOT)/..
LIBINCLUDES = -L$(ROOT)/..
VPATH       = tests

SRCS      = cxUnitTests.cpp\
            test_Player.cpp\
            test_Name.cpp\
            test_Game.cpp\
            test_GameBoard.cpp\
            test_Disc.cpp\
            test_Color.cpp\
            test_AsciiColorCode.cpp\

OBJS      = test_Player.o\
            test_Name.o\
            test_Game.o\
            test_GameBoard.o\
            test_Disc.o\
            test_Color.o\
            test_AsciiColorCode.o\

LIBS      = -lgtest\
            -lgtest_main\
            -lpthread\
            -lcXbase
 
# Product:
MAIN = cxUnitTests

# Other
RM = rm -fd *.o


all:	$(MAIN)
	@echo $(MAIN) has been compiled!

$(MAIN): $(OBJS)
	@echo Invoquing GCC...
	$(CPPC) $(LIBINCLUDES) -o $(MAIN) $(OBJS) $(LIBS)
	@echo Static library $(MAIN) created!

.cpp.o:
	@echo Invoquing GCC...
	$(CPPC) $(CPPFLAGS) $(INCLUDES) -c $< -o $@
	@echo Object files created!

clean:
	@echo Removing object files...
	$(RM)
	@echo Object files removed!

mrproper:
	@echo Cleaning project...
	$(RM) $(MAIN)
	@echo Project cleaned!

depend: $(SRCS)
	@echo Finding dependencies...
	makedepend $(INCLUDES) $^
	@echo Dependencies found!
