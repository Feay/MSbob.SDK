/******************************************************************
* Microsoft Jet
*
* Microsoft Confidential.  Copyright 1991 Microsoft Corporation.
*
* Component: CLI
*
* File: Stubs for client functions required by EB
*
* File Comments:
* <comments>
*
* Revision History:
*
*    [0]  30-May-91  RichardS	Created
*
******************************************************************/

#define STRICT

#define WINVER	0x0300		       /* Support Windows 3.00 and above */

#include <windows.h>


BOOL FAR PASCAL FTrappableClientErr(unsigned err)
{
   err = err;

   return(0);
}


BOOL FAR PASCAL FRetrySegError(_segment seg, unsigned cb, unsigned cRetry)
{
   seg = seg;
   cb = cb;
   cRetry = cRetry;

   return(0);
}


unsigned FAR PASCAL ErrCIInvoke(unsigned cArgs)
{
   cArgs = cArgs;

   return(8);
}


unsigned FAR PASCAL CbClientRtError(char FAR *pb, unsigned cbMax, unsigned err, int fUseLast)
{
   pb = pb;
   cbMax = cbMax;
   err = err;
   fUseLast = fUseLast;

   return(0);
}


void FAR PASCAL PushMessageLoop(void)
{
}


void FAR PASCAL ExitMessageLoop(void)
{
}


unsigned FAR PASCAL GetcMsgLoopCur(void)
{
   return(1);
}


void FAR PASCAL DestroyWnModule(HWND hwnd)
{
   hwnd = hwnd;
}


void FAR PASCAL RebindExpr(void)
{
}


int FAR PASCAL ErrLookupObject(char FAR *stVarName, unsigned oMrs, char _near *pClientVar)
{
   stVarName = stVarName;
   oMrs = oMrs;
   pClientVar = pClientVar;

   return(8);
}


unsigned FAR PASCAL ErrOpenModule(const char FAR *szModule, unsigned mode)
{
   szModule = szModule;
   mode = mode;

   return(8);
}


unsigned FAR PASCAL ErrCloseModule(void)
{
   return(8);
}


unsigned FAR PASCAL ErrReadModule(char FAR *pv, unsigned long cb, unsigned long FAR *pcbRead)
{
   pv = pv;
   cb = cb;
   pcbRead = pcbRead;

   return(8);
}


unsigned FAR PASCAL ErrWriteModule(const void FAR *pv, unsigned long cb)
{
   pv = pv;
   cb = cb;

   return(8);
}


unsigned FAR PASCAL ErrNewModuleObject(void)
{
   return(8);
}


unsigned FAR PASCAL ErrOpenModuleObject(char _near *szModule)
{
   szModule = szModule;

   return(8);
}


int FAR PASCAL FExistModuleName(char FAR *szModule)
{
   szModule = szModule;

   return(0);
}


HWND FAR PASCAL ClientSetFocus(HWND hwnd)
{
   hwnd = hwnd;

   return(hwnd);
}


unsigned long FAR PASCAL GetWidthHeight(void FAR *pObjectData)
{
   pObjectData = pObjectData;

   return(480UL << 16 + 640UL);        /* Assume VGA */
}


unsigned FAR PASCAL ClsLookupClass(unsigned cls, char FAR *lpchname, unsigned cchName)
{
   cls = cls;
   lpchname = lpchname;
   cchName = cchName;

   return(0);
}


unsigned FAR PASCAL OmthMapMethod(unsigned cls, unsigned imth)
{
   cls = cls;
   imth = imth;

   return(0xffff);
}


unsigned FAR PASCAL ErrPrintOut(void FAR *prcOut, char FAR *szText)
{
   prcOut = prcOut;
   szText = szText;

   return(8);
}


int FAR PASCAL DoEbMessage(HWND hwndParent, LPSTR lpText, LPSTR lpCaption, WORD wType)
{
   return(MessageBox(hwndParent, lpText, lpCaption, wType));
}


void FAR PASCAL NotifyChangeCurrentProc(void)
{
}


HWND FAR PASCAL HwndWnNewImmediate(int x, int y, int cx, int cy, HWND hwndParent)
{
   x = x;
   y = y;
   cx = cx;
   cy = cy;
   hwndParent = hwndParent;

   return(NULL);
}


LRESULT FAR PASCAL DefImmediateWindowProc(HWND hwnd, WORD wMsg, WPARAM wParam, LPARAM lParam)
{
   return(DefWindowProc(hwnd, wMsg, wParam, lParam));
}


BOOL FAR PASCAL ShowWnImmediate(HWND hwnd, int nCmdShow, HWND hwndParent)
{
   hwndParent = hwndParent;

   return(ShowWindow(hwnd, nCmdShow));
}


void FAR PASCAL DestroyWnImmediate(HWND hwnd)
{
   DestroyWindow(hwnd);
}


HWND FAR PASCAL HwndWnNewModule(unsigned long dbid, char FAR *sz)
{
   dbid = dbid;
   sz = sz;

   return(0);
}


LRESULT FAR PASCAL DefModuleWindowProc(HWND hwnd, WORD wMsg, WPARAM wParam, LPARAM lParam)
{
   return(DefWindowProc(hwnd, wMsg, wParam, lParam));
}


void FAR PASCAL GetTimeStampOfModule(char FAR *rgchModule, unsigned cchModule, void FAR *pdt)
{
   rgchModule = rgchModule;
   cchModule = cchModule;
   pdt = pdt;
}


BOOL FAR PASCAL FReadPermissionSzModule(char FAR *lpszModule)
{
   lpszModule = lpszModule;

   return(0);
}


typedef struct { char rgb[12]; } VL;


int FAR PASCAL ErrExecuteCmd(VL vl1, VL vl2, VL vl3, VL vl4, VL vl5, VL vl6,
	      VL vl7, VL vl8, VL vl9, VL vl10, VL vl11, VL vl12, VL vl13,
	      unsigned short cArg, int iCmd)
{
   vl1 = vl1;
   vl2 = vl2;
   vl3 = vl3;
   vl4 = vl4;
   vl5 = vl5;
   vl6 = vl6;
   vl7 = vl7;
   vl8 = vl8;
   vl9 = vl9;
   vl10 = vl10;
   vl11 = vl11;
   vl12 = vl12;
   vl13 = vl13;
   cArg = cArg;
   iCmd = iCmd;

   return(8);
}


char FAR * FAR PASCAL LszCmdNameOfICmd(int iCmd, char FAR *rgchBuf, unsigned short cchMax)
{
   iCmd = iCmd;
   cchMax = cchMax;

   return(rgchBuf);
}


long FAR PASCAL ICmdOfCmdName(const char FAR *szCmd)
{
   szCmd = szCmd;

   return(-1);
}


void FAR PASCAL InitDialogPosition(HWND hwnd, WORD w)
{
   hwnd = hwnd;
   w = w;
}


int FAR PASCAL ClientDialogBoxParam(HINSTANCE hInst, LPCSTR lpszDlgTemp, DLGPROC dlgprc, LPARAM lparamInit)
{
   hInst = hInst;
   lpszDlgTemp = lpszDlgTemp;
   dlgprc = dlgprc;
   lparamInit = lparamInit;

   return(0);
}


void FAR PASCAL ClientSetHelpTopic(WORD w)
{
   w = w;
}


void FAR PASCAL RefreshToolbarButtons(HWND hwnd)
{
   hwnd = hwnd;
}


void FAR PASCAL GetLszFromDbid(unsigned long dbid, LPSTR szName, WORD cchMax)
{
   dbid = dbid;
   szName = szName;
   cchMax = cchMax;
}


void FAR PASCAL ClientSetWaitCursor(void)
{
}


HWND FAR PASCAL hwndCurrentDoc(void)
{
   return((HWND) 0);
}


void FAR PASCAL ActivateDocWindow(HWND hwnd)
{
   hwnd = hwnd;
}


BOOL FAR PASCAL ClientFOverType(void)
{
   return(0);
}


void FAR PASCAL ActivateModuleWindow(HWND hwnd)
{
   hwnd = hwnd;
}


BOOL FAR PASCAL ClientEPaneMsgFilter(LONG FAR *plresult, HWND FAR *phwnd, WORD FAR *pmessage, WORD FAR *pwParam, LONG FAR *plParam)
{
   plresult = plresult;
   phwnd = phwnd;
   pmessage = pmessage;
   pwParam = pwParam;
   plParam = plParam;

   return(0);
}


BOOL FAR PASCAL CirGetOpenFileName(LPVOID /* LPOPENFILENAME */ lpofn)
{
   lpofn = lpofn;

   return(0);
}


BOOL FAR PASCAL CirGetSaveFileName(LPVOID /* LPOPENFILENAME */ lpofn)
{
   lpofn = lpofn;

   return(0);
}


DWORD FAR PASCAL CirCommDlgExtendedError(void)
{
   return(0);
}


DWORD FAR PASCAL GetPrtTextExtent(void FAR * dc, LPSTR str, int cb)
{
   dc = dc;
   str = str;
   cb = cb;

   return(0);
}


BOOL FAR PASCAL FDlgMsgFilter(HWND hdlg, WORD wm, WORD wParam, LONG lParam)
{
   hdlg = hdlg;
   wm = wm;
   wParam = wParam;
   lParam = lParam;

   return(0);
}


BOOL FAR PASCAL FAbortEventEb(void)
{
   return(0);
}

VOID FAR PASCAL VB_ApiDispatch()
	{
	return;
	}
VOID FAR PASCAL EE_ApiDispatch()
	{
	return;
	}

VOID FAR PASCAL RemoveKeyMouseMessages()
	{
	return;
	}
