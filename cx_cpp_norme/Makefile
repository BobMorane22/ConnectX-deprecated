#------------------------------------------------------------------------------#
#
# @file		makefile
# @author   Eric Poirier
# @date		March 2017
# @version	1
#
# Builds the C++ programming norm LaTeX source files into a PDF.
#
#------------------------------------------------------------------------------#

SRC  = cx_cpp_norm.tex
OUT  = cx_cpp_norm.pdf
NORM = norm
CC   = latexmk

all: $(NORM)

norm: $(SRC)
	$(CC) $(SRC)

clean:
	$(CC) -c

mrproper:
	$(CC) -c
	$(RM) $(OUT)
