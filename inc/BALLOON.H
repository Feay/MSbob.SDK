//---------------------------------------------------------------------------
//        Copyright (C) 1992-3, Microsoft Corporation
//---------------------------------------------------------------------------
// Balloon.h
//---------------------------------------------------------------------------
// Contains code to draw the balloon of the RgnWnd control
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
#define DIPSIDE_LEFT    0
#define DIPSIDE_RIGHT   1
#define DIPSIDE_TOP     2
#define DIPSIDE_BOTTOM  3

//---------------------------------------------------------------------------
// Dipdodo Style
#define DIPSTYLE_NONE           0
#define DIPSTYLE_POINTER        1
#define DIPSTYLE_BUBBLES        2
#define DIPSTYLE_ARROW          3

class CBalloonStyle
{
public:
    // Border data
    POINT m_ptCorner;
    SIZE  m_sizeBorder;
    SHORT m_sPenWidth;

    // Color data
    COLORREF m_clrBack;
    COLORREF m_clrBorder;

    // Dipdido data
    SHORT m_sDipSide;
    SHORT m_sDipBaseWidth;
    SHORT m_sDipBaseShift;
    SHORT m_sDipHeight;
    SHORT m_sDipOffset;
    SHORT m_sDipStyle;
};

//---------------------------------------------------------------------------
// class CBalloon
//---------------------------------------------------------------------------
class CBalloon
{
public:
    CBalloon(CBalloonStyle const *pstyle);
    ~CBalloon(void);

    void _export SetStyle(CBalloonStyle const *pstyle);
    CBalloonStyle * GetStyle(void) {return (CBalloonStyle *) m_pstyle;};

    // One of the below functions should be called to
    // fill in calculated data of CBalloon.
    void _export SetSize(SHORT sWidth, SHORT sHeight);
    void _export CalcRect(LPRECT prectTarget, LPRECT prectBoundary,
    LPRECT rect);

    // Draw the balloon into the hdc
    void _export Draw(HDC hdc);

    // HitTest the balloon
    SHORT _export HitTest(int x, int y);

    // Get the window's region.
    HRGN _export GetRgn(SHORT iRgn);

    void _export GetInnerRect(LPRECT prect);

    // Get the background brush
    HBRUSH _export GetBkgndBrush(HDC hdc);
    void _export PurgeCache(void);

private:
    CBalloonStyle const * m_pstyle;

    // The following may be different from field in m_pstyle
    // if CalcPos had to change orientation of the balloon
    SHORT m_sDipSide;
    SHORT m_sDipOffset;

    // Corner Width may have been reduced depending on size of balloon
    POINT m_ptCorner;

    // Graphical data to draw balloon
    RECT  m_rctRnd;         // RECT for rounded rectangle portion of balloon
    POINT m_rgptDip[7];     // Array of points for drawing Dipdido
    RECT  m_rgrctBubble[3]; // Array of rectangles for drawing a bubble dipdido

    HRGN  m_hrgnOuter;      // The region the balloon occupies.

    BOOL CacheRgns(void);
    BOOL FDipSideOk(LPRECT prectTarget,SHORT sWidth, SHORT sHeight,
    LPRECT prectBoundary);

    HBRUSH m_hbrBkgnd;      // Background brush held for GetBkgndBrush

    BOOL m_fDipFits;        // Set to true if dip fits (dip points to object,
                            // and rgnwnd is within boundary rect)
};

#define cxBalloonMargin 8
#define cyBalloonMargin 8
