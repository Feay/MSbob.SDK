//---------------------------------------------------------------------------
//  umail.h
//---------------------------------------------------------------------------
//  Copyright (c) 1993, Microsoft Corporation.  All Rights Reserved
//  Information Contained Herein Is Proprietary and Confidential.
//---------------------------------------------------------------------------
//
//  public interface file for the mail services objects for Utopia
//
//  Owner: scotts
//
//  History:
//  08-25-93    ScottS          Created
//---------------------------------------------------------------------------


#ifdef WIN32
#include <objbase.h>
#else
#include <compobj.h>
#endif

//---------------------------------------------------------------------------
//  UMail Defines
//---------------------------------------------------------------------------

// message classes
#define kMClassUtopiaIPM                    "IPM.UTOPIA"
#define kMClassUtopiaInfo                   "UTOPIA"

// interpersonal mail message classes
#define kMClassUNote                        "IPM.UTOPIA.NOTE"
#define kMClassULetter                      "IPM.UTOPIA.LETTER"
#define kMClassUPostcard                    "IPM.UTOPIA.POSTCARD"
#define kMClassUGreeting                    "IPM.UTOPIA.GREETING"
#define kMClassURecipie                     "IPM.UTOPIA.RECIPIE"
#define kMClassUNDR                         "IPM.UTOPIA.NDR"
#define kMClassUUnsent                      "IPM.UTOPIA.UNSENT"
#define kMClassUInternet                    "IPM.UTOPIA.INTERNET"
#define kMClassUResend                      "IPM.Resend"

// utopia info message classes
#define kMClassUWeather                     "UTOPIA.WEATHER"
#define kMClassUStockQuote                  "UTOPIA.STOCKQUOTE"
#define kMClassUNews                        "UTOPIA.NEWS"
#define kMClassUSportsNews                  "UTOPIA.SPORTS"

// folder indexes
#define kIFLDRInbox                         ((LONG) 0)
#define kIFLDROutbox                        ((LONG) 1)
#define kIFLDRWastebasket                   ((LONG) 2)
#define kIFLDRUser1                         ((LONG) 3)
#define kIFLDRUser2                         ((LONG) 4)
#define kIFLDRUser3                         ((LONG) 5)
#define kIFLDRUser4                         ((LONG) 6)
#define kIFLDRUser5                         ((LONG) 7)
#define kIFLDRMax                           ((LONG) 8)

// UMailNotification Event Types
#define kVBNotifNewMail                     1
#define kVBNotifTableRowAdded               2
#define kVBNotifTableRowDeleted             3
#define kVBNotifTableRowModified            4
#define kVBNotifMailRunBegin                5
#define kVBNotifMailRunEnd                  6
#define kVBNotifMailrunLikely               7

// address types used in the utopia address book
#define kAddrTypeUtopia                     ((LONG) 1)
#define kAddrTypeAOL                        ((LONG) 2)
#define kAddrTypeCompuServe                 ((LONG) 3)
#define kAddrTypeInternet                   ((LONG) 4)
#define kAddrTypeMCI                        ((LONG) 5)
#define kAddrTypeProdigy                    ((LONG) 6)
#define kAddrTypeOther                      ((LONG) 7)

#define kszAddrTypeUtopia                   "BOB"
#define kszAddrTypeInternet                 "UMI"

#define kszAddrDomainAOL                    "@aol.com"
#define kszAddrDomainCompuServe             "@compuserve.com"
#define kszAddrDomainMCI                    "@mcimail.com"
#define kszAddrDomainProdigy                "@prodigy.com"

#define kszClientDLL                        "UMAIL.DLL"
#define kszTransportDLL                     "UMLXP.DLL"
#define kszTransport32DLL                   "UMLXP32.DLL"

// transport notification (transport to client)
#define kTPNotifMailRunBegin                ((LONG) 1)
#define kTPNotifMailRunEnd                  ((LONG) 2)
#define kTPNotifMailrunStatus               ((LONG) 3)

// kTPNotifMailrunStatus types
#define kTPStatusProcessingUrgent           ((LONG) 1)
#define kTPStatusConnecting                 ((LONG) 2)
#define kTPStatusDialing                    ((LONG) 3)
#define kTPStatusDialRetry                  ((LONG) 4)
#define kTPStatusLogginOn                   ((LONG) 5)
#define kTPStatusCheckingMailbox            ((LONG) 6)
#define kTPStatusUploading                  ((LONG) 7)
#define kTPStatusDownloading                ((LONG) 8)
#define kTPStatusDisconnecting              ((LONG) 9)
#define kTPStatusProcessingNew              ((LONG) 10)

// property tags for our custom status properties
#define kSHAREDTAG_XP_NOTIF                 PROP_TAG(PT_LONG, 0x6600)
#define kSHAREDTAG_XP_MRSTATUS              PROP_TAG(PT_LONG, 0x6601)
#define kSHAREDTAG_XP_MRSTATUS_STRING       PROP_TAG(PT_STRING8, 0x6602)

// buffer size used when copying blocks of data
#define kCopyBlockSize                      1024

// baud id's
#define kBAUD2400                           ((LONG) 0)
#define kBAUD9600                           ((LONG) 1)
#define kBAUD14400                          ((LONG) 2)
#define kBAUD28800                          ((LONG) 3)

// defines for profile sections/entries
#define kszUMailCache                       "\\MAILROOM.INI"

#define kPSEC_SETUP                         "SETUP"
#define kPSEC_STATUS                        "STATUS"
#define kPSEC_USERS                         "USERS"

#define kPENT_ACCOUNT_NAME                  "ACCOUNT_NAME"
#define kPENT_ACCOUNT_ID                    "ACCOUNT_ID"
#define kPENT_ACCOUNT_PASSWORD              "ACCOUNT_PASSWORD"
#define kPENT_ACCOUNT_PHONE_NUM             "ACCOUNT_PHONE_NUM"
#define kPENT_DIAL_PREFIX                   "DIAL_PREFIX"
#define kPENT_DIAL_TYPE                     "DIAL_TYPE"
#define kPENT_DIAL_RETRY                    "DIAL_RETRY"
#define kPENT_DIAL_AUDIBLE                  "DIAL_AUDIBLE"
#define kPENT_COM_PORT                      "COM_PORT"
#define kPENT_COM_BAUD_RATE                 "COM_BAUD_RATE"
#define kPENT_MCI_CONNECT_STRING            "MCI_CONNECT_STRING"
#define kPENT_MCI_SETUP_STRING              "MCI_SETUP_STRING"
#define kPENT_MCI_MNP_SUPPORT               "MCI_MNP_SUPPORT"
#define kPENT_DEFAULT_USER                  "DEFAULT_USER"
#define kPENT_DIR_MAILROOM                  "DIR_MAILROOM"
#define kPENT_DIR_MAILRUN_IN                "DIR_MAILRUN_IN"
#define kPENT_DIR_MAILRUN_OUT               "DIR_MAILRUN_OUT"

#define kPENT_MAILRUN_DATE                  "MAILRUN_DATE"
#define kPENT_MAILRUN_TIME                  "MAILRUN_TIME"
#define kPENT_LAST_ERROR                    "LAST_ERROR"
#define kPENT_UPLOAD_COUNT                  "UPLOAD_COUNT"
#define kPENT_DOWNLOAD_COUNT                "DOWNLOAD_COUNT"
#define kPENT_REJECT_COUNT                  "REJECT_COUNT"
#define kPENT_UNSENT_COUNT                  "UNSENT_COUNT"

//
//  class task object used to callback vb apps
//  when with mail services notifications
//

// we get this definition from vbapi.h
typedef LPVOID      HCTL;       // hctl

class UMailNotif {
// Implementation
public:
    UMailNotif(HCTL hctl);

    STDMETHOD(VBNotifCallback)(THIS_ LONG FolderIndex, LONG RowIndex, ULONG VBNotif);

public:
    HCTL        m_hctl;
};


//---------------------------------------------------------------------------
//  IUMailSession Interface
//---------------------------------------------------------------------------

#undef INTERFACE
#define INTERFACE IUMailSession

DECLARE_INTERFACE_(IUMailSession, IUnknown)
{
    // IUnknown methods
    STDMETHOD(QueryInterface)(THIS_ REFIID riid, LPVOID * ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef)(THIS)  PURE;
    STDMETHOD_(ULONG,Release)(THIS) PURE;
    
    // IUMailSession methods
    STDMETHOD_(ULONG, GetVersion)(THIS_) PURE;
    STDMETHOD_(ULONG, GetSessionRef)(THIS_) PURE;
    STDMETHOD(ModemSetup)(THIS_) PURE;
    STDMETHOD(AccountSetup)(THIS_) PURE;
    STDMETHOD(LogonMailroom)(THIS_ HWND hwndParent) PURE;
    STDMETHOD(LogonAware)(THIS_ HWND hwndParent) PURE;
    STDMETHOD(LogonUtopia)(THIS_ HWND hwndParent) PURE;
    STDMETHOD(Logoff)(THIS_) PURE;
    STDMETHOD_(LPDISPATCH, CreateMessage)(THIS_) PURE;
    STDMETHOD_(LPDISPATCH, ReadMessage)(THIS_ BSTR hMsg) PURE;
    STDMETHOD_(LPDISPATCH, ReplyMessage)(THIS_ BSTR hMsg, BOOL fCopyOrigMess) PURE;
    STDMETHOD_(LPDISPATCH, ForwardMessage)(THIS_ BSTR hMsg, BOOL fCopyOrigMess) PURE;
    STDMETHOD_(LPDISPATCH, ResendMessage)(THIS_ BSTR hMsg) PURE;
    STDMETHOD(StartMailRun)(THIS_ LONG rgfFlags) PURE;
    STDMETHOD(MailrunStatus)(THIS_) PURE;
    STDMETHOD(SetMailParentWindow)(THIS_ HWND hwndParent) PURE;
    
    // Not exposed through IDispatch
    STDMETHOD_(VOID, RegisterMailEvents)(THIS_ UMailNotif * pUMailNotif) PURE;
    STDMETHOD_(void, GetUMailInboxCount)(THIS_ long * pcMsg, long * pcUnreadMsg) PURE;
};

typedef IUMailSession * LPUMAILSESSION;


//---------------------------------------------------------------------------
//  IUMailFolder Interface
//---------------------------------------------------------------------------

#undef INTERFACE
#define INTERFACE IUMailFolder

DECLARE_INTERFACE_(IUMailFolder, IUnknown)
{
    // IUnknown methods
    STDMETHOD(QueryInterface)(THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef)(THIS)  PURE;
    STDMETHOD_(ULONG,Release)(THIS) PURE;
    
    // IUMailFolder methods
    STDMETHOD_(LPDISPATCH, rgSummary)(THIS_ LONG Index) PURE;
    STDMETHOD(MoveMessage)(THIS_ BSTR hMsg, LONG FolderIndex) PURE;
    STDMETHOD(CopyMessage)(THIS_ BSTR hMsg, LONG FolderIndex) PURE;
    STDMETHOD(DeleteMessage)(THIS_ BSTR hMsg) PURE;
};

typedef IUMailFolder * LPUMAILFOLDER;


//---------------------------------------------------------------------------
//  IUMailSummary Interface
//---------------------------------------------------------------------------

#undef INTERFACE
#define INTERFACE IUMailSummary

DECLARE_INTERFACE_(IUMailSummary, IUnknown)
{
    // IUnknown methods
    STDMETHOD(QueryInterface)(THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef)(THIS)  PURE;
    STDMETHOD_(ULONG,Release)(THIS) PURE;
    
    // IUMailSummary methods
};

typedef IUMailSummary * LPUMAILSUMMARY;


//---------------------------------------------------------------------------
//  IUMailMessage Interface
//---------------------------------------------------------------------------

#undef INTERFACE
#define INTERFACE IUMailMessage

DECLARE_INTERFACE_(IUMailMessage, IUnknown)
{
    // IUnknown methods
    STDMETHOD(QueryInterface)(THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef)(THIS)  PURE;
    STDMETHOD_(ULONG,Release)(THIS) PURE;
    
    // IUMailMessage methods
    STDMETHOD_(LPDISPATCH, rgRecip)(THIS_ LONG Index) PURE;
    STDMETHOD_(LPDISPATCH, rgAttach)(THIS_ LONG Index) PURE;
    STDMETHOD(GetAttachments)(THIS_) PURE;
    STDMETHOD(SaveAttachments)(THIS_) PURE;
    STDMETHOD(GetRecipients)(THIS_ BSTR bsrgAddrID) PURE;
    STDMETHOD(AddSenderToAddressBook)(THIS_) PURE;
    STDMETHOD_(BSTR, GetAwareData)(THIS_) PURE;
    STDMETHOD(PutAwareData)(THIS_ BSTR bsFilePath, BSTR bsTitle) PURE;
    STDMETHOD(Save)(THIS_) PURE;    
    STDMETHOD(Submit)(THIS_) PURE;
    STDMETHOD_(long, GetBodyStream)(THIS_) PURE;
    STDMETHOD(CloseBodyStream)(THIS_ long lpStreamBody) PURE;
};

typedef IUMailMessage * LPUMAILMESSAGE;


//---------------------------------------------------------------------------
//  IUMailRecip Interface
//---------------------------------------------------------------------------

#undef INTERFACE
#define INTERFACE IUMailRecip

DECLARE_INTERFACE_(IUMailRecip, IUnknown)
{
    // IUnknown methods
    STDMETHOD(QueryInterface)(THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef)(THIS)  PURE;
    STDMETHOD_(ULONG,Release)(THIS) PURE;
    
    // IUMailRecip methods
};

typedef IUMailRecip * LPUMAILRECIP;


//---------------------------------------------------------------------------
//  IUMailAttach Interface
//---------------------------------------------------------------------------

#undef INTERFACE
#define INTERFACE IUMailAttach

DECLARE_INTERFACE_(IUMailAttach, IUnknown)
{
    // IUnknown methods
    STDMETHOD(QueryInterface)(THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef)(THIS)  PURE;
    STDMETHOD_(ULONG,Release)(THIS) PURE;
    
    // IUMailAttach methods
};

typedef IUMailAttach * LPUMAILATTACH;


//---------------------------------------------------------------------------
//  IUMailAdmin Interface
//---------------------------------------------------------------------------

#undef INTERFACE
#define INTERFACE IUMailAdmin

DECLARE_INTERFACE_(IUMailAdmin, IUnknown)
{
    // IUnknown methods
    STDMETHOD(QueryInterface)(THIS_ REFIID riid, LPVOID * ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef)(THIS)  PURE;
    STDMETHOD_(ULONG,Release)(THIS) PURE;
    
    // IUMailAdmin methods
    STDMETHOD(CreateUser)(THIS_ BSTR bsName, BSTR bsPassword) PURE;
    STDMETHOD_(void, DeleteUser)(THIS_ BSTR bsName, BSTR bsPassword) PURE;
    STDMETHOD(RenameUser)(THIS_ BSTR bsOldName, BSTR bsOldPassword, BSTR bsNewName) PURE;
    STDMETHOD(ChangeUserPassword)(THIS_ BSTR bsName, BSTR bsOldPassword, BSTR bsNewPassword) PURE;
    STDMETHOD_(void, SetUMailTimeZone)(THIS_ long zoneID) PURE;
};

typedef IUMailAdmin * LPUMAILADMIN;
