(TeX-add-style-hook
 "connectXGuiSpec"
 (lambda ()
   (TeX-run-style-hooks
    "latex2e"
    "report"
    "rep10")
   (TeX-add-symbols
    '("ttt" 1)
    '("includecode" 1)
    "versionNumber"
    "snippets"
    "proto"
    "img"
    "files")
   (LaTeX-add-bibliographies
    "connectXGuiSpec.bib"))
 :latex)

