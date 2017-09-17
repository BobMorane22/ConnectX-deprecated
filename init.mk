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


# File location:
# --------------------------------------------------------------------------------------------------
export SRC_ROOT = $(CX_SRC_ROOT)
export BIN_ROOT = $(CX_BUILD_ROOT)

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

export SHELL := /bin/bash

       
# Cleaning:
# --------------------------------------------------------------------------------------------------
export RM = rm -fd

# Google tests:
#---------------------------------------------------------------------------------------------------
export GTEST_COLOR = 1
