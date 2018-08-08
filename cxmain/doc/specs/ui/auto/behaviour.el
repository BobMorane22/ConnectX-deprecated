(TeX-add-style-hook
 "behaviour"
 (lambda ()
   (TeX-run-style-hooks
    "GameDlg"
    "NewGameDlg"
    "HelpDlg"
    "AboutDlg"
    "CreditsDlg"
    "LicenceDlg"
    "MessageBoxes")
   (LaTeX-add-labels
    "dlg:Game"
    "fig:GameDlgLayout"
    "dlg:NewGame"
    "fig:NewGameDlgLayout"
    "dlg:Help"
    "fig:HelpDlgLayout"
    "dlg:AboutCX"
    "fig:AboutCXDlgLayout"
    "dlg:Credits"
    "fig:CreditsDlgLayout"
    "dlg:Licence"
    "fig:Licence"
    "dlg::messageBox"))
 :latex)

