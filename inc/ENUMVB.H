/////////////////////////////////////////////////////////////////////////////
// ENUMVB.H
//
// Enumerator IDispatch VB definitions:
//  IEnumVB  -- Next() returns IDispatch 
//  IEnumVBT -- Same as IEnumVB except Skip() parameter accepts a parameter
//  IEnumVBVARIANT -- Next() returns VARIANT
//
// IDispatch (for VB) version of IEnum. 
// Limited to enumerating 1 element at a time.
//
// History:
// 07-30-93 FordM       Created.            
// 10-30-93 DLevy       IEnumVBT and IEnumVBVARIANT added
/////////////////////////////////////////////////////////////////////////////

#ifndef __ENUMVB_H__
#define __ENUMVB_H__

#include <server.h>


typedef IDispatch * PIDISPATCH;


/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
// IEnumVB Interface
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

#undef  INTERFACE
#define INTERFACE   IEnumVB

DECLARE_INTERFACE_(IEnumVB, IUnknown)
{
    // IUnknown methods
    
    STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef) (THIS)  PURE;
    STDMETHOD_(ULONG,Release) (THIS) PURE;
    
    // IEnumVB methods

    STDMETHOD_(LPDISPATCH, VBNext)(THIS) PURE;
    STDMETHOD(VBSkip)(THIS_ ULONG celt) PURE;
    STDMETHOD(VBReset)(THIS) PURE;
    STDMETHOD_(LPDISPATCH, VBClone)(THIS) PURE;
};

// Declare prototypes for IEnumVB

#define DECLARE_IEnumVB                   \
    STDMETHOD_(LPDISPATCH, VBNext)(THIS);   \
    STDMETHOD(VBSkip)(THIS);                \
    STDMETHOD(VBReset)(THIS);               \
    STDMETHOD_(LPDISPATCH, VBClone)(THIS)


#undef  INTERFACE
#define INTERFACE   IEnumVBVARIANT

DECLARE_INTERFACE_(IEnumVBVARIANT, IUnknown)
{
    // IUnknown methods
    
    STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef) (THIS)  PURE;
    STDMETHOD_(ULONG,Release) (THIS) PURE;
    
    // IEnumVB methods

    STDMETHOD_(VARIANT, VBNext)(THIS) PURE;
    STDMETHOD(VBSkip)(THIS_ ULONG celt) PURE;
    STDMETHOD(VBReset)(THIS) PURE;
    STDMETHOD_(LPDISPATCH, VBClone)(THIS) PURE;
};

/////////////////////////////////////////////////////////////////////////////
//

#endif  // ifdef __ENUMVB_H__
