/////////////////////////////////////////////////////////////////////////////
// SYSDLG.H
//
// The System Services DLL exports a set of functions to 
// allow displaying dialogs in its resources.
// The calendar reminder mechnism makes use of thse functions.
//
// History:
// 04-21-94 FordM       Created.
// 06-05-94 AlanMa      Added idlgPod
// 06-11-94 AlanMa      Added GetHwndMain with a task as a param
/////////////////////////////////////////////////////////////////////////////

#ifndef __SYSDLG_H__
#define __SYSDLG_H__

// API prototypes

STDAPI_(int) DoModalDialog(int idlg, ULONG lParam);
STDAPI_(HWND) GetHwndMain(HTASK htask);

// Date dialog data struct

struct DateData {
    long ldate;
    RECT rc;
};    

// Dialog index numbers of dialogs in syssrv's resources

#define idlgNone        0
#define idlgRemind      1
#define idlgRemindQuery 2
#define idlgClockAlarm  3
#define idlgPod         4
#define idlgDatePick    5
#define idlgSwitch   6

#endif  // ifndef __SYSDLG_H__
