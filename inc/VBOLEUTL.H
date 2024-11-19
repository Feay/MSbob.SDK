//-----------------------------------------------------------------------------
//  VBOLEUTL.H
//
//  WHAT IS IT?
//    This header file describes the abstract Component Object interfaces for
//  various ole utility objects created to get around various VB3 limitations.
// 
//  HOW DO I USE IT?
//    These interfaces are implemented in the oleutil module of the syssrv dll.
//    
//  History:
//    10-29-93  Dlevy Created
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Psuedo class factories
//-----------------------------------------------------------------------------

STDAPI GetOleServers(IEnumVARIANT ** ppenumvar);
STDAPI VBEnumVerbs(LPOLEOBJECT poleobj, IEnumVARIANT ** ppenumvar);
STDAPI_(LPUNKNOWN) NewUClsid(REFCLSID pclsid);


#undef INTERFACE
#define INTERFACE IClsid

DECLARE_INTERFACE_(IClsid, IUnknown) 
{
    // Clsid
    
    STDMETHOD(GetClsid)(LPCLSID pclsid) PURE;     
    STDMETHOD(SetClsid)(LPCLSID pclsid) PURE;
    
    // Clsid description
    
    STDMETHOD_(BSTR,GetDescription)() PURE;
    STDMETHOD(SetDescription)(BSTR bstr) PURE;
        
    // ProgID
    
    STDMETHOD_(BSTR,GetProgID)() PURE;
    STDMETHOD(SetProgID)(BSTR bstr) PURE; 
    
    // Utopia server
    
    STDMETHOD_(BOOL, GetUtopiaFlag)() PURE;
    STDMETHOD(SetUtopiaFlag)(BOOL fYes) PURE;
};

#undef INTERFACE
#define INTERFACE IVBOleVerb

DECLARE_INTERFACE_(IVBOleVerb, IUnknown)
{
    STDMETHOD_(LONG, GetVerbID)() PURE;
    STDMETHOD_(BSTR, GetVerbDescription)() PURE;
    STDMETHOD_(LONG, GetVerbFlags)() PURE;
};

