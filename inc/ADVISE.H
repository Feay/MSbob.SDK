/////////////////////////////////////////////////////////////////////////////
// ADVISE.H
//
// The System Services DLL exports a set of functions to assist in the
// management and notification of advise sinks.  The UUser, UHome, URoom,
// and USob classes make use of these functions.
//
// History:
// 04-03-93 DarrinM     Created.
// 02-08-94 FordM       Changes for cross-app advises
/////////////////////////////////////////////////////////////////////////////

#ifndef __ADVISE_H__
#define __ADVISE_H__

#include <shellsrv.h>

struct AdviseHolder {
    HWND hwndNotify;
    char szPropName[cchPropMax];
    ISysSink *padvs;
    ULONG ffOrder;
    DWORD fValid;
};
#define advhValid 0x41445648

STDAPI_(HWND) GetHwndDaemon();

POSITION AdviseAdd(CPtrList &lsadvh, const char *pszPropName,
        ISysSink *padvs, ULONG ffOrder);
BOOL AdviseRemove(CPtrList &lsadvh, POSITION pos);
BOOL AdvisePropertyChange(CPtrList &lsadvh, const char *pszPropName,
        const void *pvData, long cbDataMax, ULONG ffOrder);
BOOL AdviseObjectAdd(CPtrList &lsadvh, const void *pvObject,
        ULONG ffOrder);
BOOL AdviseObjectRemove(CPtrList &lsadvh, const void *pvObject,
        ULONG ffOrder);
#ifdef __SHELLSRV_H__
BOOL AdviseSetPosition(CPtrList &lsadvh, long x, long y, ISob *psobInsert,
        long cx, long cy, ULONG ff, ULONG ffOrder);
#endif
LRESULT AdviseNotify(short vid, HWND hwndNotify, DWORD *lpParams);

// Cross-app advise window message

#define PM_ADVISENOTIFY   (WM_USER + 0x100)


/////////////////////////////////////////////////////////////////////////////
// Advise ID (vid) numbers

// System / Shell

#define vidPropertyChange   1
#define vidObjectAdd        2
#define vidObjectRemove     3
#define vidSetPosition      4

// Calendar

#define vidEventAdd         11
#define vidEventRemove      12
#define vidEventChange      13
#define vidAlarmAdd         14
#define vidAlarmRemove      15
#define vidAlarmChange      16


/////////////////////////////////////////////////////////////////////////////
// PM_ADVISE message parameter blocks (Advise Blocks)

// PropertyChange

struct ABPropertyChange {       // abpc
    void *pvAdvise;             // points to advise sink function
    char *pszPropName;
    void *pvData;
    long cbDataMax;
    ULONG ffOrder;
};

// ObjectAdd and ObjectRemove

struct ABObject {               // abob
    void *pvAdvise;             // points to advise sink function
    const void *pvObject;
    ULONG ffOrder;
};

// Calendar events and alarms

struct ABCal {                  // abcal
    void *pvAdvise;             // points to advise sink function
    long id;
};

// SetPosition

struct ABSetPosition {          // absp
    void *pvAdvise;             // points to advise sink function
    long x;
    long y;
    ISob *psobInsert;
    long cx;
    long cy;
    ULONG ff;
    ULONG ffOrder;
};


/////////////////////////////////////////////////////////////////////////////
// Calendar

struct CalAdviseHolder
{
    HWND hwndNotify;
    IUnknown *padvs;
};


/////////////////////////////////////////////////////////////////////////////
// Class UCalAdv
//
// Calendar advise holder list.
// Uses a UCPtrList to maintain pointers to the CalAdviseHolders.
//
// History:
// 05-15-93 FordM       Created.
/////////////////////////////////////////////////////////////////////////////

class UCalAdv : public CPtrList
{
public:
    POSITION AdviseAdd(IUnknown *padvs);
    BOOL AdviseRemove(POSITION pos);

protected:
    BOOL AdviseNotify(int vid, ULONG id);
    BOOL PackCalBlock(ABCal **ppabcal, ULONG id);
};

#endif  // ifndef __ADVISE_H__
