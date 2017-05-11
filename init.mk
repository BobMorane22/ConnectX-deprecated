#--------------------------------------------------------------------------------------------------#
#
# @file    init.mk
# @author  Eric Poirier
# @date    April 2017
# @version 1
#
# This file initializes global variables used across most other Makefiles in the code base.
#
#--------------------------------------------------------------------------------------------------#


# OS:
# --------------------------------------------------------------------------------------------------
export OS = linux

# File location:
# --------------------------------------------------------------------------------------------------
export ROOT_DIR = $(CX_SRC_ROOT)

# Compilation:
# --------------------------------------------------------------------------------------------------
export CPPC                 = g++
export STANDARD_FLAGS       = -std=c++0x

ifeq ($(DEBUG), 1)
	export DEBUG_FLAGS          = -g3
	export OPT_FLAGS            =
else
	export DEBUG_FLAGS          =
	export OPT_FLAGS            = -O0
endif

export NO_LINKER_FLAGS      = -c
export WARN_AS_ERRORS_FLAGS = -pedantic-errors\
                              -Wall\
                              -Wextra\
                              -Werror\
                              -Wconversion
  
# Shell:
# --------------------------------------------------------------------------------------------------
ifeq ($(OS),linux)
	export SHELL := /bin/bash
else ifeq ($(OS),windows)
	# Reads the wnvironment variable COMSPEC (usually set to CMD.EXE)
	# See this: https://www.gnu.org/software/make/manual/make.html#Choosing-the-Shell
	# for more information.
else
	export SHELL :=
endif
       
# Cleaning:
# --------------------------------------------------------------------------------------------------
export RM = rm -fd