/////////////////////////////////////////////////////////////////////////////
// QDoc.H
//
// WHAT IS IT?
//
//  This header specifies the Component Object interfaces to the QDoc service.
//  Please refer to qdoc.doc for an overview of the QDoc service.
//
//  HOW DO I USE IT?
//
//    Include this header file in
//  your program if you want to use any of the QDoc services.
//
//  ANYTHING ELSE I SHOULD KNOW?
//    
//  All of the interfaces defined here are abstract.  This is to emphasize
//  that they just specify the protocol of the various QDoc services, and 
//  are strictly separated from the implementation.
//
// History:
// 01-04-92 DLevy     Created.
/////////////////////////////////////////////////////////////////////////////


#ifndef QDoc_Def
#define QDoc_Def

// Data types

// Print options 
typedef long PrintOptions; 
#define poNil                          (0L)

//******************************* CARD PRINTING *****************************
// Card reserves print options 1-99
#define poPrintCardMin                 (1L)
#define poPrintCardTypeASideFold       (1L)
#define poPrintCardTypeATopFold        (2L)
#define poPrintCardTypeBSideFold       (3L)
#define poPrintCardTypeBTopFold        (4L)
#define poPrintCardTypeC               (5L)
#define poPrintCardTypeD               (6L)
#define poPrintCardTypeE               (7L)
#define poPrintCardMax                 (99L)
//******************************* CARD PRINTING *****************************

#include <uerror.h>

typedef HWND far *LPHWND;

// Constants

const int cbNameMax = 256;

enum ZoomMode {qdzmNil, qdzmAll, qdzmWholePage, qdzmWholeWidth, qdzmCustom, qdzmAllStacked };

enum ViewProperty { vpropFreeze, vpropHighlightSelection, vpropAllowDragDrop, vpropAllowMarginSelection,
    vpropAllowCharProperty, vpropAllowParaProperty, vpropAllowTyping, vpropAllowSelection,
    vpropShowMargins, vpropShowTextAsPrinted, vpropClipToPrintableArea, vpropAllowSpecialEffects,
    vpropAllowSmartQuotes, vpropAllowAutosave, vpropViewPageLayout, vpropMarkFieldText, vpropAutosaveToDoc, vpropDesktopColor, vpropCollectEdits,
    vpropSnapFramesToMargins, vpropAllowUndo, vpropAllowSelectionScrolling, vpropTitle, vpropDrawToOffscreenBitmap,
    };

enum CharProperty {cpropNil = -1, cpropNormal, cpropBold, cpropItalic, cpropUnderline,
    cpropFontSize, cpropFontName, cpropColor, cpropSuper, cpropSub, cpropForeColor, cpropBackColor,
    cpropSpacing, cpropSfx, cpropPosition, cpropStripAttr };

enum CharPropertySetting {tssOff, tssOn, tssMixed};

enum FontPosition { fposNormal, fposSuper, fposSub };
enum FontSpacing  { fspNormal, fspExpand, fspCondense };

enum ParaProperty {ppropNil = -1, ppropIndent, ppropJustify, ppropDoubleSpace,
    ppropDropCapLines, ppropPageBreakBefore, ppropBullet, ppropFirstBigLetter, ppropSpaceBetween, 
    ppropLeftIndentPts, ppropFirstLineIndentPts, ppropRightIndentPts,
    ppropLineSpacingRule, ppropLineSpacingPts};
 
enum JustifySetting { jsLeft, jsRight, jsCenter, jsJustify };
 
enum IndentStyle {inNone, inFirstLine, inAll, inFirstLineExtend};

enum ScrollCommands {scrUpLine, scrDownLine, scrUpScreen, scrDownScreen, scrUpPage,
	scrDownPage, scrLeftLine, scrRightLine, scrLeftScreen, scrRightScreen, 
	scrHorizontalRange, scrVerticalRange, scrGotoLine, scrGotoPage}; 

enum ScrollValue { scrvHLine, scrvVLine, scrvHBlob, scrvVBlob, scrvCurrentPage, scrvNumPages };
    
enum Qdch { qdchAnsi, qdchUnicode, qdchVKey};
enum TextType { ttAnsi, ttAnsiRtf, ttUnicode, ttUnicodeRtf, ttQuill};

enum DocProperty {dpropPageWidth, dpropPageHeight, dpropLeftMargin,
	dpropTopMargin, dpropRightMargin, dpropBottomMargin, dpropPageArrangement,
	dpropPageNum, dpropNumFirst, dpropTab,  dpropBorder, dpropBorderSize, dpropColumns,
	dpropLineBetweenColumns, dpropFacingPages, dpropCustomPageSize, dpropPrOrient, dpropMaxPages, 
		  dpropBackground };

enum PrinterInfo { prinfoPaperWidth, prinfoPaperHeight, prinfoMinLeftMargin,
	prinfoMinRightMargin, prinfoMinTopMargin, prinfoMinBottomMargin,
	prinfoHorzRes, prinfoVertRes, prinfoOrientation, prinfoDefaultSource,
	prinfoPaperSize, prinfoCopies, prinfoScale, prinfoColor, prinfoDuplex,
	prinfoPrinterName, prinfoDriverName, prinfoPortName
	};

enum PrOrient { prOrientDefault, prOrientPortrait, prOrientLandscape };

enum FrameProperty {fpropCustom, fpropFlatFile, fpropBorder, fpropType, 
	fpropStartPage, fpropTightWrap, fpropWrapType, fpropBackground, 
	fpropOleObject, fpropBlank, fpropLeft, fpropTop, fpropWidth, fpropHeight,
	fpropSelLeft, fpropSelTop, fpropSelWidth, fpropSelHeight, fpropBorderSize, fpropDisplayOnly, fpropNoUserSelect,
	fpropZOrder };

enum TextSelectCommand {tscWord, tscSentence, tscParagraph, tscAll, tscNone};

enum SpellCommand { spIgnoreOnce, spIgnoreAlways, spIgnoreSession, spReplaceOnce,
    spReplaceAlways, spUndo };
    
enum SpellCheckFlags { spcfAll, spcfSelected, spcfWord };

enum SelectionType {stNil, stFrame, stInsert, stTextRange, stBorder};    
// QDoc's private window message ids
enum Qdmsg {
    // Scrolling Messages
    
    WM_QPP_SETSCROLLCUR = (WM_USER + 0xA00),
    WM_QPP_SETSCROLLMAX,
    WM_QPP_SETSCROLLPAGEAMT,
    WM_QPP_SETSCROLLLINEAMT,

    // Set the Cursor
    // wp = crsXXX (as defined in quill.h)
    WM_QPP_SETCURSOR,
    WM_QPP_NEWSELECTION,
	 WM_QPP_HOTSPOTCLICK,
    WM_Q_OLEMESSAGE,
    WM_Q_INDRAGDROP,
    WM_Q_ADVISEERROR,
};

enum IdleMethod { idleTimed, idleManual, idleUtopia };

// REVIEW (davidb) - duplicate definitions.  At risk of drifting...
 
// UNDONE: These public ids need to be put into a file shared by both Kwill and QDoc 
#ifndef _quill_     // Declare only if the Quill header hasn't been included

enum {crsArrow, crsWatch, crsInsert, crsFrame, crsDrag, crsPage, crsMax };

enum DisplayMode {dmNil,
    dmAbove,            // show pages above one another 
    dmBeside,           // show pages beside one another 
    dmFacing,           // show facing pages, as many pairs as will fit 
    dmOne               // show just one page 
};

enum UpdateMode {
	umNil,              /* nothing to do */
	umRedraw,           /* no change to doc, just redisplay */
	umFormat,           /* formatting changed, no CP changes */
	umEdit,             /* CPs added, deleted, replaced */
	umFrame,            /* frame added, deleted, moved, etc. */
	umDrastic           /* something major happened */
};

    
#endif

// Single, Double, Triple, and Quadruple mouseclicks.
// mcExtend to extend the selection.
enum ClickType {ctSingle, ctDouble, ctTriple, ctQuad, ctExtend};

// BSTR* or LPSTREAM for QDoc::GetText and QDoc::SetText
enum StorageType {stLPSTR, stLPBSTR, stLPSTREAM};
   
DECLARE_INTERFACE(IControlAdvise)
{
    // Scroll messages
    
    STDMETHOD(SetScrollMax)(short dxp, short dyp) PURE;
    STDMETHOD(SetScrollCur)(short xp, short yp) PURE;
    STDMETHOD(SetScrollLineAmt)(short dxp, short dyp) PURE;
    STDMETHOD(SetScrollPageAmt)(short dxp, short dyp) PURE;
    
    // Update messages
    
    STDMETHOD(NewUserSelection)() PURE;
    
    // Cursor messages
    
    STDMETHOD(StartLongOp)() PURE;
    STDMETHOD(EndLongOp)(short fAll) PURE;
    
};
typedef IControlAdvise far * LPCONTROLADVISE;

DECLARE_INTERFACE_(IControl,IUnknown) 
{
    // Mouse
    
    STDMETHOD(MouseClick)(POINT pt, ClickType ct, SelectionType* pst) PURE;     
    STDMETHOD(MouseMove)(POINT pt, int sck) PURE;
    
    // Keyboard
    
    STDMETHOD(ProcessCharMsg)(int nCh, long grfKeyState, int msg) PURE;
	
    // Scroll
    
    STDMETHOD(Scroll)(ScrollCommands scr, int wScrollAmount) PURE;
    STDMETHOD(GetScrollValue)(ScrollValue scrv, LPINT pwAmount) PURE;
    STDMETHOD(EnsureSelVisible)(BOOL fFirst) PURE;
    STDMETHOD(ScrollSelection)(SHORT grfso) PURE;

    // Advise
    
    STDMETHOD(Advise)(IControlAdvise far*) PURE;

    // Idle
    STDMETHOD(Idle)(IdleMethod idle) PURE;
    STDMETHOD(SetIdleMethod)(IdleMethod idle) PURE;
    STDMETHOD(GetIdleMethod)(IdleMethod *pidle) PURE;
};
typedef IControl far * LPCONTROL;

DECLARE_INTERFACE(IPrintCallback) 
{
    STDMETHOD(AbortPrinting)()PURE;
    STDMETHOD_(void, PrintingStarted)() PURE;
    STDMETHOD_(void, PrintingEnded)() PURE;
    STDMETHOD_(void, PrintingPage)(int cPage) PURE;
    STDMETHOD_(void, PrintingError)(int wError) PURE; 
};
typedef IPrintCallback far * LPPRINTCALLBACK;                                 
				 
DECLARE_INTERFACE_(IDocView,IUnknown)
{
    // Display

    STDMETHOD(RepaginateNow)()PURE;
    STDMETHOD(SetWindow)(HWND hwnd) PURE;    
    STDMETHOD(GetWindow)(LPHWND) PURE;
    STDMETHOD(UpdateDisplay)(HDC hdc, HRGN hrgnUpdate) PURE;
    STDMETHOD(DeferDisplay)() PURE;    
    STDMETHOD(UpdateDeferredDisplay)(short um) PURE;    
    STDMETHOD(EndDeferDisplay)(short um) PURE;    
    STDMETHOD(EraseBackground)(HDC hdc) PURE;
    STDMETHOD(ShowDocument)() PURE;
    STDMETHOD(SetViewProperty)(ViewProperty vprop, LPVARIANTARG pvargData) PURE;
    STDMETHOD(GetViewProperty)(ViewProperty vprop, LPVARIANTARG pvargData) PURE;
    
    // Document View State
    
    STDMETHOD(SetFocus)() PURE;
    STDMETHOD(KillFocus()) PURE; 

    // Printing

    STDMETHOD(Print)(int lStartPage, int lEndPage, PrintOptions po, ABORTPROC pfnAbort, IPrintCallback far *) PURE;
    STDMETHOD(GetPrinterInfo)(PrinterInfo vprop, LPVARIANTARG pvargData) PURE;
    
    // Zoom
    
    STDMETHOD(SetZoomMode)(ZoomMode) PURE;
    STDMETHOD(GetZoomMode)(ZoomMode*) PURE; 
    
    STDMETHOD(SetZoomLevel)(int) PURE;
    STDMETHOD(GetZoomLevel)(LPINT) PURE;
    
    // Display
    
    STDMETHOD(SetDisplayMode)(int) PURE;
    STDMETHOD(GetDisplayMode)(LPINT) PURE;
    
    STDMETHOD(SetDisplayRect)(RECT) PURE;
    STDMETHOD(GetDisplayRect)(LPRECT) PURE;
    
    // Document
    
    STDMETHOD(SetDocProperty)(DocProperty dprop, LPVARIANTARG pvargData) PURE;
    STDMETHOD(GetDocProperty)(DocProperty dprop, LPVARIANTARG pvargData) PURE;
    STDMETHOD(ShowPageSetupDlg)(void) PURE;
    STDMETHOD(SetDocBackground)(LPVARIANTARG pvargData, short xpLeft, short ypTop) PURE;



    
};
typedef IDocView far * LPDOCVIEW;

//-------------------------------------
// IUndo
//-------------------------------------

DECLARE_INTERFACE_(IUndo,IUnknown) 
{

  STDMETHOD(Undo)() PURE;
  STDMETHOD(Redo)() PURE;
  
  STDMETHOD(GetUndoId)(LPINT) PURE;
  STDMETHOD(GetUndoCount)(LPINT) PURE;
  STDMETHOD(GetRedoId)(LPINT) PURE;
  STDMETHOD(GetRedoCount)(LPINT) PURE;
      
  STDMETHOD(StartUndoGroup)() PURE;
  STDMETHOD(EndUndoGroup)() PURE;
  STDMETHOD(KillUndo)() PURE;
  
  STDMETHOD(EnableUndo)(BOOL fEnable) PURE;
  STDMETHOD(UndoIsEnabled)(BOOL* fEnabled) PURE;
  
};
typedef IUndo far * LPUNDO;


DECLARE_INTERFACE_(ITed,IUnknown)
{
    STDMETHOD(GetSelectionType)(SelectionType * pst) PURE; 
    STDMETHOD(GetSelectionRect)(LPRECT) PURE;
    STDMETHOD(NewDoc)() PURE; 
    STDMETHOD(ReadDoc)(VARIANT FAR* pvar, int grfOptions) PURE;
    STDMETHOD(SaveDoc)(VARIANT FAR* pvar, TextType tt, int fMakeCopy) PURE;
    
    STDMETHOD(ReadStorage)(IStorage FAR* pstg, int grfOptions) PURE;
    STDMETHOD(SaveStorage)(IStorage FAR* pstg, TextType tt, int fMakeCopy) PURE;
    STDMETHOD(ReadFile)(LPSTR pszFilePath, int grfOptions) PURE;
    STDMETHOD(SaveFile)(LPSTR pszFilePath, TextType tt, int fMakeCopy) PURE;
    
    STDMETHOD(ClearQuillClipboard)() PURE;
    STDMETHOD(CloseUnusedFiles)() PURE;
 
    STDMETHOD(EnumBorders)(LPUNKNOWN far* ppunk, BSTR bstrFile) PURE;
    STDMETHOD(ShowTipForError)(UERR err) PURE;
    STDMETHOD(ShowMessageForError)(UERR err) PURE;
    STDMETHOD_(UERR, UErrFromResult)(HRESULT hr) PURE;
    STDMETHOD_(BSTR, GetDfltMessageForUErr)(UERR uerr) PURE;
    
};
typedef ITed far * LPTED;


DECLARE_INTERFACE_(IText,IUnknown) 
{                       
    STDMETHOD(SetSelRange)(long cchStart, long cchEnd, BOOL fShow ) PURE;
    STDMETHOD(SelectNext)(TextSelectCommand tscCommand, BOOL fShow) PURE;
    STDMETHOD(GetNextRange)(TextSelectCommand tsc, long* pcpStart, long* pcpEnd) PURE;
    STDMETHOD(GetNextText)(BSTR* ppszBuffer, TextType tt, TextSelectCommand tsc) PURE;

    STDMETHOD(GetSelRange)(long *cchStart, long *cchEnd) PURE;
    
    STDMETHOD(GetStoryLength)(long* cchLength) PURE;
    STDMETHOD(GetText)(LPVOID pOutput, StorageType st, TextType CharType, LONG cpStart, LONG cpEnd) PURE;
    STDMETHOD(SetText)(LPVOID pInput, StorageType st, TextType CharType, LONG cpStart, LONG cpEnd) PURE;
      
    STDMETHOD(SetCharProperty)(CharProperty ts, LPVARIANT pvarg) PURE; 
    STDMETHOD(GetCharProperty)(CharProperty ts, LPVARIANT pvarg) PURE;  
		     
    STDMETHOD(SetParaProperty)(ParaProperty ps, LPVARIANT pvarg) PURE;
    STDMETHOD(GetParaProperty)(ParaProperty ps, LPVARIANT pvarg) PURE;

	STDMETHOD(GetStartOfPage)(short ipgd, LONG* pcpFirst)  PURE;
	STDMETHOD(GetNumPages)(short *pcPages)  PURE;

    
};
typedef IText far * LPTEXT;
DECLARE_INTERFACE_(IFrame,IUnknown)
{   
    STDMETHOD(SelectFrame)(int wFrameId) PURE;
    STDMETHOD(GetFrameSelection)(int * pwFrameId) PURE;
    STDMETHOD(SetFrameId)(int wFrameId) PURE;              
     
    STDMETHOD(SetFrameRect)(int wLeft, int wTop, int wRight, int wBottom ) PURE;
    STDMETHOD(GetFrameRect)(int& wLeft, int& wTop, int& wRight, int& wBottom) PURE;
    
    STDMETHOD(AddFrame)(FrameProperty fp, LPVARIANTARG pvargData,
	    int ipgd, BOOL fAllPages) PURE;
	    
    STDMETHOD(SetFrameProperty)(FrameProperty fp, LPVARIANTARG pvargData) PURE;
    STDMETHOD(GetFrameProperty)(FrameProperty fp, LPVARIANTARG pvargData) PURE;
    
    STDMETHOD(DoVerb)(LONG dwVerb, LPMSG pmsg) PURE;  
    
    STDMETHOD(GetFrameRange)(int wFrameId, LONG* pcpFirst, LONG* pcpLast) PURE;
 
};                        
typedef IFrame far * LPFRAME;

DECLARE_INTERFACE_(IClipboard,IUnknown) 
{
    STDMETHOD(Cut)() PURE;
    STDMETHOD(Copy)() PURE;
    STDMETHOD(Paste)() PURE;
    STDMETHOD(Delete)() PURE;
    STDMETHOD(CheckExtClipboard)() PURE; 
    STDMETHOD(WriteExtClipboard)() PURE;
    STDMETHOD(ReadExtClipboard)() PURE;
};
typedef IClipboard far * LPCLIPBOARD;

DECLARE_INTERFACE_(ISpell, IUnknown)
{
    STDMETHOD(SpellCheckDoc)(SpellCheckFlags spcf, LPINT pscrs) PURE;
    STDMETHOD(MakeCorrection)(SpellCommand spCommand, BSTR pszReplace) PURE;                                   
    STDMETHOD(StopChecking)() PURE;
    STDMETHOD_(BSTR, NextSuggestion)() PURE;
    STDMETHOD(SetSpellOptions)(LONG grfso) PURE;
    STDMETHOD(GetSpellOptions)(LONG* pgrfso) PURE;
    STDMETHOD(SetMainDictionary)(BSTR pszMainDictionary) PURE;
    STDMETHOD(SetUserDictionary)(BSTR pszUserDictionary) PURE;
    STDMETHOD(GetSpellChanges)(LPINT pcChanges) PURE;
};
typedef ISpell far * LPSPELL;

DECLARE_INTERFACE_(IBorder, IUnknown)
{
    STDMETHOD_(BSTR, GetName)() PURE;
    STDMETHOD_(short, GetDefaultSize)() PURE;
    STDMETHOD(DrawBorder)(HDC hdc, int left, int top, int right, int bottom, int dzp) PURE;
    STDMETHOD_(long, GetId)() PURE;
    
    STDMETHOD(GetClo)(LPVOID pv) PURE;
    
};
DECLARE_INTERFACE_(IMailMerge,IUnknown) 
{                       
    STDMETHOD(InsertDBField)(LPSTR szFieldName, LPSTR szData) PURE;
    STDMETHOD(ChangeDBFieldText)(LPSTR szFieldName, LPSTR szData) PURE;
    STDMETHOD(GetDBFieldText)(BSTR* ppszBuffer, LONG cpField) PURE;
    STDMETHOD(GetDBFieldName)(BSTR* ppszBuffer, LONG cpField) PURE;
    STDMETHOD(IsDBFieldSelected)() PURE;
    STDMETHOD(DoesDBFieldExist)(LPSTR szFieldName, short *pcCount) PURE; 
    STDMETHOD(GetDBFieldRange)(LPSTR szFieldName, LONG * pcpFirst, LONG * pcpLim) PURE;
    STDMETHOD(SelectDBField)(LPSTR szFieldName) PURE;

	STDMETHOD(CreateHotSpotField)(LONG cpFirst, LONG cpLim, long uid) PURE;

    
};
typedef IMailMerge far * LPMailMerge;


#endif
