// crgn.h

#ifndef _CRGN
#define _CRGN

#include "balloon.h"
#include "clipping.h"

// the following hit test stuff ws extracted from vbapi.h
#define HT_ON         7
#define HT_SOLID_NEAR     6
#define HT_PATTERN_NEAR   5
#define HT_HOLLOW_NEAR    4
#define HT_SOLID      3
#define HT_PATTERN    2
#define HT_HOLLOW     1
#define HT_MISS       0
typedef struct tagHITTEST
  {
  POINT pt;     // Point to test (in parent's coordinates)
  RECT  rect;       // Rect of self (in parent's coordinates)
  } HITTEST;
typedef HITTEST FAR *LPHITTEST;

typedef enum tagAUTOSIZE
        { AutoSizeNone, AutoSizeResize, AutoSizeRestore,
            AutoSizeResizeNoPos, AutoSizeNoneYesPos, AutoSizeEnd} AUTOSIZE;

typedef enum tagSTATUS
        { NotLoaded, Loaded, FirstTime } STATUS;

typedef struct tagRGNWND_FLAGS
{
    unsigned int enMousePointer:3; //Mouse pointer type //UNDONE: form or control property???
    int fCached:1;        //Currently cached
    int fCacheOnClose:1;  //If True, then Cache on AutoClose
    unsigned int sAutoScale:2;     //
} RGNWND_FLAGS;

#define AUTOSCALE_NONE    0
#define AUTOSCALE_RUNTIME 1
#define AUTOSCALE_ALL     2

// UNDONE:  This is the exact same list, with different names, as the list of
// balloon styles in tippage.h, with the addition of the CBALLOONSTYLES (which
// perhaps should be renamed BS_MAX).

enum {
    iBalloonStyleCustom = 0,
    iBalloonStyleSpeakPointerBottom,
    iBalloonStyleSpeakPointerRight,
    iBalloonStyleThinkBubblesBottom,
    iBalloonStyleThinkBubblesRight,
    iBalloonStyleArrowLeft,
    iBalloonStyleArrowRight,
    iBalloonStyleArrowUp,
    iBalloonStyleArrowDown,
    iBalloonStyleSquare,
    CBALLOONSTYLES,
};

/////////////////////////////////////////////////////////////////////////////
// CRgnWndDialog - a modal or modeless dialog

class CRgnWndDialog : public CDialog
{
    DECLARE_DYNAMIC(CRgnWndDialog)

public:
    // visible interface routines
    void SetAutoPos(AUTOSIZE asz, LPRECT prcBounds = NULL);
    void SetObjectRect(RECT rctOb)
      { m_rctObject = rctOb; }
    void SetObjectRect(RECT *rctOb)
      { m_rctObject = *rctOb; }
    void SetObjectRect(CRect rctOb)
      { m_rctObject = rctOb; }
    void SetBalloonStyle(short Style);
    CBalloonStyle *GetBalloonStyle();
    void SetAutoClose(BOOL fClose);
    void SetModal(BOOL fModal);
    void CalcModalLevel(void);
    void SetOpaque(BOOL opaque);
    void SetMousePointer(LPCSTR lpcsMousey);

    void InitialSetFocus(void);

    // passthrough create to CDialog
    BOOL Create(UINT nIDTemplate, CWnd* pParentWnd /* = NULL */)
        { return CDialog::Create(MAKEINTRESOURCE(nIDTemplate), pParentWnd); }

    int DoModal(BOOL fModal);
    int DoModal(void) {return DoModal(TRUE);};
    int UDoModal(void) {return DoModal(TRUE);};
    int DoModalWithAutoClose(void);

    // special "dont allow this window to move" flag
    BOOL m_fNoMove;

    void AutoPos(void);

protected:
    CRgnWndDialog();
    // internal utilitiy routines
    void AutoPos(BOOL bFirst);
    void MoveControls(int dx, int dy);
    void SetDefaults();
    void AutoScale();
    void AutoSizeRgnWnd(AUTOSIZE autsize);
    void UpdateRgnWndSize();
    SHORT RgnWndHittest(LPHITTEST lpht);
    BOOL UIsControlVisible(HWND hwnd);
    void OnPaintHdc(HDC hdc);

    // internal variables
    // the first one is here only for compatibility with
    // the equivalent VB routines.
    RGNWND_FLAGS m_fl;      // Bitfield structure

    SHORT         m_sBalloonStyle;
    CBalloonStyle m_balloonstyle;  // Balloon Data
    CBalloon     *m_pballoon;

    HWND        m_hwndRealParent;

    // Rect for AutoPos target object
    RECT        m_rctObject;
    SIZE        m_sizeAutoScale;
    RECT        m_rctBounds;

    // AutoClose/Modality propertyies
    BOOL        m_fAutoClose;
    BOOL        m_fModal;
    SHORT       m_sModalLevel;

    // Non-property state information
    STATUS      m_fLoaded;
    AUTOSIZE    m_autosize;
    BOOL        m_bOpaque;

    RECT        m_rctWndRgn;

    HCURSOR     m_ghcurMove;
    HCURSOR     m_ghcurNormal;
    LONG        m_lstyle;

    // CDialog Overrides
public:
    CRgnWndDialog(LPCSTR lpszTemplateName, CWnd* pParentWnd = NULL);
    CRgnWndDialog(UINT nIDTemplate, CWnd* pParentWnd = NULL);

    ~CRgnWndDialog();

    virtual void OnOK();
    virtual void OnCancel();
    void SetNoActivate(BOOL fNoActivate)
        {m_fNoActivate = fNoActivate;};

    virtual void EndDialog(int nResult)
        {
        CDialog::EndDialog(nResult);
        };
private:
    BOOL m_fInDefKey;
    BOOL m_fKeepFocus;
    BOOL m_fNoActivate;

    virtual BOOL OnInitDialog(void);  
    
    static BOOL s_fRemovedSaveBits;

protected:

    virtual BOOL FInitDialog(BOOL fDoSetFocus = TRUE);

    //{{AFX_MSG(CRgnWndDialog)
    afx_msg void OnPaint();
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg void OnDestroy();
    afx_msg void OnMove(int x, int y);
    afx_msg void OnSize(UINT nType, int cx, int cy);
    afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
    afx_msg BOOL OnEraseBkgnd(CDC* pDC);
    afx_msg void OnNcDestroy();
    afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);

    afx_msg BOOL OnQueryNewPalette();
    afx_msg void OnPaletteChanged(CWnd* pFocusWnd);
    afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

    afx_msg int OnMouseActivate(CWnd* pWnd, UINT nHitTest, UINT message);
    afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
    afx_msg void OnWindowPosChanging( WINDOWPOS FAR* lpwndpos );
    afx_msg void OnWindowPosChanged( WINDOWPOS FAR* lpwndpos );
    afx_msg UINT OnNcHitTest( CPoint pt );
    afx_msg LONG OnAutoClose(UINT wp, LONG  lp);
    afx_msg LONG OnGetRgn(UINT wp, LONG lp);
    afx_msg LONG OnQueryAutoClose(UINT wp, LONG  lp);
    afx_msg LONG OnErrorClick(UINT wp, LONG  lp);
    afx_msg LONG OnChangePC(UINT wparam, LONG lparam);
    afx_msg void OnSetFocus(CWnd* pOldWnd);
    afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};


// Useful helper function:

void MySendMessageToDescendants(HWND hwnd, UINT message, UINT wParam, LONG lParam, BOOL fDeep);


#endif //_crgn
