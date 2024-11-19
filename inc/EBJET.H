//---------------------------------------------------------------------------
// ebjet.h
//---------------------------------------------------------------------------
// Copyright (c) 1992-1993, Microsoft Corporation
//                 All Rights Reserved
// Information Contained Herein Is Proprietary and Confidential.
//---------------------------------------------------------------------------
//
// This header file should be included instead of jet.h.  This file
// declares the prototypes of the EbJet cover functions that do the stack
// switching before calling Jet.  The file also provides macros that map
// Jet function names to the EbJet cover functions.
//
// Owner: gustavj
//
// History:
// 06-20-93 GustavJ     Created.
//---------------------------------------------------------------------------


#include "jet.h"

#ifdef  __cplusplus
extern "C" {
#endif

//--------------------------------------------------------------------
//
// Eb Init/Term
//
//--------------------------------------------------------------------

BOOL __export FAR PASCAL EbEbInit(void);

void __export FAR PASCAL EbEbTerm(void);

//--------------------------------------------------------------------
//
// Jet Cover prototypes
//
//--------------------------------------------------------------------
#undef JET_API
#define JET_API __export FAR PASCAL 

JET_ERR JET_API EbJetInit(void);

JET_ERR JET_API EbJetTerm(void);

JET_ERR JET_API EbJetSetSystemParameter(JET_SESID sesid, unsigned long paramid,
    unsigned long lParam, const char _far *sz);

JET_ERR JET_API EbJetGetSystemParameter(JET_SESID sesid, unsigned long paramid,
    unsigned long _far *plParam, char _far *sz, unsigned long cbMax);

JET_ERR JET_API EbJetGetLastErrorInfo(JET_SESID sesid,
    JET_EXTERR _far *pexterr, unsigned long cbexterrMax,
    char _far *sz1, unsigned long cch1Max,
    char _far *sz2, unsigned long cch2Max,
    char _far *sz3, unsigned long cch3Max,
    unsigned long _far *pcch3Actual);

JET_ERR JET_API EbJetBeginSession(JET_SESID _far *psesid,
    const char _far *szUserName, const char _far *szPassword);

JET_ERR JET_API EbJetDupSession(JET_SESID sesid, JET_SESID _far *psesid);

JET_ERR JET_API EbJetEndSession(JET_SESID sesid, JET_GRBIT grbit);

JET_ERR JET_API EbJetGetVersion(JET_SESID sesid, unsigned long _far *pwVersion);

JET_ERR JET_API EbJetIdle(JET_SESID sesid, JET_GRBIT grbit);
JET_ERR JET_API EbJetIdle2(JET_SESID sesid, JET_GRBIT grbit);

JET_ERR JET_API EbJetCapability(JET_SESID sesid, JET_DBID dbid,
    unsigned long lArea, unsigned long lFunction, JET_GRBIT _far *pgrbit);

JET_ERR JET_API EbJetCreateDatabase(JET_SESID sesid,
    const char _far *szFilename, const char _far *szConnect,
    JET_DBID _far *pdbid, JET_GRBIT grbit);

JET_ERR JET_API EbJetAttachDatabase(JET_SESID sesid, const char _far *szFilename);

JET_ERR JET_API EbJetDetachDatabase(JET_SESID sesid, const char _far *szFilename);

JET_ERR JET_API EbJetCreateTable(JET_SESID sesid, JET_DBID dbid,
    const char _far *szTableName, unsigned long lPages, unsigned long lDensity,
    JET_TABLEID _far *ptableid);

JET_ERR JET_API EbJetRenameTable(JET_SESID sesid, JET_DBID dbid,
    const char _far *szTableName, const char _far *szTableNew);

JET_ERR JET_API EbJetDeleteTable(JET_SESID sesid, JET_DBID dbid,
    const char _far *szTableName);

JET_ERR JET_API EbJetGetTableColumnInfo(JET_SESID sesid, JET_TABLEID tableid,
    const char _far *szColumnName, void _far *pvResult, unsigned long cbMax,
    unsigned long InfoLevel);

JET_ERR JET_API EbJetGetColumnInfo(JET_SESID sesid, JET_DBID dbid,
    const char _far *szTableName, const char _far *szColumnName,
    void _far *pvResult, unsigned long cbMax, unsigned long InfoLevel);

JET_ERR JET_API EbJetAddColumn(JET_SESID sesid, JET_TABLEID tableid,
    const char _far *szColumn, const JET_COLUMNDEF _far *pcolumndef,
    const void _far *pvDefault, unsigned long cbDefault,
    JET_COLUMNID _far *pcolumnid);

JET_ERR JET_API EbJetRenameColumn(JET_SESID sesid, JET_TABLEID tableid,
    const char _far *szColumn, const char _far *szColumnNew);

JET_ERR JET_API EbJetDeleteColumn(JET_SESID sesid, JET_TABLEID tableid,
    const char _far *szColumn);

JET_ERR JET_API EbJetGetTableIndexInfo(JET_SESID sesid, JET_TABLEID tableid,
    const char _far *szIndexName, void _far *pvResult, unsigned long cbResult,
    unsigned long InfoLevel);

JET_ERR JET_API EbJetGetTableReferenceInfo(JET_SESID sesid, JET_TABLEID tableid,
    const char _far *szReferenceName, void _far *pvResult,
    unsigned long cbResult, unsigned long InfoLevel);

JET_ERR JET_API EbJetGetTableInfo(JET_SESID sesid, JET_TABLEID tableid,
    void _far *pvResult, unsigned long cbMax, unsigned long InfoLevel);

JET_ERR JET_API EbJetGetIndexInfo(JET_SESID sesid, JET_DBID dbid,
    const char _far *szTableName, const char _far *szIndexName,
    void _far *pvResult, unsigned long cbResult, unsigned long InfoLevel);

JET_ERR JET_API EbJetGetReferenceInfo(JET_SESID sesid, JET_DBID dbid,
    const char _far *szTableName, const char _far *szReference,
    void _far *pvResult, unsigned long cbResult, unsigned long InfoLevel);

JET_ERR JET_API EbJetCreateIndex(JET_SESID sesid, JET_TABLEID tableid,
    const char _far *szIndexName, JET_GRBIT grbit,
    const char _far *szKey, unsigned long cbKey, unsigned long lDensity);

JET_ERR JET_API EbJetRenameIndex(JET_SESID sesid, JET_TABLEID tableid,
    const char _far *szIndex, const char _far *szIndexNew);

JET_ERR JET_API EbJetDeleteIndex(JET_SESID sesid, JET_TABLEID tableid,
    const char _far *szIndexName);

JET_ERR JET_API EbJetCreateReference(JET_SESID sesid, JET_TABLEID tableid,
    const char _far *szReferenceName, const char _far *szColumns,
    const char _far *szReferencedTable,
    const char _far *szReferencedColumns, JET_GRBIT grbit);

JET_ERR JET_API EbJetRenameReference(JET_SESID sesid, JET_TABLEID tableid,
    const char _far *szReference, const char _far *szReferenceNew);

JET_ERR JET_API EbJetDeleteReference(JET_SESID sesid, JET_TABLEID tableid,
    const char _far *szReferenceName);

JET_ERR JET_API EbJetGetObjectInfo(JET_SESID sesid, JET_DBID dbid,
    JET_OBJTYP objtyp, const char _far *szContainerName,
    const char _far *szObjectName, void _far *pvResult, unsigned long cbMax,
    unsigned long InfoLevel);

JET_ERR JET_API EbJetCreateObject(JET_SESID sesid, JET_DBID dbid,
    const char _far *szContainerName, const char _far *szObjectName,
    JET_OBJTYP objtyp);

JET_ERR JET_API EbJetDeleteObject(JET_SESID sesid, JET_DBID dbid,
    const char _far *szContainerName, const char _far *szObjectName);

JET_ERR JET_API EbJetRenameObject(JET_SESID sesid, JET_DBID dbid,
    const char _far *szContainerName, const char _far *szObjectName,
    const char _far *szObjectNew);

JET_ERR JET_API EbJetBeginTransaction(JET_SESID sesid);

JET_ERR JET_API EbJetCommitTransaction(JET_SESID sesid, JET_GRBIT grbit);

JET_ERR JET_API EbJetRollback(JET_SESID sesid, JET_GRBIT grbit);

JET_ERR JET_API EbJetUpdateUserFunctions(JET_SESID sesid);

JET_ERR JET_API EbJetLoggingOn(JET_SESID sesid);

JET_ERR JET_API EbJetLoggingOff(JET_SESID sesid);

JET_ERR JET_API EbJetGetDatabaseInfo(JET_SESID sesid, JET_DBID dbid,
    void _far *pvResult, unsigned long cbMax, unsigned long InfoLevel);

JET_ERR JET_API EbJetCloseDatabase(JET_SESID sesid, JET_DBID dbid,
    JET_GRBIT grbit);

JET_ERR JET_API EbJetCloseTable(JET_SESID sesid, JET_TABLEID tableid);

JET_ERR JET_API EbJetOpenDatabase(JET_SESID sesid, const char _far *szFilename,
    const char _far *szConnect, JET_DBID _far *pdbid, JET_GRBIT grbit);

JET_ERR JET_API EbJetOpenTable(JET_SESID sesid, JET_DBID dbid,
    const char _far *szTableName, const void _far *pvParameters,
    unsigned long cbParameters, JET_GRBIT grbit, JET_TABLEID _far *ptableid);

JET_ERR JET_API EbJetDelete(JET_SESID sesid, JET_TABLEID tableid);

JET_ERR JET_API EbJetUpdate(JET_SESID sesid, JET_TABLEID tableid,
    void _far *pvBookmark, unsigned long cbBookmark,
    unsigned long _far *pcbActual);

JET_ERR JET_API EbJetRetrieveColumn(JET_SESID sesid, JET_TABLEID tableid,
    JET_COLUMNID columnid, void _far *pvData, unsigned long cbData,
    unsigned long _far *pcbActual, JET_GRBIT grbit, JET_RETINFO _far *pretinfo);

JET_ERR JET_API EbJetSetColumn(JET_SESID sesid, JET_TABLEID tableid,
    JET_COLUMNID columnid, const void _far *pvData, unsigned long cbData,
    JET_GRBIT grbit, JET_SETINFO _far *psetinfo);

JET_ERR JET_API EbJetPrepareUpdate(JET_SESID sesid, JET_TABLEID tableid,
    unsigned long prep);

JET_ERR JET_API EbJetGetRecordPosition(JET_SESID sesid, JET_TABLEID tableid,
    JET_RECPOS _far *precpos, unsigned long cbRecpos);

JET_ERR JET_API EbJetGotoPosition(JET_SESID sesid, JET_TABLEID tableid,
    unsigned long pos);

JET_ERR JET_API EbJetGetCursorInfo(JET_SESID sesid, JET_TABLEID tableid,
    void _far *pvResult, unsigned long cbMax, unsigned long InfoLevel);

JET_ERR JET_API EbJetDupCursor(JET_SESID sesid, JET_TABLEID tableid,
    JET_TABLEID _far *ptableid, JET_GRBIT grbit);

JET_ERR JET_API EbJetGetCurrentIndex(JET_SESID sesid, JET_TABLEID tableid,
    char _far *szIndexName, unsigned long cchIndexName);

JET_ERR JET_API EbJetSetCurrentIndex(JET_SESID sesid, JET_TABLEID tableid,
    const char _far *szIndexName);

JET_ERR JET_API EbJetMove(JET_SESID sesid, JET_TABLEID tableid,
    long cRow, JET_GRBIT grbit);

JET_ERR JET_API EbJetMakeKey(JET_SESID sesid, JET_TABLEID tableid,
    const void _far *pvData, unsigned long cbData, JET_GRBIT grbit);

JET_ERR JET_API EbJetSeek(JET_SESID sesid, JET_TABLEID tableid,
    JET_GRBIT grbit);

JET_ERR JET_API EbJetFastFind(JET_SESID sesid, JET_DBID dbid,
    JET_TABLEID tableid, const char _far *szExpr, JET_GRBIT grbit,
    signed long _far *pcrow);

JET_ERR JET_API EbJetGetBookmark(JET_SESID sesid, JET_TABLEID tableid,
    void _far *pvBookmark, unsigned long cbMax,
    unsigned long _far *pcbActual);

JET_ERR JET_API EbJetCompact(JET_SESID sesid, const char _far *szDatabaseSrc,
    const char _far *szConnectSrc, const char _far *szDatabaseDest,
    const char _far *szConnectDest, JET_PFNSTATUS pfnStatus,
    JET_GRBIT grbit);

JET_ERR JET_API EbJetGotoBookmark(JET_SESID sesid, JET_TABLEID tableid,
    void _far *pvBookmark, unsigned long cbBookmark);

JET_ERR JET_API EbJetComputeStats(JET_SESID sesid, JET_TABLEID tableid);


/*****************************************************************************

    SEC API

*****************************************************************************/

JET_ERR JET_API EbJetGetSidFromName(JET_SESID sesid, const char _far *szName,
    void _far *pvSid, unsigned long cbMax, unsigned long _far *pcbActual,
    long _far *pfGroup);

JET_ERR JET_API EbJetGetNameFromSid(JET_SESID sesid,
    const void _far *pvSid, unsigned long cbSid,
    char _far *szName, unsigned long cchName, long _far *pfGroup);

JET_ERR JET_API EbJetCreateUser(JET_SESID sesid, const char _far *szUser,
    const char _far *szPassword, const void _far *pvSid, unsigned long cbSid);

JET_ERR JET_API EbJetChangeUserPassword(JET_SESID sesid,
    const char _far *szUser, const char _far *szOldPassword,
    const char _far *szNewPassword);

JET_ERR JET_API EbJetDeleteUser(JET_SESID sesid, const char _far *szUser);

JET_ERR JET_API EbJetCreateGroup(JET_SESID sesid, const char _far *szGroup,
    const void _far *pvSid, unsigned long cbSid);

JET_ERR JET_API EbJetAddMember(JET_SESID sesid,
    const char _far *szGroup, const char _far *szUser);

JET_ERR JET_API EbJetRemoveMember(JET_SESID sesid,
    const char _far *szGroup, const char _far *szUser);

JET_ERR JET_API EbJetDeleteGroup(JET_SESID sesid, const char _far *szGroup);

JET_ERR JET_API EbJetSetAccess(JET_SESID sesid, JET_DBID dbid,
    const char _far *szContainerName, const char _far *szObjectName,
    const char _far *szName, JET_ACM acm, JET_GRBIT grbit);

JET_ERR JET_API EbJetGetAccess(JET_SESID sesid, JET_DBID dbid,
    const char _far *szContainerName, const char _far *szObjectName,
    const char _far *szName, long fIndividual,
    JET_ACM _far *pacm, JET_GRBIT _far *pgrbit);

JET_ERR JET_API EbJetValidateAccess(JET_SESID sesid, JET_DBID dbid,
    const char _far *szContainerName, const char _far *szObjectName,
    JET_ACM acmRequired);

JET_ERR JET_API EbJetSetOwner(JET_SESID sesid, JET_DBID dbid,
    const char _far *szContainerName, const char _far *szObjectName,
    const char _far *szName);

JET_ERR JET_API EbJetGetOwner(JET_SESID sesid, JET_DBID dbid,
    const char _far *szContainerName, const char _far *szObjectName,
    char _far *szName, unsigned long cchMax);


/*****************************************************************************

    LINK API

*****************************************************************************/

JET_ERR JET_API EbJetCreateLink(JET_SESID sesid, JET_DBID dbid,
    const char _far *szLink, JET_DBID dbidFrom, const char _far *szFrom,
    JET_GRBIT grbit);

JET_ERR JET_API EbJetExecuteSql(JET_SESID sesid, JET_DBID dbid,
    const char _far *szSql);

/***************************************************************************

    Query API

*****************************************************************************/

JET_ERR JET_API EbJetOpenVtQbe(JET_SESID sesid, const char _far *szExpn,
    long _far *plCols, JET_TABLEID _far *ptableid, JET_GRBIT grbit);

JET_ERR JET_API EbJetCreateQuery(JET_SESID sesid, JET_DBID dbid,
    const char _far *szQuery, JET_TABLEID _far *ptableid);

JET_ERR JET_API EbJetOpenQueryDef(JET_SESID sesid, JET_DBID dbid,
    const char _far *szQuery, JET_TABLEID _far *ptableid);

/* CONSIDER: Is rgchSql a zero-terminated string?  Maybe it should be for
 *         consistency.
 */

JET_ERR JET_API EbJetSetQoSql(JET_SESID sesid, JET_TABLEID tableid,
    char _far *rgchSql, unsigned long cchSql);

JET_ERR JET_API EbJetRetrieveQoSql(JET_SESID sesid, JET_TABLEID tableid,
    char _far *rgchSql, unsigned long cchMax,
    unsigned long _far *pcchActual);

JET_ERR JET_API EbJetCopyQuery(JET_SESID sesid, JET_TABLEID tableidSrc,
    JET_DBID dbidDest, const char _far *szQueryDest,
    JET_TABLEID _far *ptableidDest);

JET_ERR JET_API EbJetOpenSVT(JET_SESID sesid, JET_DBID dbid,
    const char _far *szQuery, const void _far *pvParameters,
    unsigned long cbParameters, unsigned long crowSample, JET_GRBIT grbit,
    void _far *pmgblist, unsigned long cbMax, unsigned long _far *pcbActual);

JET_ERR JET_API EbJetGetQueryParameterInfo(JET_SESID sesid, JET_DBID dbid,
    const char _far *szQuery, void _far *pvResult, unsigned long cbMax,
    unsigned long _far *pcbActual);

JET_ERR JET_API EbJetRestartQuery(JET_SESID sesid, JET_TABLEID tableid,
    const void _far *pvParameters, unsigned long cbParameters);

JET_ERR JET_API EbJetSetFatCursor(JET_SESID sesid, JET_TABLEID tableid,
    void _far *pvBookmark, unsigned long cbBookmark, unsigned long crowSize);

JET_ERR JET_API EbJetFillFatCursor(JET_SESID sesid, JET_TABLEID tableid,
    void _far *pvBookmark, unsigned long cbBookmark, unsigned long crow,
    unsigned long _far *pcrow, JET_GRBIT grbit);

JET_ERR JET_API EbJetExecuteTempQuery(JET_SESID sesid, JET_DBID dbid,
    JET_TABLEID tableid, const void _far *pvParameters,
    unsigned long cbParameters, JET_GRBIT grbit, JET_TABLEID _far *ptableid);

JET_ERR JET_API EbJetExecuteTempSVT(JET_SESID sesid, JET_DBID dbid,
    JET_TABLEID tableid, const void _far *pvParameters,
    unsigned long cbParameters, unsigned long crowSample, JET_GRBIT grbit,
    void _far *pmgblist, unsigned long cbMax, unsigned long _far *pcbActual);

JET_ERR JET_API EbJetGetTempQueryColumnInfo(JET_SESID sesid, JET_DBID dbid,
    JET_TABLEID tableid, const char _far *szColumnName,
    void _far *pvResult, unsigned long cbMax, unsigned long InfoLevel);

JET_ERR JET_API EbJetGetTempQueryParameterInfo(JET_SESID sesid, JET_DBID dbid,
    JET_TABLEID tableid, void _far *pvResult, unsigned long cbMax,
    unsigned long _far *pcbActual);

JET_ERR JET_API EbJetOpenTempTable(JET_SESID sesid,
    const JET_COLUMNDEF _far *prgcolumndef, unsigned long ccolumn,
    JET_GRBIT grbit, JET_TABLEID _far *ptableid,
    JET_COLUMNID _far *prgcolumnid);

#ifdef  __cplusplus
}
#endif


//--------------------------------------------------------------------
//
// Map Jet to EbJet macros
//
//--------------------------------------------------------------------

#ifndef NOEBJETMAP

#define JetInit                      EbJetInit
#define JetTerm                      EbJetTerm
#define JetSetSystemParameter        EbJetSetSystemParameter
#define JetGetSystemParameter        EbJetGetSystemParameter
#define JetGetLastErrorInfo          EbJetGetLastErrorInfo
#define JetBeginSession              EbJetBeginSession
#define JetDupSession                EbJetDupSession
#define JetEndSession                EbJetEndSession
#define JetGetVersion                EbJetGetVersion
#define JetIdle                      EbJetIdle
#define JetIdle2                     EbJetIdle2
#define JetCapability                EbJetCapability
#define JetCreateDatabase            EbJetCreateDatabase
#define JetAttachDatabase            EbJetAttachDatabase
#define JetDetachDatabase            EbJetDetachDatabase
#define JetCreateTable               EbJetCreateTable
#define JetRenameTable               EbJetRenameTable
#define JetDeleteTable               EbJetDeleteTable
#define JetGetTableColumnInfo        EbJetGetTableColumnInfo
#define JetGetColumnInfo             EbJetGetColumnInfo
#define JetAddColumn                 EbJetAddColumn
#define JetRenameColumn              EbJetRenameColumn
#define JetDeleteColumn              EbJetDeleteColumn
#define JetGetTableIndexInfo         EbJetGetTableIndexInfo
#define JetGetTableReferenceInfo     EbJetGetTableReferenceInfo
#define JetGetTableInfo              EbJetGetTableInfo
#define JetGetIndexInfo              EbJetGetIndexInfo
#define JetGetReferenceInfo          EbJetGetReferenceInfo
#define JetCreateIndex               EbJetCreateIndex
#define JetRenameIndex               EbJetRenameIndex
#define JetDeleteIndex               EbJetDeleteIndex
#define JetCreateReference           EbJetCreateReference
#define JetRenameReference           EbJetRenameReference
#define JetDeleteReference           EbJetDeleteReference
#define JetGetObjectInfo             EbJetGetObjectInfo
#define JetCreateObject              EbJetCreateObject
#define JetDeleteObject              EbJetDeleteObject
#define JetRenameObject              EbJetRenameObject
#define JetBeginTransaction          EbJetBeginTransaction
#define JetCommitTransaction         EbJetCommitTransaction
#define JetRollback                  EbJetRollback
#define JetUpdateUserFunctions       EbJetUpdateUserFunctions
#define JetLoggingOn                 EbJetLoggingOn
#define JetLoggingOff                EbJetLoggingOff
#define JetGetDatabaseInfo           EbJetGetDatabaseInfo
#define JetCloseDatabase             EbJetCloseDatabase
#define JetCloseTable                EbJetCloseTable
#define JetOpenDatabase              EbJetOpenDatabase
#define JetOpenTable                 EbJetOpenTable
#define JetDelete                    EbJetDelete
#define JetUpdate                    EbJetUpdate
#define JetRetrieveColumn            EbJetRetrieveColumn
#define JetSetColumn                 EbJetSetColumn
#define JetPrepareUpdate             EbJetPrepareUpdate
#define JetGetRecordPosition         EbJetGetRecordPosition
#define JetGotoPosition              EbJetGotoPosition
#define JetGetCursorInfo             EbJetGetCursorInfo
#define JetDupCursor                 EbJetDupCursor
#define JetGetCurrentIndex           EbJetGetCurrentIndex
#define JetSetCurrentIndex           EbJetSetCurrentIndex
#define JetMove                      EbJetMove
#define JetMakeKey                   EbJetMakeKey
#define JetSeek                      EbJetSeek
#define JetFastFind                  EbJetFastFind
#define JetGetBookmark               EbJetGetBookmark
#define JetCompact                   EbJetCompact
#define JetGotoBookmark              EbJetGotoBookmark
#define JetComputeStats              EbJetComputeStats
#define JetGetSidFromName            EbJetGetSidFromName
#define JetGetNameFromSid            EbJetGetNameFromSid
#define JetCreateUser                EbJetCreateUser
#define JetChangeUserPassword        EbJetChangeUserPassword
#define JetDeleteUser                EbJetDeleteUser
#define JetCreateGroup               EbJetCreateGroup
#define JetAddMember                 EbJetAddMember
#define JetRemoveMember              EbJetRemoveMember
#define JetDeleteGroup               EbJetDeleteGroup
#define JetSetAccess                 EbJetSetAccess
#define JetGetAccess                 EbJetGetAccess
#define JetValidateAccess            EbJetValidateAccess
#define JetSetOwner                  EbJetSetOwner
#define JetGetOwner                  EbJetGetOwner
#define JetCreateLink                EbJetCreateLink
#define JetExecuteSql                EbJetExecuteSql
#define JetOpenVtQbe                 EbJetOpenVtQbe
#define JetCreateQuery               EbJetCreateQuery
#define JetOpenQueryDef              EbJetOpenQueryDef
#define JetSetQoSql                  EbJetSetQoSql
#define JetRetrieveQoSql             EbJetRetrieveQoSql
#define JetCopyQuery                 EbJetCopyQuery
#define JetOpenSVT                   EbJetOpenSVT
#define JetGetQueryParameterInfo     EbJetGetQueryParameterInfo
#define JetRestartQuery              EbJetRestartQuery
#define JetSetFatCursor              EbJetSetFatCursor
#define JetFillFatCursor             EbJetFillFatCursor
#define JetExecuteTempQuery          EbJetExecuteTempQuery
#define JetExecuteTempSVT            EbJetExecuteTempSVT
#define JetGetTempQueryColumnInfo    EbJetGetTempQueryColumnInfo
#define JetGetTempQueryParameterInfo EbJetGetTempQueryParameterInfo
#define JetOpenTempTable             EbJetOpenTempTable

#endif  // #ifndef NOEBJETMAP