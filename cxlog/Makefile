#--------------------------------------------------------------------------------------------------#
#
# @file    Makefile
# @author  morane
# @date    June, 2019
# @version 1
#
# This makefile defines how cxlog should be built. The following
# build step is done from here:
#
#    1. Build libcxlog.a
#
# To use this makefile, you need at least these tools installed on your
# machine:
#
#    1. GNU make (tested with)
#    2. gcc compiler (g++ is used)
#
#--------------------------------------------------------------------------------------------------#

# Compiler:
CPPFLAGS             = $(OPT_FLAGS) $(DEBUG_FLAGS) $(NO_LINKER_FLAGS) $(STANDARD_FLAGS) #\
                       #$(WARN_AS_ERRORS_FLAGS)

# Source files, headers, etc.:
MAKEFILE_LOC = $(SRC_ROOT)/cxlog
OBJ_DIR      = $(BIN_ROOT)/connectx/objects/cxlog
OUT_DIR      = $(BIN_ROOT)/connectx
LIBS_OUT     = $(BIN_ROOT)/connectx/libs
LIBS_INCLUDE = -static -L$(LIBS_OUT)
INCLUDES     = -I$(SRC_ROOT)
VPATH        = src

SRCS     = ChainLogger.cpp               \
           CSVMessageFormatter.cpp       \
           FileLogTarget.cpp             \
           IncrementalChainedLogger.cpp  \
           IncrementalLogger.cpp         \
           ISO8601TimestampFormatter.cpp \
           Logger.cpp                    \
           Logging.cpp                   \
           LoggingManager.cpp            \
           StdLogTarget.cpp              \
           StringStreamLogTarget.cpp     \
           VerbosityLevel.cpp

OBJS     = $(OBJ_DIR)/ChainLogger.o               \
           $(OBJ_DIR)/CSVMessageFormatter.o       \
           $(OBJ_DIR)/FileLogTarget.o             \
           $(OBJ_DIR)/IncrementalChainedLogger.o  \
           $(OBJ_DIR)/IncrementalLogger.o         \
           $(OBJ_DIR)/ISO8601TimestampFormatter.o \
           $(OBJ_DIR)/Logger.o                    \
           $(OBJ_DIR)/Logging.o                   \
           $(OBJ_DIR)/LoggingManager.o            \
           $(OBJ_DIR)/StdLogTarget.o              \
           $(OBJ_DIR)/StringStreamLogTarget.o     \
           $(OBJ_DIR)/VerbosityLevel.o

LIBS = -lcxinv

# Build output:

# Product:
MAIN = libcxlog.a # static library


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

