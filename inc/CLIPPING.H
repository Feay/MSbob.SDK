//---------------------------------------------------------------------------
//        Copyright (C) 1992-3, Microsoft Corporation
//---------------------------------------------------------------------------
// Clipping.h
//---------------------------------------------------------------------------
// Contains clipping code for Utopia apps.
//---------------------------------------------------------------------------

#ifndef __CLIPPING__
#define __CLIPPING__

//---------------------------------------------------------------------------
// Exported C routines
//---------------------------------------------------------------------------

#ifdef __cplusplus
extern "C" {            /* Assume C declarations for C++ */
#endif  /* __cplusplus */

HDC _export CDECL UGetDC(HWND hwnd);
HDC _export CDECL UBeginPaint(HWND hwnd, PAINTSTRUCT FAR * pps);
HDC _export CDECL UGetWindowDC(HWND hwnd);
void _export CDECL ClipWnds(HWND hwnd, HDC hdc, BOOL fAll);

#ifdef __cplusplus
}
#endif  /* __cplusplus */

// the rest of this is C++ specific 

#ifdef __cplusplus
#ifdef _AFX

//---------------------------------------------------------------------------
// Registered messages
//---------------------------------------------------------------------------
///static const UINT NEAR nRgMsgGetRgn = RegisterWindowMessage("UtopiaGetRgn");
extern const UINT NEAR nRgMsgGetRgn;

void _export CDECL ClipWnds(HWND hwnd, HRGN hrgn, BOOL fAll);

// CDC and CWnd class substitutes

#define UCWndGetDC() CDC::FromHandle(UGetDC(m_hWnd))
#define UCWndArgGetDC(x) CDC::FromHandle(UGetDC(x->m_hWnd))
#define UCWndGetWindowDC() CDC::FromHandle(UGetWindowDC(m_hWnd))
#define UCWndBeginPaint() CDC::FromHandle(UBeginPaint(m_hWnd, lpPaint))

// UPaintDC derives from the CPaintDC class of MFC
// and makes the appropriate calls to UBeginPaint ...

class UPaintDC : public CDC
{
// Constructors
public:
    UPaintDC(CWnd* pWnd)
    {
        if (!Attach(UBeginPaint(m_hWnd = pWnd->m_hWnd, &m_ps)))
            AfxThrowResourceException();
    }

// Attributes
protected:
    HWND m_hWnd;
public:
    PAINTSTRUCT m_ps;       // actual paint struct !

// Implementation
public:
    virtual ~UPaintDC()
    {
        ::EndPaint(m_hWnd, &m_ps);
        Detach();
    }
};

class UClientDC : public CClientDC
{
public:
    UClientDC(CWnd* pWnd) : CClientDC(pWnd)
      {
      if (m_hDC)
        ClipWnds(pWnd->m_hWnd, m_hDC, TRUE);
      };
};
#endif // of AFX part
#endif // of the C++ part

#endif
