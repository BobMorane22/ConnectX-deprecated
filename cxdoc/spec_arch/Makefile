#------------------------------------------------------------------------------#
#
# @file     Makefile
# @author   Eric Poirier
# @date     May 2019
#
# Builds the Connect X architecture specification LaTeX source files into a PDF.
#
#------------------------------------------------------------------------------#

SRC  = spec_arch.tex
OUT  = spec_arch.pdf
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
