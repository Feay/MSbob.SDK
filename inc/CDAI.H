//---------------------------------------------------------------------------
// cdai.h
//---------------------------------------------------------------------------
// Copyright (c) 1992-1993, Microsoft Corporation
//                 All Rights Reserved
// Information Contained Herein Is Proprietary and Confidential.
//---------------------------------------------------------------------------
//
// This header file contains the classes and related defines for the C++
// Data Access Interface (CDAI).
//
// Owner: mikehar
//
// History:
// 06-14-93 Mikehar     Created.
//---------------------------------------------------------------------------
#if !defined( _CDAI_H_ )
#define _CDAI_H_

#include <afxwin.h>
#include <ebjet.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef unsigned long DBID;     // Database Identifier
typedef long DBERR;    // Database Return code
#ifdef APIENTRY
#undef APIENTRY
#endif

#define APIENTRY PASCAL _export

// definitions for JetColumnInfo structure positions
#define kCIFPresentationOrder           0
#define kCIFColumnName                  1
#define kCIFColumnID                    2
#define kCIFColumnType                  3
#define kCIFCountry                     4
#define kCIFLangID                      5
#define kCIFCP                          6
#define kCIFCollate                     7
#define kCIFCBMax                       8
#define kCIFGRBit                       9
#define kCIFDefault                     10
#define kCIFBaseTableName               11
#define kCIFBaseColumnName              12

// since we rely on the structure of the jet stuff we'll check here
// to see if anything changed in jet.h and warn if so.
#if (!defined(cColumnInfoCols) ||  cColumnInfoCols != 13)
#pragma message ("WARNING: JET.H has changed in some way !!")
#endif


// Forward declarations

class CDatabase;
class CRecordSet;
class CTable;
class CField;
class CDynaset;
class CSnapshot;
class CQueryDef;
class CDbErr;


//////////////////////////////////////////////////////////////////////////////////
// CDAI Init and Helper Functions
//////////////////////////////////////////////////////////////////////////////////

BOOL APIENTRY BeginSession(DBID * pidSession, BOOL *fTerminate,
        char * pszUser = "Admin", char * pszPassword = "");
void APIENTRY EndSession(DBID idSession, BOOL fTerminate);
BOOL APIENTRY OpenDatabase(DBID idSession, CDatabase **ppdb,
        const char *pszName, const char *pszLocale = NULL,
        unsigned long ffOptions = 0);
BOOL APIENTRY RepairDatabase(DBID idSession, const char *pszName);

//////////////////////////////////////////////////////////////////////////////////
// Jet error code mapper function
//////////////////////////////////////////////////////////////////////////////////

STDAPI_(HRESULT) ResultFromDbErr(JET_ERR dberr);

/////////////////////////////////////////////////////////////////////////////
// CDAI Classes
/////////////////////////////////////////////////////////////////////////////

class CDbErr
{
protected:
    JET_ERR m_err;      // Most recent Jet err for the derived class

public:
    CDbErr(void) {m_err = 0;};

    JET_ERR GetLastDbErr(void){return m_err;};
};


/////////////////////////////////////////////////////////////////////////////
// CDatabase
/////////////////////////////////////////////////////////////////////////////

class CDatabase : public CObject, public CDbErr
{
public:
    DBID m_idSession;       //Jet Session id
    DBID m_id;              //Jet Database id
private:
    CString m_sName;        //Database Name
    CString m_sConnect;     //Database Connect String
    CTable  *m_pTable;      //CTable object used with Get()

public:
    CDatabase(DBID idSession, DBID id);
    APIENTRY CDatabase(const char *pcszName);
    APIENTRY ~CDatabase();

    // Public Members

    unsigned long m_ulCollatingOrder; //**
    const char    *m_pszConnect;      //**
    const char    *m_pszName;        //**
    BOOL    m_fTransactions;         //**
    BOOL    m_fUpdatable;            //**
    BOOL    m_fExclusive;            //**
    unsigned long m_cQueryTimeout;         //Not used -- ODBC

    // Public Properties

    DBERR APIENTRY BeginTrans(void);      //**
    DBERR APIENTRY CommitTrans(void);     //**
    DBERR APIENTRY Rollback(void);        //**

    DBERR APIENTRY Close(void);       //**
    DBERR APIENTRY CreateDynaset(CDynaset **ppDynaset,
            const char *pszSource, unsigned long ffOptions = 0); //**
    DBERR APIENTRY CreateSnapshot(CSnapshot **ppSnapshot,
            const char *pszSource, unsigned long ffOptions = 0); //**
    DBERR APIENTRY Execute(const char *pszSQL);
    DBERR APIENTRY ListTables(CSnapshot **ppTables);        //**
    DBERR APIENTRY OpenQueryDef(CQueryDef **ppQueryDef, const char *pszName); //**
    DBERR APIENTRY OpenTable(CTable **ppTable, const char *pszName,
            unsigned long ffFlags = 0, const void _far *pvParameters = NULL,
            unsigned long culParameters = NULL); //**
    DBERR APIENTRY DeleteTable(const char *pszName);

    CTable& APIENTRY Get(const char *pszTable);
};

// Flags for OpenTable, CreateDynaset, CSnapshot

#define DB_DENYWRITE    1
#define DB_DENYREAD     2
#define DB_READONLY     4

/////////////////////////////////////////////////////////////////////////////
// CRecordSet Class - base class for CTable, CSnapshot and CDynaset
/////////////////////////////////////////////////////////////////////////////

class CRecordSet : public CObject , public CDbErr
{

protected:
    CString     m_sSort;
    CString     m_sFilter;
    CString     m_sName;
    unsigned long m_ffOptions;
    DBID        m_idSession;
    DBID        m_id;           // jet table id
    DBID        m_iddb;         // jet database id
    unsigned long ulType;       // Type of recordset

    unsigned long m_cbActBookmark;// Actual size of bookmark in m_rgchBookmark;
    char m_rgchBookmark[10];     // should be large enough (Kelly says 4 bytes is enough today)

    CField *m_pField;
    CRecordSet(void);

public:
    // public members
#ifdef _DEBUG
    virtual void Dump(CDumpContext& dc) const;
#endif
    // DateCreated;
    // LastModified;
    // LastUpdated;
    BOOL    m_ffBOF;             //**
    BOOL    m_ffEOF;             //**
    BOOL    m_ffLockEdits;
    const char *m_pszName;
    BOOL    m_ffNoMatch;
    BOOL    m_ffTransactions;
    BOOL    m_ffUpdatable;

    // public methods

    DBERR APIENTRY BeginTrans(void);  //**
    DBERR APIENTRY CommitTrans(void); //**
    DBERR APIENTRY Rollback(void);    //**

    DBERR APIENTRY Close(void);       //**
    DBERR APIENTRY AddNew(void);      //**
    DBERR APIENTRY Edit(void);        //**
    DBERR APIENTRY Update(void **ppvBookmark = NULL);      //**
    DBERR APIENTRY Cancel(void);      //**
    DBERR APIENTRY Clone(CTable **ppClone); //**

    DBERR APIENTRY CreateDynaset(CDynaset **ppDynaset,
            unsigned long ffOptions = 0);
    DBERR APIENTRY CreateSnapshot(CSnapshot **ppSnapshot,
            unsigned long ffOptions = 0);

    DBERR APIENTRY MoveFirst(void);   //**
    DBERR APIENTRY MoveLast(void);    //**
    DBERR APIENTRY MoveNext(void);    //**
    DBERR APIENTRY MovePrevious(void); //**

    DBERR APIENTRY FindFirst(const char *pszCriteria);
    DBERR APIENTRY FindLast(const char *pszCriteria);
    DBERR APIENTRY FindNext(const char *pszCriteria);
    DBERR APIENTRY FindPrevious(const char *pszCriteria);

    DBERR APIENTRY Get(CField **ppField, DBID id);

    DBERR APIENTRY GetValue(const char *pszField, void *pvBuffer,
            unsigned long culBuf, unsigned long * pculAct = NULL, JET_RETINFO *pRetInfo = NULL); //**
    DBERR APIENTRY SetValue(const char *pszField, void *pvBuffer,
            unsigned long culBuf, BOOL fAppend = FALSE, VOID *pvSetInfo = NULL); //**
    DBERR APIENTRY GetValue(DBID id, void *pvBuffer, unsigned long culBuf,
            unsigned long * pculAct = NULL, JET_RETINFO *pRetInfo = NULL); //**
    DBERR APIENTRY SetValue(DBID id, void *pvBuffer, unsigned long culBuf,
            BOOL fAppend = FALSE, VOID *pvSetInfo = NULL); //**

    DBERR APIENTRY ListIndexes(CSnapshot **ppIndexes);   //**
    DBERR APIENTRY ListFields(CSnapshot **pFields);      //**

    DBERR APIENTRY Sort(const char *pszSort);
    DBERR APIENTRY Filter(const char *pszFilter);

    DBERR APIENTRY SetTableId(DBID idTable);

    DBERR APIENTRY GetBookmark(void **ppvBookmark);
    DBERR APIENTRY GotoBookmark(void *pvBookmark = NULL);
    DBERR APIENTRY DeleteBookmark(void *pvBookmark);

    CField& APIENTRY Get(const char *pszField);
    CField& APIENTRY Get(DBID id);

    DBERR APIENTRY GetRecordCount(long * pcRecords);
    DBERR APIENTRY GetFieldID(LPSTR szField, DBID *pdbid);
    DBERR APIENTRY GetFieldIDs(DBID *pdbid, int count);
};

#define DB_EOF  -10     // End of file
#define DB_BOF  -11     // Beginning of file

/////////////////////////////////////////////////////////////////////////////
// CTable
/////////////////////////////////////////////////////////////////////////////

class CTable : public CRecordSet
{
private:
    CString m_sIndex;

public:
    CTable(DBID idSession, DBID iddb, DBID id, const char *pszName);
    ~CTable();
 
public:
    // public members

    const char *m_pszIndex; //?!?!

    // public methods

    DBERR APIENTRY SetIndex(const char *pszIndex);
    DBERR APIENTRY Delete(void);
    DBERR APIENTRY Delete(const char *pszMember);
    DBERR APIENTRY Clone(CTable **ppClone);  //**
    DBERR _cdecl _export Seek(const char *pszCompare,
            unsigned long culFields, ...);  //**
};

// Use the following macros to create subclasses of CTable with
// Get/SetValueOf member functions for retrieving the fields of
// the table using field ids instead of strings.
//
// e.g.
// 
// BEGIN_TABLE(CMyTable, 3)
//    DECLARE_INLINE_TableField(Field0, 0);
//    DECLARE_INLINE_TableField(Field1, 1);
//    DECLARE_INLINE_TableField(Field2, 2);
// END_TABLE(CMyTable)
//
// Then in your .cpp file put:
//
// DEFINE_TABLE(CMyTable, 3);
//
// You can now cast CTable pointers to CMyTable pointers to access the new
// Get/SetValueOf member functions (after calling GetFieldIDs()).
//
// CTable *ptable;
// CMyTable *pmytable;
//
// pdb->OpenTable(&ptable, "MyTable", ...);
// pmytable = (CMyTable *) ptable;
// pmytable->GetFieldIDs();
// pmytable->GetValueOfField0(...);
// pmytable->SetValueOfField2(...);
//     

#define BEGIN_TABLE(name, cfields) \
     class name : public CTable \
       { \
	 static DBID s_rgIDFields[cfields]; \
       public: \
	 name(void) : CTable(0,0,0,0) \
	   {}; \
	 DBERR GetFieldIDs(void);

#define END_TABLE(name) \
       };

#define DEFINE_TABLE(name, cfields) \
    DBID name::s_rgIDFields[cfields]; \
    DBERR name::GetFieldIDs(void) \
      { \
      if (s_rgIDFields[0] == 0) \
	return CTable::GetFieldIDs(s_rgIDFields, cfields); \
      return DB_OK; \
      }

#define DECLARE_INLINE_TableField(name, iid) \
    static DBID APIENTRY GetIDOf##name(void) \
      { \
      return s_rgIDFields[iid]; \
      }; \
    DBERR APIENTRY GetValueOf##name(void *pvBuffer, unsigned long culBuf, \
            unsigned long * pculAct = NULL, JET_RETINFO *pRetInfo = NULL) \
      { \
      return GetValue(s_rgIDFields[iid],pvBuffer,culBuf,pculAct,pRetInfo); \
      } \
    DBERR APIENTRY SetValueOf##name(void *pvBuffer, unsigned long culBuf, \
            BOOL fAppend = FALSE, VOID *pvSetInfo = NULL) \
      { \
      return SetValue(s_rgIDFields[iid],pvBuffer,culBuf,fAppend,pvSetInfo); \
      };

/////////////////////////////////////////////////////////////////////////////
// CDynaset
/////////////////////////////////////////////////////////////////////////////

class CDynaset : public CRecordSet
{
    // public members

    // public methods
public:
    CDynaset(DBID sesid, DBID dbid, DBID id, const char *pszname);
    ~CDynaset();

    DBERR APIENTRY Delete(void);
    DBERR APIENTRY Delete(const char *pszMember);
    DBERR APIENTRY Clone(CDynaset **ppClone);       //**
};

/////////////////////////////////////////////////////////////////////////////
// CSnapshot
/////////////////////////////////////////////////////////////////////////////

class CSnapshot : public CRecordSet
{
private:
    unsigned long  m_ulType;
    unsigned long  m_crecord;
    union {
        JET_COLUMNLIST  m_jcl;
        JET_OBJECTLIST  m_jol;
        JET_INDEXLIST   m_jil;
    };

public:

    CSnapshot(DBID idSession, DBID iddb, DBID id, const char *pszName,
            unsigned long ulSpecial, void *pv);
    ~CSnapshot();

    DBERR APIENTRY Clone(CSnapshot **ppClone);
    DBERR APIENTRY GetValue(const char *pszField, void *pvBuffer, unsigned long culBuf,
                            unsigned long * pculAct = NULL, JET_RETINFO *pRetInfo = NULL); //**
    DBERR APIENTRY SetValue(const char *pszField, void *pvBuffer,
            unsigned long culBuf, BOOL fAppend = FALSE, VOID *pvSetInfo = NULL); //**
    DBERR APIENTRY GetValue(DBID id, void *pvBuffer, unsigned long culBuf,
            unsigned long * pculAct = NULL, JET_RETINFO *pretinfo = NULL); //**
    DBERR APIENTRY SetValue(DBID id, void *pvBuffer, unsigned long culBuf,
            BOOL fAppend = FALSE, VOID *pvSetInfo = NULL); //**
    DBERR APIENTRY GetCount(unsigned long *pulcount); //**
};

/////////////////////////////////////////////////////////////////////////////
// CField
/////////////////////////////////////////////////////////////////////////////

class CField : public CObject, public CDbErr
{
private:
    DBID    m_idTable;      // table id
    DBID    m_iddb;         // database id
    DBID    m_id;           // column id
    JET_COLUMNDEF m_jcd;
    DBID    m_idSession;

public:
    CField(DBID idSession, DBID iddb, DBID idTable, JET_COLUMNDEF *pjcd);

    // Public members

    unsigned long m_ulAttributes;
    unsigned long m_ulCollatingOrder;
    char *m_pszName;
    // OrdinalPosition
    unsigned long m_ulSize;
    CTable *m_SourceTable;
    CField *m_SourceField;
    unsigned long m_ulType;

    // public methods

    DBERR APIENTRY Append(void);
    DBERR APIENTRY AppendChunk(void);
    DBERR APIENTRY Close(void);       //**
    DBERR APIENTRY GetValue(void *pvBuffer, unsigned long culBuf,
            unsigned long * pculAct = NULL, JET_RETINFO *pretinfo = NULL); //**
    unsigned long APIENTRY GetValue(void);
    DBERR APIENTRY SetValue(void *pvbuffer, unsigned long culBuf,
            BOOL fAppend = FALSE); //**
    DBERR APIENTRY DataSize(unsigned long *pulSize);
    DBERR APIENTRY GetChunk(unsigned long ulOffset, unsigned long ulSize,
            void *pvBuffer);
};

/////////////////////////////////////////////////////////////////////////////
// CQueryDef
/////////////////////////////////////////////////////////////////////////////
typedef struct _QUERYPARAM {
    char *pszName;
    unsigned long ulType;
    long    ulSize;
    void    *pvData;
} QUERYPARAM;


class CQueryDef : public CObject, public CDbErr
{
private:
    char *m_pszQueryName;        // Name of the query
    DBID m_idSession;       // main session id
    DBID m_iddb;            // database id
    unsigned long m_culParams;          // number of parameters
    QUERYPARAM *m_pqp;      // array of parameters

public:
    CQueryDef(DBID idSession, DBID iddb, const char *pszName, QUERYPARAM *pqp,
            unsigned long  culParams);

    ~CQueryDef();

    // public members
    const char *m_pszName;    //** Read Only
    const char *m_pszSQL;

    // public methods

    DBERR APIENTRY Close(void);       //**
    DBERR APIENTRY Execute(unsigned long ffOptions);
    DBERR APIENTRY SetParameter(const char *pszName, void *pvData,
            unsigned long cbData = 0);           //**
    DBERR APIENTRY GetParameter(const char *pszName, void *pvData,
            unsigned long cbData = 0);
    DBERR APIENTRY CreateDynaset(CDynaset **ppDynaset,
            unsigned long ffOptions = 0);    //**
    DBERR APIENTRY CreateSnapshot(CSnapshot **ppSnapshot,
            unsigned long ffOptions = 0);    //**
    DBERR APIENTRY ListParameters(CSnapshot **ppSnapshot);
};


#define DB_OK       0
#define DB_ERR      -1
#define DB_WRN      1

#define DS_TABLENAME    100

#ifdef __cplusplus
};
#endif

#endif//_CDAI_H_
