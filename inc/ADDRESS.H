//-------------------------------------------------------------
//
// ADDRESS.H
//
//-------------------------------------------------------------
//
//  This is a public utopia header file.
//
//-------------------------------------------------------------
//
//    This header file provides the APIs and abstract interfaces
// for using the Address Book services.
//
//-------------------------------------------------------------
//
//  Owner:  Mikehar
//
//-------------------------------------------------------------

//#ifndef __XADDRESS_H__
//#define __XADDRESS_H__

#include <cdai.h>

/////////////////////////////////////////////////////////////////////////////
// Interfaces
/////////////////////////////////////////////////////////////////////////////

struct IBook;
struct IPerson;
struct IABookSrv;

/////////////////////////////////////////////////////////////////////////////
// IAbEnum Interface
/////////////////////////////////////////////////////////////////////////////

#undef  INTERFACE
#define INTERFACE   IAbEnum

DECLARE_INTERFACE_(IAbEnum, IEnum)
{
    // *** IUnknown methods ***
    STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef) (THIS)  PURE;
    STDMETHOD_(ULONG,Release) (THIS) PURE;

    // *** IEnum methods
    STDMETHOD(Next)(THIS_ ULONG celt, void *prgv, ULONG FAR* pceltFetched)
            PURE;
    STDMETHOD(Skip)(THIS_ ULONG celt) PURE;
    STDMETHOD(Reset)(THIS) PURE;
    STDMETHOD(Clone)(THIS_ IEnum FAR* FAR* ppenm) PURE;

    //*** IAbEnum methods ***
    STDMETHOD(Back)(THIS_ ULONG celt, void *prgv, ULONG FAR* pceltFetched)
            PURE;
    STDMETHOD(MoveFirst)(THIS) PURE;
    STDMETHOD(MoveLast)(THIS) PURE;
    STDMETHOD(MoveNext)(THIS) PURE;
    STDMETHOD(MovePrevious)(THIS) PURE;

    STDMETHOD(FindFirst)(THIS_ long idProperty, ULONG ulCompare,
            void *pvValue, void *prgv) PURE;
    STDMETHOD(FindLast)(THIS_ long idProperty, ULONG ulCompare,
            void *pvValue, void *prgv) PURE;
    STDMETHOD(FindNext)(THIS_ long idProperty, ULONG ulCompare,
            void *pvValue, void *prgv) PURE;
    STDMETHOD(FindPrevious)(THIS_ long idProperty, ULONG ulCompare,
            void *pvValue, void *prgv) PURE; 
};

/////////////////////////////////////////////////////////////////////////////
// IABookSrv Interface
/////////////////////////////////////////////////////////////////////////////

#undef  INTERFACE
#define INTERFACE   IABookSrv

#define AB_MAX_NAME 80

DECLARE_INTERFACE_(IABookSrv, IUnknown)
{
    // *** IUnknown methods ***
    STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef) (THIS)  PURE;
    STDMETHOD_(ULONG,Release) (THIS) PURE;

    //*** IABookSrv methods ***
    STDMETHOD(CreateBook)(THIS_ ULONG ulFlags, const char *pszName,
        long *plBookId) PURE;
    STDMETHOD(EnumBooks)(THIS_ ULONG ulFlags, IAbEnum **ppcenum) PURE;
    STDMETHOD(RemoveBook)(THIS_ long lBookId) PURE;
    STDMETHOD(SelectBook)(THIS_ ULONG ulFlags, long lBookId) PURE;
    STDMETHOD(FindBook)(THIS_ IBook **ppIBook, long lBookId) PURE;

    STDMETHOD(FindPerson)(THIS_ long lPersonId, IPerson **ppcperson) PURE;
    STDMETHOD(RemovePerson)(THIS_ IPerson *pIPerson) PURE;
    STDMETHOD(MovePerson)(THIS_ long lPersonId, long lNewBookId) PURE;
    
    STDMETHOD(Print)(THIS_ HWND hwnd, BOOL fLabels, IAbEnum *pEnum, long *plIds) PURE;
    STDMETHOD(GetDefaultBook)(THIS_ IBook **ppIBook) PURE;
    STDMETHOD(SetDefaultBook)(THIS_ long lBookId) PURE;
    
};

#define AB_BOOK        0
#define AB_LIST        1
#define AB_COMPOSITE   2
#define AB_PRIVATE     4
#define AB_NOCREATETOC 8
/////////////////////////////////////////////////////////////////////////////
//IBook Interface
/////////////////////////////////////////////////////////////////////////////

#undef  INTERFACE
#define INTERFACE   IBook

DECLARE_INTERFACE_(IBook, IUnknown)
{
    // *** IUnknown methods ***
    STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef) (THIS)  PURE;
    STDMETHOD_(ULONG,Release) (THIS) PURE;

    //*** IBook methods ***
    STDMETHOD(CreatePerson)(THIS_ IPerson **ppPerson) PURE;
    STDMETHOD(AddPerson)(THIS_ IPerson *pPerson, long lAddressId) PURE;
    STDMETHOD(RemovePerson)(THIS_ IPerson *pIPerson) PURE;

    STDMETHOD(SetSort)(THIS_ long *rgidProperties, BOOL *rgbAscending,
            int cProps) PURE;
    STDMETHOD(SetFilter)(THIS_ long *rgidProperties, ULONG *rglCompare,
            void **rgpvValues, int cProps) PURE;
    STDMETHOD(EnumPeople)(IAbEnum **ppcenum, IBook *pList, CTable **pptRes = NULL) PURE;

    STDMETHOD(GetProperty)(THIS_ long lPropId, void *pvBuffer,
            long cbBufferMax, long *plSize) PURE;
    STDMETHOD(SetProperty)(THIS_ long lPropId, const void *pvData,
            long cbDataMax) PURE;
};

#define propBookName            1
#define propBookPassword        2
#define propBookUserId          3
#define propBookOwnerId         4
#define propBookId              5
#define propBookType            6
#define propBookTocId           7

#define AB_GETPEOPLE_SELECTED       0
#define AB_GETPEOPLE_ALL            1

#define AB_CMP_EQL      0x0001
#define AB_CMP_GT       0x0002
#define AB_CMP_LT       0x0003
#define AB_CMP_GTE      0x0004
#define AB_CMP_LTE      0x0005
#define AB_CMP_LIKE     0x0006
#define AB_CMP_BTWN     0x0007
#define AB_CMP_OPEN     0x0008
#define AB_CMP_CLOSE    0x0009
#define AB_CMP_NULL     0x000a
#define AB_CMP_MASK     0x0FFF

#define AB_CMP_AND      0x1000
#define AB_CMP_OR       0x2000
#define AB_CMP_NOT      0x4000

/////////////////////////////////////////////////////////////////////////////
//IPerson Interface
/////////////////////////////////////////////////////////////////////////////

#undef  INTERFACE
#define INTERFACE   IPerson

DECLARE_INTERFACE_(IPerson, IUnknown)
{
    // *** IUnknown methods ***
    STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef) (THIS)  PURE;
    STDMETHOD_(ULONG,Release) (THIS) PURE;

    // *** IPerson methods ***
    STDMETHOD(GetProperty)(THIS_ long lPropId, void *pvBuffer, long cbBufferMax,
            long *plSize) PURE;
    STDMETHOD(SetProperty)(THIS_ long lPropId, const void *pvData,
            long cbDataMax) PURE;
    STDMETHOD(Flush)(THIS) PURE;
    STDMETHOD(Refresh)(THIS) PURE;
    STDMETHOD(Clone)(THIS_ IPerson **ppcperson, BOOL ffClearName = FALSE)PURE;
};

#define AB_FIRSTSTRING        0
#define propPersonFullname    0
#define propPersonTitle       1
#define propPersonFirst       2
#define propPersonLast        3
#define propPersonSPDate1     4
#define propPersonSPDate2     5
#define propPersonSPDate3     6
#define propPersonSPDate4     7
#define propPersonSPName1     8
#define propPersonSPName2     9
#define propPersonSPName3     10
#define propPersonSPName4     11
#define propPersonAddress1    12
#define propPersonAddress2    13
#define propPersonCity        14
#define propPersonState       15
#define propPersonZip         16
#define propPersonCountry     17
#define propPersonPHHome      18
#define propPersonPHWork1     19
#define propPersonPHWork2     20
#define propPersonPHFax       21
#define propPersonPHOther1    22
#define propPersonPHOther2    23
#define propPersonEmailname   24
#define propPersonHomeLabel   25
#define propPersonWork1Label  26
#define propPersonWork2Label  27
#define propPersonFaxLabel    28
#define propPersonOther1Label 29
#define propPersonOther2Label 30
#define AB_LASTSTRING         31

#define AB_FIRSTID            50
#define propPersonId          50
#define propPersonAddressId   51
#define propPersonOwnerId     52
#define propPersonBookId      53
#define propPersonEmailType   54
#define propPersonSDateId1    55
#define propPersonSDateId2    56
#define propPersonSDateId3    57
#define propPersonSDateId4    58
#define AB_LASTID             59

#define propPersonPosition    60
#define propPersonSelected    61
#define propPersonNotes       62
#define propPersonBusiness    63

STDAPI_(BOOL) GetABookSrv(IABookSrv **ppcabs);

//#endif // __XADDRESS_H__
