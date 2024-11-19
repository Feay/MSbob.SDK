//---------------------------------------------------------------------------
//        Copyright (C) 1992-3, Microsoft Corporation
//---------------------------------------------------------------------------
// hooks.h
//
// Implemented in rgnwnd\modality.cpp
//---------------------------------------------------------------------------

void _export InstallHooks(HMODULE hmod);
void _export UninstallHooks(void);
BOOL _export AddToModalList(HWND hwnd, SHORT sLevel, BOOL fModal, BOOL fAutoClose);
BOOL _export RemoveFromModalList(HWND hwnd);
SHORT _export NextModalLevel(void);
SHORT _export GetCurModalLevel(void);
SHORT _export GetCurModelessLevel(void);

STDAPI ShowBadClickTip(HWND hwndParent, LPRECT prect, BOOL fOnButton);

extern const UINT NEAR nRgMsgMouseEnter;
extern const UINT NEAR nRgMsgMouseExit;

// nRgMsgAutoClose
//   wparam - BOOL fDoAnim - TRUE to do the button animation
//   LOWORD(lparam) - VK_ that triggered this message
//   HOWORD(lparam) - Not used
//   returns nothing
extern const UINT NEAR nRgMsgAutoClose;

inline void AutoClose(HWND hwnd, USHORT vk, BOOL fDoAnim = FALSE)
{
    SendMessage(hwnd, nRgMsgAutoClose, fDoAnim, MAKELONG(vk,0));
}

#ifdef VB_VERSION
inline void AutoClose(HCTL hctl, USHORT vk, BOOL fDoAnim = FALSE)
{
    VBSendControlMsg(hctl, nRgMsgAutoClose, fDoAnim, MAKELONG(vk,0));
}
#endif

// nRgMsgFQueryAutoClose
//   wparam - Not used
//   lparam - POINT where mouse was clicked
//   returns TRUE if the window should autoclose.
extern const UINT NEAR nRgMsgFQueryAutoClose;

inline BOOL FQueryAutoClose(HWND hwnd, LONG lp)
{
    return (BOOL) SendMessage(hwnd, nRgMsgFQueryAutoClose, 0, lp);
}

inline BOOL FQueryAutoClose(HWND hwnd, POINT point)
{
    return FQueryAutoClose(hwnd, MAKELONG(point.x, point.y));
}

#ifdef VB_VERSION
inline BOOL FQueryAutoClose(HCTL hctl, LONG lp)
{
    return (BOOL) VBSendControlMsg(hctl, nRgMsgFQueryAutoClose, 0, lp);
}

inline BOOL FQueryAutoClose(HCTL hctl, POINT point)
{
    return FQueryAutoClose(hctl, MAKELONG(point.x, point.y));
}
#endif

// nRgMsgGetCtrlFlags
//   wparam - Not used
//   lparam - Not used
//   returns combination of the following flags bits
extern const UINT NEAR nRgMsgGetCtrlFlags;
#define UCTRL_fDefault 0x0001
#define UCTRL_fCancel  0x0002

inline USHORT GetCtrlFlags(HWND hwnd)
{
    return (USHORT) SendMessage(hwnd, nRgMsgGetCtrlFlags, 0, 0);
}

#ifdef VB_VERSION
inline USHORT GetCtrlFlags(HCTL hctl)
{
    return (USHORT) VBSendControlMsg(hctl, nRgMsgGetCtrlFlags, 0, 0);
}
#endif

// nRgMsgDoClick - Fires the Click event of the control
//   wparam - BOOL fBloop - TRUE to do animation.
//   lparam - Not used
//   returns - TRUE if the Click event was fired.
extern const UINT NEAR nRgMsgDoClick;

inline BOOL FDoClick(HWND hwnd, BOOL fDoAnim)
{
    return (BOOL) SendMessage(hwnd, nRgMsgDoClick, fDoAnim, 0);
}

#ifdef VB_VERSION
inline BOOL FDoClick(HCTL hctl, BOOL fDoAnim)
{
    return (BOOL) VBSendControlMsg(hctl, nRgMsgDoClick, fDoAnim, 0);
}
#endif

extern const UINT NEAR nRgMsgErrorClick;
inline BOOL FErrorClick(HWND hwnd)
{
    return (BOOL) SendMessage(hwnd, nRgMsgErrorClick, 0, 0);
}

#ifdef VB_VERSION
inline BOOL FErrorClick(HCTL hctl)
{
    return (BOOL) VBSendControlMsg(hctl, nRgMsgErrorClick, 0, 0);
}
#endif

inline void PostErrorClick(HWND hwnd)
{
    PostMessage(hwnd, nRgMsgErrorClick, 0, 0);
}

//UNDONE: Remove these as soon as Gazoo removes their references to them.
extern const UINT NEAR nRgMsgDefaultOK;
extern const UINT NEAR nRgMsgDefaultCancel;
