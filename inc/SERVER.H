/////////////////////////////////////////////////////////////////////////////
//                              _SERVER.H
/////////////////////////////////////////////////////////////////////////////
//
// WHAT IS IT?
//   This is the private header file for the Server library.
//
// HOW DO I USE IT?
//   These classes provide the basic structure required of any server object.
//   Create descendant classes as necessary
//
// ANYTHING SPECIAL I SHOULD KNOW?
//
//
/////////////////////////////////////////////////////////////////////////////

#ifndef _server_def
#define _server_def

#include <stddef.h>

#include <compont.h>
#include <uerror.h>

///////////////////////////////////////
//  Forward Declarations
///////////////////////////////////////


// Defined in dispatch.cpp:
class UDispatch;

// Defined in server.cpp:
class UServer;

// Defined in inplace.cpp:
class UInPlaceServer;


/////////////////////////////////////////////////////////////////////////////
//                        Interface Map Segments
/////////////////////////////////////////////////////////////////////////////

#define ADD_UServer                                    \
    ADD_INTERFACE(IDataObject)                         \
    ADD_INTERFACE(IOleObject)                          \
    ADD_INTERFACE(IPersist)                            \
    ADD_INTERFACE(IPersistStorage)

#define ADD_UInPlaceServer                             \
    ADD_UServer                                        \
    ADD_INTERFACE(IOleInPlaceObject)                   \
    ADD_INTERFACE(IOleInPlaceActiveObject)

#define ADD_UDispatch                                  \
    ADD_INTERFACE(IDispatch)                           \
    ADD_INTERFACE(IGetStruct)



/////////////////////////////////////////////////////////////////////////////
//                          UServer
/////////////////////////////////////////////////////////////////////////////


class UServer :
    public CComponent,
    public IDataObject,
    public IOleObject,
    public IPersistStorage {
public:

    UServer(CClassFactory * pFactory, LPUNKNOWN punkOuter = NULL);
    ~UServer();

    //virtual HRESULT DoVerbOpen(LPMSG lpmsg) = 0;
    virtual HRESULT GetMetafile(LPMETAFILEPICT lpMFPict, DWORD dwAspect) = 0;
    virtual HRESULT LoadData(LPSTORAGE pStorage) = 0;
    virtual HRESULT SaveData(LPSTORAGE pStorage, BOOL fSameAsLoad) = 0;

    /////////////////////
    // Data members
    ////////////////////

    BOOL m_fDirty;

    SIZEL m_sizeL;
    LPSTORAGE m_pStorage;
    LPOLECLIENTSITE m_pOleClientSite;
    LPDATAADVISEHOLDER m_pDataAdviseHldr;
    LPOLEADVISEHOLDER m_pOleAdviseHldr;

    /////////////////////
    // IUnknown methods
    ////////////////////

    /////////////////////
    // IPersist methods
    ////////////////////

    STDMETHOD(GetClassID) (THIS_ LPCLSID lpClassID) ;

    ///////////////////////////
    // IPersistStorage methods
    ///////////////////////////

    STDMETHOD(IsDirty) (THIS) ;
    STDMETHOD(InitNew) (THIS_ LPSTORAGE pStg) ;
    STDMETHOD(Load) (THIS_ LPSTORAGE pStg) ;
    STDMETHOD(Save) (THIS_ LPSTORAGE pStgSave, BOOL fSameAsLoad) ;
    STDMETHOD(SaveCompleted) (THIS_ LPSTORAGE pStgNew) ;
    STDMETHOD(HandsOffStorage) (THIS) ;

    /////////////////////////
    // IOleObject methods
    /////////////////////////

    STDMETHOD(SetClientSite) (THIS_ LPOLECLIENTSITE pClientSite) ;
    STDMETHOD(GetClientSite) (THIS_ LPOLECLIENTSITE FAR* ppClientSite) ;
    STDMETHOD(SetHostNames) (THIS_ LPCSTR szContainerApp, LPCSTR szContainerObj) ;
    STDMETHOD(Close) (THIS_ DWORD dwSaveOption) ;
    STDMETHOD(SetMoniker) (THIS_ DWORD dwWhichMoniker, LPMONIKER pmk) ;
    STDMETHOD(GetMoniker) (THIS_ DWORD dwAssign, DWORD dwWhichMoniker,
                LPMONIKER FAR* ppmk) ;
    STDMETHOD(InitFromData) (THIS_ LPDATAOBJECT pDataObject,
                BOOL fCreation,
                DWORD dwReserved) ;
    STDMETHOD(GetClipboardData) (THIS_ DWORD dwReserved,
                LPDATAOBJECT FAR* ppDataObject) ;
    STDMETHOD(DoVerb) (THIS_ LONG iVerb,
                LPMSG lpmsg,
                LPOLECLIENTSITE pActiveSite,
                LONG lindex,
                HWND hwndParent,
                LPCRECT lprcPosRect) ;
    STDMETHOD(EnumVerbs) (THIS_ LPENUMOLEVERB FAR* ppenumOleVerb) ;
    STDMETHOD(Update) (THIS) ;
    STDMETHOD(IsUpToDate) (THIS) ;
    STDMETHOD(GetUserClassID) (THIS_ CLSID FAR* pClsid) ;
    STDMETHOD(GetUserType) (THIS_ DWORD dwFormOfType, LPSTR FAR* pszUserType) ;
    STDMETHOD(SetExtent) (THIS_ DWORD dwDrawAspect, LPSIZEL lpsizel) ;
    STDMETHOD(GetExtent) (THIS_ DWORD dwDrawAspect, LPSIZEL lpsizel) ;

    STDMETHOD(Advise)(THIS_ LPADVISESINK pAdvSink, DWORD FAR* pdwConnection) ;
    STDMETHOD(Unadvise)(THIS_ DWORD dwConnection) ;
    STDMETHOD(EnumAdvise) (THIS_ LPENUMSTATDATA FAR* ppenumAdvise) ;
    STDMETHOD(GetMiscStatus) (THIS_ DWORD dwAspect, DWORD FAR* pdwStatus) ;
    STDMETHOD(SetColorScheme) (THIS_ LPLOGPALETTE lpLogpal) ;

    /////////////////////////
    // IDataObject methods
    ////////////////////////

    STDMETHOD(GetData) (THIS_ LPFORMATETC pformatetcIn,
                            LPSTGMEDIUM pmedium ) ;
    STDMETHOD(GetDataHere) (THIS_ LPFORMATETC pformatetc,
                            LPSTGMEDIUM pmedium ) ;
    STDMETHOD(QueryGetData) (THIS_ LPFORMATETC pformatetc ) ;
    STDMETHOD(GetCanonicalFormatEtc) (THIS_ LPFORMATETC pformatetc,
                            LPFORMATETC pformatetcOut) ;
    STDMETHOD(SetData) (THIS_ LPFORMATETC pformatetc, STGMEDIUM FAR * pmedium,
                            BOOL fRelease) ;
    STDMETHOD(EnumFormatEtc) (THIS_ DWORD dwDirection,
                            LPENUMFORMATETC FAR* ppenumFormatEtc) ;

    STDMETHOD(DAdvise) (THIS_ FORMATETC FAR* pFormatetc, DWORD advf,
                    LPADVISESINK pAdvSink, DWORD FAR* pdwConnection) ;
    STDMETHOD(DUnadvise) (THIS_ DWORD dwConnection) ;
    STDMETHOD(EnumDAdvise) (THIS_ LPENUMSTATDATA FAR* ppenumAdvise) ;

};

/////////////////////////////////////////////////////////////////////////////
//                          UInPlaceServer
/////////////////////////////////////////////////////////////////////////////

class UInPlaceServer :
  public UServer,
  public IOleInPlaceObject,
  public IOleInPlaceActiveObject {
public:

    UInPlaceServer(CClassFactory * pFactory, LPUNKNOWN punkOuter = NULL);
    ~UInPlaceServer();

    // These variables must be set by the descendant of
    // UInPlaceServer before it may be properly used:
    CWnd * m_pWndActive;
    CWnd * m_pWndParent;
    char * m_pchShortName;

    // To be implemented by derived class
    virtual HRESULT GetMetafile(LPMETAFILEPICT lpMFPict, DWORD dwAspect) = 0;
    virtual HRESULT LoadData(LPSTORAGE pStorage) = 0;
    virtual HRESULT SaveData(LPSTORAGE pStorage, BOOL fSameAsLoad) = 0;

    BOOL m_fInPlaceActive;
    BOOL m_fHelpMode;

    // Helper functions
    HRESULT DoVerbOpen(LPMSG lpmsg);
    HRESULT DoVerbEdit(LPMSG lpmsg);
    HRESULT GetOleInPlaceSite( LPOLEINPLACESITE FAR* ppOleInPlaceSite ) ;
    void SetActiveObject( LPOLEINPLACESITE pOleInPlaceSite, BOOL fThis );

    // Overridden IOleObject methods:
    STDMETHOD(Close) (THIS_ DWORD dwSaveOption) ;
    STDMETHOD(DoVerb) (THIS_ LONG iVerb,
                LPMSG lpmsg,
                LPOLECLIENTSITE pActiveSite,
                LONG lindex,
                HWND hwndParent,
                LPCRECT lprcPosRect) ;

    ////////////////////////
    // IOleWindow Interface
    ////////////////////////

    STDMETHOD(GetWindow) (THIS_ HWND FAR* lphwnd) ;
    STDMETHOD(ContextSensitiveHelp) (THIS_ BOOL fEnterMode) ;

    ////////////////////////
    // IOleInPlaceObject Interface
    ////////////////////////

    STDMETHOD(InPlaceDeactivate) (THIS) ;
    STDMETHOD(UIDeactivate) (THIS) ;
    STDMETHOD(SetObjectRects) (THIS_ LPCRECT lprcPosRect,
                    LPCRECT lprcClipRect) ;
    STDMETHOD(ReactivateAndUndo) (THIS) ;

    ////////////////////////
    // IOleInPlaceActiveObject Interface
    ////////////////////////

    STDMETHOD(TranslateAccelerator) (THIS_ LPMSG lpmsg) ;
    STDMETHOD(OnFrameWindowActivate) (THIS_ BOOL fActivate) ;
    STDMETHOD(OnDocWindowActivate) (THIS_ BOOL fActivate) ;
    STDMETHOD(ResizeBorder) (THIS_ LPCRECT lprectBorder, LPOLEINPLACEUIWINDOW lpUIWindow, BOOL fFrameWindow) ;
    STDMETHOD(EnableModeless) (THIS_ BOOL fEnable) ;

};

/////////////////////////////////////////////////////////////////////////////
//                          UDispatch
/////////////////////////////////////////////////////////////////////////////

class UDispatch :
    public IDispatch,
    public IGetStruct {
public:

    UDispatch();
    ~UDispatch();

    HRESULT SetInterface( LPVOID pInterface, LPINTERFACEDATA pInterfaceData );
    HRESULT SetPropertyData(LPVOID pStruct, LPPROPERTYDATA pPropertyData);

protected:
    inline HRESULT UDispatch::SetError(HRESULT hr)
    {
        return m_hrDisp = hr;
    }

private:
    ITypeInfo * m_ptinfo;
    LPVOID m_pInterface;
    LPINTERFACEDATA m_pInterfaceData;
    LPVOID m_pStruct;
    LPPROPERTYDATA m_pPropertyData;
    HRESULT m_hrDisp;

    WORD UErrCvt(void);
    BOOL LookupPropName(char *pcszName, DISPID *pDispId);
    ////////////////////////
    // IDispatch Interface
    ////////////////////////
public:

    STDMETHOD(GetTypeInfoCount)(THIS_ UINT FAR* pctinfo) ;

    STDMETHOD(GetTypeInfo)(
      THIS_
      UINT itinfo,
      LCID lcid,
      ITypeInfo FAR* FAR* pptinfo) ;

    STDMETHOD(GetIDsOfNames)(
      THIS_
      REFIID riid,
      char FAR* FAR* rgszNames,
      UINT cNames,
      LCID lcid,
      DISPID FAR* rgdispid) ;

    STDMETHOD(Invoke)(
      THIS_
      DISPID dispidMember,
      REFIID riid,
      LCID lcid,
      WORD wFlags,
      DISPPARAMS FAR* pdispparams,
      VARIANT FAR* pvarResult,
      EXCEPINFO FAR* pexcepinfo,
      UINT FAR* puArgErr) ;


    ////////////////////////
    // IGetStruct Interface
    ////////////////////////
public:

    STDMETHOD(GetStruct)(THIS_ LPVOID FAR * ppv);
    STDMETHOD(GetSetProperty)(THIS_ BOOL fGet, LONG dispidProp,
                    LPFIELDDATA pFldData, VARIANTARG * pVArg, LONG Index);

};

/////////////////////////////////////////////////////////////////////////////
//                Macros for easy use of UDispatch
/////////////////////////////////////////////////////////////////////////////

// Macro Overview
//
// METHOD(meth, index)
//   Standard method, not overloaded, returns HRESULT
// METHOD_(meth, type, index)
//   Use for methods that return something other than HRESULT
// METHOD_NOPARAMS(meth, type, index)
//   Use for methods that take no parameters
// PROPERTY(structure, prop, type)
//   Use for identifying fields in STRUCTDATA
// GETPROP(prop, type, index)
//   GetProperty method
// SETPROP(prop, index)
//   SetProperty method
//
// Parameter description:
//   meth:    Name of method
//   prop:    Name of property
//   type:    Return type of method or type of property.
//   index:   Index into V-table for method or get/set property method.
//
// For examples of how to use these macros, see TMPLTS\COMPONT.CPP.

#define METHOD(meth, index) \
    {rgch##meth, rgpdata##meth, dispid##meth, index, CC_CDECL, \
            sizeof(rgpdata##meth) / sizeof(PARAMDATA), DISPATCH_METHOD, VT_I4}

#define METHOD_(meth, type, index) \
    {rgch##meth, rgpdata##meth, dispid##meth, index, CC_CDECL, \
            sizeof(rgpdata##meth) / sizeof(PARAMDATA), DISPATCH_METHOD, type}

#define METHOD_NOPARAMS(meth, type, index) \
    {rgch##meth, NULL, dispid##meth, index, CC_CDECL, \
            0, DISPATCH_METHOD, type}

#define IDISP_PROP_ID 0x80000000

#define PROPERTY(structure, prop, type) \
    {rgch##prop, type, dispid##prop, offsetof(structure, prop)}

#define PROPERTY_NOSTRUCT(prop, type) \
    {rgch##prop, type, dispid##prop, -1}

#define GETPROP(prop, type, index) \
    {rgch##prop, NULL, dispid##prop, index, CC_CDECL, \
            0, DISPATCH_PROPERTYGET, type}

#define SETPROP(prop, index) \
    {rgch##prop, rgpdata##prop, dispid##prop, index, CC_CDECL, \
            sizeof(rgpdata##prop) / sizeof(PARAMDATA), DISPATCH_PROPERTYPUT, VT_NULL}

#endif // _server_def
