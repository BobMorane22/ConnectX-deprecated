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

all:	$(MAIN)
	@echo $(MAIN) has been compiled and linked!

$(MAIN): $(OBJS)
	@echo Invoquing GCC...
	$(CPPC) $(LIBINCLUDES) -o $(MAIN) $(OBJS) $(LIBS)
	@echo $(MAIN) created!

.cpp.o:
	@echo Invoquing GCC...
	$(CPPC) $(CPPFLAGS) $(INCLUDES) -c $< -o $@
	@echo Object files created!

clean:
	@echo Removing object files...
	$(RM) *.o
	@echo Object files removed!

mrproper: clean
	@echo Cleaning project...
	$(RM) $(MAIN)
	@echo Project cleaned!

depend: $(SRCS)
	@echo Finding dependencies...
	makedepend $(INCLUDES) $^
	@echo Dependencies found!
