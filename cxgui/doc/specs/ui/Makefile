#------------------------------------------------------------------------------#
#
# @file		Makefile
# @author   Eric Poirier
# @date		December 2017
# @version	1.0
#
# Builds the C++ programming GUI specification LaTeX source files into a PDF.
#
#------------------------------------------------------------------------------#

SRC  = cxgui_spec.tex
OUT  = cxgui_spec.pdf
SPEC = spec
CC   = latexmk

all: $(SPEC)

norm: $(SRC)
	$(CC) $(SRC)

clean:
	$(CC) -c

mrproper:
	$(CC) -c
	$(RM) $(OUT)
