#!/bin/bash

# LaTeX ---> HTML
htlatex cx_cpp_norme.tex "xhtml, mathml, charset=utf-8" " -cunihtf -utf8"

# HTML ---> Markdown
pandoc cx_cpp_norme.html -o cx_cpp_norme.md
