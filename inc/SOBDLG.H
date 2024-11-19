/////////////////////////////////////////////////////////////////////////////
// SOBDLG.H
//
//
// History:
// 04-24-93 DarrinM     Created.
// 04-09-94 DarrinM     Now derives from CRgnWndDialog.
// 11-02-94 AlanMa		Added fBlnPreventFocus
/////////////////////////////////////////////////////////////////////////////

#ifndef __SOBDLG_H__
#define __SOBDLG_H__

#include <shellsrv.h>
#include <actor.h>
#include <actions.h>
#include <crgn.h>

/////////////////////////////////////////////////////////////////////////////
// CSobDialog dialog

//const ULONG fBlnExpandForBln =  0x0001;
const ULONG fBlnPosOnScreen =   0x0002;
//const ULONG fBlnNoStem =        0x0004;
//const ULONG fBlnStemLeft =      0x0008;
//const ULONG fBlnStemRight =     0x0010;
//const ULONG fBlnStemTop =       0x0020;
//const ULONG fBlnStemBottom =    0x0040;
//const ULONG fBlnInterceptInput =0x0080;  //set for a dialog that cancels on NC mouse click
const ULONG fBlnCancelModal =   0x0100;  //set for a modeless input-intercept dialog
//const ULONG fBlnNoRedraw =      0x0200;
const ULONG fBlnPosByWizard =   0x0400;
//const ULONG fBlnDisabled =      0x0800;
const ULONG fBlnSubmissive =    0x1000;  // balloons that hide when others show
//const ULONG fBlnExpandForStem = 0x2000;
const ULONG fBlnCache =         0x4000;
const ULONG fBlnBeginSpeaking = 0x8000;
const ULONG fBlnPreventFocus  = 0x0010;

class CSobDialog : public CRgnWndDialog
{
// Construction
public:
    CSobDialog(UINT nIDTemplate, CWnd* pParent, CRect *prcOwner = NULL,
            ULONG ff = 0);
    virtual ~CSobDialog();
    virtual int DoModal();
    virtual void EndDialog(int idResult);
    void AutoPos(BOOL bFirst);
    virtual BOOL OnReInitDialog();

// Dialog Data
    //{{AFX_DATA(CSobDialog)
//  enum { IDD = _UNKNOWN_RESOURCE_ID_ };
        // NOTE: the ClassWizard will add data members here
    //}}AFX_DATA

protected:
    IActor *m_pActor;
    CRect m_rcActor;
    CRect m_rc;

private:
    ULONG m_ff;
    DWORD m_dwSinkId;
    CRect m_rcOwner;
    BOOL m_fModal;
    int m_idResult;

// Implementation
protected:
    virtual void OnClickOk(UINT a = 0, int b = 0, CWnd* c = 0, LPVOID d = 0);
    virtual void OnClickCancel(UINT a = 0, int b = 0, CWnd* c = 0, LPVOID d = 0);

    virtual BOOL FInitDialog(BOOL fDoSetFocus = TRUE);

    // Generated message map functions
    //{{AFX_MSG(CSobDialog)
    afx_msg void OnWindowPosChanging(WINDOWPOS FAR *pwndpos);
    afx_msg void OnClose();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

void IncDecDialogCount(int n);

#endif // #ifdef __SOBDLG_H__
