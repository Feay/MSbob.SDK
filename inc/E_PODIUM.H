#ifndef _E_PODIUM_H_
#define _E_PODIUM_H_  

#include <tippage.h>

// used by dlgpod.cpp and vpodium.cpp
#define PODIUM_EXIT_FROM_LOGIN   0
#define PODIUM_EXIT_FROM_ROOM    1
#define PODIUM_EXIT_FROM_APP     2

// return values from sysdlg.dll to podium control inside ucc.vbx
#define PODIUM_RET_CANCEL   0
#define PODIUM_RET_CLOSEALL 1	// obsolete: no way to shut down all now
#define PODIUM_RET_CLOSEAPP 2
#define PODIUM_RET_SWITCHED 3
#define PODIUM_RET_CLOSECURRENT 4

// integer param values for "Close" event
#define EXIT_SLOW   0
#define EXIT_FAST   1
#define EXIT_LOGOUT 2
#define EXIT_SHUTDOWN 3
#define EXIT_TO_SHELL_AND_LOGOUT 4	// obsolete

// integer param values for "DialogState" event
#define DLGPOD_CANCEL    0  // user selected cancel on podium dialog
#define DLGPOD_SWITCH    1  // user selected switch to another app on podium dialog
#define DLGPOD_GOINGUP   2  // user just selected podium button so dialog coming up
#define DLGPOD_DOUBLECLICKED   3  // user just selected podium button so dialog coming up

// property value settings for the ForceExit property
#define FORCENOTHING 0
#define FORCESWITCH  1
#define FORCELOGOUT  2

// defines to compare for return from GetNumAppsRunning()
#define SHELLEXIT_OTHERSRUNNING (1)
#define SHELLEXIT_NOAPPSRUNNING (0)
#define SHELLEXIT_OTHERSCLOSING (-1)

class DLGPOD_INFO {
public:
	DLGPOD_INFO() {
        hwndSwitchTo = NULL;
    	fShowSwitchList = FALSE;
    	fDoubleClicked = FALSE;
		fSwitchToUtopiaApp = FALSE;
        fSwitchRequested = FALSE;
    };
    
    RECT rectPodium;
    RECT rectForDialog;
    HWND hwndSwitchTo;
    USHORT wExitFrom;
    USHORT wDlgResult;
	BOOL fSwitchToUtopiaApp;
    BOOL fDoubleClicked;
    BOOL fShowSwitchList;
    BOOL fSwitchRequested;
    LPTIP pTipUcc; // copy of gpTipUcc
};
 

#endif
 