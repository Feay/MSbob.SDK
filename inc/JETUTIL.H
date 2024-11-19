/*=================================================================
Microsoft Jet

Microsoft Confidential.  Copyright 1991 Microsoft Corporation.

Component: Jet Utility DLL

File: jetutil.h - JET Utility APIs

File Comments:

Revision History:

    [0]  29-Jul-91  w-rtyson   Created

=================================================================*/

#if !defined(_JETUTIL_INCLUDED)
#define _JETUTIL_INCLUDED

#ifdef	__cplusplus
extern "C" {
#endif

#pragma pack(2)

/******************************************************************
 *
 * Import/Export section follows...
 *
 */


#define IMEX_PUBLIC	_loadds _far _pascal



typedef unsigned JET_FMT;


	/* File Formats */

#define JET_fmtDelimited	0	/* ASCII: delimited	  */
#define JET_fmtFixed		1	/* ASCII: Fixed-Width	  */
#define JET_fmtBIFF		2	/* Spreadsheet: Excel 2.x */
#define JET_fmtBIFF3		3	/* Spreadsheet: Excel 3.0 */
#define JET_fmtBIFF4		4	/* Spreadsheet: Excel 4.0 */
#define JET_fmtWKS		5	/* Spreadsheet: Lotus 1.x */
#define JET_fmtWK1		6	/* Spreadsheet: Lotus 2.x */
#define JET_fmtWK3		7	/* Spreadsheet: Lotus 3.x */


	/* Import/Export functions */
typedef enum { fImport, fImportAppend, fExport };

	/* Date Formats */

typedef enum { fDateDMY, fDateDYM, fDateMDY, fDateMYD, fDateYDM, fDateYMD };



/**********
 *
 *	DESCRIPTOR TYPES
 *
 **********/

	/* TABLE DESCRIPTOR */
typedef struct JET_TBLDESC {
	char		szFileName[256];	/* name of src/dest file	*/
	JET_SESID	sesid;			/* session id			*/
	JET_DBID	dbid;			/* database id			*/
	char		szTableName[65];	/* name of src/dest table	*/
	char		chFiller;
	JET_TABLEID	tblid;			/* tableid of the src table for export */
	unsigned	ccoldesc;		/* number of columns in table */
	int		fRow1Names;		/* first row is column names? */
	unsigned long	CodePage;		/* code page of external file */

	/****** ASCII Only ******/
	char		szBadRecsFileName[256]; /* Bad records file (import only) */
	char		chTextDelimiter;	/* Text delimiter		*/
	char		chFieldSep;		/* Field separator		*/
	char		szRowSep[3];		/* Row separator		*/
	char		chDecimalSep;		/* Decimal separator		*/
	char		chDateDelimiter;	/* Date delimiter		*/
	char		chTimeDelimiter;	/* Time delimiter		*/
	int		fLeadingZero;		/* Use leading zero in dates?	*/
	unsigned	dateFormat;		/* Date format			*/
	int		fCentury;		/* Use century in date? 	*/

	/****** ASCII fixed-width ******/
	unsigned long	cbRowSize;		/* Size of fixed-width row	*/

	/****** SS Only ******/
	char		szRange[256];		/* Named Range of cells.	*/

	/****** Internal Imex use only (DO NOT MODIFY) ******/
	void far	*pvTblInfoBlock;	/* Pointer to internal tbl info structure */

	} JET_TBLDESC;


	/* COLUMN DESCRIPTOR */
typedef struct JET_COLDESC {
	int		fIncluded;		/* fTrue = include this col	*/
	char		szColumnName[65];	/* JET Column Name		*/
	char		chFiller;
	JET_COLTYP	coltyp; 		/* Column Type			*/
	JET_GRBIT	colattribute;		/* Column Attribute		*/
	unsigned long	cbWidth;		/* Col's width or max length    */
						/* of variable width column	*/

	/****** ASCII fixed-width ******/
	unsigned long	cbStartOffset;		/* Col's offset in the row  */

	/****** Internal Imex use only (DO NOT MODIFY) ******/
	JET_COLUMNID	columnid;		/* Column Id			*/
	unsigned	iRowBuf;		/* Index of col in szRowBuf	*/
	unsigned	wExtra; 		/* Extra storage		*/

	} JET_COLDESC;


/**********
 *
 *	Error, Warning and Status Notification Codes
 *
 **********/

#define JET_wrnImexSSNotRecalcd 	 32001
#define JET_errImexCantOpenFile 	-32002
#define JET_errImexBadTableName 	-32003
#define JET_errImexOutOfMemory		-32004
#define JET_errImexBadCDESC		-32005
#define JET_errImexTableTDESCMismatch	-32006
#define JET_errImexCantOpenBadRecFile	-32007
#define JET_errImexEndofFile		-32008
#define JET_errImexBadFileType		-32009
#define JET_errImexCantWriteToFile	-32010
#define JET_errImexCantSetMark		-32011
#define JET_errImexCantGoMark		-32012
#define JET_errImexBadRange		-32013
#define JET_errImexBogusFile		-32014
#define JET_errImexNoMatchingColumns	-32015
#define JET_errImexPasswordProtected	-32016
#define JET_errImexUnparsableRecord	-32017


#define JET_sncImexTypeConversionFail	31000
#define JET_sncImexFieldSetFail 	31001
#define JET_sncImexFieldTruncation	31002
#define JET_sncImexUnparsableRecord	31003
#define JET_sncImexKeyViolation 	31004
#define JET_sncImexRowTruncation	31005
#define JET_sncImexFileTruncation	31006



/**********
 *
 *	PROTOTYPES
 *
 **********/

JET_ERR IMEX_PUBLIC JetImexSetup(
	JET_TBLDESC	_far *ptdesc,
	int		fOperation,
	JET_FMT 	fmt);

JET_ERR IMEX_PUBLIC JetImexSetupColumns(
	JET_TBLDESC	_far *ptdesc,
	JET_COLDESC	_far rgcdesc[]);

JET_ERR IMEX_PUBLIC JetImexImport(
	JET_TBLDESC	_far *ptdesc,
	JET_COLDESC	_far rgcdesc[]);

JET_ERR IMEX_PUBLIC JetImexExport(
	JET_TBLDESC	_far *ptdesc,
	JET_COLDESC	_far rgcdesc[]);

JET_ERR IMEX_PUBLIC JetImexFreeResources(
	JET_TBLDESC	_far *ptdesc);


#pragma pack()

#ifdef	__cplusplus
}
#endif

#endif	/* _JETUTIL_INCLUDED */
