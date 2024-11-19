////////////////////////////////////////////////////////////////////////////
// DB.H
//
//
//
// History:
// ??-??-92 DarrinM     Created.
/////////////////////////////////////////////////////////////////////////////

#include <cdai.h>
#include <uttime.h>

#ifndef __DB_H__
#define __DB_H__

#ifdef  __cplusplus
extern "C" {
#endif

class UDbDir;

#ifndef DBAPI
#define DBAPI  _far _pascal _export _loadds
#endif

#ifndef PCSTR
typedef const char *    PCSTR;
#endif

typedef unsigned long DBID;     // Database ID == 0 indicates failure
typedef unsigned long FLDID;    // Field ID == 0 indicates failure
typedef unsigned long FTYP;     // Field Type
typedef double DBDATE;          // Database date
#define cbTextMax   256         // Imposed by DB
#define cbBkmkMax   256         // Max bookmark size

CDatabase * DBAPI GetSystemDb();

BOOL DBAPI DbInit(void);

DBID DBAPI DbCreateTable(PCSTR pszTableName, CDatabase *pdb = NULL);
DBID DBAPI DbOpenTable(PCSTR pszTableName, CDatabase *pdb = NULL);
void DBAPI DbCloseTable(DBID tid, CDatabase *pdb = NULL);
void DBAPI DbDeleteTable(PCSTR pszTableName, CDatabase *pdb = NULL);
DBID DBAPI DbGetFieldId(DBID tid, PCSTR pszColumnName, CDatabase *pdb = NULL);
int  DBAPI DbGetRecordCount(DBID tid, CDatabase *pdb = NULL);

BOOL DBAPI DbGoToRecord(DBID tid, long cmdWhere, CDatabase *pdb = NULL);

// Valid cmdWhere values

#define DGR_FIRST       JET_MoveFirst
#define DGR_LAST        JET_MoveLast
#define DGR_NEXT        JET_MoveNext
#define DGR_PREV        JET_MovePrevious

BOOL DBAPI DbSeekRecord(DBID tid, long cmd, CDatabase *pdb = NULL);

// Valid cmd values

#define DSR_EQUAL       JET_bitSeekEQ
#define DSR_LESSEQUAL   JET_bitSeekLE
#define DSR_GREATEREQUAL JET_bitSeekGE
#define DSR_LESS        JET_bitSeekLT
#define DSR_GREATER     JET_bitSeekGT

unsigned long DBAPI DbGetField(DBID tid, DBID fid, void _far *pvBuffer, int cbMax,
        UINT ff = 0, CDatabase *pdb = NULL);

#define DGF_LASTWRITE   JET_bitRetrieveCopy

BOOL DBAPI DbSetField(DBID tid, DBID fid, void _far *pvBuffer, int cbMax, CDatabase *pdb = NULL);

BOOL DBAPI DbSetIndex(DBID tid, PCSTR pszIndexName, CDatabase *pdb = NULL);
BOOL DBAPI DbMakeKey(DBID tid, void _far *pvBuffer, unsigned long cbSize, BOOL fAddToKey, CDatabase *pdb = NULL);

BOOL DBAPI DbPrepareUpdate(DBID tid, long cmd, CDatabase *pdb = NULL);

// Valid cmd values

#define DPU_INSERT          JET_prepInsert
#define DPU_REPLACE         JET_prepReplace
#define DPU_INSERTBEFORE    JET_prepInsertBeforeCurrent

BOOL DBAPI DbUpdate(DBID tid, void _far *pvBookmark = NULL, unsigned long cbBookmark = 0,
                unsigned long _far *pcbActual = NULL, CDatabase *pdb = NULL);

FLDID DBAPI DbAddField (DBID tid, PCSTR lpszName, FTYP ftyp,
                  unsigned long cbMax, BOOL fAutoIncrement, CDatabase *pdb = NULL);

// Valid ftyp values

#define ftypNil                JET_coltypNil
#define ftypBit                JET_coltypBit
#define ftypUnsignedByte       JET_coltypUnsignedByte
#define ftypShort              JET_coltypShort
#define ftypLong               JET_coltypLong
#define ftypCurrency           JET_coltypCurrency
#define ftypIEEESingle         JET_coltypIEEESingle
#define ftypIEEEDouble         JET_coltypIEEEDouble
#define ftypDateTime           JET_coltypDateTime
#define ftypBinary             JET_coltypBinary
#define ftypText               JET_coltypText
#define ftypLongBinary         JET_coltypLongBinary
#define ftypLongText           JET_coltypLongText


BOOL DBAPI DbCreateIndex (DBID tid, PCSTR pszName, PCSTR pszIndex, CDatabase *pdb = NULL);

long DBAPI DbGetLastError (void);
BOOL DBAPI DbDeleteRecord(DBID tid, CDatabase *pdb = NULL);

#ifdef  __cplusplus
}
#endif


/////////////////////////////////////////////////////////////////////////////
// WHAT IS IT?
// The classes UDbRecord, UDbRecordList, and UDbDir are designed to encapsul-
// ate the database and abstract its implementation for user classes.  The
// storage model presented is that of a number of containers (UDbRecordList)
// each containing an arbitrary number of objects (UDbRecord).  A directory
// of containers (UDbDir) provides quick access to a record given a 'database
// address' (DBA).
//
//
// HOW DO I USE IT?
// See the headers of each of these classes for details.
//
//
// ANYTHING SPECIAL I SHOULD KNOW?
// All database-specific code should be in this module so we can port to a
// different database easily.  The implementation of these classes should hide
// as many details of the underlying database as possible.
//
// History:
// 10-02-92 DarrinM     Created.
/////////////////////////////////////////////////////////////////////////////

typedef unsigned long DBA;
#define RIDMASK             0x00FFFFFF
#define MakeDBA(tid, rid)   ((DBA)(((DWORD)tid << 24) | rid))
#define IdbdeFromDba(dba)   (dba >> 24)
#define RidFromDba(dba)     (dba & RIDMASK)
#define DbaFromRid(rid)     (rid & RIDMASK)

struct DbDirEntry
{
    char szTableName[50];
    int cOpenTables;
    DBID tid;
    DBID fidUnique;
    void *pvFieldIds;
};

// The order of these macros must match the ordering in the rgdbde array
// in DLL\TASK.CPP.

#define dbaError            MakeDBA(0, 0)
#define dbaSobs             MakeDBA(1, 0)
#define dbaSobLists         MakeDBA(2, 0)
#define dbaUtopiaApps       MakeDBA(3, 0)
#define dbaHomeInfo         MakeDBA(4, 0)
//#define dbaSobClassActions  MakeDBA(5, 0)
#define dbaUsers            MakeDBA(6, 0)
#define dbaCalendar         MakeDBA(7, 0)
#define dbaRooms            MakeDBA(8, 0)
#define dbaListManager      MakeDBA(9, 0)
#define dbaSchedule         MakeDBA(10, 0)
//#define dbaImageLibrary     MakeDBA(11, 0)
//#define dbaImageCategories  MakeDBA(12, 0)
//#define dbaImageDesignStyles MakeDBA(13, 0)
#define dbaRoomTypes        MakeDBA(14, 0)

/////////////////////////////////////////////////////////////////////////////
// class UDbDir
//
// WHAT IS IT?
// The database directory is used to support the mapping from a 'database
// address' (DBA) to a specific database table and record.  The directory
// also caches the field ids for the records of each table.
//
//
// HOW DO I USE IT?
// All Utopia applications construct a UtopiaApp object.  During its
// construction it creates a UDbDir instance for the calling application.
// Typically, user classes don't interact directly with the directory
// but use it indirectly via UDbRecord and UDbRecordList.
//
// Follow these steps to add a new table to the directory:
//
// 1. Create the table in the database (possibly with Access).
// 2. Make sure the table has a column named "UniqueID" and an index on it.
// 3. Add a line with the table's name to the grgdbde array above.
// 4. Create a new "dba<tablename>" constant for accessing the table.
//
//
// ANYTHING SPECIAL I SHOULD KNOW?
// Each application has its own copy of the master directory to avoid
// conflicts.  The pointer to this copy is stored in the app's UtopiaApp
// object.
//
// History:
// 10-02-92 DarrinM     Created.
// 10-16-92 FordM       Added CreateTable, DeleteTable
/////////////////////////////////////////////////////////////////////////////

class UDbDir       // dbd
{
public:
    UDbDir(DbDirEntry *rgdbde, int cdbde);
    ~UDbDir();
    BOOL CreateTable(PCSTR szTableName);
    BOOL OpenTable(DBA dba);
    BOOL CloseTable(DBA dba);
    BOOL DeleteTable(DBA dba);
    DbDirEntry *GetDirEntry(DBA dba)
    {
        Assert(IdbdeFromDba(dba) != 0, slError, "uninitialized DBA being used ");
        return &m_rgdbde[IdbdeFromDba(dba)];
    }

    void *GetFieldIds(DBA dba) { return m_rgdbde[IdbdeFromDba(dba)].pvFieldIds; }
    BOOL SetFieldIds(DBA dba, void *pvFieldIds);
    static void * APIENTRY AllocFieldIds(int cb);
    CDatabase *GetDb() { return m_pdb; }
    BOOL SetDb(CDatabase *pdb);

private:
    DbDirEntry *m_rgdbde;
    int m_cdbde;
    CDatabase *m_pdb;
};


/////////////////////////////////////////////////////////////////////////////
// class URecordList
//
// WHAT IS IT?
// The URecordList class provides a collection interface to a database table.
// The interface is similar to that provided by other MFC collections, such
// as CObList and is designed to be as ignorant as possible of the table's
// actual contents.
//
//
// HOW DO I USE IT?
// The URecordList constructor must be passed the database address of the
// table the collection is to include.
//
// See <???> for example usage.
//
// To perform an indexed query on the database, use SetQuery and then
// Find in a loop to get each match.  Find returns 0 when no more matches
// are available.
//
// ANYTHING SPECIAL I SHOULD KNOW?
// URecordList doesn't cache any of the table's records (although the
// database probably does) so each lookup can potentially involve a disk hit.
//
// History:
// 10-02-92 DarrinM     Created.
/////////////////////////////////////////////////////////////////////////////

class _export URecordList      // lsr
{
public:
    URecordList(DBA dba);
    ~URecordList();

    BOOL CDECL SetQuery(char *pszIndex, long cmd, int cKeys, ...);
    DBA Find();
    POSITION GetHeadPosition();
    DBA GetNext(POSITION &rpos);

private:
    DBA m_dba;
    DBID m_tid;
    DbDirEntry *m_pdbde;
    char m_szIndex[50];
    void *m_pvKey;
    int m_cbKey;
    DBID m_fidKey;
    void *m_pvKeyT;
    long m_cmd;
};


/////////////////////////////////////////////////////////////////////////////
// class UDbRecord
//
// WHAT IS IT?
// UDbRecord is used to load and store information in the database.  It has
// all the methods needed for reading and writing records.  For most classes,
// UDbRecord (and derived classes) is their only interface to the records in
// the database.
//
//
// HOW DO I USE IT?
// Classes which desire persistance for some of their members should follow
// these steps:
//
// 1. Derive the class from UDbRecord.
// 2. Add the methods Load, Save to the class and implement them.
// 3. Create a structure for the persistant member's field ids.
// 4. Add the method GetFieldIds to the class and implement it.
//
// See HOME\ROOM.* for example usage.
//
//
// ANYTHING SPECIAL I SHOULD KNOW?
// Although GetField can be used to get strings from the database, it is
// preferable to use GetTextField because it handles the possibility of
// the database string being unterminated.
//
// History:
// 10-02-92 DarrinM     Created.
// 10-16-92 FordM       Added AddField, AddIndex
/////////////////////////////////////////////////////////////////////////////

class _export UDbRecord        // dbr
{
public:
    UDbRecord();
    ~UDbRecord();
    BOOL PrepareUpdate();
    BOOL Update();
    BOOL Delete();
    DBID GetFieldId(PCSTR pszColumnName);
    BOOL SetField(DBID fid, void *pvBuffer, int cbMax);
    BOOL SetTimeField(DBID fid, UTime time);
    unsigned long GetField(DBID fid, void *pvBuffer, int cbMax, UINT ff = 0);
    unsigned long GetTextField(DBID fid, void *pvBuffer, int cbMax, UINT ff = 0);
    BOOL GetTimeField(DBID fid, UTime *ptime);
    void *GetFieldIds();
    BOOL SetFieldIds(void *pvFieldIds);
    BOOL SeekToSelf();
    BOOL SetDba(DBA dba);
    DBA  GetDba();
    DBID GetId();
    BOOL SetId(DBID id);
    DBID AddField(PCSTR szFieldName, FTYP ftyp, DWORD cbMax, BOOL fAutoInc);
    BOOL AddIndex(PCSTR szIndexName, PCSTR szIndex);

protected:
    DBA m_dba;
};

#endif  // ifdef __DB_H__
