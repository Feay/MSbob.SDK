////////////////////////////////////////////////////////////////////////////
// CALSRV.H
//
// Calendar service public declarations
//
// History:
// 04-21-93 FordM   Created.
/////////////////////////////////////////////////////////////////////////////
//
//  This is a public utopia header file.
//
//-------------------------------------------------------------

#ifndef __CALSRV_H__
#define __CALSRV_H__

#include <syssrv.h>
#include <uttime.h>
#include <toc.h>


typedef unsigned long CALID;
typedef unsigned long USERID;

// Declare these here so they can be defined in any order.

struct ICal;
struct IEvent;
struct ISchedule;
struct IAlarm;
struct IEventSink;
struct IAlarmSink;

typedef ICal * PICAL;
typedef IEvent * PIEVENT;
typedef ISchedule * PISCHEDULE;
typedef IAlarm * PIALARM;
typedef IEventSink * PIEVENTSINK;
typedef IAlarmSink * PIALARMSINK;
typedef IEnumVARIANT * PIENUM;


/////////////////////////////////////////////////////////////////////////////
// Cal Interface

#undef  INTERFACE
#define INTERFACE   ICal

DECLARE_INTERFACE_(ICal, IUnknown)
{
    // IUnknown methods

    STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef) (THIS)  PURE;
    STDMETHOD_(ULONG,Release) (THIS) PURE;

    // ICal methods

    STDMETHOD(Create)(THIS_ CALID *pcalId, LPCSTR pszName, 
            USERID uid, int iItem) PURE;
    STDMETHOD(Remove)(THIS_ CALID calId) PURE;        
    STDMETHOD(Find)(THIS_ CALID *pcalId, LPCSTR pszName, int iItem) PURE;
    STDMETHOD(GetDefault)(THIS_ CALID *pcalId, USERID uid, int iItem) PURE;
    STDMETHOD(GetUserId)(THIS_ CALID calId, USERID *puid) PURE;

    STDMETHOD(CreateEvent)(THIS_ PIEVENT *ppcev) PURE;
    STDMETHOD(AddEvent)(THIS_ PIEVENT pcev) PURE;
    STDMETHOD(RemoveEvent)(THIS_ PIEVENT pcev) PURE;
    STDMETHOD(FindEvent)(THIS_ ULONG idEvent, PIEVENT *ppcev) PURE;

    STDMETHOD(EnumAllEvents)(THIS_ PIENUM *ppenm) PURE;
    STDMETHOD(QueryEvents)(THIS_ PIENUM *ppenm, CALID calId, ULONG ffQuery,
            DATE dateFirst, DATE dateLast, LPCSTR pszText, ULONG ffOnFlags,
            ULONG ffOffFlags, ULONG idApp, USERID uid) PURE;

    STDMETHOD(Advise)(THIS_ PIEVENTSINK padvs, ULONG *pnConnection) PURE;
    STDMETHOD(Unadvise)(THIS_ ULONG nConnection) PURE;
};


// Valid ffQuery values:

#define fQTime      0x00010000L
#define fQText      0x00020000L
#define fQAppFlags  0x00040000L
#define fQUserId    0x00080000L
#define fQAppId     0x00100000L
// Schedule Query only:
#define fQEventId   0x00200000L 

// Valid iItem values:

#define iItemCalendar   0
#define iItemTasklist   1


/////////////////////////////////////////////////////////////////////////////
// Event Interface

#undef  INTERFACE
#define INTERFACE   IEvent

DECLARE_INTERFACE_(IEvent, IUnknown)
{
    // IUnknown methods

    STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef) (THIS)  PURE;
    STDMETHOD_(ULONG,Release) (THIS) PURE;

    // IEvent methods

    STDMETHOD(Clone) (THIS_ PIEVENT *ppcev) PURE;

    STDMETHOD(SetCalId) (THIS_ CALID calId) PURE;
    STDMETHOD(SetStartTime) (THIS_ DATE date) PURE;
    STDMETHOD(SetDuration) (THIS_ ULONG nSeconds) PURE;
    STDMETHOD(SetText) (THIS_ LPCSTR pszText) PURE;
    STDMETHOD(SetReminder) (THIS_ ULONG nSeconds, BOOL fSet, ULONG idApp) PURE;
    STDMETHOD(SetDupInterval) (THIS_ int ndupUnit, int ndupFactor) PURE;
    STDMETHOD(SetRepeat) (THIS_ BOOL fSet, const DATE *pdateEnd) PURE;
    STDMETHOD(SetAppFlags) (THIS_ ULONG ff, BOOL fSet) PURE;
    STDMETHOD(SetAppData) (THIS_ const void *pvData, ULONG cbData) PURE;

    STDMETHOD(GetCalId) (THIS_ CALID *pidCal) PURE;
    STDMETHOD(GetStartTime) (THIS_ DATE *pdate) PURE;
    STDMETHOD(GetStartTimeFromMaster) (THIS_ DATE *pdate) PURE;
    STDMETHOD(GetDuration) (THIS_ ULONG *pnSeconds) PURE;
    STDMETHOD(GetText) (THIS_ LPSTR pszBuffer, ULONG cbMax, ULONG *pcbActual) PURE;
    STDMETHOD(GetReminder) (THIS_ BOOL *pfSet, ULONG *pnSeconds, ULONG *pidApp) PURE;
    STDMETHOD(GetDupInterval) (THIS_ int *pdupUnit, int *pdupFactor) PURE;
    STDMETHOD(GetFirstInterval) (THIS_ DATE dateBase, DATE *pdateFirst) PURE;
    STDMETHOD(GetNextInterval) (THIS_ DATE dateBase, DATE *pdateNext) PURE;
    STDMETHOD(GetRepeat) (THIS_ BOOL *pfSet, DATE *pdateStart, BOOL *pfEnd, DATE *pdateEnd) PURE;
    STDMETHOD(GetAppFlags) (THIS_ ULONG *pff) PURE;
    STDMETHOD(GetAppData) (THIS_ void *pvData, ULONG cbMax, ULONG *pcbActual) PURE;

    STDMETHOD(GetEventId) (THIS_ ULONG *pidEvent) PURE;
    STDMETHOD(GetAppId) (THIS_ ULONG *pidApp) PURE;
    STDMETHOD(GetUserId) (THIS_ ULONG *puid) PURE;

    STDMETHOD(ReminderDone)(THIS) PURE;
};

// SetDupInterval units:

typedef enum
{
    ndupNever = 0,
    ndupDaily,
    ndupWeekday,
    ndupWeekly,
    ndupSemiMonthly,
    ndupMonthly,
    ndupYearly
} DupUnit;

// SetAppFlags limits:

#define ffEvAppMin 0x00000000L
#define ffEvAppMax 0x0000ffffL

// IEvent app flags in use by applications

#define fCevTaskDone    0x00000001L     // Tasklist task marked done
#define fCevMoreInfo    0x00000002L     // More info (tasklist or event)
#define fCevRepRelative 0x00000004L     // Reschedule task relative to done date
#define fCevNoDueDate   0x00000008L     // Use "None" as due date in tasklist
#define fCevMailRun     0x00000010L     // The event is a scheduled mailrun


/////////////////////////////////////////////////////////////////////////////
// Schedule Interface

#undef  INTERFACE
#define INTERFACE   ISchedule

DECLARE_INTERFACE_(ISchedule, IUnknown)
{
    // IUnknown methods

    STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef) (THIS)  PURE;
    STDMETHOD_(ULONG,Release) (THIS) PURE;

    // ISchedule methods

    STDMETHOD(CreateAlarm) (THIS_ PIALARM *ppalr) PURE;
    STDMETHOD(AddAlarm) (THIS_ PIALARM palr) PURE;
    STDMETHOD(RemoveAlarm) (THIS_ PIALARM palr) PURE;
    STDMETHOD(FindAlarm) (THIS_ ULONG idAlarm, PIALARM *ppalr) PURE;

    STDMETHOD(EnumAllAlarms) (THIS_ PIENUM *ppenm) PURE;
    STDMETHOD(QueryAlarms) (THIS_ PIENUM *ppenm, ULONG ffQuery,
            DATE dateFirst, DATE dateLast, ULONG idApp, 
            ULONG idEvent, ULONG idUser) PURE;

    STDMETHOD(Advise) (THIS_ PIALARMSINK padvs, ULONG *pnConnection) PURE;
    STDMETHOD(Unadvise) (THIS_ ULONG nConnection) PURE;
};



/////////////////////////////////////////////////////////////////////////////
// Alarm Interface

#undef  INTERFACE
#define INTERFACE   IAlarm

DECLARE_INTERFACE_(IAlarm, IUnknown)
{
    // IUnknown methods

    STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef) (THIS)  PURE;
    STDMETHOD_(ULONG,Release) (THIS) PURE;

    // IAlarm methods

    STDMETHOD(Set) (THIS_ DATE date, ULONG idApp, 
            ULONG idEvent, ULONG idUser) PURE;
    STDMETHOD(Get) (THIS_ DATE *pdate, ULONG *pidApp, 
            ULONG *pidEvent, ULONG *pidUser) PURE;

    STDMETHOD(GetId) (THIS_ ULONG *pidAlarm) PURE;
};



/////////////////////////////////////////////////////////////////////////////
// EventSink Interface

#undef  INTERFACE
#define INTERFACE   IEventSink

DECLARE_INTERFACE_(IEventSink, IUnknown)
{
    // IUnknown methods

    STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef) (THIS)  PURE;
    STDMETHOD_(ULONG,Release) (THIS) PURE;

    // IEventSink methods

    STDMETHOD(OnEventAdd) (THIS_ ULONG idEvent) PURE;
    STDMETHOD(OnEventRemove) (THIS_ ULONG idEvent) PURE;
    STDMETHOD(OnEventChange) (THIS_ ULONG idEvent) PURE;
};



/////////////////////////////////////////////////////////////////////////////
// AlarmSink Interface

#undef  INTERFACE
#define INTERFACE   IAlarmSink

DECLARE_INTERFACE_(IAlarmSink, IUnknown)
{
    // IUnknown methods

    STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef) (THIS)  PURE;
    STDMETHOD_(ULONG,Release) (THIS) PURE;

    // IAlarmSink methods

    STDMETHOD(OnAlarmTrigger) (THIS_ ULONG idAlarm) PURE;
    STDMETHOD(OnAlarmAdd) (THIS_ ULONG idAlarm) PURE;
    STDMETHOD(OnAlarmRemove) (THIS_ ULONG idAlarm) PURE;
    STDMETHOD(OnAlarmChange) (THIS_ ULONG idAlarm) PURE;
};



/////////////////////////////////////////////////////////////////////////////
//  Direct APIs for object retrieval

STDAPI GetCal(ICal **ppcal);
STDAPI GetSchedule(ISchedule **ppsched);

/////////////////////////////////////////////////////////////////////////////
//
//---------------------------------------------------------------------------
// Tasklist API's
//---------------------------------------------------------------------------

STDAPI_(BOOL) PrintTaskList(HDC hdc, CRect *prcDay,DBID idCal,
        int ffWhichToPrint);
        
STDAPI_(BOOL) ContinuePrintingTaskList(HDC hdc, CRect *prcDay);

#endif  // ifdef __CALSRV_H__
