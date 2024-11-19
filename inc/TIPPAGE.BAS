' TIPPAGE.BAS

' trigger: modal dialog with no user choice is active and user clicks on inactive area
' point to: modal balloon
' kill: user clicks ok on modal dialog with no choice
' BEEP
' NOTE: trap and kill for this tip must be implement on an app by app, dialog by dialog basis
Global Const sTRAOKNoChoice = 3000

' trigger: when an app brings up the address book control and it contains names (as opposed to books and mailing lists)
Global Const sTRAEmptyAddressControl = 3001

' trigger: clicks scroll up arrow on screen in list or topic view (in notebook) or clicks on prev page screen arrow (in addressbook)
' point to: arrrow just clicked
' kill: uses page up 
Global Const sTRAPageUp = 3002

' trigger: clicks scroll down arrow on screen in list or topic view (in notebook) or clicks on next page screen arrow (in addressbook)
' point to: arrrow just clicked
' kill: uses page down
Global Const sTRAPageDown = 3003

' points to: Choose or setup printer button in utopia print dialog
' trigger: print dialog appears
' kill: user brings up windows printer setup dialog
' 
Global Const sTRAPrintSetup = 3004

' 
Global Const sERRNoDefaultPrinter = 1000

' Trigger: put up while character searching
' Killed: never
' Where: from character
Global Const sDIASearching = 1001

' trigger: program opens
' point to: character
Global Const sTRAExit = 3005

' trigger: about dialog comes up
' kill: user clicks exit button on podium
' point to: character (side)
Global Const sTRAAboutExit = 3006

' Trigger:  Click off a modal dialog that has no default OK button
' Point to:  The modal dialog
Global Const sDIAOffModal = 1002

' Trigger:  User clicks off a modal dialog that has a default button
' Point to:  The default button
Global Const sDIAOffModalWithOK = 1003

' 
Global Const sTIPLongWait = 1004

' 
Global Const sTIPShortWait = 1005

' 
Global Const sTIPStartApp = 1006

' user hasn't checked a box
Global Const sERRCheckSomething = 1007
