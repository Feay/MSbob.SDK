//--------------------------------------------------------------------------
// SHELLSRV.H
//
//
//
// History:
// 03-21-93 DarrinM     Created.
//-------------------------------------------------------------------------

#ifndef __SHELLSRV_H__
#define __SHELLSRV_H__

#include <syssrv.h>
#include <actor.h>
#include <tippage.h>
#include <image.h>

#define PM_LSOBCLICK        WM_USER + 1
#define WM_NOLBUTTONDBLCLK  WM_USER + 2
#define WM_NORBUTTONDBLCLK  WM_USER + 3
// following three also defined in /home/globals.h
//#define PM_ROOMCHANGE       WM_USER + 4
#define PM_INPUTINTERCEPT   WM_USER + 5
#define PM_DELETEOBJECT     WM_USER + 6
#define PM_RSOBCLICK        WM_USER + 7
#define PM_ActionFinished   WM_USER + 8
#define WM_MOUSEENTER       WM_USER + 9
#define WM_MOUSELEAVE       WM_USER + 10
#define PM_LOGON            WM_USER + 11
#define PM_CHANGEME         WM_USER + 12
#define WM_MOUSECANCEL      WM_USER + 13  // cancel dbl click timer

// Declare these here so they can be defined in any order.

struct IHome;
struct IRoom;
struct IEnumRoom;
struct ISob;
struct IEnumSob;
struct ISobUI;
struct ISysSink;
struct ISobSink;

// UNDONE: Wouldn't necessarily want to expose all these (sobtWnd,
// sobtHandles, sobtLogon, etc) to the universe.

enum SobType {
     sobtGeneric, sobtNav, sobtLogon, sobtAnimation, sobtWnd, sobtHandles,
     sobtActor, sobtBackground, sobtLaunch, sobtLabel
};

// {public room, private room, public room w/pasword on it}

enum Security { secNone, secCreator, secPassword };

//-------------------------------------------------------------------------
// Home Interface

DECLARE_INTERFACE_(IHome, IUnknown)
{
    STDMETHOD(LogOn)(IUser *pusr, char *pszPassword) PURE;
    STDMETHOD(LogOff)() PURE;

    STDMETHOD(DoMouseEvent)(ULONG message, long x, long y,
            ULONG flags, UINT CSMsg) PURE;
    STDMETHOD(Paint)(HDC hdc, long xLeft, long yTop, long xRight, long yBottom) PURE;

    STDMETHOD(CreateRoom)(IRoom **pprm) PURE;
    STDMETHOD(AddRoom)(IRoom *prm) PURE;
    STDMETHOD(RemoveRoom)(IRoom *prm) PURE;
    STDMETHOD(EnumRooms)(IEnum **ppenmRoom) PURE;
    STDMETHOD(FindRoom)(const char *pszRoomName, ULONG id, IRoom **pprm) PURE;

    STDMETHOD(GetCurrentRoom)(IRoom **pprm) PURE;
    STDMETHOD(SetCurrentRoom)(IRoom *prm) PURE;
    STDMETHOD(SecureSetCurrentRoom)(IRoom *prm) PURE;

    STDMETHOD(GetProperty)(const char *pszPropName, void *pvBuffer,
            long cbBufferMax) PURE;
    STDMETHOD(SetProperty)(const char *pszPropName, const void *pvData,
            long cbDataMax) PURE;
    STDMETHOD(Advise)(const char *pszPropName, ISysSink *padvs,
            DWORD *pdwConnection, ULONG ffOrder) PURE;
    STDMETHOD(Unadvise)(DWORD dwConnection) PURE;
};

// timezone id's defined for umail settimezone interface
#define kZIDNewfoundland                    ((LONG) 0)
#define kZIDAtlantic                        ((LONG) 1)
#define kZIDEastern                         ((LONG) 2)
#define kZIDCentral                         ((LONG) 3)
#define kZIDMountain                        ((LONG) 4)
#define kZIDArizona                         ((LONG) 5)
#define kZIDPacific                         ((LONG) 6)
#define kZIDAlaska                          ((LONG) 7)
#define kZIDHawaii                          ((LONG) 8)
#define kZIDMAX                             ((LONG) 9)

//-------------------------------------------------------------------------
// Room Interface

DECLARE_INTERFACE_(IRoom, IUnknown)
{
    STDMETHOD(CreateSob)(IUtopiaApp *puapp, ISob **ppsob) PURE;
    STDMETHOD(AddSob)(ISob *psob, const ISob *psobInsertAfter) PURE;
    STDMETHOD(RemoveSob)(ISob *psob) PURE;
    STDMETHOD(EnumSobs)(IEnum **ppenmSob) PURE;
    STDMETHOD(ReleaseSobs)() PURE;
    // after enumerating sobs, releasing sobs of rooms other than the
    // current room can help free up memory.

    STDMETHOD(Update)() PURE;

    STDMETHOD(Init)(const char *pszRoomName, const char *pszType) PURE;
    STDMETHOD(Clone)(IRoom **pprmClone) PURE;

    STDMETHOD(GetProperty)(const char *pszPropName, void *pvBuffer,
            long cbBufferMax) PURE;
    STDMETHOD(SetProperty)(const char *pszPropName, const void *pvData,
            long cbDataMax) PURE;
    STDMETHOD(Advise)(const char *pszPropName, ISysSink *padvs,
            DWORD *pdwConnection, ULONG ffOrder) PURE;
    STDMETHOD(Unadvise)(DWORD dwConnection) PURE;
};

const ULONG fRmTemplate =   0x0001;     // room is a template
const ULONG fRmNavigable =  0x0002;     // room can be navigated to

const ULONG cchRoomNameMax = 80;
const ULONG cchRoomTypeMax = 50;

const ULONG idrEntry = 1;               // Predefined room ids
const ULONG idrCommon = 64;
const ULONG idrInvalid = 0xFFFF;        // for doors w/no destination

// Room type ids

typedef ULONG RoomType;
const RoomType rmtEntry =       1;
const RoomType rmtStudy =       2;
const RoomType rmtLiving =      3;
const RoomType rmtKitchen =     4;
const RoomType rmtConservatory = 5;
const RoomType rmtGarage =      6;
const RoomType rmtKids =        7;
const RoomType rmtAttic =       8;
const RoomType rmtSafe =        9;
const RoomType rmtCommon =      10;
const RoomType rmtMouseHole =   11;


//-------------------------------------------------------------------------
// Sob Interface

DECLARE_INTERFACE_(ISob, IUnknown)
{
    STDMETHOD(Init)() PURE;
    STDMETHOD(Clone)(ISob **ppsobClone) PURE;
    STDMETHOD(Exec)() PURE;

    STDMETHOD(SetPosition)(long x, long y, ISob *psobInsert, long cx,
            long cy, ULONG ffFlags) PURE;

    STDMETHOD(GetProperty)(const char *pszPropName, void *pvBuffer,
            long cbBufferMax) PURE;
    STDMETHOD(SetProperty)(const char *pszPropName, const void *pvData,
            long cbDataMax) PURE;
    STDMETHOD(Advise)(const char *pszPropName, ISobSink *padvs,
            DWORD *pdwConnection, ULONG ffOrder) PURE;
    STDMETHOD(Unadvise)(DWORD dwConnection) PURE;
};

const ULONG fSobPublic =      0x0001;      // Sob is shared amongst all users
const ULONG fSobOpaque =      0x0002;      // Sob has no transparent areas
const ULONG fSobVisible =     0x0004;      // Sob is visible
const ULONG fSobLocked =      0x0008;      // Sob is locked
const ULONG fSobCacheImage =  0x0010;      // Sob's image is cached as a bitmap
const ULONG fSobFromTemplate= 0x0020;      // Sob was created from a template
const ULONG fSobPersistant =  0x0040;      // Sob persists across shell close/open
const ULONG fSobSizing =      0x0080;      // Sob is being resized
const ULONG fSobHot =         0x0100;      // Sob responds to clicks (shows hot cursor)
const ULONG fSobImageOverride = 0x0200;
const ULONG fSobRegenImage =  0x4000;      // Sob's image needs regeneration

const ULONG fPosMove =        0x0001;      // move object
const ULONG fPosSize =        0x0002;      // size object
const ULONG fPosZOrder =      0x0004;      // set object's depth
const ULONG fPosHide =        0x0008;      // hide object
const ULONG fPosShow =        0x0010;      // show object
const ULONG fPosNoRedraw =    0x0020;      // alter object without updating display
const ULONG fPosForceRedraw = 0x0040;      // force display update
const ULONG fPosInvalidate =  0x0080;      // postpone display update

#define ForceRedraw(psob) psob->SetPosition(0, 0, 0, 0, 0, fPosForceRedraw)

#define psobBottom      (ISob *)1
#define psobTop         (ISob *)2
#define psobBottomMost  (ISob *)3
#define psobTopMost     (ISob *)4


//-------------------------------------------------------------------------
// SobUI Interface

DECLARE_INTERFACE_(ISobUI, IUnknown)
{
    STDMETHOD(Init)(ISob *psob, ISobUI *psuiBase) PURE;
    STDMETHOD(Paint)(HDC hdc, const RECT *prcSob, const RECT *prcInvalid) PURE;
    STDMETHOD(Intersect)(const RECT *prcSob, const POINT *ppt) PURE;
    STDMETHOD(Input)(const RECT *prcSob, UINT message, const POINT *ppt) PURE;
    STDMETHOD(Clone)(ISob *psobClone, ISobUI **ppsuiClone) PURE;
};

// Standard sobtAnimation actions.

// #define actionIdle           1    // Defined in inc\actions.h
#define actionLeftClick         2
#define actionRightClick        3
#define actionMouseEnter        4
#define actionMouseLeave        5
#define actionLeftDoubleClick   6


//--------------------------------------------------------------------------
// SobSink Interface

#undef  INTERFACE
#define INTERFACE   ISobSink

DECLARE_INTERFACE_(ISobSink, IUnknown)
{
    STDMETHOD(OnPropertyChange)(const char *pszPropName, const void *pvData,
            long cbDataMax, ULONG ffOrder) PURE;
    STDMETHOD(OnSetPosition)(long x, long y, ISob *psobInsert, long cx, long cy,
            ULONG ffFlags, ULONG ffOrder) PURE;
    STDMETHOD(OnObjectAdd)(const void *pvObject, ULONG ffOrder) PURE;
    STDMETHOD(OnObjectRemove)(const void *pvObject, ULONG ffOrder) PURE;
};


//-------------------------------------------------------------------------
//

STDAPI_(IHome *) CreateHome(HWND hwndClient);
STDAPI_(IHome *) GetHome();
STDAPI_(HWND) GetHomeWnd(); // no reference count
STDAPI_(void) UpdateCurrentRoom();
// the next returns the home address formatted with CR/LF
#define _ADDR_MAX 330     //what pBuffer must be at least.
#define _MAX_ADDR_LINE   80 // longest line in the address is this
STDAPI GetHomeAddress(char *pBuffer, UINT cchBuf);
STDAPI_(HCURSOR) GetShellCursor(LPCSTR id);
STDAPI CreateImageFromRoom(BOOL fDarken, BOOL fActor, LPIMAGE FAR* ppimg);

// the next four functions are to make the character say somthing.
// shellmsg bln should be used with Modal auto takedowns.

STDAPI ShellMsgBln(LPTIP tipObj, TIPID tipID, HWND hwndParent,
        LPCRECT lprcPointTo, BALLOONSTYLE bs);
STDAPI ShellShowTip(LPTIP tipObj, TIPID tipID, HWND hwndParent,
        LPCRECT lprcPointTo, BALLOONSTYLE bs);
// don't use this unshow tip with tipidall, it needs to be called for
// each tip you used shellshowtip.
STDAPI ShellUnshowTip(LPTIP tipObj, TIPID tipID);
STDAPI TipFromUErr(UERR uerr);


// UMail administrative functions

typedef enum ChangeUMailUserAction {cuaChangeName, cuaChangePassword};

STDAPI_(void) GetUMailInboxCount(long * pcMsg, long * pcUnreadMsg);
STDAPI_(void) SetUMailTimeZone(long zoneID);
STDAPI_(void) ChangeUMailUser(ChangeUMailUserAction cua, LPSTR pszArg1, LPSTR pszArg2, LPSTR pszArg3);


// helper function for adding sobs to the current room
// first two for active sobs

STDAPI_(ISob *) AddSob(IUtopiaApp *puapp, BOOL fShow);
STDAPI_(ISob *) AddSobPos(IUtopiaApp *puapp, long x, long y, BOOL fShow);
STDAPI_(void) AddDecoSob();                 // in decoblns.cpp
STDAPI_(void) AddDoorSob();                 // in doorblns.cpp

// SetSobImage is called either with an id OR with id = 0 and
// the attribute list and count for choosing an image.  Will set
// the image on all objects in the current room whose puapp name
// matches pszUAppName

STDAPI SetSobImage(ULONG id, int cAttributes, ULONG *prgAttributes,
        ULONG appid);

STDAPI_(ISob *) CreateActorSob(const char *pszActorPath);
STDAPI_(ISob *) CreateLabelSob(ISob *psobTarget);

// Sound APIs 

STDAPI_(void)   PlayShellSound(ACTION action, WORD wFlags);
STDAPI_(DWORD)  GetShellVolume();
STDAPI_(void)   SetShellVolume(DWORD dwVolume);
STDAPI_(BOOL)   fVolumeSupport();  // does our device even set volume?

// Must send click pair to avoid screwing up button state in UHome::DoMouseEvent SED

#define HideHandles(phome) phome->DoMouseEvent(WM_RBUTTONDOWN, 32000, 32000,\
             0, 0);  phome->DoMouseEvent(WM_RBUTTONUP, 32000, 32000, 0, 0)

//-------------------------------------------------------------------------
//

// temporary function for V1, will be replaced by sob command interface

STDAPI_(void) InvokeSobDeleteBln(ISob *psob, CRect *prcOwner, ULONG ff);
STDAPI_(void) InvokeGoAnyRoomBln();

STDAPI_(ULONG) GetRoomTypeId(const char *pszRoomType);
STDAPI_(BOOL) GetDesignStyleName(ULONG idDesignStyle, char *pszDesignStyle,
        int cbDesignStyleMax);
STDAPI_(void) CheckToRemoveUsers();     // helper cleanup function
STDAPI_(void) FreeCachedShellBlns();    // Home.exe calls when deactivated.

#endif  // ifdef __SHELLSRV_H__
