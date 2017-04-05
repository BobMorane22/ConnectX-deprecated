#--------------------------------------------------------------------------------------------------#
#
# @file    Makefile
# @author  Eric Poirier
# @date    April 2017
# @version 1
#
# This makefile defines how the unit tests for cXbase are built.
#
# To use this makefile, you need at least these tools installed on your
# machine:
#
#    1. GNU make (tested with)
#    2. gcc compiler (g++ is used)
#    3. cxbase library
#
#--------------------------------------------------------------------------------------------------#

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
INCLUDES    = -I$(ROOT)/../publicAPI
LIBINCLUDES = -L$(ROOT)/..
VPATH       = integration

SRCS      = main.cpp

OBJS      = main.o

LIBS      = -lcXbase

# Product:
MAIN = connectx-nw.out # Connect X, no window version

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
