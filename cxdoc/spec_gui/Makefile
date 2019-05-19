#------------------------------------------------------------------------------#
#
# @file		Makefile
# @author   Eric Poirier
# @date		December 2017
#
# Builds the Connect X GUI specification LaTeX source files into a PDF.
#
#------------------------------------------------------------------------------#

SRC  = spec_gui.tex
OUT  = spec_gui.pdf
SPEC = spec
CC   = latexmk

all: $(SPEC)

spec: $(SRC)
	$(CC) $(SRC)

clean:
	$(CC) -c

mrproper:
	$(CC) -c
	$(RM) $(OUT)
