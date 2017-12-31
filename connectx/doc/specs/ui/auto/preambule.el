(TeX-add-style-hook
 "preambule"
 (lambda ()
   (TeX-add-to-alist 'LaTeX-provided-package-options
                     '(("appendix" "titletoc" "title") ("hyperref" "colorlinks=true" "allcolors=black" "plainpages=false" "pdfpagelabels") ("tocbibind" "nottoc") ("geometry" "margin=1.25in") ("inputenc" "utf8") ("fontenc" "T1") ("babel" "main=english" "french") ("caption" "font=small")))
   (add-to-list 'LaTeX-verbatim-environments-local "lstlisting")
   (add-to-list 'LaTeX-verbatim-macros-with-braces-local "lstinline")
   (add-to-list 'LaTeX-verbatim-macros-with-braces-local "hyperref")
   (add-to-list 'LaTeX-verbatim-macros-with-braces-local "hyperimage")
   (add-to-list 'LaTeX-verbatim-macros-with-braces-local "hyperbaseurl")
   (add-to-list 'LaTeX-verbatim-macros-with-braces-local "nolinkurl")
   (add-to-list 'LaTeX-verbatim-macros-with-braces-local "url")
   (add-to-list 'LaTeX-verbatim-macros-with-braces-local "path")
   (add-to-list 'LaTeX-verbatim-macros-with-delims-local "lstinline")
   (add-to-list 'LaTeX-verbatim-macros-with-delims-local "url")
   (add-to-list 'LaTeX-verbatim-macros-with-delims-local "path")
   (TeX-run-style-hooks
    "appendix"
    "hyperref"
    "tocbibind"
    "geometry"
    "setspace"
    "multicol"
    "lmodern"
    "inputenc"
    "fontenc"
    "babel"
    "graphicx"
    "wrapfig"
    "caption"
    "subcaption"
    "tikz"
    "floatrow"
    "pdfpages"
    "cleveref"
    "longtable"
    "amsmath"
    "xcolor"
    "listingsutf8"
    "keystroke"))
 :latex)

