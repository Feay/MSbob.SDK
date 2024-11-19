//---------------------------------------------------------------------------
// SOBDLG.CPP
//
// IMPORTANT: In order for balloon dialogs to work properly, derived classes
// must make sure CSobDialog receives OnInitDialog and OnWindowPosChanging
// messages.
//
// Moved to \inc to allow inclusion in any dll, to overcome problems
// exporting the message map.  This code depends on the Shellsrv dll.
//
// History:
// 04-24-93 DarrinM     Created.
// 04-09-94 DarrinM     Switched from Sob-based to CRgnWndDialog-based.
// 11-02-94 AlanMa		Added fBlnPreventFocus chk
//---------------------------------------------------------------------------

#include "stdafx.h"
#include "sobdlg.h"
#include <dbg.h>
#include <actor.h>
#include <image.h>
#include <compont.h>


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// UDialogCountSink class definition and implementation
//
// Used by fBlnSubmissive (modeless) dialogs to be notified when they
// should hide and show themselves.
//
// History:
// 01-13-94 DarrinM     Created.
//---------------------------------------------------------------------------

class UDialogCountSink : public ISysSink, CSimple {
public:
    UDialogCountSink(CSobDialog *pdlg) { m_pdlg = pdlg; }

private:
    CSobDialog *m_pdlg;

public:
    // IUnknown methods and data

    DECLARE_IUNKNOWN;

    // ISysSink methods

    STDMETHOD(OnPropertyChange)(const char *pszPropName, const void *pvData,
            long cbDataMax, ULONG ffOrder);
    STDMETHOD(OnObjectAdd)(const void *pvObject, ULONG ffOrder) {
        return S_OK;
    }
    STDMETHOD(OnObjectRemove)(const void *pvObject, ULONG ffOrder) {
        return S_OK;
    }
};


DEFINE_IUNKNOWN_(UDialogCountSink, ISysSink);

STDMETHODIMP UDialogCountSink::OnPropertyChange(const char *pszPropName,
        const void *pvData, long cbDataMax, ULONG ffOrder)
{
    // This sink is only called for when the Home's propDialogCount
    // property is changed.

    static long cblnOld;

    if (ffOrder & fAdvBefore) {
        IHome *phome = GetHome();
        OOSRELEASE(phome);
        phome->GetProperty(propDialogCount, &cblnOld, sizeof(cblnOld));

    } else if (ffOrder & fAdvAfter) {
        long cblnNew = *(long *)pvData;
        if (cblnNew == 1 && cblnOld == 0) {

            // Hide the submissive balloon.

            m_pdlg->ShowWindow(SW_HIDE);

        } else if (cblnNew == 0 && cblnOld == 1) {

            // Show the submissive balloon.

            m_pdlg->ShowWindow(SW_SHOW);
        }
    }

    return S_OK;
}


//---------------------------------------------------------------------------
// CSobDialog dialog

CSobDialog::CSobDialog(UINT nIDTemplate, CWnd* pParent, CRect *prcOwner,
        ULONG ff)
    : CRgnWndDialog(nIDTemplate, pParent)
{
    //{{AFX_DATA_INIT(CSobDialog)
        // NOTE: the ClassWizard will add member initialization here
    //}}AFX_DATA_INIT

    m_ff = ff;
    if (prcOwner != NULL)
        m_rcOwner = *prcOwner;

    m_fModal = FALSE;
#if 0
    SetNoActivate(TRUE);
#endif
}


CSobDialog::~CSobDialog()
{
    if (m_ff & fBlnSubmissive) {
        IHome *phome = GetHome();
        OOSRELEASE(phome);
        phome->Unadvise(m_dwSinkId);
    }

    if (m_pActor)
        m_pActor->Release();
}


BEGIN_MESSAGE_MAP(CSobDialog, CRgnWndDialog)
    //{{AFX_MSG_MAP(CSobDialog)
    ON_WM_WINDOWPOSCHANGING()
    ON_WM_CLOSE()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

//---------------------------------------------------------------------------
// CSobDialog message handlers

//---------------------------------------------------------------------------
// OnInitDialog
//
//
// History:
// 04-24-93 DarrinM     Created.
// 01-13-94 DarrinM     Added fBlnSubmissive stuff.
//---------------------------------------------------------------------------

BOOL CSobDialog::FInitDialog(BOOL fDoSetFocus)
{
    if (m_ff & fBlnSubmissive) {
        ISysSink *psnk = new UDialogCountSink(this);
        if (psnk == NULL)
            return FALSE;

        // Release the sink so when the final Unadvise is called (in
        // CSobDialog destructor) the sink will be freed.

        OOSRELEASE(psnk);

        IHome *phome = GetHome();
        OOSRELEASE(phome);

        if (phome->Advise(propDialogCount, psnk, &m_dwSinkId,
                fAdvBefore | fAdvAfter) != S_OK)
            return FALSE;
    }

    // Map fBln flags to something CRgnWndDialog can use.

    if (m_ff & fBlnPosOnScreen) {
        SetObjectRect(m_rcOwner);
        SetBalloonStyle(iBalloonStyleArrowRight);
    }

    if (m_ff & fBlnCancelModal) {
        SetAutoClose(TRUE);
    }

    // get actor pointer

    GetGuide(&m_pActor, &m_rcActor);
    
    if(m_ff & fBlnPreventFocus)
    	fDoSetFocus = FALSE;

    return CRgnWndDialog::FInitDialog(fDoSetFocus);
}


void CSobDialog::OnWindowPosChanging(WINDOWPOS FAR *pwndpos)
{
    extern void IncDecDialogCount(int n);

    if ((pwndpos->flags & SWP_SHOWWINDOW) && !IsWindowVisible()) {

        // Dominant dialogs (the default) increment the Shell's count of
        // dominant dialogs which triggers AdviseSinks set by fBlnSubmissive
        // balloons so they can hide.  The hiding submissive dialogs show
        // themselves again when they're advised of the dominant count being
        // decremented to 0.

        if (!(m_ff & fBlnSubmissive))
            IncDecDialogCount(1);

        if (m_ff & fBlnBeginSpeaking)
            m_pActor->PlayAction(actionBeginSpeaking, fAsync);

        GetWindowRect(&m_rc);
    }

    if ((pwndpos->flags & SWP_HIDEWINDOW) && (IsWindowVisible())){

        // Dominant dialogs decrement the Room's propDialogCount.

        if (!(m_ff & fBlnSubmissive))
            IncDecDialogCount(-1);
    
#if 0
    CWnd *pwndParent = GetParent();

    Assert(pwndParent != NULL, slError, "CSobDialog does not have an owner!");
    if (pwndParent)
      pwndParent->SetFocus();
#endif
    }


    CRgnWndDialog::OnWindowPosChanging(pwndpos);
}


void IncDecDialogCount(int n)
{
    IHome *phome = GetHome();
    OOSRELEASE(phome);

    long cbln;
    phome->GetProperty(propDialogCount, &cbln, sizeof(cbln));
    cbln += n;
    phome->SetProperty(propDialogCount, &cbln, sizeof(cbln));
}


//---------------------------------------------------------------------------
// DoModal
//
//
// History:
// 04-13-94  DarrinM    Created.
//---------------------------------------------------------------------------

int CSobDialog::DoModal()
{
    SetNoActivate(FALSE);
    if (!(m_ff & fBlnCache))
        return CRgnWndDialog::DoModal();

    // Set make the dialog modal (and automatically set the modal level)
    Assert(!m_fModal, slError, "Dialog already in modal state!");
    SetModal(TRUE);

    // Create the dialog if it isn't already, otherwise just show it.

    if (m_hWnd == NULL) {
        if (!Create(LOWORD(m_lpDialogTemplate), m_pParentWnd))
            return -1;
    } else {

        InitialSetFocus();

        // Show it.

        ShowWindow(SHOW_OPENWINDOW);
        UpdateWindow();
    }

    // Disable the parent window.

    m_pParentWnd->EnableWindow(FALSE);

    // Do the modal loop.

    MSG msg;
    while (m_fModal && GetMessage(&msg, NULL, NULL, NULL)) {
        if (!IsDialogMessage(&msg)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return m_idResult;
}


void CSobDialog::EndDialog(int idResult)
{
    if (!(m_ff & fBlnCache)) {
        CRgnWndDialog::EndDialog(idResult);
        return;
    }

    m_pParentWnd->EnableWindow(TRUE);
    m_pParentWnd->SetFocus();
    SetWindowPos(NULL, 0, 0, 0, 0, SWP_HIDEWINDOW | SWP_NOACTIVATE |
            SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER);

    m_idResult = idResult;
    m_fModal = FALSE;
    m_sModalLevel = 0;
}


// AutoPos is a protected member of CRgnWndDialog so this is how we
// get to it.

void CSobDialog::AutoPos(BOOL bFirst)
{
    CRgnWndDialog::AutoPos(bFirst);
}


BOOL CSobDialog::OnReInitDialog()
{
    return TRUE;
}


void CSobDialog::OnClose()
{
    OnCancel();
}

void CSobDialog::OnClickOk(UINT a, int b, CWnd* c, LPVOID d)
{
    if (m_pActor != NULL)
        m_pActor->PlayAction(actionCharacterSuccessMinor, fAsync);

    if (m_ff & fBlnCancelModal && !(m_ff & fBlnCache)) {
        DestroyWindow();
        delete this;
    } else {
        EndDialog(IDOK);
    }
}


// NOTE:  This code assumes dialogs created modeless have fBlnCancelModal,
// and dialogs created modal do not.  If you have a modeless dialog w/o
// this flag set, do not call OnCancel, but call DestroyWindoy and delete
// 'this' in your own code.  You cannot have a modal bln that is
// fBlnCancelModal.

void CSobDialog::OnClickCancel(UINT a, int b, CWnd* c, LPVOID d)
{
    if (m_pActor != NULL)
        m_pActor->PlayAction(actionAcknowledgingACancel, fAsync);

    if (m_ff & fBlnCancelModal && !(m_ff & fBlnCache)) {
        DestroyWindow();
        delete this;
    } else {
        EndDialog(IDCANCEL);
    }
}

