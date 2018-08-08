#--------------------------------------------------------------------------------------------------#
#
# @file    Makefile
# @author  morane
# @date    December, 2017
# @version 1
#
# This makefile defines how the connectx documentation is built.
#
# To use this makefile, you need at least these tools installed on your
# machine:
#
#    1. GNU make (tested with)
#    2. Doxygen
#
#--------------------------------------------------------------------------------------------------#

MAKEFILE_LOC = $(SRC_ROOT)/connectx/doc

# Doxygen:
DOXYDIR  = $(MAKEFILE_LOC)/doxygen
DOXYFILE = $(DOXYDIR)/Doxyfile

.PHONY: doxygen clean

doxygen:
	@echo Generating Doxygen documentation...
	doxygen $(DOXYFILE)
	@echo Doxygen documentation created!

mrproper: clean

clean:
	@echo Deleting Doxygen documentation...
	$(RM) -r $(DOXYDIR)/html
	@echo Doxygen documentation deleted!

