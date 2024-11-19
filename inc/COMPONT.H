/////////////////////////////////////////////////////////////////////////////
//                               COMPONT.H
/////////////////////////////////////////////////////////////////////////////
//
// WHAT IS IT?
//   This header file provides the classes and macros to be used to
//   create generic component objects that support an arbitrary collection
//   of interfaces.
//
// HOW DO I USE IT?
//   For detailed instructions on using the Utopia OLE object library,
//   read the document OLEOBJ.DOC in the DOC directory.
//
// ANYTHING SPECIAL I SHOULD KNOW?
//
/////////////////////////////////////////////////////////////////////////////

#ifndef _component_def
#define _component_def

#include "dispatch.h"
#include "utguid.h"


///////////////////////////////////////
//  Forward Declarations
///////////////////////////////////////

class CComponent;
class CUnknown;
class CClassFactory;

///////////////////////////////////////
//  Helper Functions
///////////////////////////////////////

// UNDONE:  This include is used because *some* people want
//  to use this code when they don't have AFX around (UCC.MAK).
#ifdef __AFXWIN_H__
BOOL FAppLaunchedByOle( CWinApp * pWinApp ); 
#endif

#ifndef _WINDLL
void AllObjectsReleased();
#endif

#ifdef _DEBUG
LPSTR LpszFromIID(REFIID riid);
#endif

// Task Identification code used by CSimple's reference tracking.
#ifdef WIN32
UNDONE: This needs to be implemented for Win32.
//NOTE: The implementation should be something simple & fast (IE: no system calls)

#else

typedef HTASK TASKID;
//#define GetTaskID() GetCurrentTask()
#define GetTaskID() ((TASKID)1)
#endif

// Use this macro to obtain class factory pointers.  Returns an HRESULT:

#define GetClassFactory(clsid, ppCF)                                      \
    CoGetClassObject( (clsid), CLSCTX_INPROC_HANDLER, NULL,               \
            IID_IClassFactory, (LPVOID FAR*) (ppCF) )

/////////////////////////////////////////////////////////////////////////////
//                   IDispatch implementation support
/////////////////////////////////////////////////////////////////////////////

#define VT_MASK(vt)                 ((vt) & 0x1FFF)

// field data accessor privileges
#define fdRdPriv                    0x00000001
#define fdWrPriv                    0x00000002
#define fdRdWrPriv                  (fdRdPriv | fdWrPriv)

typedef struct FARSTRUCT tagFIELDDATA {
    char FAR * szName;              // field name
    VARTYPE vt;                     // field type
    DISPID dispid;                  // field ID
    UINT db;                        // offset to field
    ULONG flags;                    // RESERVED: should be zero
} FIELDDATA, FAR * LPFIELDDATA;

typedef struct FARSTRUCT tagPROPERTYDATA {
    FIELDDATA FAR * pflddata;       // pointer to an array of FIELDDATAs
    UINT cFields;                   // count of fields
} PROPERTYDATA, FAR * LPPROPERTYDATA;

/////////////////////////////////////////////////////////////////////////////
//                        IUnknown Interfaces
/////////////////////////////////////////////////////////////////////////////

// Use this macro in your implementation class definition to declare
// concrete prototypes of the IUnknown functions.  NOTE:  Do NOT use
// this macro in defining an abstract class.  These functions
// may later be defined with the macros below.

#define DECLARE_IUNKNOWN                                                 \
    STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID FAR* ppvObj);   \
    STDMETHOD_(ULONG,AddRef) (THIS);                                     \
    STDMETHOD_(ULONG,Release) (THIS)
 

#define DEBUG_SECTION_NAME "UtopiaDebug"
#define DEBUG_GLOBAL_NAME "All"

// define IUNKNOWN debug flags
#ifdef _DEBUG
#define fAddRefPrint    0x0001
#define fAddRefBreak    0x0002
#define fReleasePrint   0x0004
#define fReleaseBreak   0x0008
#define fReleaseAsserts 0x0010
#define fDeleteAsserts  0x0020
#define fCheckRefs      0x0040
#define fTermCleanup    0x0080
#define fDefaultFlags   (fReleaseAsserts | fDeleteAsserts)
#endif

#ifdef _DEBUG
#define DOADDREF(CName) TaskAddRef(CName)
#define DORELEASE(CName) TaskRelease(CName)
#else
#define DOADDREF(CName) TaskAddRef()
#define DORELEASE(CName) TaskRelease()
#endif

// Use this macro to define the IUnknown functions of an object
// that supports only a single interface (in addition to IUnknown),
// and no outer aggregation:  The object _must_ derive from CSimple. 

#define DEFINE_IUNKNOWN_(ClassName, iid)                                 \
STDMETHODIMP ClassName::QueryInterface(REFIID riid, LPVOID FAR* ppvObj)  \
{                                                                        \
    if (ppvObj == NULL)                                                  \
        return ResultFromScode(E_INVALIDARG);                            \
                                                                         \
    if ( riid == IID_IUnknown || riid == (IID_##iid) ) {                 \
        *ppvObj = (iid FAR*) this;                                       \
        AddRef();                                                        \
        return NOERROR;                                                  \
    }                                                                    \
                                                                         \
    *ppvObj = NULL;                                                      \
    return ResultFromScode(E_NOINTERFACE);                               \
}                                                                        \
    STDADDREF(ClassName)                                                 \
    STDRELEASE(ClassName)

#define DEFINE_IUNKNOWN2_(ClassName, iid1, iid2)                         \
STDMETHODIMP ClassName::QueryInterface(REFIID riid, LPVOID FAR* ppvObj)  \
{                                                                        \
    if (ppvObj == NULL)                                                  \
        return ResultFromScode(E_INVALIDARG);                            \
                                                                         \
    if ( riid == IID_IUnknown || riid == (IID_##iid1) ) {                \
        *ppvObj = (iid1 FAR*) this;                                      \
        AddRef();                                                        \
        return NOERROR;                                                  \
    }                                                                    \
                                                                         \
    if ( riid == (IID_##iid2) ) {                                        \
        *ppvObj = (iid2 FAR*) this;                                      \
        AddRef();                                                        \
        return NOERROR;                                                  \
    }                                                                    \
                                                                         \
    *ppvObj = NULL;                                                      \
    return ResultFromScode(E_NOINTERFACE);                               \
}                                                                        \
    STDADDREF(ClassName)                                                 \
    STDRELEASE(ClassName)

#define STDADDREF(ClassName)                                             \
STDMETHODIMP_(ULONG) ClassName::AddRef()                                 \
{                                                                        \
    return DOADDREF(#ClassName);                                         \
}

#define STDRELEASE(ClassName)                                            \
STDMETHODIMP_(ULONG) ClassName::Release()                                \
{                                                                        \
    ULONG cref;                                                          \
                                                                         \
    if ((cref = DORELEASE(#ClassName)) == 0)                             \
        delete this;                                                     \
    return cref;                                                         \
}

//debug stuff for DEFINE_IUNKNOWN(ClassName)
#ifdef _DEBUG
#define DOCOMPADDREF(CName)                                              \
    ULONG cref;                                                          \
    cref = m_punkOuter->AddRef();                                        \
    DoCompDebug(CName, TRUE, cref);                                      \
    return cref;

#define DOCOMPRELEASE(CName)                                             \
    ULONG cref;                                                          \
    m_punkOuter->AddRef();                                               \
    cref = m_punkOuter->Release() - 1;                                   \
    DoCompDebug(CName, FALSE, cref);                                     \
    m_punkOuter->Release();                                              \
    return cref;
#else
#define DOCOMPADDREF(CName)                                              \
    return m_punkOuter->AddRef(); 
#define DOCOMPRELEASE(CName)                                             \
    return m_punkOuter->Release();
#endif

// Use the following macro to define the IUnknown functions of a
// tightly bound inner aggregate. If you use this macro you must derive
// from CComponent (or don't define _DEBUG)


#define DEFINE_IUNKNOWN(ClassName)                                       \
STDMETHODIMP ClassName::QueryInterface(REFIID riid, LPVOID FAR* ppvObj)  \
{                                                                        \
    return m_punkOuter->QueryInterface(riid, ppvObj);                    \
}                                                                        \
                                                                         \
STDMETHODIMP_(ULONG) ClassName::AddRef()                                 \
{                                                                        \
    DOCOMPADDREF(#ClassName)                                             \
}                                                                        \
STDMETHODIMP_(ULONG) ClassName::Release()                                \
{                                                                        \
    DOCOMPRELEASE(#ClassName)                                            \
}


/////////////////////////////////////////////////////////////////////////////
//                        Interface Maps
/////////////////////////////////////////////////////////////////////////////

// [UNDONE]
// this warning (4005: macro redefinition) is turned off here because
// afxwin.h has the samed named macro.  we might want to rename
// ours sometime.
#pragma warning (disable: 4005)
#define DECLARE_INTERFACE_MAP                                            \
        STDMETHOD(_QueryInterface)(REFIID riid, LPVOID FAR* ppvObj);
#pragma warning (default: 4005)

#define BEGIN_INTERFACE_MAP(ClassName)                                   \
STDMETHODIMP ClassName::_QueryInterface(REFIID riid, LPVOID FAR* ppvObj) \
{                                                                        \
    if (riid == IID_IUnknown) {                                          \
        *ppvObj = LpControllingUnknown();                                \
        LpControllingUnknown()->AddRef();                                \
        return NOERROR;                                                  \
    }                                                                    \
    goto ClassName##_QI2;                                                \
ClassName##_QI1:                                                         \
    return CComponent::QueryAggregates(riid, ppvObj);                    \
ClassName##_QI2:

#define BEGIN_INTERFACE_MAP_(ClassName, ParentClassName)                 \
STDMETHODIMP ClassName::_QueryInterface(REFIID riid, LPVOID FAR* ppvObj) \
{                                                                        \
    if (riid == IID_IUnknown) {                                          \
        *ppvObj = LpControllingUnknown();                                \
        LpControllingUnknown()->AddRef();                                \
        return NOERROR;                                                  \
    }                                                                    \
    goto ClassName##_QI2;                                                \
ClassName##_QI1:                                                         \
    return ParentClassName::_QueryInterface(riid, ppvObj);               \
ClassName##_QI2:

#define ADD_INTERFACE(iface)                                             \
    if (riid == IID_##iface) {                                           \
        *ppvObj = (iface *) this;                                        \
        ((iface *) this)->AddRef();                                      \
        return NOERROR;                                                  \
    }

#define END_INTERFACE_MAP(ClassName)                                     \
    goto ClassName##_QI1;                                                \
}

/////////////////////////////////////////////////////////////////////////////
//                        Aggregate Map
/////////////////////////////////////////////////////////////////////////////

#define DECLARE_AGGREGATE_MAP                                            \
        STDMETHOD(InitAggregates)();

#define BEGIN_AGGREGATE_MAP(ClassName)                                   \
STDMETHODIMP ClassName::InitAggregates()                                 \
{                                                                        \
    HRESULT hr;                                                          \
                                                                         \
    goto ClassName##_IA2;                                                \
ClassName##_IA1:                                                         \
    return NOERROR;                                                      \
ClassName##_IA2:

#define BEGIN_AGGREGATE_MAP_(ClassName, ParentClassName)                 \
STDMETHODIMP ClassName::InitAggregates()                                 \
{                                                                        \
    HRESULT hr;                                                          \
                                                                         \
    goto ClassName##_IA2;                                                \
ClassName##_IA1:                                                         \
    return ParentClassName::InitAggregates();                            \
ClassName##_IA2:

#define ADD_AGGREGATE(clsid)                                             \
    hr = AddAggregate(clsid);                                            \
    if (FAILED(hr))                                                      \
        return hr;

#define END_AGGREGATE_MAP(ClassName)                                     \
    goto ClassName##_IA1;                                                \
}

/////////////////////////////////////////////////////////////////////////////
//                    CreateInstance macros 
/////////////////////////////////////////////////////////////////////////////

#define DECLARE_CREATEINSTANCE                                           \
        STDMETHOD(CreateInstance) (LPUNKNOWN punkOuter, REFIID riid,     \
                LPVOID FAR* ppvObj);

#define DEFINE_CREATEINSTANCE(Factory, Object)                           \
STDMETHODIMP Factory::CreateInstance(LPUNKNOWN punkOuter, REFIID riid,   \
        LPVOID FAR* ppvObj)                                              \
{                                                                        \
    HRESULT hr;                                                          \
                                                                         \
    if (ppvObj == NULL)                                                  \
        return ResultFromScode(E_INVALIDARG);                            \
    *ppvObj = NULL;                                                      \
                                                                         \
    Object * pObj = new Object(this, punkOuter);                         \
    if (pObj == NULL)                                                    \
        return ResultFromScode(E_OUTOFMEMORY);                           \
                                                                         \
    if (FAILED(hr = pObj->_QueryInterface(riid, ppvObj))) {              \
        delete pObj;                                                     \
        return hr;                                                       \
    }                                                                    \
                                                                         \
    return NOERROR;                                                      \
}

#define DEFINE_CREATEINSTANCE_(Factory, Object, Init)                    \
STDMETHODIMP Factory::CreateInstance(LPUNKNOWN punkOuter, REFIID riid,   \
        LPVOID FAR* ppvObj)                                              \
{                                                                        \
    HRESULT hr;                                                          \
                                                                         \
    if (ppvObj == NULL)                                                  \
        return ResultFromScode(E_INVALIDARG);                            \
    *ppvObj = NULL;                                                      \
                                                                         \
    Object * pObj = new Object(this, punkOuter);                         \
    if (pObj == NULL)                                                    \
        return ResultFromScode(E_OUTOFMEMORY);                           \
                                                                         \
    if (FAILED(hr = pObj->Init()) ||                                     \
            FAILED(hr = pObj->_QueryInterface(riid, ppvObj))) {          \
        delete pObj;                                                     \
        return hr;                                                       \
    }                                                                    \
                                                                         \
    return NOERROR;                                                      \
}

#define DEFINE_CREATEINSTANCE_NOAGGR(Factory, Object)                    \
STDMETHODIMP Factory::CreateInstance(LPUNKNOWN punkOuter, REFIID riid,   \
        LPVOID FAR* ppvObj)                                              \
{                                                                        \
    HRESULT hr;                                                          \
                                                                         \
    if (ppvObj == NULL)                                                  \
        return ResultFromScode(E_INVALIDARG);                            \
    *ppvObj = NULL;                                                      \
                                                                         \
    if (punkOuter != NULL)                                               \
        return ResultFromScode(CLASS_E_NOAGGREGATION);                   \
                                                                         \
    Object * pObj = new Object(this);                                    \
    if (pObj == NULL)                                                    \
        return ResultFromScode(E_OUTOFMEMORY);                           \
                                                                         \
    if (FAILED(hr = pObj->_QueryInterface(riid, ppvObj))) {              \
        delete pObj;                                                     \
        return hr;                                                       \
    }                                                                    \
                                                                         \
    return NOERROR;                                                      \
}

#define DEFINE_CREATEINSTANCE_NOAGGR_(Factory, Object, Init)             \
STDMETHODIMP Factory::CreateInstance(LPUNKNOWN punkOuter, REFIID riid,   \
        LPVOID FAR* ppvObj)                                              \
{                                                                        \
    HRESULT hr;                                                          \
                                                                         \
    if (ppvObj == NULL)                                                  \
        return ResultFromScode(E_INVALIDARG);                            \
    *ppvObj = NULL;                                                      \
                                                                         \
    if (punkOuter != NULL)                                               \
        return ResultFromScode(CLASS_E_NOAGGREGATION);                   \
                                                                         \
    Object * pObj = new Object(this);                                    \
    if (pObj == NULL)                                                    \
        return ResultFromScode(E_OUTOFMEMORY);                           \
                                                                         \
    pObj->AddRef();                                                      \
    if (FAILED(hr = pObj->Init()) ||                                     \
            FAILED(hr = pObj->_QueryInterface(riid, ppvObj))) {          \
        delete pObj;                                                     \
        return hr;                                                       \
    }                                                                    \
    pObj->Release();                                                     \
                                                                         \
    return NOERROR;                                                      \
}


/////////////////////////////////////////////////////////////////////////////
//                           CSimple 
/////////////////////////////////////////////////////////////////////////////
// Use the DEFINE_IUNKNOWN(Classname, iid) macro with your derived
// class to gain debug benefits

class CSimple {
    STDMETHOD_(ULONG,Release) (THIS) PURE;

private:
    CSimple FAR* m_next;
    CSimple FAR* m_prev;
    ULONG m_nTasks;
    struct TaskRefs {
        TASKID tr_task;
        ULONG tr_cref;
        TaskRefs FAR* tr_next;
        TaskRefs FAR* tr_prev;
    } m_trf;
    
public:
    friend void CleanUpTaskRefs(ULONG ff);
    friend void STDAPICALLTYPE InitCSimple(CSimple FAR* pcs);
    friend void STDAPICALLTYPE UnlinkCSimple(CSimple FAR* pcs);
    void ResetRefs();

protected:
#ifdef _DEBUG
    char *m_cname;
    int m_ffDebug;
    void DoDebug(TaskRefs *ptrf, char *CName, BOOL fAddRef);
    #define DEBUG_CNAME char * CName
    ULONG TaskAddRef(DEBUG_CNAME = NULL);
    ULONG TaskRelease(DEBUG_CNAME = NULL);
    CSimple(DEBUG_CNAME = NULL) 
    {
        m_cname = CName;
        InitCSimple(this);
    }
#else
    #define DEBUG_CNAME
    ULONG TaskAddRef();
    ULONG TaskRelease();
    CSimple() { InitCSimple(this); }
#endif

    ~CSimple() { UnlinkCSimple(this); }

}; 


/////////////////////////////////////////////////////////////////////////////
//                           COneTask 
/////////////////////////////////////////////////////////////////////////////

// COneTask is a version of CSimple that may only be used
// in one task.  When completed, it will assert if AddRef'ed or Released
// in a task other than the one where it was created.

struct COneTask : CSimple {

#ifdef _DEBUG
    HTASK m_htask;
#endif

    COneTask() {
#ifdef _DEBUG
        m_htask = GetCurrentTask();
#endif
    };
    
    // UNDONE:  TaskAddRef, TaskRelease
};                        

// If an object derives from COneTask, then it may benefit from being allocated
// by the task allocator.      

#if 0

#ifdef new
#define DEBUG_PARAMS        , LPCSTR lpszFileName, int nLine   
#define USE_DEBUG_PARAMS    , lpszFileName, nLine
#else
#define DEBUG_PARAMS   
#define USE_DEBUG_PARAMS
#endif

void * TaskAlloc(size_t size DEBUG_PARAMS);
void TaskDelete(void __far * ptr);

#define DEFINE_TASK_ALLOC                               \
    void * operator new(size_t size DEBUG_PARAMS) {     \
        return TaskAlloc(size USE_DEBUG_PARAMS);        \
    };                                                  \
    void operator delete(void * ptr) {                  \
        TaskDelete(ptr);                                \
    };
    
#else

#define DEFINE_TASK_ALLOC

#endif
    

/////////////////////////////////////////////////////////////////////////////
//                           CUnknown 
/////////////////////////////////////////////////////////////////////////////

class CUnknown : public IUnknown, public CSimple {
public:

    DECLARE_IUNKNOWN;

    CComponent * m_pComponent;
};

/////////////////////////////////////////////////////////////////////////////
//                           CComponent 
/////////////////////////////////////////////////////////////////////////////
// use the DEFINE_IUNKNOWN(ClassName) macro in your derived class
// to gain debug benefits.
// UNDONE:  See above comment on using this header without MFC
#ifdef __AFXWIN_H__

class CComponent {
public:
    //virtual __export FAR PASCAL ~CComponent();
    virtual ~CComponent();

    DECLARE_INTERFACE_MAP;
    DECLARE_AGGREGATE_MAP;

    HRESULT QueryAggregates(REFIID riid, LPVOID FAR* ppvObj);
    HRESULT AddAggregate(REFCLSID rclsid);

    CComponent(CClassFactory * pFactory = NULL, LPUNKNOWN punkOuter = NULL);

    LPUNKNOWN m_punkOuter;
    LPUNKNOWN LpControllingUnknown() { return &m_unknown; };

private:
    CUnknown m_unknown;
    CDWordArray m_rglpunkAggr;
protected:    
    CClassFactory * m_pFactory;

#ifdef _DEBUG
public:
    short m_ffDebug;
    void CComponent::DoCompDebug(char *CName, BOOL fAddRef, ULONG cref);
#endif
};


/////////////////////////////////////////////////////////////////////////////
//                        CClassFactory
/////////////////////////////////////////////////////////////////////////////

class CClassFactory : public IClassFactory {
public:
      
    friend HRESULT STDAPICALLTYPE  DllCanUnloadNow();
      
//////////////////////////////////////////
//    Init and Deinit
/////////////////////////////////////////

    CClassFactory();

//////////////////////////////////////////
//    IClassFactory interface
/////////////////////////////////////////

    DECLARE_IUNKNOWN;

    STDMETHOD(CreateInstance) (THIS_ LPUNKNOWN pUnkOuter,
                              REFIID riid,
                              LPVOID FAR* ppunkObject) ;
    STDMETHOD(LockServer) (THIS_ BOOL fLock) ;

//////////////////////////////////////////
//    Factory services
/////////////////////////////////////////

    HRESULT OkToClose();
    void ObjectCreated();
    void ObjectReleased();

    HRESULT StartFactory(REFCLSID rclsid);
    void StopFactory();

    REFCLSID Clsid() { return m_clsid; };

    static HRESULT GetClassObject(REFCLSID rclsid, REFIID riid,
            LPVOID FAR* ppvObj);

    CLSID m_clsid;
protected:
    ULONG m_cref;                    // ole ref count
    ULONG m_cObjectsCreated;         // number of objects currently in use
    ULONG m_cLock;                   // number of locks on this factory
    DWORD m_dwRegister;

private:
    static CDWordArray NEAR m_rglpFactory;

};

// UNDONE:
// interface for IGetStruct
// this interface description really needs a home, it's placed
// here for now.
#undef  INTERFACE
#define INTERFACE IGetStruct

DECLARE_INTERFACE_(IGetStruct, IUnknown)
{
    /* IUnknown methods */
    STDMETHOD(QueryInterface)(THIS_ REFIID riid, void FAR* FAR* ppvObj) PURE;
    STDMETHOD_(ULONG, AddRef)(THIS) PURE;
    STDMETHOD_(ULONG, Release)(THIS) PURE;

    /* IGetStruct methods */
    STDMETHOD(GetStruct)(THIS_ LPVOID FAR * ppv) PURE;
};

typedef IGetStruct FAR * LPGETSTRUCT;

#endif  // !__AFX_H__

#endif // _component_def
