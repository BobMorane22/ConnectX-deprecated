#------------------------------------------------------------------------------#
#
# @file     Makefile
# @author   Eric Poirier
# @date     March 2017
#
# Builds the Connect X C++ programming coding standard LaTeX source files
# into a PDF.
#
#------------------------------------------------------------------------------#

SRC        = coding_std.tex
OUT        = coding_std.pdf
CODING_STD = coding_std
CC         = latexmk

all: $(CODING_STD)

coding_std: $(SRC)
	$(CC) $(SRC)

clean:
	$(CC) -c

mrproper:
	$(CC) -c
	$(RM) $(OUT)
