// iborder.h : border inteface
//
 
#ifndef __IBORDER_H__
#define __IBORDER_H__

 
/////////////////////////////////////////////////////////////////////////////
// CBorderApp:
// See border.cpp for the implementation of this class
//
DECLARE_INTERFACE_(IBorder, IUnknown)
{
    STDMETHOD(SetHmeta)(int irghmeta, HMETAFILE hmeta) PURE;
    STDMETHOD(GetHmeta)(int irghmeta, HMETAFILE* phmeta) PURE;
    
    STDMETHOD(SetChmeta)(int chmeta) PURE;
    STDMETHOD(GetChmeta)(int* pchmeta) PURE;

    STDMETHOD(SetIhmeta)(int irgihmeta, int ihmeta) PURE;
    STDMETHOD(GetIhmeta)(int irgihmeta, int* pihmeta) PURE;
                                                    
        
    STDMETHOD(SetDzpDefault)(int dzpDefault) PURE;
    STDMETHOD(GetDzpDefault)(int* pdzpDefault) PURE;
    
    STDMETHOD(SetDzpCorner)(int dzpSize) PURE;
    STDMETHOD(GetDzpCorner)(int* pdzpSize) PURE;
    
    STDMETHOD(SetDxpTopBottom)(int dxpTopBottom) PURE;
    STDMETHOD(GetDxpTopBottom)(int* pdxpTopBottom) PURE;
    
    STDMETHOD(SetDypLeftRight)(int dypLeftRight) PURE;
    STDMETHOD(GetDypLeftRight)(int* pdypLeftRight) PURE;
        
    STDMETHOD(SetFextra)(BOOL fExtra) PURE;        
    STDMETHOD(GetFextra)(BOOL* pfExtra) PURE;
    
    STDMETHOD(SetPszName)(LPSTR pszName) PURE;
    STDMETHOD(GetPszName)(LPSTR pszName) PURE;
};

#endif
