/////////////////////////////////////////////////////////////////////////////
// Toc.H
//
// Table of Content Interface
//
// History:
// 09-10-93 Mikehar Created.
/////////////////////////////////////////////////////////////////////////////

#ifndef __Toc_h__
#define __Toc_h__

#include <compont.h>
#include <server.h>
#include <cdai.h>
#include <time.h>
#include <enumvb.h>

class UItem;
struct IItem;
typedef IDispatch *PIDISPATCH;

#define tocDOSTypeId   -1

#define tocMaxName 80
#define tocMaxPassword 15
#define tocUniqueStamp 0xFFEEDDCC
#define gszTocProc "TOCPROC"

typedef struct _tocheader {
    long lTocStamp;     //Unique dword
    long lHeaderSize;   //versioning
    GUID SystemId;      //Unique system id

    // App Info
    char szAppName[50]; //App Name
    long lAppId;        //App Id from Orig system

    // Type Info
    char szTypeName[50];//Type name
    long lTypeId;       //Type Id from Orig system
    long lFlags;

    // Person Info
    char szUserName[50]; //Name of User
    long lUserId;       //UserId from Orig System

    // Item Info
    long    lItemId;       // lItemId from Original System
    char    szTitle[50];
    char    szPassword[tocMaxPassword];
    long    lSize;          //size of attachment
    long    dCreated;
    long    dLastModified;
    long    lScratchSize;
} TOCHEADER, *PTOCHEADER;

// IDispatch Interfaces

/////////////////////////////////////////////////////////////////////////////
// IToc Interface
/////////////////////////////////////////////////////////////////////////////

#undef  INTERFACE
#define INTERFACE   IToc

DECLARE_INTERFACE_(IToc, IUnknown)
{
    // *** IUnknown methods ***
    STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef) (THIS)  PURE;
    STDMETHOD_(ULONG,Release) (THIS) PURE;

    //*** IToc methods ***
    STDMETHOD(SetSort)(THIS_ const long *rgidProperties,
            const BOOL *rgbAscending, int cProps) PURE;
    STDMETHOD(SetFilter)(THIS_ const long *rglidProperties,
        const ULONG *rglCompare, const void **rgpvValues, int cProps) PURE;
    STDMETHOD(GetItems)(THIS_ ULONG ulFlags, IEnum **ppIEnum) PURE;

    STDMETHOD(CreateItem)(THIS_ IItem **ppIItem,
            long lTypeId, const char *pszTocFile = NULL,
            const char *pszDestFilename = NULL) PURE;
    STDMETHOD(BundleItem)(THIS_ long lItemId, const char *pszFilename,
        const char *pszPassword) PURE;

    STDMETHOD(RemoveItem)(THIS_ long lItemId, const char *pszPassword) PURE;
    STDMETHOD(FindItem)(THIS_ long lItemId, IItem **ppIItem,
        const char *pszPassword) PURE;

    STDMETHOD(GetMRU)(THIS_ long lAppId, long lType, long *rgIds, time_t *rgDates) PURE;
    STDMETHOD(Touch)(THIS_ long lItemId) PURE;

    STDMETHOD(AddType)(THIS_ long lAppId, const char *pszTypeName, long lFlags, const char *pszDLL, const char *pszTocProc, long *plTypeId) PURE;
    STDMETHOD(RemoveType)(THIS_ long lTypeId) PURE;
    STDMETHOD(GetTypeName)(THIS_ long lTypeId, char *pszName, long *plSize) PURE;
    STDMETHOD(GetTypeId)(THIS_ const char *pszName, long *plTypeId) PURE;
    STDMETHOD(GetTypes)(THIS_ IEnum **ppIEnum) PURE;
    STDMETHOD(AddUser)(THIS_ DBID uid) PURE;
};
// Valid bits for AddType's lFlags
#define tocBundle   1
#define tocUnBundle 2
#define tocDelete   4
#define tocDOSFile  8
#define tocAddUser  16

#define tocFlagsMask (tocBundle|tocUnBundle|tocDelete|tocDOSFile|tocAddUser)
#define tocDOSFlags (tocBundle|tocUnBundle|tocDelete|tocDOSFile)

//Valid Bits for SetFilter's lCompare
#define tocCmpEql      0x0001
#define tocCmpGt       0x0002
#define tocCmpLt       0x0003
#define tocCmpGte      0x0004
#define tocCmpLte      0x0005
#define tocCmpLike     0x0006
#define tocCmpBtwn     0x0007
#define tocCmpMask     0x0FFF

#define tocCmpAnd      0x1000
#define tocCmpOr       0x2000
#define tocCmpNot      0x4000


/////////////////////////////////////////////////////////////////////////////
// IItem Interface
/////////////////////////////////////////////////////////////////////////////

#undef  INTERFACE
#define INTERFACE   IItem

DECLARE_INTERFACE_(IItem, IUnknown)
{
    // *** IUnknown methods ***
    STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef) (THIS)  PURE;
    STDMETHOD_(ULONG,Release) (THIS) PURE;

    //*** IItem methods ***

    STDMETHOD(GetProperty)(THIS_ long lPropId, void *pvBuffer, long cbBufferMax,
            long *plSize) PURE;
    STDMETHOD(SetProperty)(THIS_ long lPropId, const void *pvData,
            long cbDataMax) PURE;

    STDMETHOD(SetPassword)(THIS_ const char *pszOldPassword,
            const char *pszNewPassword) PURE;
    STDMETHOD(VerifyPassword)(THIS_ const char *pszPassword) PURE;
    STDMETHOD(AddItem)(THIS) PURE;

    STDMETHOD(Refresh)(THIS) PURE;
    STDMETHOD(Flush)(THIS) PURE;
    STDMETHOD(Init)(THIS_ const char *pszFilename, const char *pszDest) PURE;
};

#define tocFirstProp            1
#define tocFirstId              1
#define tocId                   1
#define tocAppId                2
#define tocUserId               3
#define tocCreatorId            4
#define tocType                 5
#define tocSize                 6
#define tocFlags                7
#define tocCreation             8
#define tocLastModified         9
#define tocLastId               10

#define tocFirstString          10
#define tocTitle                10
#define tocPassword             11
#define tocFilename             12
#define tocLastString           13

#define tocScratch              13
#define tocLastProp             14

#define tocItemValid     0x01
#define tocItemString    0x02
#define tocItemLong      0x04
#define tocItemAddNew    0x08
#define tocItemDate      0x10
#define tocItemBundled   0x20
#define tocItemDirty     (tocItemString|tocItemLong|tocItemAddNew|tocItemDate)

STDAPI_(BOOL) GetToc(IToc **ppIToc);
typedef HRESULT (STDAPICALLTYPE* TOCPROC)(ULONG ulFlags, void* pv1, void *pv2);

/////////////////////////////////////////////////////////////////////////////
// class UToc
//
// Table of Contents
//
// History:
// 09-10-93 Mikehar     Created.
/////////////////////////////////////////////////////////////////////////////
typedef struct _TypeNode {
    struct _TypeNode *pNext;
    long        lTypeId;
    TOCPROC  pfnBundle;
    HINSTANCE   hinst;
} TypeNode, *PTypeNode;

class UToc : public IToc, CComponent, UDispatch
{
public:
    UToc(CDatabase *pdb, DBID uid = 0);
    virtual ~UToc();

private:
    ULONG   m_ulFlags;
    CDatabase *m_pdb;
    char    *m_pszOrderBy;
    char    *m_pszWhere;
    CTable  *m_pt;    // our standard Table
    CTable  *m_ptMRU; // the MRU table
    CTable  *m_ptType; // the list of types [CONSIDER] should this be a ram based table?
    long    m_lUserId;
    PTypeNode m_pTypeList;
public:
    // IUnknown methods

    DECLARE_IUNKNOWN;

    // IDispatch methods

    DECLARE_INTERFACE_MAP;

    // IToc methods
    STDMETHOD(SetSort)(const long *rgidProperties,
            const BOOL *rgbAscending, int cProps);
    STDMETHOD(SetFilter)(const long *rglidProperties,
        const ULONG *rglCompare, const void **rgpvValues, int cProps);
    STDMETHOD(GetItems)(ULONG ulFlags, IEnum **ppIEnum);

    STDMETHOD(CreateItem)(THIS_ IItem **ppIItem, long lTypeId,
            const char *pszTocFile = NULL, const char *pszDestFilename = NULL);
    STDMETHOD(BundleItem)(THIS_ long lItemId, const char *pszFilename,
        const char *pszPassword);

    STDMETHOD(RemoveItem)(THIS_ long lItemId, const char *pszPassword);
    STDMETHOD(FindItem)(THIS_ long lItemId, IItem **ppIItem,
        const char *pszPassword);

    STDMETHOD(GetMRU)(THIS_ long lAppId, long lType, long *rgIds, time_t *rgDates);
    STDMETHOD(Touch)(THIS_ long lItemId);

    STDMETHOD(AddType)(THIS_ long lAppId, const char *pszTypeName, long lFlags, 
            const char *pszDLL, const char *pszTocProc, long *plTypeId);
    STDMETHOD(RemoveType)(THIS_ long lTypeId);
    STDMETHOD(GetTypeName)(THIS_ long lTypeId, char *pszName, long *plSize);
    STDMETHOD(GetTypeId)(THIS_ const char *pszName, long *plTypeId);
    STDMETHOD(GetTypes)(IEnum **ppIEnum);
    STDMETHOD(AddUser)(THIS_ DBID uid);
//    STDMETHOD(Advise)(THIS_ IItemSINK padvs, ULONG *pnConnection);
//    STDMETHOD(Unadvise)(THIS_ ULONG nConnection);

    // VB Methods
    STDMETHOD(VBSetSort)(long lPropId, BOOL bAscending); //17
    STDMETHOD(VBSetFilter)(long lPropId, ULONG ulCompare,
            struct tagVARIANT var);
    STDMETHOD_(PIDISPATCH, VBGetItems)(void);
    STDMETHOD_(PIDISPATCH, VBCreateItem)(long lTypeId, const char *pszFilename,
            const char *pszDest);
    STDMETHOD_(PIDISPATCH, VBFindItem)(long lItemId, const char *pszPassword);
    STDMETHOD_(long, VBAddType)(long lAppId, const char *pszTypeName, long lFlags, 
            const char *pszDLL, const char *pszTocProc); //22
    STDMETHOD_(BSTR, VBGetTypeName)(long lTypeId);
    STDMETHOD_(long , VBGetTypeId)(const char *pszName);
    STDMETHOD_(PIDISPATCH, VBGetTypes)(void);
    STDMETHOD_(long, VBGetMRUId)(long lAppId, long lType, int iIndex);
    STDMETHOD_(long, VBGetMRUDate)(long lAppId, long lType, int iIndex);
    STDMETHOD_(LONG,GetIToc) (THIS);

    HRESULT GetTypeNode(TypeNode **ppTypeNode, long lTypeId);
private:
    HRESULT LoadService(long lTypeId, TypeNode **ppTypeNode);
    HRESULT Bundle(IItem *pIItem, const char *pszFilename);
    HRESULT Delete(long lItemId, long lTypeId, IItem *pIItem);

    // Advise holder

//    UCalAdv *m_pcaladv;

public:
    HRESULT RemoveItemFromMRU(long lItemId, long lAppId, long lTypeId, long uidExclude);
//    void AdviseChange(long lItemId, IItem *pIItem);
};
typedef struct tagUITEMPROPS {
    long Id;
    long AppId;
    long UserId;
    long CreatorId;
    long Type;
    long Size;
    long Flags;
    long Creation;
    long LastModified;
    BSTR Title;
    BSTR Filename;
    BSTR Scratch;
} UITEMPROPS, *PUITEMPROPS;

/////////////////////////////////////////////////////////////////////////////
// class UItem
//
// Toc Item class
//
// History:
// 09-10-93 Mikehar     Created.
/////////////////////////////////////////////////////////////////////////////
class UItem : public IItem, CComponent, UDispatch
{
private:
    UITEMPROPS m_props;
public:
    UItem(IUnknown *punk, UToc *pUToc, CTable *pt, long lItemId);
    virtual ~UItem();

private:
    // Interesting things we keep track of;
    CTable *m_pt;
    IUnknown *m_punk;
    UToc    *m_pUToc;
    void    *m_pvBookmark;
    ULONG   m_ulFlags;
    TOCPROC  m_pfnBundle;
    void    *m_pvScratch;
    long    m_lScratchSize;
    // Properties
    char    *m_pszName;             // Item title
    char    *m_pszDest;             // dest file name override (output)
    char    *m_pszPassword;
    long    m_rglProps[tocLastId - tocFirstId];
    char    *m_pszFilename;         //Bundle File. This is set when an item
                                    // is created if a filename was passed
                                    // in to CreateItem. The file is then
                                    // unbundled at Add() time and this string
                                    // is released.
    time_t    m_Creation;
    time_t    m_LastModify;
public:
    // IUnknown methods

    DECLARE_IUNKNOWN;

    // IDispatch methods

    DECLARE_INTERFACE_MAP;

    // IItemVB methods

//    DECLARE_ITocVB;

    // IItem methods

    STDMETHOD(GetSetProperty)(THIS_ BOOL fget, LONG dispid,
            LPFIELDDATA pflddata, VARIANTARG * pvarg, LONG index);
    STDMETHOD(GetProperty)(long lPropId, void *pvBuffer, long cbBufferMax,
            long *plSize);
    STDMETHOD(SetProperty)(long lPropId, const void *pvData, long cbDataMax);

    STDMETHOD(SetPassword)(const char *pszOldPassword, const char *pszNewPassword);
    STDMETHOD(VerifyPassword)(const char *pszPassword);

    STDMETHOD(AddItem)(void);
    STDMETHOD(Refresh)(void);
    STDMETHOD(Flush)(void);
    STDMETHOD(Init)(const char *pszFilename, const char *pszDestFilename);

//    STDMETHOD(Advise)(THIS_ IItemSINK padvs, ULONG *pnConnection);
//    STDMETHOD(Unadvise)(THIS_ ULONG nConnection);

private:
    HRESULT UnBundle();
    // Advise holder

//    UCalAdv *m_pcaladv;

public:
//    void AdviseChange(long lItemId, IItem *pIItem);
};

#endif // __TOC_H__


