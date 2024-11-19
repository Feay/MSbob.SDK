/////////////////////////////////////////////////////////////////////
//
//  STDAFX.H
//
//  This is the global list of precompiled headers.  If you wish
//  to add to it, make sure it works for everybody.
//
////////////////////////////////////////////////////////////////////

//#pragma message ("Compiling the Utopia Precompiled Header file...")

#include <afxwin.h>
#include <afxcoll.h>
#include <afxext.h>
#include <string.h>
#include <ole2.h>  // includes most other OLE header files
#include <dispatch.h>
#include <olenls.h>

#include <udebug.h>

// NOTE: This hoses the IMPLEMENT_DYNCREATE and IMPLEMENT_SERIAL macros
// so 'new' must be #undefed around code that uses these macros, thus:
//
// #ifdef new
// #undef new
// #endif
// IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)
// #define new DEBUG_NEW

#define new DEBUG_NEW

/////////////////////////////////////////////////////////////////////////////
// VB-Event parameter macros (from MFC tech note #27)
// 01-21-94 FordM Corrected AFX_NUM_EVENTPARAMINDEX macro

#define AFX_NUM_EVENTPARAM(type, lpParams) \
    (type FAR&)(**(type FAR* FAR*)lpParams)
#define AFX_HLSTR_EVENTPARAM(lpParams) \
    (HLSTR FAR&)(*(HLSTR FAR*)lpParams)
#define AFX_NUM_EVENTPARAMINDEX(type, lpParams, index) \
    (type FAR&)(**((type FAR* FAR*)(lpParams) + index))
#define AFX_HLSTR_EVENTPARAMINDEX(lpParams, index) \
    (HLSTR FAR&)(*((HLSTR FAR*)(lpParams) + index))

