//---------------------------------------------------------------------------
// uerror.h
//---------------------------------------------------------------------------
// Error codes and error handling macros.
//---------------------------------------------------------------------------
// Copyright (c) 1993-1994, Microsoft Corporation
//                 All Rights Reserved
// Information Contained Herein Is Proprietary and Confidential.
//---------------------------------------------------------------------------
//
// UTOPIA ERRORS
//
// All Utopia errors and results should be defined in this file.
//
// Utopia errors (of type UERR) are 16 bit integers that can directly
// correspond to VB errors.  I.e., where VB defines an appropriate error
// value, we use that error value, and where the error is specific to 
// Utopia, we use error values in the user defined error range provided
// by VB.  Thus, all Utopia errors may be given as VB exceptions.
//
// Utopia results (of type HRESULT) are 32 bit integers as defined
// and used by OLE 2.0 and other COM interfaces.  Where possible,
// Utopia COM interfaces will return predefined HRESULTs.  Custom
// Utopia results that are errors will have facility == FACILITY_ITF, 
// and scode equal to the corresponding Utopia 16 bit error.
//
// Utopia results that are informative and not errors do NOT correspond
// to UERRs, and may not be used as VB exceptions.  Interfaces that
// return successful results other than NOERROR return this value to 
// the VB program, which then checks this return result.     
//--------------------------------------------------------------------------- 


#ifndef uerror_h
#define uerror_h

#include <scode.h>

typedef USHORT UERR;                    // Same as VB type ERR

#define ERR_NONE                        0

#define UERR_ERROR                      20000   // First app defined VB error.

//---------------------------------------------------------------------------
// error handling macros
//---------------------------------------------------------------------------

// This macro may be used to map custom Utopia errors to HRESULTs.  It should NOT be
// used to map arbitrary UERRs, because (for instance) it does not map UERR_OOM to
// E_OUTOFMEMORY.
 
#define ResultFromUErr(err)             (err == ERR_NONE ? NOERROR : ResultFromScode(MAKE_SCODE(SEVERITY_ERROR, FACILITY_ITF, err)))
#define ResultFromUWrn(wrn)             (ResultFromScode(MAKE_SCODE(SEVERITY_SUCCESS, FACILITY_ITF, wrn)))

// The following two macros are used to build OLE 2.0 style sCodes

#define MAKE_UTOP_E( err )              (MAKE_SCODE( SEVERITY_ERROR, FACILITY_ITF, err ))
#define MAKE_UTOP_S( warn )             (MAKE_SCODE( SEVERITY_SUCCESS, FACILITY_ITF, warn ))


// NOTE:  SetError() is a protected inline function in UDispatch.  Perhaps these macros
// should be moved there.

#define SError(scode)                   SetError(ResultFromScode(scode))
#define UError(uerr)                    SetError(ResultFromUErr(uerr))
#define DError(dberr)                   SetError(ResultFromDbErr(dberr))

// These string limits apply to strings put in uerror.str:

#define cchMessageMax   255             // No more than 255 characters in a message.
#define cbMessageMax    256             // That's 256 when you count the NULL.

//--------------------------------------------------------------------------
// System Services...

// System Services to help you map errors and get messages.
// NOTE:  APIs that return BSTRs are only defined if you previously #include <variant.h>  We
// don't just include variant.h from here since it defines other things that conflict
// for some of our clients.
#ifdef _VARIANT_H_
STDAPI_(BSTR) GetDfltMessageForResult(HRESULT hr);  // Get the standard system message
STDAPI_(BSTR) GetDfltMessageForUErr(UERR uerr);  
#endif
STDAPI_(UERR) UErrFromResult(HRESULT hr);        // Get a convient UErr for your HR.

  // 'C++' version of above
STDAPI GetDfltStringForUErr(UERR uerr, char* pBuffer, UINT cbBuffer);
#define GetDfltStringForResult(hr, pbuf, cbbuf)    GetDfltStringForUerr(UErrFromResult(hr), pbuf, cbbuf)

STDAPI_(UERR) UGetLastError(void);               // Meant to be accessed from VB.
STDAPI_(UERR) SetLastError(UERR uerr); 
STDAPI_(UERR) UWarnFromResult(HRESULT hr);       // Get a convenient UWarn for your HR.

//---------------------------------------------------------------------------
// Error handling: This file contains error codes exported by Utopia services.
//
//   If you are exporting an error to a service user, you should determine if
//   the error is already covered by OLE or not.  If so, use it, and set up a
//   mapping between that error and a predefined VB error (listed here) or add
//   your own error code in the manner described below, and add the mapping to
//   the routine UDispatch::SetError(), if that interface is exposed through
//   IDispatch.
//
//   If your error is not covered by OLE, determine if the error is provided
//   by VB.  If not, create a new categorized error here,
//   while being sure that this error does not overlap any OLE errors
//   currently in use.
//
//  UNDONE: Prior to shipping we should determine exactly what error codes
//  UNDONE: are being used, and which aren't.
//
//  *WARNING* *WARNING* *WARNING* *WARNING* *WARNING* *WARNING*
//
//  BEFORE ADDING NEW ERROR CODES:
//
//      a.  Use any applicable OLE error first.  Modify uerror.cpp, UErrFromResult
//              if necessary.
//      1.  See if the error is already here.
//      2.  See if the error is also a VB error (and use the same code)
//      3.  Categorize the error.
//      4.  Add the error to Utopia.bas if it can be encountered by a VB app.
//      5.  Add a comment for the error, so others will understand it.
//      6.  Add a string for it in uerror.str.
//
//  If you use an OLE error - do make sure that it is mapped to a UERR in
//  syssrv\uerror.h.  This is used by GetDfltMessageForResult() when it figures
//  which error message to return.
//
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
// The following errors are VB errors
//---------------------------------------------------------------------------

// Bias the string IDs for VB errors above the ranges used by Actor & Syssrv.
#define VB2ID(err)   ((err)+2000)

#define UERR_OVERFLOW                       6    // Math overflow.
#define UERR_OOM                            7    // Out of memory.
#define UERR_DLL                            8    // DLL can't be loaded.
#define UERR_INTERNAL                       51   // Catchall internal error.
#define UERR_FILENOTFOUND                   53   // File not found.
#define UERR_FILEINUSE                      55   // File Already Open.
#define UERR_DEVICEIO                       57   // Device I/O error.
#define UERR_FILEEXISTS                     58   // File Already Exists
#define UERR_BADRECLEN                      59   // Bad Record Length
#define UERR_DISKFULL                       61   // Disk full.
#define UERR_EOF                            62   // End of File
#define UERR_BADRECNUM                      63   // Bad Record Number
#define UERR_BADFILENAME                    64   // Invalid Filename specified.
#define UERR_TOOMANYFILES                   67   // Too Many Files
#define UERR_DEVICEUNAVAIL                  68   // Device unavailable.
#define UERR_PERMISSIONDENIED               70   // File access denied
#define UERR_DISKNOTREADY                   71   // Busy disk.
#define UERR_RENACROSSDRIVE                 72   // Rename across Drive
#define UERR_ACCESSDENIED                   75   // The path or file was not accessable
#define UERR_PATHNOTFOUND                   76   // Path Not Found
#define UERR_OLEOBJECTNOTSET                91   // Used an uninitialized Object variable
#define UERR_OLEAUTOMATION                  440  // General ole automation error
#define UERR_FILEFORMAT                     321  // Bad file format
#define UERR_CLIPBOARDFORMAT                460  // Bad clipboard format
#define UERR_PRINTER                        482  // Printer error.

#define UERR_LAST_VB_ERROR                  999
// NOTE: Do not define VB error numbers above 999
//       to avoid conflict with string numbers in syssrv STRINGTABLE

// -- Ole errors trapped by VB

#define UERR_OLE_NO_OBJECT                 31004   // No Object
#define UERR_OLE_CANNOT_CLOSE              31006   // Can not close object
#define UERR_OLE_CANNOT_PASTE              31007   // Can not paste object
#define UERR_OLE_CANNOT_COPY               31009   // Can not copy object
#define UERR_OLE_CANNOT_INITOLE            31022   // Can not initialize Ole
#define UERR_OLE_UNKNOWN_CLASS             31023   // Invalid or Unknown class
#define UERR_OLE_CANNOT_CREATE_EMBED       31032   // Can not create embedded object
#define UERR_OLE_INVALID_VERB              31034   // Invalid verb index
#define UERR_OLE_CANNOT_SAVE_TO_FILE       31036   // Can not save object to a file
#define UERR_OLE_CANNOT_LOAD_FROM_FILE     31037   // Can not load object from file 

//---------------------------------------------------------------------------
// generic errors.
//
//  PLEASE ADD COMMENTS, so everyone will know when to use these
//---------------------------------------------------------------------------

#define UERR_GEN_OPERATION_CANCELLED    0x000 + UERR_ERROR  // User abort
#define UERR_GEN_OPERATION_FAILED       0x001 + UERR_ERROR  // General failure.  Reason unknown.
#define UERR_GEN_METHOD_NOT_FOUND       0x002 + UERR_ERROR
#define UERR_GEN_COULDNT_READ_PROP      0x003 + UERR_ERROR
#define UERR_GEN_COULDNT_WRITE_PROP     0x004 + UERR_ERROR
#define UERR_GEN_READ_ONLY_PROP         0x005 + UERR_ERROR
#define UERR_GEN_UNKNOWN_PROP           0x006 + UERR_ERROR
#define UERR_GEN_NOT_YET_IMPLEMENTED    0x007 + UERR_ERROR
#define UERR_GEN_SYSTEMRESOURCES        0x008 + UERR_ERROR  // Out of file handles, or such
#define UERR_GEN_BADSYSTEMSETUP         0x009 + UERR_ERROR  // Missing SHARE.EXE, old OLE, etc.  Rerun Setup
#define UERR_GEN_FILEREADONLY           0x00a + UERR_ERROR  // File is ReadOnly
#define UERR_GEN_FILEEXISTS             0x00b + UERR_ERROR  // File already Exists
#define UERR_GEN_LOCKEDDISK             0x00c + UERR_ERROR  // The disk is write protected
#define UERR_GEN_FILECREATE             0x00d + UERR_ERROR  // Could not create a file.  Reason unknown.
#define UERR_GEN_FILEREAD               0x00e + UERR_ERROR  // A problem reading a file - Reason unknown.
#define UERR_GEN_FILEWRITE              0x00f + UERR_ERROR  // A problem writing a file - Reason unknown.
#define UERR_GEN_FILEOPEN               0x010 + UERR_ERROR  // A problem opening a file - Reason unknown.
#define UERR_GEN_JET                    0x011 + UERR_ERROR  // Catchall for any unmapped Jet error
#define UERR_GEN_FILEFORMAT             0x012 + UERR_ERROR  // Bad File Format
#define UERR_GEN_NO_PRINTER             0x013 + UERR_ERROR  // No printer available for printing
#define UERR_GEN_PRINTER_SLEEPING       0x014 + UERR_ERROR  // Printer not responding
#define UERR_GEN_BADPARAMETER           0x015 + UERR_ERROR  // invalid formal parameter 
#define UERR_GEN_BADPASSWORD            0x016 + UERR_ERROR  // invalid password
#define UERR_GEN_BAD_PRINTER            0x017 + UERR_ERROR  // The printer can't do graphics, or can't do TrueType.
#define UERR_GEN_BAD_PRINTERCHG         0x018 + UERR_ERROR  // Attempt was made to switch to an unacceptable printer.
#define UERR_GEN_FULLDISK               0x019 + UERR_ERROR  // generalized disk full error
#define UERR_GEN_BADDISK                0x01a + UERR_ERROR  // bad media type or wrong format disk
#define UERR_GEN_PRINTER_CONFIG         0x01b + UERR_ERROR  // printer driver installed, but can't load it.

//---------------------------------------------------------------------------
// mail mapi subsystem.
//---------------------------------------------------------------------------

#define UERR_UMAIL_FIRST                0x040 + UERR_ERROR
#define UERR_UMAIL_LAST                 0x07F + UERR_ERROR

#define UERR_UMAIL_MAPIINIT_FAILED      UERR_UMAIL_FIRST + 0
#define UERR_UMAIL_LOGON_FAILED         UERR_UMAIL_FIRST + 1
#define UERR_UMAIL_ADMIN_FAILED         UERR_UMAIL_FIRST + 2
#define UERR_UMAIL_MAILRUN_FAILED       UERR_UMAIL_FIRST + 3
#define UERR_UMAIL_FOLDER_MCD_FAILED    UERR_UMAIL_FIRST + 4
#define UERR_UMAIL_MESSAGE_SAVE_FAILED  UERR_UMAIL_FIRST + 5
#define UERR_UMAIL_NOT_ALLOWED          UERR_UMAIL_FIRST + 6
#define UERR_UMAIL_GUEST_LOGON          UERR_UMAIL_FIRST + 7
#define UERR_UMAIL_NO_ACCOUNT_INFO      UERR_UMAIL_FIRST + 8
#define UERR_UMAIL_DUP_FOLDER_NAME      UERR_UMAIL_FIRST + 9
#define UERR_UMAIL_NO_TRANSPORT         UERR_UMAIL_FIRST + 10
#define UERR_UMAIL_INVALID_MESSHANDLE   UERR_UMAIL_FIRST + 11
#define UERR_UMAIL_CORRUPT_STORE        UERR_UMAIL_FIRST + 12

#define UWRN_UMAIL_USER_CANCEL          UERR_UMAIL_LAST - 0
#define UWRN_UMAIL_DELIVERED            UERR_UMAIL_LAST - 1
#define UWRN_UMAIL_NOT_DELIVERED        UERR_UMAIL_LAST - 2


//---------------------------------------------------------------------------
// actor services
//---------------------------------------------------------------------------

#define UERR_ACTOR_FIRST                0x080 + UERR_ERROR
#define UERR_ACTOR_LAST                 0x0BF + UERR_ERROR

// File is not a valid Utopia Actor or Animation file
#define ACTOR_E_INVALID                 MAKE_UTOP_E(UERR_ACTOR_FIRST + 0)

// Actor file does not contain definition for given locale
#define ACTOR_E_LOCALENOTSUPPORTED      MAKE_UTOP_E(UERR_ACTOR_FIRST + 1)

// Requested action is not defined by actor or animation
#define ACTOR_E_NOTDEFINED              MAKE_UTOP_E(UERR_ACTOR_FIRST + 2)

// Actor object does not support animations, just phrases
#define ACTOR_E_NOANIMATION             MAKE_UTOP_E(UERR_ACTOR_FIRST + 3)

//---------------------------------------------------------------------------
// table of contents
//---------------------------------------------------------------------------

#define UERR_TOC_FIRST                  0x0C0 + UERR_ERROR
#define UERR_TOC_LAST                   0x0FF + UERR_ERROR

#define UERR_TOC_TOO_MANY_FILES         UERR_TOC_FIRST + 1 //EMFILE
#define UERR_TOC_INVALID_TYPE           UERR_TOC_FIRST + 2 // Invalid Type Id
#define UERR_TOC_INVALID_ITEM           UERR_TOC_FIRST + 3 // Invalid Item Id
#define UERR_TOC_INVALID_TYPE_DLL       UERR_TOC_FIRST + 4 // Invalid TOCPROC dll
#define UERR_TOC_INVALID_BUNDLE         UERR_TOC_FIRST + 5 // Invalid bundled file
#define UERR_TOC_INVALID_APP            UERR_TOC_FIRST + 6 // Invalid App Id
#define UERR_TOC_INVALID_USER           UERR_TOC_FIRST + 7 // Invalid User Id
#define UERR_TOC_DUPLICATE_NAME         UERR_TOC_FIRST + 8 // Duplicate Book Name
#define UERR_TOC_NO_UTOPIA_FILES        UERR_TOC_FIRST + 9 // No utopia bundle files on disk

// During item deletion, the TOC File was not deleted due to a dos error
#define UWRN_TOC_FILE_NOT_DELETED       MAKE_UTOP_S(UERR_TOC_FIRST + 12) 


//---------------------------------------------------------------------------
// Quill/Qdoc
//---------------------------------------------------------------------------

#define UERR_QUILL_FIRST                UERR_ERROR + 0x100
#define UERR_QUILL_LAST                 UERR_ERROR + 0x13F

#define UERR_QUILL_CVTFAILED            UERR_QUILL_FIRST + 0    // File conversion Failed
#define UERR_QUILL_TOOMANYFILES         UERR_QUILL_FIRST + 1    // Too many open Quill documents
#define UERR_QUILL_TOOMANYEDITS         UERR_QUILL_FIRST + 2    // Too many edits in Quill doc
#define UERR_QUILL_SPELL_MAINDICT       UERR_QUILL_FIRST + 3    // Problem opening spelling dict 
#define UERR_QUILL_SPELL_USERDICT       UERR_QUILL_FIRST + 4    // Problem opening user dict
#define UERR_QUILL_SPELL_SPELLCHECK     UERR_QUILL_FIRST + 5    // Problem doing spell check
#define UERR_QUILL_SPELL_INIT           UERR_QUILL_FIRST + 6    // Problem doing spell init
#define UERR_QUILL_ADD_FRAME            UERR_QUILL_FIRST + 7    // Problem making a new frame
#define UERR_QUILL_FORMAT               UERR_QUILL_FIRST + 8    // Formatting problem, probably low resources
#define UERR_QUILL_CUT                  UERR_QUILL_FIRST + 9    // Quill cut failed    
#define UERR_QUILL_COPY                 UERR_QUILL_FIRST + 10   // Quill copy failed
#define UERR_QUILL_PASTE                UERR_QUILL_FIRST + 11   // Quill paste failed
#define UERR_QUILL_DELETE               UERR_QUILL_FIRST + 12   // Quill delete failed
#define UERR_QUILL_NOTATEXTSELECTION    UERR_QUILL_FIRST + 13   // Only valid for text selections.
#define UERR_QUILL_NOTAFRAMESELECTION   UERR_QUILL_FIRST + 14   // Only valid for a frame selection.
#define UERR_QUILL_SPELL_INSTALLATION   UERR_QUILL_FIRST + 15   // Problem loading MSSPELL.DLL.
#define UERR_QUILL_AUTOSAVEFAILED       UERR_QUILL_FIRST + 16   // Background Autosave operation failed.

//---------------------------------------------------------------------------
// Calendar
//---------------------------------------------------------------------------

#define UERR_CAL_FIRST                  0x140 + UERR_ERROR
#define UERR_CAL_LAST                   0x17F + UERR_ERROR  

#define UERR_CAL_QUERYFAILED            UERR_CAL_FIRST + 0      // Database query failed
#define UERR_CAL_NODEFAULT              UERR_CAL_FIRST + 1      // No default calendar
#define UERR_CAL_NEWDEFAULT             UERR_CAL_FIRST + 2      // Warning: new default created

//---------------------------------------------------------------------------
// Tippage
//---------------------------------------------------------------------------

#define UERR_TIP_FIRST                  0x180 + UERR_ERROR
#define UERR_TIP_LAST                   0x1BF + UERR_ERROR

// Tip ID was not defined (setup problem or programming error)
#define TIP_E_INVALID                   MAKE_UTOP_E(UERR_TIP_FIRST + 0)

// Successful tippage returns:

// Tip displayed, user chose Cancel
#define TIP_S_CANCEL                    MAKE_UTOP_S(UERR_TIP_FIRST + 1) 

// Triggered tip did not get displayed
#define TIP_S_NOTDISPLAYED              MAKE_UTOP_S(UERR_TIP_FIRST + 2)

// Triggered tip should be displayed by the application
#define TIP_S_APPDISPLAY                MAKE_UTOP_S(UERR_TIP_FIRST + 3) 

// No hints left in hint-o-rama
#define TIP_S_NOHINTSLEFT               MAKE_UTOP_S(UERR_TIP_FIRST + 4) 


//---------------------------------------------------------------------------
// Syssrv
//---------------------------------------------------------------------------

#define UERR_SYSSRV_FIRST                0x1C0 + UERR_ERROR
#define UERR_SYSSRV_LAST                 0x1FF + UERR_ERROR

#define SYSSRV_E_UTOPIAINIT_FAILED      MAKE_UTOP_E(UERR_SYSSRV_FIRST + 0)
#define SYSSRV_E_GETSYSTEM_FAILED       MAKE_UTOP_E(UERR_SYSSRV_FIRST + 1)
#define SYSSRV_E_INVALID_USER           MAKE_UTOP_E(UERR_SYSSRV_FIRST + 2)
#define SYSSRV_E_INVALID_APP            MAKE_UTOP_E(UERR_SYSSRV_FIRST + 3)
#define SYSSRV_E_INVALID_TASK           MAKE_UTOP_E(UERR_SYSSRV_FIRST + 4)

// errors that could be returned from a task launching

#define UERR_TASK_WINVERWRONG           (UERR_SYSSRV_FIRST + 5)
#define UERR_TASK_INVALIDEXE            (UERR_SYSSRV_FIRST + 6)
#define UERR_TASK_NONWINEXE             (UERR_SYSSRV_FIRST + 7)
#define UERR_TASK_SECONDINST            (UERR_SYSSRV_FIRST + 8)
#define UERR_TASK_EXECOMPRESD           (UERR_SYSSRV_FIRST + 9)
#define UERR_TASK_DLLCORRUPT            (UERR_SYSSRV_FIRST + 10)
#define UERR_TASK_EXE32BIT              (UERR_SYSSRV_FIRST + 11)
#define UERR_TASK_PATHNOTFOUND          (UERR_SYSSRV_FIRST + 12)
#define UERR_TASK_FILENOTFOUND          (UERR_SYSSRV_FIRST + 13)
#define UERR_TASK_UNKNOWN               (UERR_SYSSRV_FIRST + 14)

// not a syssrv error, but a system wide error
#define UERR_SYS_LOWGDI                 (UERR_SYSSRV_FIRST + 15)
#define UERR_SYS_DISPLAYCHANGE          (UERR_SYSSRV_FIRST + 16)
#define UERR_SYS_DISPLAYCHANGE2         (UERR_SYSSRV_FIRST + 17)

#define UERR_JET_DBNOTFOUND             (UERR_SYSSRV_FIRST + 18)
#define UERR_JET_ACCESSDENIED           (UERR_SYSSRV_FIRST + 19)
#define UERR_JET_REPAIRFAILED           (UERR_SYSSRV_FIRST + 20)
#define USUCC_FIRSTTASK                 (UERR_SYSSRV_FIRST + 21)

//---------------------------------------------------------------------------
// Address Book Service
//---------------------------------------------------------------------------

#define UERR_ABOOK_FIRST                0x200 + UERR_ERROR
#define UERR_ABOOK_LAST                 0x23F + UERR_ERROR

#define UERR_ABOOK_EMPTYBOOK            UERR_ABOOK_FIRST + 0    // the book is empty
#define UERR_ABOOK_CANCELUNBUNDLE       UERR_ABOOK_FIRST + 1    // User canceled out of a unbundle
#endif // !uerror_h
