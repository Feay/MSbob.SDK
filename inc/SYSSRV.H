//--------------------------------------------------------------------------
// SYSSRV.H
//
//
//
// History:
// 09-04-92 DarrinM     Created.
// 09-21-92 FordM       Added PCSTR def.
// 11-19-92 DarrinM     Redefined UImage.
// 12-09-92 FordM       Added class USystemParam.
// 03-13-93 DarrinM     Created from UTOPIA.H.
// 08-24-94 AlanMa      GetUtopiaAppInfo() can now receive the closing HTASKs
//--------------------------------------------------------------------------

#ifndef __SYSSRV_H__
#define __SYSSRV_H__

#include <ole2.h>
#include <uprop.h>

// Declare these here so they can be defined in any order.

struct IUser;
struct IEnum;
struct IUtopiaApp;
struct ITask;
struct ISysSink;

//--------------------------------------------------------------------------
// System Interface
//
// Note on EnumUsers: it will enumerate all users.  check to see that
// propRemoveDate == 0 to ensure a valid (non-removed) user.  SED

STDAPI GetUtopiaDirectory(char *pszDir, long cbDirMax);
STDAPI_(char far *) GetImagePath(char *pszImage);
STDAPI_(LONG) GetDiskFreeSpace(int nDriveNum);
STDAPI_(LONG) GetDiskFreeSpaceInfo(int nDriveNum, long *plBytesPerCluster);

// UNDONE: (dwm) These will probably be replaced by DLL entrypoints.
#undef  INTERFACE
#define INTERFACE   ISystem

DECLARE_INTERFACE_(ISystem, IUnknown)
{
    // *** IUnknown methods ***
    STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef) (THIS)  PURE;
    STDMETHOD_(ULONG,Release) (THIS) PURE;

    STDMETHOD(GetCurrentUser)(IUser **ppusr) PURE;
    STDMETHOD(SetCurrentUser)(IUser *pusr, char *pszPassword) PURE;
    STDMETHOD(EnumUsers)(IEnum **ppenmUser) PURE;
    STDMETHOD(FindUser)(ULONG id, IUser **ppusr) PURE;
    STDMETHOD(CreateUser)(IUser **ppuser) PURE;
    STDMETHOD(AddUser)(IUser *pusr) PURE;
    STDMETHOD(RemoveUser)(IUser *pusr) PURE;

    STDMETHOD(CreateApp)(IUtopiaApp **ppuapp) PURE;
    STDMETHOD(AddApp)(IUtopiaApp *puapp) PURE;
    STDMETHOD(RemoveApp)(IUtopiaApp *puapp) PURE;
    STDMETHOD(EnumApps)(IEnum **ppenmApp) PURE;
    STDMETHOD(FindApp)(const char *pszAppName, ULONG id, IUtopiaApp **ppuapp)
            PURE;

    STDMETHOD(CreateTask)(IUtopiaApp *puapp, ITask **pptask) PURE;
    STDMETHOD(AddTask)(ITask *ptask) PURE;
    STDMETHOD(RemoveTask)(ITask *ptask) PURE;
    STDMETHOD(EnumTasks)(IEnum **ppenmTask) PURE;
    STDMETHOD(FindTask)(HTASK htask, ITask **pptask) PURE;
    STDMETHOD(Exec)(const char *pszAppName, ULONG cmd, void *pvData,
            long cbDataMax, ULONG idFile, ULONG ffFlags) PURE;

    STDMETHOD(Advise)(const char *pszPropName, ISysSink *padvs,
            DWORD *pdwConnection, ULONG ffOrder) PURE;
    STDMETHOD(Unadvise)(DWORD dwConnection) PURE;
};

// FM 05/24/94. cmd values for task launch (many unused)

const ULONG cmdDefault =    0;      // Do standard default action
const ULONG cmdOpenFile =   1;      // Open file whose id is task's propFileId
const ULONG cmdOpen =       2;      // Open / no file specified
const ULONG cmdCreate =     3;      // Create new file
const ULONG cmdAlarm =      4;      // Alarm triggered. Alarm id is task's propEventId
const ULONG cmdCalInfo =    5;      // More info (cal). Event id is task's propEventId

//--------------------------------------------------------------------------
// UtopiaApp Interface
#undef  INTERFACE
#define INTERFACE   IUtopiaApp

DECLARE_INTERFACE_(IUtopiaApp, IUnknown)
{
    STDMETHOD(GetProperty)(const char *pszPropName, void *pvBuffer,
            long cbBufferMax) PURE;
    STDMETHOD(SetProperty)(const char *pszPropName, const void *pvData,
            long cbDataMax) PURE;
};

const ULONG fAppSobable =           0x0001;
const ULONG fAppSobUI =             0x0002;
const ULONG fAppLaunchAtShellLoad = 0x0004;
const ULONG fAppLaunchAtUserLogon = 0x0008;
const ULONG fAppCustomerSupport =   0x0010;
const ULONG fAppWinDOS =            0x0020;
const ULONG fAppMailWrite =         0x0040;
const ULONG fAppMailRead =          0x0080;
const ULONG fAppExecable =          0x0100;
const ULONG fAppProgman =           0x0200;
const ULONG fAppSobUseMRU =         0x0400;


//--------------------------------------------------------------------------
// Task Interface
#undef  INTERFACE
#define INTERFACE   ITask

// want 15 K of gdi to launch an app, which is 15/64 = 23.44 % of gdi memory
#define MIN_GDI_FOR_LAUNCH 24 
#define GDI_LOW_FOR_RUN    24    
#define MIN_DISKSPACE_FOR_LAUNCH 256   //K-bytes
#define LOW_DISKSPACE_FOR_LAUNCH 1024  //K-bytes

DECLARE_INTERFACE_(ITask, IUnknown)
{
    STDMETHOD(GetProperty)(const char *pszPropName, void *pvBuffer,
            long cbBufferMax) PURE;
    STDMETHOD(SetProperty)(const char *pszPropName, const void *pvData,
            long cbDataMax) PURE;
};

STDAPI_(void) SetAppWindowStyle(HWND hwnd);
STDAPI_(int) GetNumAppsRunning();
STDAPI SendChangePCNotice();    //notify all apps PC has changed

// internal uses of m_ff
#define fTskUninitialized   0x0001

// external uses of m_ff: defines for "FLAGS" property - also in \shared\utopia.bas
#define fTskShuttingDown	0x0002

//--------------------------------------------------------------------------
// User Interface

#undef  INTERFACE
#define INTERFACE   IUser
#define dwInvalidVolume (DWORD)MAKELONG(0xFFFE, 0x0001)
#define MIN_ADDED_USERID 5  // less than this is a user we shipped like guest

DECLARE_INTERFACE_(IUser, IUnknown)
{
    // *** IUnknown methods ***
    STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef) (THIS)  PURE;
    STDMETHOD_(ULONG,Release) (THIS) PURE;

    STDMETHOD(CheckPassword)(const char *pszPassword) PURE;
    STDMETHOD_(BOOL, Save)() PURE;

    STDMETHOD(GetProperty)(const char *pszPropName, void *pvBuffer,
            long cbBufferMax) PURE;
    STDMETHOD(SetProperty)(const char *pszPropName, const void *pvData,
            long cbDataMax) PURE;
    STDMETHOD(Advise)(const char *pszPropName, ISysSink *padvs,
            DWORD *pdwConnection, ULONG ffOrder) PURE;
    STDMETHOD(Unadvise)(DWORD dwConnection) PURE;
};

// For propGender:

typedef enum {
    GENDER_NEUTRAL = 0,
    GENDER_FEMALE = 1,
    GENDER_MALE = 2,
    GENDER_INVALID = 3,
} GENDER;

const ULONG uidPublic = 0;
const ULONG uidGuest = 2;
const ULONG uidCreator = 3;     // PRIVATE:
const ULONG uidDefault = 4;

//--------------------------------------------------------------------------
// Enum Interface

#undef  INTERFACE
#define INTERFACE   IEnum

DECLARE_INTERFACE_(IEnum, IUnknown)
{
    STDMETHOD(Next)(THIS_ ULONG celt, void *prgv, ULONG FAR* pceltFetched)
            PURE;
    STDMETHOD(Skip)(THIS_ ULONG celt) PURE;
    STDMETHOD(Reset)(THIS) PURE;
    STDMETHOD(Clone)(THIS_ IEnum FAR* FAR* ppenm) PURE;
};

//--------------------------------------------------------------------------
// SysSink Interface

#undef  INTERFACE
#define INTERFACE   ISysSink

DECLARE_INTERFACE_(ISysSink, IUnknown)
{
    STDMETHOD(OnPropertyChange)(const char *pszPropName, const void *pvData,
            long cbDataMax, ULONG ffOrder) PURE;
    STDMETHOD(OnObjectAdd)(const void *pvObject, ULONG ffOrder) PURE;
    STDMETHOD(OnObjectRemove)(const void *pvObject, ULONG ffOrder) PURE;
};

const ULONG fAdvBefore =    0x0001;
const ULONG fAdvAfter =     0x0002;
const ULONG fAdvAddRemove = 0x0004;
const ULONG fAdvInteger =   0x0008;

//--------------------------------------------------------------------------
// Primary System interfaces

STDAPI_(HRESULT) UtopiaInitialize(ITask **ppitask);
STDAPI_(BOOL) UtopiaUninitialize(void);
STDAPI_(void) UtopiaIdle();
STDAPI_(void) UtopiaActivate(BOOL fActivate);   // DO NOT USE: will be removed shortly.
STDAPI_(void) UtopiaDoEvents();
STDAPI_(BOOL) GetSystem(ISystem **ppISystem);
STDAPI GetCurrentUTask(ITask **pptask);
STDAPI GetActiveUTask(ITask **pptask);
STDAPI GetShellUTask(ITask **pptask);
STDAPI_(GUID *) GetSystemId(void);
STDAPI UInitCOM();
#define UUninitCOM()    CoUninitialize()
STDAPI_(BOOL) GetDesignTimeStatus();

// return code from utopia init if yours is the first utopia task

#define S_FIRSTTASK  MAKE_SCODE(SEVERITY_SUCCESS, FACILITY_ITF, USUCC_FIRSTTASK)

// Currently only accessable from within utopia.dll. 
// CONSIDER:  Changing to STDAPI_(void).
void IdleJet();
    

//--------------------------------------------------------------------------
// Sound interfaces

#ifdef WMIX_ALL  // Set by extern "C" { #include <wavemix.h> }
STDAPI UtopiaPlaySound(LPMIXWAVE lpWave, WORD cLoops, DWORD * pdwGroup);
STDAPI UtopiaStopSound(DWORD dwGroup);
#endif

STDAPI_(void) UMessageBeep(UINT mb);
STDAPI UtopiaSoundActivate(BOOL fActive);

//--------------------------------------------------------------------------
// Idle Procedure stuff

typedef int HIDLEPROC;
typedef void(* IDLEPROC)(void);
STDAPI_(HIDLEPROC) RegisterIdleProc(IDLEPROC);
STDAPI_(void) RemoveIdleProc(HIDLEPROC);
STDAPI_(void) LaunchApps(ULONG fAppLaunchFlag);
STDAPI_(void) IdleLogon(BOOL fLogon);

//--------------------------------------------------------------------------
// Termination Procedure stuff

// To declare a termination proc, use the following macro as follows:
//
// TERMPROCIMP MyTermProc(ULONG ff)

#define TERMPROCIMP  void _cdecl _loadds

typedef void *HTERMPROC;    //POSITION from CPtrList
typedef void (*TERMPROC)(ULONG ff);
const ULONG fTrmAbnormal =  0x0001;
const ULONG fTrmNormal =    0x0002;
const ULONG fTrmShell =     0x0004;

STDAPI_(HTERMPROC) AddTerminationProc(TERMPROC pfnTerm);
STDAPI_(BOOL) RemoveTerminationProc(HTERMPROC htp);

//--------------------------------------------------------------------------
// Cursor functions

STDAPI_(HCURSOR) LoadUtopiaCursor(LPCSTR id);

#define IDC_NO          MAKEINTRESOURCE(32517)
#define IDC_DRAG        MAKEINTRESOURCE(32518)
#define IDC_KNOCK       MAKEINTRESOURCE(32519)
#define IDC_SIZEN       MAKEINTRESOURCE(32520)
#define IDC_SIZES       MAKEINTRESOURCE(32521)
#define IDC_SIZEE       MAKEINTRESOURCE(32522)
#define IDC_SIZEW       MAKEINTRESOURCE(32523)
#define IDC_SIZENW      MAKEINTRESOURCE(32524)
#define IDC_SIZENE      MAKEINTRESOURCE(32525)
#define IDC_SIZESW      MAKEINTRESOURCE(32526)
#define IDC_SIZESE      MAKEINTRESOURCE(32527)
#define IDC_DRAGTEXT    MAKEINTRESOURCE(32528)
#define IDC_MOVETEXT    MAKEINTRESOURCE(32529)
#define IDC_COPYTEXT    MAKEINTRESOURCE(32530)
#define IDC_COPY        MAKEINTRESOURCE(32531)
#define IDC_DRAGSMALL   MAKEINTRESOURCE(32532)
#define IDC_COPYSMALL   MAKEINTRESOURCE(32533)
#define IDC_NODROPSMALL MAKEINTRESOURCE(32534)
#define IDC_NOCLICK     MAKEINTRESOURCE(32535)
#define IDC_LEFT        MAKEINTRESOURCE(32536)
#define IDC_RIGHT       MAKEINTRESOURCE(32537)

STDAPI_(BOOL) ShowWaitCursor(BOOL fShow);

class WaitCursor {
public:
    WaitCursor()  { ShowWaitCursor(TRUE); }
    ~WaitCursor() { ShowWaitCursor(FALSE); }
};


//--------------------------------------------------------------------------
// Random helpers

//
// The MMTimer class can be used to time operations to an accuracy of one
// millisecond.  It gives a little more flexibility than the TimeIt class
// (which follows).
//

// "#define TIMING 1" if you want to use the MMTimer class to time operations.
// Don't forget to link with MMSYSTEM.LIB

#if TIMING

#pragma message(__FILE__ " : warning : Timing macros enabled")

#ifndef _INC_MMSYSTEM
#include <mmsystem.h>
#endif

#define DeclareTimerOn(t) MMTimer t
#define DeclareTimerOff(t) MMTimer t(FALSE)
#define TimingOn_(mmtimer) mmtimer.On()
#define TimingOff_(mmtimer) mmtimer.Off()
#define TimingClearTotal_(mmtimer) mmtimer.ClearTotal()
#define TimingDumpTotal_(mmtimer,sz) mmtimer.DumpTotal(sz)
#define TimingStart_(mmtimer) mmtimer.Start()
#define TimingStop_(mmtimer,sz) mmtimer.Stop(sz)


#define DeclareTimer() MMTimer mmtimer
#define TimingClearTotal() TimingClearTotal_(mmtimer)
#define TimingDumpTotal(sz) TimingDumpTotal_(mmtimer, sz)
#define TimingStart() TimingStart_(mmtimer)
#define TimingStop(sz) TimingStop_(mmtimer, sz)

class MMTimer
  {
  public:
    MMTimer(void)
      {
      m_cEnabled = 1;
      m_ulTimeStart = 0;
      m_ulTimeTotal = 0;
      }
    
    MMTimer(BOOL fEnabled)
      {
      m_cEnabled = fEnabled ? 1 : 0;
      m_ulTimeStart = 0;
      m_ulTimeTotal = 0;
      }

    void On(void)
      {
      m_cEnabled++;
      }
    
    void Off()
      {
      m_cEnabled--;
      }
    
    void ClearTotal(void)
      {
      m_ulTimeTotal = 0;
      }
    
    void Start(void)
      {
      m_ulTimeStart = timeGetTime();
      }
    
    void Stop(LPSTR szTitle)
      {
      LONG ulTime = timeGetTime() - m_ulTimeStart;

      m_ulTimeTotal += ulTime;

      if (m_cEnabled > 0)
    {
    char szMsg[256];

    wsprintf(szMsg, "%s: %lu ms\n", szTitle, ulTime);
    OutputDebugString(szMsg);
    }
      }
    
    void DumpTotal(LPSTR szTitle)
      {
      if (m_cEnabled > 0)
    {
    char szMsg[256];

    wsprintf(szMsg, "%s: %lu ms\n", szTitle, m_ulTimeTotal);
    OutputDebugString(szMsg);
    }
      }

  protected:
    ULONG m_ulTimeStart;
    ULONG m_ulTimeTotal;
    USHORT m_cEnabled;
  };

#else

#define DeclareTimerOn(t)
#define DeclareTimerOff(t)
#define TimingOn_(mmtimer)
#define TimingOff_(mmtimer)
#define TimingClearTotal_(mmtimer)
#define TimingDumpTotal_(mmtimer,sz)
#define TimingStart_(mmtimer)
#define TimingStop_(mmtimer,sz)


#define DeclareTimer()
#define TimingClearTotal()
#define TimingDumpTotal(sz)
#define TimingStart()
#define TimingStop(sz)
#endif

// NOTE: #include MMSYSTEM.H if you want to use this handy function timing
// class.  Don't forget to add MMSYSTEM.LIB to your Link options (Options...
// Linker...Windows Libraries).

#ifdef _INC_MMSYSTEM
//
// This class can be used to time the execution of a block of code (defined
// by C++ scoping rules).  Just instantiate a TimeIt object at the beginning
// of the block and when the object goes out of scope (and TimeIt's destructor
// is called) the elapsed time will be sent to debug output.
//

class TimeIt {
public:
    TimeIt(LPSTR psz)  {
        m_pszNote = psz;
        m_tmStart = timeGetTime();
    }

    ~TimeIt() {
        wsprintf(m_szT, "%s %ldms\n", m_pszNote, timeGetTime() - m_tmStart);
        OutputDebugString(m_szT);
    }

private:
    DWORD m_tmStart;
    LPSTR m_pszNote;
    char m_szT[80];
};

#endif


#ifdef HM_BEGIN_EVENT

class ProcLog {
public:
    ProcLog(LPSTR psz, WORD info)  {
        m_InfoD = *(LPDWORD)psz;
        m_InfoW = *(LPWORD)(psz+sizeof(DWORD));
        LogMsg((HWND)info, HM_BEGIN_EVENT, m_InfoW, m_InfoD);
    }

    ~ProcLog() {
        LogMsg(NULL, HM_END_EVENT, m_InfoW, m_InfoD);
    }

private:
    DWORD m_InfoD;
    WORD m_InfoW;
};

#endif


//
// To avoid unRelease()'ed object bugs, use the macro OOSRELEASE (Out Of Scope
// Release) immediately after you obtain an AddRef'ed object.  When the current
// scope is exited the object will be Released.  Exit cases become much simpler
// as you don't have to remember which objects to Release for each one.
//

class IUnknownReleaser {
public:
    IUnknownReleaser(IUnknown *punk) {
        m_punk = punk;
    }

    ~IUnknownReleaser() {
        m_punk->Release();
    }

private:
    IUnknown *m_punk;
};

#define OOSRELEASE(punk) IUnknownReleaser urel##punk(punk)

//
// Similarly, to avoid undeleted pointers to objects, use the
// macro OOSDELETE.
//

// make sure we have MFC/CPP around since this uses
// CObject

#ifdef _AFX

class CObjectDeleter {
public:
    CObjectDeleter(CObject *pob) {
        m_pob = pob;
    }

    ~CObjectDeleter() {
        delete m_pob;
    }

private:
    CObject *m_pob;
};

#define OOSDELETE(pob) CObjectDeleter udel##pob(pob)

#endif  // ifdef _AFX

//
//  class task object uses to callback vb apps
//  when they are activated/deactivated.  the property
//  in the task object is saved via the USink Control
//

// we get this definition from vbapi.h
typedef LPVOID      HCTL;       // hctl

class UVBNotif {
// Implementation
public:
    UVBNotif(HCTL hctl);

    STDMETHOD(VBNotifCallback)(THIS_ ULONG VBEvent);

public:
    HCTL m_hctl;
    LPVOID m_lpfnApiVector;
};

#endif  // ifdef __SYSSRV_H__

