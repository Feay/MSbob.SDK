//---------------------------------------------------------------------------
// tippage.h
//---------------------------------------------------------------------------
// Copyright (c) 1992-1993, Microsoft Corporation
//                 All Rights Reserved
// Information Contained Herein Is Proprietary and Confidential.
//---------------------------------------------------------------------------
// 
// Header file for both tippage and user tracking services.
//
//---------------------------------------------------------------------------
//
// Owner:  Larry Powelson
//
// 8-19-94 added ResolveAString
//---------------------------------------------------------------------------

#ifndef _TIPPAGE_H_
#define _TIPPAGE_H_  

#include <uerror.h>

// Tip resource ID

typedef WORD TIPID;


//---------------------------------------------------------------------------
//
// System tips
//
// These tip ids are avaliable to all tip objects.  All tipid values below
// tipidSystemMax are considered to be system tips.

#define tipidSystemMax  ((TIPID) 4999) 

#include <tippage.tip>


// Balloon styles:
// UNDONE:  These should be moved somewhere near CRgnWndDlg

typedef enum {  
    BS_CUSTOM = 0,
    BS_SPEAK_BOTTOM,
    BS_SPEAK_RIGHT,
    BS_THINK_BOTTOM,
    BS_THINK_RIGHT,
    BS_ARROW_LEFT,
    BS_ARROW_RIGHT,
    BS_ARROW_UP,
    BS_ARROW_DOWN,
    BS_SQUARE,      
    BS_MAX,   
    
    // Additional style flags
    BS_TOPMOST = 0x4000,
    BS_OPAQUE = -32768 // 0x8000 if enums were unsigned  
     
} BALLOONSTYLE;    


// Tip modality options:

typedef enum {    
    TM_AUTOTAKEDOWN = 0,
    TM_MODAL,
    TM_MODELESSDISMISS,        // Modeless, dimisses when clicked on anywhere
    TM_MODELESS,               // Modeless, dimisses on button click  
    TM_MODALAUTOTAKEDOWN,
    TM_MAX,
} TIPMODAL;

// Button options:

typedef enum {   
    TB_NONE = 0,
    TB_OK,
    TB_CANCEL,
    TB_OKCANCEL,   
    TB_MAX,
} TIPBTN;

// Tip styles (icons)

typedef enum {    
    TS_PLAIN = 0,
    TS_HINT,
    TS_ALERT,
    TS_QUESTION,
    TS_ERROR,
    TS_MAX,
} TIPSTYLE;    


// Predefined Application IDs:

#define APPID_CURRENT    ((DWORD) 0)                        
#define APPID_SYSTEM     ((DWORD) -1)   // System tips only
#define APPID_NOSAVE     ((DWORD) -2)   // Track tips, but don't save from one invokation to the next
#define APPID_NONE       ((DWORD) -2)   // (obsolete) same as APPID_NOSAVE 

#define TIPID_ALL        ((TIPID) 0)
#define TIPID_NONE       ((TIPID) -1)        

#define tipNil      TIPID_NONE          // (obsolete, but still used in quill)

//---------------------------------------------------------------------------
//
// Tippage API
//
//---------------------------------------------------------------------------

#undef INTERFACE
#define INTERFACE ITip 


DECLARE_INTERFACE_(ITip, IUnknown)
{
    // *** IUnknown methods ***
    STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef) (THIS)  PURE;
    STDMETHOD_(ULONG,Release) (THIS) PURE;

    // *** ITip methods ***  
    STDMETHOD(ShowTip) (THIS_ TIPID tipid, HWND hwndParent, LPCRECT lprcPointTo, BALLOONSTYLE bs) PURE;
    STDMETHOD(TriggerTipNoShow) (THIS_ TIPID tipid) PURE;
    STDMETHOD(FTestTip) (THIS_ TIPID tipid) PURE;
    STDMETHOD(UnshowTip) (THIS_ TIPID tipid) PURE;
    STDMETHOD(KillTip) (THIS_ TIPID tipid) PURE;      
    STDMETHOD(ReviveTip) (THIS_ TIPID tipid) PURE; 
    STDMETHOD(ShowHintORama) (THIS_ TIPID tipidHOR, TIPID tipidConfirm, HWND hwndParent) PURE; 
    STDMETHOD_(BOOL, FIsTipShowing) (THIS_ TIPID tipidFirst, TIPID tipidLast) PURE;
    
    STDMETHOD(TriggerTip) (THIS_ TIPID tipid, HWND hwndParent, LPCRECT lprcPointTo, BALLOONSTYLE bs) PURE;
    STDMETHOD(ShowAboutBox) (THIS_ HWND hwndParent, LPCSTR szName, LPCSTR szCopyright, 
            TIPID tipidKeyboard, TIPID tipidHOR, WORD wFlags) PURE;
};

typedef ITip FAR* LPTIP;    


// to be called when the user changes
STDAPI UpdateTracking(ULONG uid);

STDAPI LoadTips(DWORD appID, HINSTANCE hinst, LPTIP FAR* ppTip);
STDAPI LoadTipsEx(DWORD appID, HINSTANCE hinst, LPCSTR szRes, LPTIP FAR* ppTip); 

STDAPI ShowTipEx(LPCSTR szHeader, LPCSTR szBody, LPCSTR szOK, LPCSTR szCancel, TIPSTYLE ts, TIPMODAL tm, 
        HWND hwndParent, LPCRECT lprcPointTo, BALLOONSTYLE bs);

STDAPI UShowErrorTip(HWND hwnd, USHORT err, LPCSTR szError); 

STDAPI UDeleteTrackingData();

#ifdef _DEBUG
STDAPI_(void) DebugTracking(DWORD appID, DWORD userID, BOOL fReload);
#endif 

// The following helper function is available for people who have previously included <actor.h>:

#ifdef __ACTOR_H__

// CONSIDER:  Add parameters BALLOONSTYLE bs = BS_SPEAK_RIGHT and LPCRECT lprcPointTo = NULL

STDAPI TriggerActorTip(LPTIP pTip, TIPID tipid, HWND hwndParent, ACTION action);

#endif

// Splash screen / About box functions

#include <image.h>

#define USSS_UTOPIACOMPONENT    0x0001
#define USSS_PICTID             0x0002 
#define USSS_HOMELOGO           0x0004

STDAPI UShowStartupScreen(LPCSTR szName, LPCSTR szCopyright, LPIMAGE pImage, WORD wFlags);  
STDAPI UShowAboutBox(HWND hwndParent, LPCSTR szName, LPCSTR szCopyright, LPTIP pTip, TIPID tipidKeyboard, TIPID tipidHOR, WORD wFlags);

// Buffer passed in must have room for 21 characters:

STDAPI UGetPID(LPSTR szPID);

#endif //_TIPPAGE_H_
