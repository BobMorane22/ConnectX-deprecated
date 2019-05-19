#--------------------------------------------------------------------------------------------------#
#
# @file    Makefile
# @author  Eric Poirier
# @date    May 2019
#
# This makefile defines the build process for the entire Connect X project documentation.
#
#--------------------------------------------------------------------------------------------------#

MAIN     = cxdoc

TARGETS  += coding_std \
            spec_arch  \
            spec_gui

.PHONY: coding_std spec_arch spec_gui

all: $(MAIN)

$(MAIN): $(TARGETS)
	@echo $(TARGETS)

coding_std:
	$(MAKE) -C coding_std

spec_arch:
	$(MAKE) -C spec_arch

spec_gui:
	$(MAKE) -C spec_gui

mrproper:
	@echo Removing Connect X documntation...
	$(MAKE) mrproper -C coding_std
	$(MAKE) mrproper -C spec_arch
	$(MAKE) mrproper -C spec_gui

clean:
	@echo Cleaning Connect X documentation...
	$(MAKE) clean -C coding_std
	$(MAKE) clean -C spec_arch
	$(MAKE) clean -C spec_gui
