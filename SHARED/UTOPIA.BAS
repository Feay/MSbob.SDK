'-----------------------------------------------------------------------
' utopia.bas
'-----------------------------------------------------------------------
' Copyright (c) 1993-1994 Microsoft Corporation
'                   All Rights Reserved
' Information Contained Herein Is Proprietary and Confidential
'-----------------------------------------------------------------------
' Common routines for Utopia applications written in VB.
'
' Owner: daviddow
'
' History:
'   9/21/93      created.
'   2/01/94      johans   Added GetUtopiaDir routine
'-----------------------------------------------------------------------
Option Explicit

' Visual Basic Errors

'   3 Return without GoSub
'   5 Illegal function call
'   6 Overflow
'   7 Out of memory
'   9 Subscript out of range
'  10 Duplicate definition
'  11 Division by zero
'  13 Type mismatch
'  14 Out of string space
'  16 String formula too complex
'  17 Can't continue
'  19 No Resume
'  20 Resume without error
'  28 Out of stack space
'  35 Sub or Function not defined
'  48 Error in loading DLL
'  49 Bad DLL calling convention
'  51 Internal error
'  52 Bad file name or number

Global Const VBERR_FileNotFound = 53 'File not found
Global Const VBERR_BadFileMode = 54  'Bad file mode
Global Const VBERR_FileAlreadyOpen = 55  'File already open
Global Const VBERR_DeviceIOError = 57 ' Device I/O error
Global Const VBERR_FileAlreadyExists = 58 ' File already exists
Global Const VBERR_BadRecordLen = 59  'Bad record length
Global Const VBERR_DiskFull = 61  'Disk full
Global Const VBERR_EOF = 62  'Input past end of file
Global Const VBERR_BadRecordNum = 63  'Bad record number
Global Const VBERR_BadFileName = 64 ' Bad file name
Global Const VBERR_TooManyFiles = 67  'Too many files
Global Const VBERR_DeviceUnavailable = 68  'Device unavailable
Global Const VBERR_PermissionDenied = 70  'Permission denied
Global Const VBERR_DiskNotReady = 71  'Disk not ready
Global Const VBERR_RenameAcrossDrive = 74  'Can't rename with different drive
Global Const VBERR_PathFileNoAccess = 75  'Path/File access error
Global Const VBERR_PathNotFound = 76  'Path not found
Global Const VBERR_ObjectNotSet = 91  'Object variable not Set

Global Const IDC_WAIT = 32514&

Type RECT
    Left As Integer
    Top As Integer
    right As Integer
    bottom As Integer
End Type

'-----------------------------------------------------------------------
' Regional Window and form caching
'-----------------------------------------------------------------------
Declare Sub RgnwndUnload Lib "utopia.dll" (ByVal h As Integer)

' Used for regional window

Global Const DIP_NONE = 0
Global Const DIP_POINTER = 1
Global Const DIP_BUBBLES = 2
Global Const DIP_ARROW = 3

Global Const DIP_SIDE_LEFT = 0
Global Const DIP_SIDE_RIGHT = 1
Global Const DIP_SIDE_TOP = 2
Global Const DIP_SIDE_BOTTOM = 3

' Standard balloon styles
Global Const BS_CUSTOM = 0
Global Const BS_SPEAK_BOTTOM = 1
Global Const BS_SPEAK_RIGHT = 2
Global Const BS_THINK_BOTTOM = 3
Global Const BS_THINK_RIGHT = 4
Global Const BS_ARROW_LEFT = 5
Global Const BS_ARROW_RIGHT = 6
Global Const BS_ARROW_UP = 7
Global Const BS_ARROW_DOWN = 8

'Screen resolutions
Global Const SCR_VGA = 0
Global Const SCR_SVGA = 1
Global Const SCR_OTHER = 2

Global gScrX As Integer
Global gScrY As Integer
Global gScrType As Integer

Global gcDlgCache As Integer     ' actual set dialog cache size
Const CACHE_SIZE = 10            ' maximum dialog cache size
Dim rgForm(CACHE_SIZE) As Form   ' the dialog cache
Dim frmMax As Integer            ' current number of dialogs cached

Dim hCursor As Integer


'-----------------------------------------------------------------------
' Calendar API
'-----------------------------------------------------------------------
Global Const CEV_PROPIDNONE = 0
Global Const CEV_PROPIDCALLD = 1
Global Const CEV_PROPIDSTARTTIME = 2
Global Const CEV_PROPIDDURATION = 3
Global Const CEV_PROPIDTEXTLENGTH = 4
Global Const CEV_PROPIDTEXT = 5
Global Const CEV_PROPIDREMINDSET = 6
Global Const CEV_PROPIDREMINDSECONDS = 7
Global Const CEV_PROPIDREMINDAPPID = 8
Global Const CEV_PROPIDDUPUNIT = 9
Global Const CEV_PROPIDDUPFACTOR = 10
Global Const CEV_PROPIDREPEATSET = 11
Global Const CEV_PROPIDREPEATSTARTDATE = 12
Global Const CEV_PROPIDREPEATENDSET = 13
Global Const CEV_PROPIDREPEATENDDATE = 14
Global Const CEV_PROPIDAPPFLAGS = 15
Global Const CEV_PROPIDAPPDATALENGTH = 16
Global Const CEV_PROPIDAPPDATA = 17
Global Const CEV_PROPIDEVENTID = 18
Global Const CEV_PROPIDAPPID = 19
Global Const CEV_PROPIDUSERID = 20

Global Const CEV_NDUPNEVER = 0
Global Const CEV_NDUPDAILY = 1
Global Const CEV_NDUPWEEKDAY = 2
Global Const CEV_NDUPWEEKLY = 3
Global Const CEV_NDUPSEMIMONTHLY = 4
Global Const CEV_NDUPMONTHLY = 5
Global Const CEV_NDUPYEARLY = 6

Global Const CALR_PROPIDNONE = 0
Global Const CALR_PROPIDTIME = 1
Global Const CALR_PROPIDALARMID = 2
Global Const CALR_PROPIDEVENTID = 3
Global Const CALR_PROPIDAPPID = 4
Global Const CALR_PROPIDUSERID = 5

Global Const CAL_FQTIME = &H10000
Global Const CAL_FQTEXT = &H20000
Global Const CAL_FQAPPFLAGS = &H40000
Global Const CAL_FQUSERID = &H80000
Global Const CAL_FQAPPID = &H100000

Global Const CEV_TASKDONE = &H1
Global Const CEV_MOREINFO = &H2
Global Const CEV_REPRELATIVE = &H3
Global Const CEV_NODUEDATE = &H4
Global Const CAL_FQEVENTID = &H200000

'-----------------------------------------------------------------------
' Utopia Errors
' UNDONE:  From inc\uerror.h.  Need better update mechanism.
'-----------------------------------------------------------------------

Global Const ERR_NONE = 0
Global Const UERR_ERROR = 20000

Global Const UERR_OLEOBJECTNOTSET = 91
Global Const UERR_OLEAUTOMATION = 440

Global Const UERR_GEN_BADSYSTEMSETUP = UERR_ERROR + 9

' umail service errors
Global Const UERR_UMAIL_MAPIINIT = UERR_ERROR + &H40
Global Const UERR_UMAIL_LOGON = UERR_ERROR + &H41
Global Const UERR_UMAIL_ADMIN = UERR_ERROR + &H42
Global Const UERR_UMAIL_MAILRUN = UERR_ERROR + &H43
Global Const UERR_UMAIL_FOLDER_MCD = UERR_ERROR + &H44
Global Const UERR_UMAIL_MESSAGE_SAVE = UERR_ERROR + &H45
Global Const UERR_UMAIL_NOT_ALLOWED = UERR_ERROR + &H46
Global Const UERR_UMAIL_GUEST_LOGON = UERR_ERROR + &H47
Global Const UERR_UMAIL_NO_ACCOUNT_INFO = UERR_ERROR + &H48
Global Const UERR_UMAIL_DUP_FOLDER_NAME = UERR_ERROR + &H49
Global Const UERR_UMAIL_NO_TRANSPORT = UERR_ERROR + &H4A
Global Const UERR_UMAIL_INVALID_MESSHANDLE = UERR_ERROR + &H4B
Global Const UERR_UMAIL_CORRUPT_STORE = UERR_ERROR + &H4C

' umail service warnings
Global Const UWRN_UMAIL_USER_CANCEL = UERR_ERROR + &H7F
Global Const UWRN_UMAIL_DELIVERED = UERR_ERROR + &H7E
Global Const UWRN_UMAIL_NOT_DELIVERED = UERR_ERROR + &H7D


' tippage errors

Global Const UERR_TIP_FIRST = UERR_ERROR + &H180
Global Const UERR_TIP_E_INVALID = UERR_TIP_FIRST

' toc errors

Global Const UERR_TOC_FIRST = UERR_ERROR + &HC0
Global Const UERR_TOC_TOO_MANY_FILES = UERR_TOC_FIRST + 1
Global Const UERR_TOC_INVALID_TYPE = UERR_TOC_FIRST + 2
Global Const UERR_TOC_INVALID_ITEM = UERR_TOC_FIRST + 3
Global Const UERR_TOC_INVALID_TYPE_DLL = UERR_TOC_FIRST + 4
Global Const UERR_TOC_INVALID_BUNDLE = UERR_TOC_FIRST + 5
Global Const UERR_TOC_INVALID_APP = UERR_TOC_FIRST + 6
Global Const UERR_TOC_INVALID_USER = UERR_TOC_FIRST + 7
Global Const UERR_TOC_DUPLICATE_NAME = UERR_TOC_FIRST + 8

'system errors


Global Const UERR_SYSSRV_FIRST = &H1C0 + UERR_ERROR
Global Const UERR_SYSSRV_LAST = &H1FF + UERR_ERROR

'errors that could be returned from a task launching

Global Const UERR_TASK_WINVERWRONG = (UERR_SYSSRV_FIRST + 5)
Global Const UERR_TASK_INVALIDEXE = (UERR_SYSSRV_FIRST + 6)
Global Const UERR_TASK_NONWINEXE = (UERR_SYSSRV_FIRST + 7)
Global Const UERR_TASK_SECONDINST = (UERR_SYSSRV_FIRST + 8)
Global Const UERR_TASK_EXECOMPRESD = (UERR_SYSSRV_FIRST + 9)
Global Const UERR_TASK_DLLCORRUPT = (UERR_SYSSRV_FIRST + 10)
Global Const UERR_TASK_EXE32BIT = (UERR_SYSSRV_FIRST + 11)
Global Const UERR_TASK_PATHNOTFOUND = (UERR_SYSSRV_FIRST + 12)
Global Const UERR_TASK_FILENOTFOUND = (UERR_SYSSRV_FIRST + 13)
Global Const UERR_TASK_UNKNOWN = (UERR_SYSSRV_FIRST + 14)

' not a syssrv error, but a system wide error
Global Const UERR_SYS_LOWGDI = (UERR_SYSSRV_FIRST + 15)

Global Const UERR_JET_DBNOTFOUND = (UERR_SYSSRV_FIRST + 18)
Global Const UERR_JET_ACCESSDENIED = (UERR_SYSSRV_FIRST + 19)
Global Const UERR_JET_REPAIRFAILED = (UERR_SYSSRV_FIRST + 20)
Global Const USUCC_FIRSTTASK = (UERR_SYSSRV_FIRST + 21)

' abook errors
Global Const UERR_ABOOK_EMPTYBOOK = UERR_ERROR + &H200
Global Const UERR_ABOOK_CANCELUNBUNDLE = UERR_ERROR + &H201

'-----------------------------------------------------------------------
' Tippage API
'-----------------------------------------------------------------------

Global Const TIPID_ALL = 0
Global Const TIPID_NONE = -1   ' Used to disable keyboard/HOR in About box, confirm in HOR.

Global gTipObject As Object

' success result from inc\uerror.h:
Global Const TIP_S_CANCEL = &H40000 + UERR_TIP_FIRST + 1
Global Const TIP_S_APPDISPLAY = &H40000 + UERR_TIP_FIRST + 3

Const APPID_CUR = 0&
' To save tracking data when running standalone, set gAppID to your hard-coded
' appID value, as determined by your entry in UTOPIA.MDB.
Global gAppID As Long

Declare Function LongFromPtr Lib "UTOPIA.dll" (ptr As Any) As Long

' From tipedit.bas:
' UNDONE:  I believe UShowErrorTip is the only one needed here.
Global Const typeModal = 1
Global Const styleAlert = 2
Global Const styleError = 4
Declare Function ShowTipEx Lib "UTOPIA.DLL" (ByVal szHeader$, ByVal szBody$, ByVal szOK$, ByVal szCancel$, ByVal ts%, ByVal tm%, ByVal hwndParent%, lprc As RECT, ByVal bs%) As Long
Declare Sub UShowErrorTip Lib "UTOPIA.DLL" (ByVal hWnd As Integer, ByVal uErr As Integer, ByVal szError As Any)

'_DEBUG
' This is technically available in retail, but should only be used by VB apps as
' a debugging tool.
Declare Function UDeleteTrackingData Lib "UTOPIA.dll" () As Long
'_END

'-----------------------------------------------------------------------
' Actor actions
'-----------------------------------------------------------------------
Global Const ACT_IDLE = 1
Global Const ACT_GREET = 2
Global Const ACT_BYE = 3
Global Const ACT_SPEAK = 4
Global Const ACT_CLICKME = 5
Global Const ACT_MJSUCCESS = 6
Global Const ACT_MNSUCCESS = 7
Global Const ACT_MJFAIL = 8
Global Const ACT_MNFAIL = 9
Global Const ACT_CANCEL = 10
Global Const ACT_MJATTEN = 11
Global Const ACT_MNATTEN = 12
Global Const ACT_SEARCH = 13
Global Const ACT_FOUND = 14
Global Const ACT_CERR = 15
Global Const ACT_HERR = 16
Global Const ACT_HSUCCESS = 17
Global Const ACT_PRINT = 18
Global Const ACT_RGESTURE = 19
Global Const ACT_CONFIRM = 20
Global Const ACT_BIRTHDAY = 21
Global Const ACT_RECORD = 22
Global Const ACT_WORK = 23
Global Const ACT_THINK = 24
Global Const ACT_SENDMAIL = 25
Global Const ACT_LISTEN = 26
Global Const ACT_QBYE = 31
Global Const ACT_APPEAR = 32

' Special actions:
Global Const ACT_SHOW = 0
Global Const ACT_STOP = -1
Global Const ACT_RESUME = -3

' For use by WaitUntilActionFinished()
Global gfActionFinished As Integer

Declare Function FWaitingForAnimToFinish Lib "UTOPIA.DLL" () As Integer

'-----------------------------------------------------------------------
' Address Book
'-----------------------------------------------------------------------

Global Const AB_BOOKS = 0
Global Const AB_LISTS = 1
Global Const AB_COMPOSITE = 2
Global Const AB_PRIVATE = 4

'-----------------------------------------------------------------------
' Mail Aware Applications
'-----------------------------------------------------------------------
Global Const UMAIL_COMPOSE = 1
Global Const UMAIL_READ = 2
Global Const UMAIL_EDIT = 3

'-----------------------------------------------------------------------
' TOC constants
'-----------------------------------------------------------------------

Global Const tocId = 1
Global Const tocAppId = 2
Global Const tocUserId = 3
Global Const tocCreatorId = 4
Global Const tocType = 5
Global Const tocSize = 6
Global Const tocFlags = 7
Global Const tocLastId = 8
Global Const tocCreation = 8
Global Const tocLastModified = 9
Global Const tocTitle = 10

Global Const tocCmpEql = &H1
Global Const tocCmpGt = &H2
Global Const tocCmpLt = &H3
Global Const tocCmpGte = &H4
Global Const tocCmpLte = &H5

Global Const tocCmpAnd = &H1000
Global Const tocCmpOr = &H2000
Global Const tocCmpNot = &H4000

'-----------------------------------------------------------------------
' CMD launch constants (propCommand of ITask)
'-----------------------------------------------------------------------
Global Const cmdNothing = -1        ' NULL. Used to mark a task that has already been
        ' opened.
Global Const cmdDefault = 0         ' Do standard default action
Global Const cmdOpenFile = 1        ' Open file whose id is task's propFileId
Global Const cmdOpen = 2            ' Open / no file specified
Global Const cmdCreate = 3          ' Create new file
Global Const cmdAlarm = 4           ' Alarm triggered. Alarm id is task's propEventId
Global Const cmdCalInfo = 5         ' More info (cal). Event id is task's propEventId
Global Const cmdMailRead = 6
Global Const cmdMailCompose = 7
Global Const cmdMailEdit = 8
Global Const cmdMailResend = 9

'-----------------------------------------------------------------------
' Utopia App Id's
'-----------------------------------------------------------------------

Global Const idCalendar = 5
Global Const idNotebook = 6
Global Const idCheckbook = 7
Global Const idMailroom = 12
Global Const idAddress = 30
Global Const idLetterWriter = 31
Global Const idSafari = 182
Global Const idChooser = 183
Global Const idHome = 185
Global Const idBackup = 187
Global Const idFinancialGuide = 188
Global Const idSafariBS = 194

'-----------------------------------------------------------------------
' Windows API
'-----------------------------------------------------------------------
Type POINTAPI
    x As Integer
    y As Integer
End Type

Declare Function LoadCursor Lib "User" (ByVal hInstance As Integer, ByVal lpCursorName As Any) As Integer
Declare Function SetCursor Lib "User" (ByVal hCursor As Integer) As Integer
Declare Function GetActiveWindow Lib "User" () As Integer
Declare Function GetParent Lib "User" (ByVal hWnd As Integer) As Integer

Declare Function LoadLibrary Lib "kernel" (ByVal szLibrary As String) As Integer
Declare Sub FreeLibrary Lib "kernel" (ByVal hInstance As Integer)
Global Const HINSTANCE_ERROR = 32

Declare Sub GetWindowRect Lib "User" (ByVal hWnd As Integer, rc As RECT)
Declare Sub GetClientRect Lib "User" (ByVal hWnd As Integer, rc As RECT)
Declare Sub InflateRect Lib "User" (lpRect As RECT, ByVal x As Integer, ByVal y As Integer)
Declare Sub MapWindowPoints Lib "User" (ByVal hWndFrom As Integer, ByVal hWndTo As Integer, lppt As Any, ByVal cPoints As Integer)

Declare Function GetWindowText Lib "User" (ByVal hWnd As Integer, ByVal lpString As String, ByVal aint As Integer) As Integer
Declare Function GetWindowTextLength Lib "User" (ByVal hWnd As Integer) As Integer

Declare Function GetDeviceCaps Lib "GDI" (ByVal hDC As Integer, ByVal nIndex As Integer) As Integer
Global Const HORZRES = 8    '  Horizontal width in pixels
Global Const VERTRES = 10   '  Vertical width in pixels

Declare Sub ClipCursor Lib "User" (lpRect As Any)
Declare Sub GetCursorPos Lib "User" (lpPoint As POINTAPI)
Declare Sub ClientToScreen Lib "User" (ByVal hWnd As Integer, lpPoint As POINTAPI)

Declare Function IntersectRect Lib "User" (lpDestRect As RECT, lpSrc1Rect As RECT, lpSrc2Rect As RECT) As Integer
Declare Sub ScreenToClient Lib "User" (ByVal hWnd As Integer, lpPoint As POINTAPI)

Declare Function GetDoubleClickTime Lib "User" () As Integer

Declare Function GetPrivateProfileInt Lib "Kernel" (ByVal lpApplicationName As String, ByVal lpKeyName As String, ByVal nDefault As Integer, ByVal lpFileName As String) As Integer
Declare Function GetProfileString Lib "Kernel" (ByVal lpAppName As String, lpKeyName As Any, ByVal lpDefault As String, ByVal lpReturnedString As String, ByVal nSize As Integer) As Integer
Declare Function GetProfileInt Lib "Kernel" (ByVal lpApplicationName As String, ByVal lpKeyName As String, ByVal nDefault As Integer) As Integer
Declare Function GetPrivateProfileString Lib "Kernel" (ByVal lpApplicationName As String, ByVal lpKeyName As String, ByVal lpDefault As String, ByVal lpReturnedString As String, ByVal nSize As Integer, ByVal lpFileName As String) As Integer

Declare Sub WaitMessage Lib "User" ()

Global Const PM_NOREMOVE = &H0
Global Const PM_REMOVE = &H1
Global Const PM_NOYIELD = &H2

Type MSG
    hWnd As Integer
    message As Integer
    wParam As Integer
    lParam As Long
    time As Long
    pt As POINTAPI
End Type
Declare Function PeekMessage Lib "User" (lpmsg As MSG, ByVal hWnd As Integer, ByVal wMsgFilterMin As Integer, ByVal wMsgFilterMax As Integer, ByVal wRemoveMsg As Integer) As Integer
Declare Function DispatchMessage Lib "User" (lpmsg As MSG) As Long

Global Const hWnd_TOP = 0
Global Const hWnd_BOTTOM = 1
Global Const hWnd_TOPMOST = -1
Global Const hWnd_NOTOPMOST = -2
Global Const SWP_NOSIZE = &H1
Global Const SWP_NOMOVE = &H2
Global Const SWP_NOZORDER = &H4
Global Const SWP_NOACTIVATE = &H10
Global Const SWP_SHOWWINDOW = &H40
Global Const SWP_HIDEWINDOW = &H80

' common dialog flags

Global Const OFN_HIDEREADONLY = &H4
Global Const OFN_OVERWRITEPROMPT = &H2

Declare Function SetParent Lib "User" (ByVal hWndChild As Integer, ByVal hWndNewParent As Integer) As Integer
Declare Function FindWindow Lib "User" (ByVal Class As Long, ByVal Caption As String) As Integer
Declare Sub SetWindowPos Lib "User" (ByVal hWnd As Integer, ByVal hWndInsertAfter As Integer, ByVal x As Integer, ByVal y As Integer, ByVal cx As Integer, ByVal cy As Integer, ByVal wFlags As Integer)
Declare Function BringWindowToTop Lib "User" (ByVal hWnd As Integer) As Integer

'
' Virtual Keys
'

Global Const VK_F1 = &H70
Global Const VK_F2 = &H71
Global Const VK_F3 = &H72
Global Const VK_F4 = &H73
Global Const VK_F5 = &H74

Global Const VK_A = &H41
Global Const VK_B = &H42
Global Const VK_C = &H43
Global Const VK_D = &H44
Global Const VK_E = &H45
Global Const VK_F = &H46
Global Const VK_G = &H47
Global Const VK_H = &H48
Global Const VK_I = &H49
Global Const VK_J = &H4A
Global Const VK_K = &H4B
Global Const VK_L = &H4C
Global Const VK_M = &H4D
Global Const VK_N = &H4E
Global Const VK_O = &H4F
Global Const VK_P = &H50
Global Const VK_Q = &H51
Global Const VK_R = &H52
Global Const VK_S = &H53
Global Const VK_T = &H54
Global Const VK_U = &H55
Global Const VK_V = &H56
Global Const VK_W = &H57
Global Const VK_X = &H58
Global Const VK_Y = &H59
Global Const VK_Z = &H5A

Global Const VK_RETURN = &HD

'-----------------------------------------------------------------------
' VB Constants
'-----------------------------------------------------------------------
Global Const MB_OK = 0                 ' OK button only
Global Const MB_OKCANCEL = 1           ' OK and Cancel buttons
Global Const MB_ABORTRETRYIGNORE = 2   ' Abort, Retry, and Ignore buttons
Global Const MB_YESNOCANCEL = 3        ' Yes, No, and Cancel buttons
Global Const MB_YESNO = 4              ' Yes and No buttons
Global Const MB_RETRYCANCEL = 5        ' Retry and Cancel buttons

Global Const MB_ICONSTOP = 16          ' Critical message
Global Const MB_ICONQUESTION = 32      ' Warning query
Global Const MB_ICONEXCLAMATION = 48   ' Warning message
Global Const MB_ICONINFORMATION = 64   ' Information message

Global Const MB_APPLMODAL = 0          ' Application Modal Message Box
Global Const MB_DEFBUTTON1 = 0         ' First button is default
Global Const MB_DEFBUTTON2 = 256       ' Second button is default
Global Const MB_DEFBUTTON3 = 512       ' Third button is default
Global Const MB_SYSTEMMODAL = 4096      'System Modal

' MsgBox return values
Global Const IDOK = 1                  ' OK button pressed
Global Const IDCANCEL = 2              ' Cancel button pressed
Global Const IDABORT = 3               ' Abort button pressed
Global Const IDRETRY = 4               ' Retry button pressed
Global Const IDIGNORE = 5              ' Ignore button pressed
Global Const IDYES = 6                 ' Yes button pressed
Global Const IDNO = 7                  ' No button pressed

Global Const SHIFTKEY = 1               ' Use these to interpret
Global Const CTRLKEY = 2                ' KeyDown events
Global Const ALTKEY = 4

'-----------------------------------------------------------------------
' Mediaview Errors
'-----------------------------------------------------------------------

Global Const GMVERR_OOM = 1001   '// Out Of Memory
Global Const GMVERR_OODC = 1002 '// Out of Display Contexts
Global Const GMVERR_NOTITLE = 1003
Global Const GMVERR_FNF = 1004  '// File Not Found
Global Const GMVERR_NOTOPIC = 1005
Global Const GMVERR_BADPRINT = 1006
Global Const GMVERR_BADFILE = 1007
Global Const GMVERR_OLDFILE = 1008
Global Const GMVERR_DiskFull = 1009
Global Const GMVERR_FSReadWrite = 1010
Global Const GMVERR_FCEndOfTopic = 1011
Global Const GMVERR_BADPARAM = 1012
Global Const GMVERR_NOFONTCHANGE = 1013
Global Const GMVERR_NOMOREHOTSPOTS = 1014
Global Const GMVERR_BADCOLOR = 1015
Global Const GMVERR_BADEWWINCLASS = 1016
Global Const GMVERR_PARTIAL = 1017
Global Const GMVERR_NOADDRESS = 1018
Global Const GMVERR_NORECTANGLE = 1019
Global Const GMVERR_NOVSCROLL = 1020 '// No Vertical Scrollbar
Global Const GMVERR_NOHSCROLL = 1021 '// No Horizontal Scrollbar
Global Const GMVERR_CANTFINDDLL = 1022
Global Const GMVERR_CANTUSEDLL = 1023
Global Const GMVERR_EWOOM = 1024 '// Embedded Window Out Of Memory
Global Const GMVERR_DEBUGMISMATCH = 1025
Global Const GMVERR_BADPOLYGON = 1026 '// less than 3 pts or none passed
Global Const GMVERR_BADEWCALLBACK = 1027

'----------------------------------------------------------
' Podium event parameter values
'----------------------------------------------------------

' integer param values for "Close" event from Podium: passed onto NotifyShellShuttingDown, too!
Global Const CLOSE_SLOW = 0               'regular exit thru podium
Global Const CLOSE_FAST = 1               'doubleclick on podium exit btn
Global Const CLOSE_LOGOUT = 2             'shell gets this if exiting from room
Global Const CLOSE_SHUTDOWN = 3           'shell gets this if user wants out!


' integer param values for "DialogState" event
Global Const POD_DIALOGSTATE_CANCEL = 0     ' user selected cancel on podium dialog
Global Const POD_DIALOGSTATE_SWITCH = 1 ' user selected switch to another app on podium dialog
Global Const POD_DIALOGSTATE_GOINGUP = 2  ' user just selected podium button so dialog coming up
Global Const POD_DIALOGSTATE_DOUBLECLICK = 3  ' user just double clicked on podium so it's not going up - chance to cancel exit by setting Proceed to False still exists

'-----------------------------------------------------------------------
' Utopia System Services Support
'-----------------------------------------------------------------------
Global Const PATH_MAX& = 256
Global gstUtopiaDir As String

Declare Function GetUtopiaDirectory Lib "UTOPIA.DLL" (ByVal stDir As String, ByVal cbDirMax As Long) As Long
Declare Sub UtopiaIdle Lib "UTOPIA.DLL" ()
Declare Sub UtopiaDoEvents Lib "UTOPIA.DLL" ()
Declare Function UtopiaInitialize Lib "UTOPIA.DLL" (ppTask As Long) As Long
Declare Function UtopiaUninitialize Lib "UTOPIA.DLL" () As Integer
Declare Function UGetLastError Lib "UTOPIA.DLL" () As Integer
Declare Function GetDfltMessageForUErr Lib "UTOPIA.DLL" (ByVal uErr As Integer) As String
Declare Function UErrFromResult Lib "UTOPIA.DLL" (ByVal hr As Long) As Integer
Declare Function UWarnFromResult Lib "UTOPIA.DLL" (ByVal hr As Long) As Integer
Declare Function GetNumAppsRunning Lib "UTOPIA.DLL" () As Integer
Declare Function VBGetHomeAddress Lib "UTOPIA.DLL" () As String
Declare Function GetHomeAddress Lib "UTOPIA.DLL" (ByVal st As String, ByVal cch As Integer) As Long
Declare Sub SetAppWindowStyle Lib "UTOPIA.DLL" (ByVal hWnd As Integer)

' Sound support
Declare Sub UtopiaSoundActivate Lib "UTOPIA.DLL" (ByVal fActive As Integer)
Declare Sub UtopiaPlaySoundFile Lib "UTOPIA.DLL" (ByVal sz As String, ByVal cLoops As Integer, dwGroup As Long)
Declare Sub UMessageBeep Lib "UTOPIA.DLL" (ByVal mb As Integer)

' Call this after initializing Utopia:
Global Const USSS_UTOPIACOMPONENT = 1
Global Const USSS_PICTID = 2
Declare Function UShowStartupScreen Lib "UTOPIA.DLL" (ByVal szName As String, ByVal szCopyright As String, ByVal pictID As Long, ByVal wFlags As Integer) As Long

' Only use this function if pTip = NULL
Declare Function UShowAboutBox Lib "UTOPIA.DLL" (ByVal hwndParent As Integer, ByVal szName As String, ByVal szCopyright As String, ByVal pTip As Long, ByVal tipidKey As Integer, ByVal tipidHOR As Integer, ByVal wFlags As Integer) As Long

' Hack routines to build a null-terminated list of longs
Declare Sub VBDeleteList Lib "UTOPIA" (ByVal lListId As Long)
Declare Function VBAddItemToList Lib "UTOPIA" (ByVal lListId As Long, ByVal lItem As Long) As Long

'-----------------------------------------------------------------------
' Utopia Object Support
'-----------------------------------------------------------------------
Declare Sub CoFreeUnusedLibraries Lib "compobj" ()

Global gUTObject As Object
Dim gUtopiaInitObject As Object

'-----------------------------------------------------------------------
' Errors
'-----------------------------------------------------------------------
Global Const S_OK = 0
Global Const S_FALSE = 1

'Facility_Null Errors
Global Const E_UNEXPECTED = &H8000FFFF
Global Const E_NOTIMPL = &H80000001
Global Const E_OUTOFMEMORY = &H80000002
Global Const E_INVALIDARG = &H80000003
Global Const E_NOINTERFACE = &H80000004
Global Const E_POINTER = &H80000005
Global Const E_HANDLE = &H80000006
Global Const E_ABORT = &H80000007
Global Const E_FAIL = &H80000008
Global Const E_ACCESSDENIED = &H80000009


'-----------------------------------------------------------------------
' Tasklist Printing API's and constants
'-----------------------------------------------------------------------
Declare Function PrintTaskList% Lib "Tasklist.vbx" (ByVal printerdc As Integer, rc As RECT, ByVal DBID As Long, ByVal fWhichtoPrint As Integer)
Declare Function ContinuePrintingTaskList% Lib "Tasklist.vbx" (ByVal printerdc As Integer, rc As RECT)

Global Const TL_PRINT_DONE = &H1
Global Const TL_PRINT_UNDONE = &H2

'-----------------------------------------------------------------------
'Bit fields for UTask.Flags:
Global Const TASK_SHUTTING_DOWN = &H2

'-----------------------------------------------------------------------
'NotifyShellShuttingDown
'
'Apps must call this Function once they begin their normal shutdown procedure right
'   *after* any chance there is to abort the shutdown
'Apps should NOT exit if this Function returns False - they should expect that this
'   Function MAY return False and be able to continue as normal if it does
'
'Do not bother to call this Function in an *abnormal* app termination routine
'
'Calling this is required because:
'   1. Other Apps may be exiting and they need to fully exit first:
'        VB can stack overflow if 2 VB apps in a row exit fast (via 2 Alt-F4s, e.g.)
'   2. To allow the shell to know an app is exiting in case it receives an exit
'        request right away so that it won't falsely put up (include it in) switch dialog
'
'Params:
'   exiting: True if you are closing, False if your shutdown is aborted (required)
'   exitSpeed: either Global Const CLOSE_FAST or CLOSE_SLOW, pass in what came
'              from Podium's Close event, or pass in CLOSE_FAST on receipt of Alt-F4
'
'Returns:
'   1. True (usually)
'   2. False (only if other apps are in process of exiting and you are requesting a fast exit)
'
'Examples:
'   In the handling of your Alt-F4 code:
'       If NotifyShellShuttingDown(True, CLOSE_FAST) = False Then Exit Sub 'Do NOT exit, continue
'
'    In the response to your Podium Close event:
'       If NotifyShellShuttingDown(True, ExitSpeed) = False Then Exit Sub 'Do NOT exit, continue
'
'Note: be sure to call this in any additional place that the user can request an exit. For instance
'      the LetterWriter has a special Exit button when just getting going. Also, some apps have
'      more than one place Alt-F4's and Podium Close's get handled
'

'-----------------------------------------------------------------------
' Purpose:
'   Adds a form the the dialog cache, and percolates it to the top of the
' cache.  If the cache is full, then the least recently used, non-visible
' dialog is unloaded and removed from the cache.  In the unlikely event
' that all the dialogs in the cache are full, this function returns False
' and does not load the form.
'
' Notes:
'   The form cache should contain valid forms from 0 to frmMax, inclusive.
' E.g., rgForm(frmMax) is valid, frmMax = -1 when the cache is empty, and
' frmMax = gcDlgCache when the cache is full.
'-----------------------------------------------------------------------
Function FCacheDialog (frm As Form) As Integer
    Dim i As Integer
    Dim j As Integer

    'See if we've shown the form before
    For i = 0 To frmMax
    If frm Is rgForm(i) Then

    'Percolate this form to the top

    For j = i To 1 Step -1: Set rgForm(j) = rgForm(j - 1): Next j
    Set rgForm(0) = frm
    FCacheDialog = True
    Exit Function

    End If
    Next i

    'we didn't find it, so add it to the list
    If frmMax = gcDlgCache Then
    ' Cache is full.  Unload the last invisible form in the list
    For i = frmMax To 0 Step -1
    If rgForm(i) Is Nothing Then
    Exit For
    ElseIf rgForm(i).Rgnwnd1.Cached And Not rgForm(i).Visible Then
    Unload rgForm(i)
    Set rgForm(i) = Nothing
    Exit For
    End If
    Next i

    ' If all forms in cache are visible, then we can't do anything.
    If i < 0 Then Exit Function
    Else
    ' Cache isn't full, so add it to the end.
    frmMax = frmMax + 1
    i = frmMax
    End If

    ' Percolate items from position i
    For j = i - 1 To 0 Step -1: Set rgForm(j + 1) = rgForm(j): Next j
    Set rgForm(0) = frm
    Load frm
    ' Since form is in cache, make sure it doesn't get unloaded if autoclosed
    frm.Rgnwnd1.CacheOnClose = True
    FCacheDialog = True

End Function

Function FCacheFull () As Integer
    FCacheFull = frmMax = gcDlgCache
End Function

' Returns true if the file exists.
' sName should be a fully qualified file name.
Function FFileExists (sName As String) As Integer
    FFileExists = False
    On Error Resume Next
    If Dir$(sName) <> "" Then FFileExists = True
End Function

'----------------------------------------------------------------------
' FIsDefaultPrinterSetup
'
' Checks the user's win.in for an entry in the windows, device.  If any
' thing is found, returns true, else false
'
'----------------------------------------------------------------------
Function FIsDefaultPrinterSetup () As Integer
    Dim stPrinter As String * 60
    If GetProfileString(ByVal "windows", ByVal "device", ByVal "", ByVal stPrinter, Len(stPrinter)) = 0 Then
    FIsDefaultPrinterSetup = False
    Else
    FIsDefaultPrinterSetup = True
    End If

End Function

'-----------------------------------------------------------------------
' Returns TRUE if tip is showing in the given range, FALSE otherwise.
' If tipidFirst = tipidLast = TIPID_ALL, then this returns TRUE if any
' tip is shown.
'-----------------------------------------------------------------------
Function FIsTipShowing (tipidFirst As Integer, tipidLast As Integer) As Integer

    On Error Resume Next

    If gTipObject.FIsTipShowing(tipidFirst, tipidLast) <> 0 Then
    FIsTipShowing = True
    End If

End Function

'-------------------------------------------------------
' This function is useful to deterime if you window is
' currently in the foreground. Since a balloon may be
' the active window, fIsWndActive not only looks at the
' active window, but it steps through all of its
' parents to see if the specified window is on that list.
'
' Returns false if the window is not in the active chain
' and true if it is.
'-------------------------------------------------------
Function FIsWndActive (ByVal hWnd As Integer)
    Dim hWndActive As Integer

    FIsWndActive = True
    hWndActive = GetActiveWindow()
    While hWndActive
    If hWndActive = hWnd Then Exit Function
    hWndActive = GetParent(hWndActive)
    Wend
    FIsWndActive = False

End Function

'-----------------------------------------------------------------------
' FLoadTips
'
' Loads the Tip Object displayer with the given tip resource file.
' Pass in a null string to just load system tips.
'
' Returns False if the tip resource file exists but cannot be
' loaded.  Returns True if the tip resource file is loaded
' successfully, or if it doesn't exist.  In this case, gTipObject
' will just load the system tip object.  If this function returns
' False then gTipObject is Nothing, and calling FShowTipAtCtl and
' friends will cause an error.
'-----------------------------------------------------------------------
Function FLoadTips (szTipFile As String) As Integer

    Dim szTipResource As String

    ' Load tip resource file.  If tip resource file cannot be
    ' loaded, then return False.

    Set gTipObject = Nothing
    On Error Resume Next
    If Right$(App.Path, 1) = "\" Then
    szTipResource = App.Path + szTipFile
    Else
    szTipResource = App.Path + "\" + szTipFile
    End If

    Set gTipObject = gUTObject.LoadTips(gAppID, szTipResource)
    If gTipObject Is Nothing Then
'_DEBUG
    'UNDONE:  This is commented because it doesn't get removed properly
    'because it is in the shared directory.

    'MsgBox "Could not load tips: " & szTipResource, MB_ICONEXCLAMATION + MB_OK + MB_SYSTEMMODAL
'_END
    FLoadTips = False
    Else
    FLoadTips = True
    End If

End Function

'-----------------------------------------------------------------------
' Purpose:
'   This is a less aggressive version of FCacheDialog.  If the cache is
' not yet full, then the given form will be put in the cache, but not
' percolated to the top. If the cache is full, then this function will
' do nothing, even if forms in the cache are hidden.
'
' Use this routine in your idle processing loop to precache expected
' dialogs on startup.
'
' Returns:
'   True if form was cached, False if cache was full.
'-----------------------------------------------------------------------
Function FPreCacheDialog (frm As Form) As Integer
    Dim i As Integer

    FPreCacheDialog = True

    'See if the form cache is full
    If frmMax = gcDlgCache Then
    FPreCacheDialog = False
    Exit Function
    End If

    FPreCacheDialog = True

    'See if the form has already been cached
    For i = 0 To frmMax
    If frm Is rgForm(i) Then Exit Function
    Next i

    'Cache and load the form.  Cache first, because loading
    'may cause other forms to get put in the cache.
    frmMax = frmMax + 1
    Set rgForm(frmMax) = frm
    Load frm
    ' Since form is in cache, make sure it doesn't get unloaded if autoclosed
    frm.Rgnwnd1.CacheOnClose = True

End Function

Sub FreeCursor ()
    Dim iRet As Integer
    If hCursor Then iRet = SetCursor(hCursor)
End Sub

'-----------------------------------------------------------------------
' Shows the Hint-O-Rama.
'
' Returns True if the hint-o-rama was turned off.  In this case, the app
' should respond by displaying the app-specific tip on how to turn the
' hint-o-rama back on.
'
' NOTE:  This function is obsolete, and only retained for backward compatibility.
' Please use ShowHintORama instead.
'-----------------------------------------------------------------------
Function FShowHintORama (tipID As Integer, ByVal hwndParent As Integer) As Integer

    Dim t As Long

    On Error GoTo err_FShowHintORama

    t = gTipObject.ShowHintORama(tipID, TIPID_NONE, hwndParent)

    If t = TIP_S_CANCEL Then
    FShowHintORama = True
    End If

    Exit Function

err_FShowHintORama:
    ' Check if gTipObject was not created or if
    ' tipID is an invalid tip.

    If Err = UERR_OLEOBJECTNOTSET Or Err = UERR_OLEAUTOMATION Or Err = UERR_TIP_E_INVALID Then
    UShowErrorTip hwndParent, UERR_GEN_BADSYSTEMSETUP, 0&
    Else
    UShowErrorTip hwndParent, Err, Error$
    End If

    Exit Function

End Function

'-----------------------------------------------------------------------
' Shows the given tip at the given control.
'
' Returns False if the tip was modal and the user chose Cancel.  Otherwise returns
' True.
'-----------------------------------------------------------------------
Function fShowTipAtCtl (tipID As Integer, ctl As Control, bs As Integer) As Integer

    Dim t As Long
    Dim hwndParent As Integer
    Dim rc As RECT

    On Error GoTo err_FShowTipAtCtl

    ' HACK ALERT:  The following call sets t to be a pointer to the rectangle
    ' rc.  This is so that it may be passed to the IDispatch function, since
    ' VB 3.0 doesn't allow passing a pointer to a user defined structure to
    ' IDispatch.

    GetTipParams ctl, hwndParent, rc, t

    t = gTipObject.ShowTip(tipID, hwndParent, t, bs)

    If t = 0 Then
    fShowTipAtCtl = True
    End If

    Exit Function

err_FShowTipAtCtl:
    ' Check if gTipObject was not created or if
    ' tipID is an invalid tip.

    If Err = UERR_OLEOBJECTNOTSET Or Err = UERR_OLEAUTOMATION Or Err = UERR_TIP_E_INVALID Then
    UShowErrorTip hwndParent, UERR_GEN_BADSYSTEMSETUP, 0&
    Else
    UShowErrorTip hwndParent, Err, Error$
    End If

    Exit Function

End Function

'-----------------------------------------------------------------------
' Shows the given tip at the given control rectangle.
'
' Returns False if the tip was modal and the user chose Cancel.  Otherwise returns
' True.
'-----------------------------------------------------------------------
Function FShowTipAtCtlRect (tipID As Integer, ctl As Control, bs As Integer, rc As RECT) As Integer
    Dim t As Long
    Dim hwndParent As Integer

    On Error GoTo err_FShowTipAtCtlRect

    ' HACK ALERT:  The following call sets t to be a pointer to the rectangle
    ' rc.  This is so that it may be passed to the IDispatch function, since
    ' VB 3.0 doesn't allow passing a pointer to a user defined structure to
    ' IDispatch.
    hwndParent = ctl.Parent.hWnd
    ' Translate rectangle to screen coordinates
    Call MapWindowPoints(hwndParent, 0, rc, 2)
    t = LongFromPtr(rc)

    t = gTipObject.ShowTip(tipID, hwndParent, t, bs)

    If t = 0 Then
    FShowTipAtCtlRect = True
    End If

    Exit Function

err_FShowTipAtCtlRect:
    ' Check if gTipObject was not created or if
    ' tipID is an invalid tip.

    If Err = UERR_OLEOBJECTNOTSET Or Err = UERR_OLEAUTOMATION Or Err = UERR_TIP_E_INVALID Then
    UShowErrorTip hwndParent, UERR_GEN_BADSYSTEMSETUP, 0&
    Else
    UShowErrorTip hwndParent, Err, Error$
    End If

    Exit Function


End Function

'-----------------------------------------------------------------------
' Tests to see whether the tip, if triggered, would be displayed.
' May be used for either simple or complex tips.  Call this function
' to indicate to the user that a tip is available, should they wish
' to see it.
'-----------------------------------------------------------------------
Function FTestTip (tipID As Integer)

    Dim hr As Long

    On Error Resume Next
    hr = gTipObject.FTestTip(tipID)

    If Err = 0 And hr = 0& Then
    FTestTip = True
    End If

End Function

'-----------------------------------------------------------------------
' Triggers the given application defined tip.  Returns True if the
' tip is fired, False otherwise.
'-----------------------------------------------------------------------
Function fTriggerTip (tipID As Integer) As Integer

    Dim hr As Long

    On Error Resume Next
    hr = gTipObject.TriggerTipNoShow(tipID)

    If hr = 0& Or hr = TIP_S_APPDISPLAY Then
    fTriggerTip = True
    End If

End Function

'-----------------------------------------------------------------------
' Triggers the given tip.  If it should be displayed, it is displayed pointing
' to the given control.
'
' Returns True if the tip was displayed, unless the tip was modal and the user chose Cancel.
' Otherwise returns False.
'-----------------------------------------------------------------------
Function FTriggerTipAtCtl (tipID As Integer, ctl As Control, bs As Integer) As Integer

    Dim t As Long
    Dim hwndParent As Integer
    Dim rc As RECT

    On Error GoTo err_FTriggerTipAtCtl

    ' HACK ALERT:  The following call sets t to be a pointer to the rectangle
    ' rc.  This is so that it may be passed to the IDispatch function, since
    ' VB 3.0 doesn't allow passing a pointer to a user defined structure to
    ' IDispatch.

    GetTipParams ctl, hwndParent, rc, t

    t = gTipObject.TriggerTip(tipID, hwndParent, t, bs)

    If t = 0 Then
    FTriggerTipAtCtl = True
    End If

    Exit Function

err_FTriggerTipAtCtl:
    ' Check if gTipObject was not created or if
    ' tipID is an invalid tip.

    If Err = UERR_OLEOBJECTNOTSET Or Err = UERR_OLEAUTOMATION Or Err = UERR_TIP_E_INVALID Then
    UShowErrorTip hwndParent, UERR_GEN_BADSYSTEMSETUP, 0&
    Else
    UShowErrorTip hwndParent, Err, Error$
    End If

    Exit Function

End Function

'-----------------------------------------------------------------------
' Triggers the given tip.  If it should be displayed, it is displayed pointing
' to the given RECT.
'
' Returns True if the tip was displayed, unless the tip was modal and the user chose Cancel.
' Otherwise returns False.
'-----------------------------------------------------------------------
Function FTriggerTipAtCtlRect (tipID As Integer, ctl As Control, bs As Integer, rc As RECT) As Integer

    Dim t As Long
    Dim hwndParent As Integer

    On Error GoTo err_FTriggerTipAtCtlRect

    ' HACK ALERT:  The following call sets t to be a pointer to the rectangle
    ' rc.  This is so that it may be passed to the IDispatch function, since
    ' VB 3.0 doesn't allow passing a pointer to a user defined structure to
    ' IDispatch.
    hwndParent = ctl.Parent.hWnd
    ' Translate rectangle to screen coordinates
    Call MapWindowPoints(hwndParent, 0, rc, 2)
    t = LongFromPtr(rc)

    t = gTipObject.TriggerTip(tipID, hwndParent, t, bs)

    If t = 0 Then
    FTriggerTipAtCtlRect = True
    End If

    Exit Function

err_FTriggerTipAtCtlRect:
    ' Check if gTipObject was not created or if
    ' tipID is an invalid tip.

    If Err = UERR_OLEOBJECTNOTSET Or Err = UERR_OLEAUTOMATION Or Err = UERR_TIP_E_INVALID Then
    UShowErrorTip hwndParent, UERR_GEN_BADSYSTEMSETUP, 0&
    Else
    UShowErrorTip hwndParent, Err, Error$
    End If

    Exit Function
End Function

Function fUtopiaInit () As Integer

    Dim uErr As Integer
    Dim fStand As Integer
    On Error Resume Next

    fUtopiaInit = True
    fStand = GetProfileInt("MS-BOB", "fStandalone", 0)
    
    uErr = UtopiaInit()
'_DEBUG
    If (uErr = USUCC_FIRSTTASK) Then Exit Function
'_END
    If (uErr = USUCC_FIRSTTASK) And (fStand = 1) Then Exit Function
    If uErr <> ERR_NONE Then
       UShowErrorTip 0, uErr, ""
       If uErr = USUCC_FIRSTTASK Then UtopiaUnInit
       fUtopiaInit = False
    End If

End Function

' Purpose:
'  Get the title of the active window.
Function GetActiveWindowTitle ()
    Dim hWnd As Integer
    Dim cch As Integer
    Dim stTitle As String

    hWnd = GetActiveWindow()
    If hWnd = 0 Then Exit Function

    cch = GetWindowTextLength(hWnd) + 1

    stTitle = String(cch, 0)
    cch = GetWindowText(hWnd, stTitle, cch)

    GetActiveWindowTitle = stTitle

End Function

' Purpose:
'  Given an app id, return the app's name (as stored in
'  the utopia database
Function GetAppName (Id As Long)

    Dim Sys As Object
    Dim App As Object

    On Error GoTo Err_GetAppName

    Set Sys = gUTObject.GetSystem()
    Set App = Sys.FindApp("", Id)
    GetAppName = App.Name

    Exit Function

Err_GetAppName:

    Exit Function ' return an empty string

End Function

Function GetRes (ByVal hDC As Integer) As Integer

    'Get the screen size
    gScrX = GetDeviceCaps(hDC, HORZRES)
    gScrY = GetDeviceCaps(hDC, VERTRES)

    If gScrX = 640 And gScrY = 480 Then
    gScrType = SCR_VGA
    ElseIf gScrX = 1024 And gScrY = 768 Then
    gScrType = SCR_SVGA
    Else
    gScrType = SCR_OTHER
    End If

    GetRes = gScrType
End Function

'-----------------------------------------------------------------------
' Helper function for FShowTipAtCtl and FTriggerTipAtCtl.  This
' function loads the hWnd and rc parameters with the necessary
' data.
'
' NOTE:  Assumes control coordinates are in twips!
'-----------------------------------------------------------------------
Private Sub GetTipParams (ctl As Control, hWnd As Integer, rc As RECT, lprc As Long)

    hWnd = ctl.Parent.hWnd

    rc.Left = ctl.Left / Screen.TwipsPerPixelX
    rc.Top = ctl.Top / Screen.TwipsPerPixelY
    rc.right = rc.Left + ctl.Width / Screen.TwipsPerPixelX
    rc.bottom = rc.Top + ctl.Height / Screen.TwipsPerPixelY

    ' Translate rectangle to screen coordinates
    Call MapWindowPoints(hWnd, 0, rc, 2)

    lprc = LongFromPtr(rc)

End Sub

' Return the Current user's Id
' On failure, 0 is returned
Function GetUserId () As Long
    Dim utsystem As Object
    Dim person As Object

    On Error GoTo Err_GetUserId

    Set utsystem = gUTObject.GetSystem()
    Set person = utsystem.GetCurrentUser()
    GetUserId = person.Id
    Exit Function

Err_GetUserId:
    GetUserId = 0 ' same as public
    Exit Function

End Function

Sub GetUtopiaDir ()
' Purpose: Set the global string gstUtopiaDir to point
'   to the Utopia Installation directory.

  Dim retval, i%, n%, st As String * PATH_MAX

  ' Get the Utopia Installation Directory
  retval = GetUtopiaDirectory(st, PATH_MAX&)

  ' Becasue of the fixed length string, strip off the redundant buffer space
  i = 1: n = 1
  Do While n <> 0
    n = InStr(i, st, "\")
    If n <> 0 Then i = n + 1
  Loop
  gstUtopiaDir$ = Left(st, i - 1)

End Sub

'
' Loads the global gUTObject, which can then be used to create
' various utopia objects.
'
' Returns True if gUTObject has been loaded successfully, False
' otherwise.
'
Function GetUtopiaObject () As Integer

    GetUtopiaObject = True

    If (gUTObject Is Nothing) Then
    Set gUTObject = CreateObject("Utopia")

    If (gUTObject Is Nothing) Then GetUtopiaObject = False
    End If

End Function

'-----------------------------------------------------------------------
' Removes one life from the given tip.  Call this subroutine whenever
' the user demonstrates knowledge of a tracked tip's contents.
'
' NOTE:  Do NOT call this subroutine to remove a modeless tip after
' it has been displayed.  To do that, use UnshowTip instead.
'-----------------------------------------------------------------------
Sub KillTip (tipID As Integer)

    Dim hr As Long

    On Error Resume Next
    hr = gTipObject.KillTip(tipID)

End Sub

Function NotifyShellShuttingDown (exiting As Integer, exitSpeed As Integer) As Integer
    Dim Task As Object
    Dim flagStatus As Long
    Dim nResult As Integer

    'Inquire to system services as to how many other apps are running
    nResult = GetNumAppsRunning()
    
    'If other apps are in the process of exiting (nResult = -1) AND
    '   we are attempting to exit fast (via Alt-F4 or podium doubleclick)
    '   then abort this app's exit request by returning False
    If (nResult < 0) And (exitSpeed = CLOSE_FAST) And (exiting = True) Then
    'App can not shutdown
    NotifyShellShuttingDown = False
    Else
    'Get Task Object
    Set Task = gUTObject.GetCurrentUTask()

    'Get flag status
    flagStatus = Task.Flags

    'Set bit in flag property if exiting else clear
    If exiting Then
        Task.Flags = flagStatus Or TASK_SHUTTING_DOWN
    Else
        Task.Flags = flagStatus And (Not TASK_SHUTTING_DOWN)
    End If

    Set Task = Nothing

    'App can Shutdown
    NotifyShellShuttingDown = True

    End If

End Function

'-----------------------------------------------------------------------
' Makes the given actor control run the given animation, and doesn't return
' until it is finished.
'
' Parameters:
'   ctl --  Name of actor control to play action
'   act --  Action to play.
'-----------------------------------------------------------------------
Sub PlaySynchronousAction (ctl As Actor, act As Integer)

ctl.Sync = True
ctl.Action = act

End Sub

'-----------------------------------------------------------------------
' Position this form in relation to some object
'-----------------------------------------------------------------------
Sub PositionForm (Rgnwnd1 As Control, ByVal hwndParent As Integer, ctl As Control)
    Rgnwnd1.ObjectHeight = ctl.Height
    Rgnwnd1.ObjectWidth = ctl.Width
    Rgnwnd1.ObjectX = ctl.Left
    Rgnwnd1.ObjectY = ctl.Top
    Rgnwnd1.ParentHwnd = hwndParent
    Rgnwnd1.AutoPos = 2
End Sub

'  Position a balloon to point at a control in a form
'  This function ASSUMES that both the form containing the control as well
'  as the form being positioned share the same parent window
Private Sub PositionFormAtCtlInForm (Rgnwnd1 As Control, ByVal hwndParent As Integer, frmTarget As Form, ctlTarget As Control)
    Rgnwnd1.ObjectHeight = ctlTarget.Height
    Rgnwnd1.ObjectWidth = ctlTarget.Width
    Rgnwnd1.ObjectX = frmTarget.Left + ctlTarget.Left ' coordinates are in parent window terms, so we need to adjust
    Rgnwnd1.ObjectY = frmTarget.Top + ctlTarget.Top
    Rgnwnd1.ParentHwnd = hwndParent
    Rgnwnd1.AutoPos = 2

End Sub

Private Sub PositionFormAtForm (Rgnwnd1 As Control, ByVal hwndParent As Integer, f As Form)
    Rgnwnd1.ObjectHeight = f.Height
    Rgnwnd1.ObjectWidth = f.Width
    Rgnwnd1.ObjectX = f.Left
    Rgnwnd1.ObjectY = f.Top
    Rgnwnd1.ParentHwnd = hwndParent
    Rgnwnd1.AutoPos = 2
End Sub

'----------------------------------------------------------
' Sizes and positions main form.
' NOTE: Use PositionMainFormActorPodium if possible.
' created: barryl 9/6/94
'----------------------------------------------------------
Sub PositionMainForm (frmMain As Form)
   'position form
    'note that windowstate must be 0 (normal) because
    'maximized vb forms are actually 4 pixels larger than the screen
    'which causes scale control to misposition control and room image
    frmMain.WindowState = 0
    frmMain.Move 0, 0, Screen.Width, Screen.Height
End Sub

'----------------------------------------------------------
' sizes and positions main form, actor and podium control
' created: barryl 9/6/94
'----------------------------------------------------------
Sub PositionMainFormActorPodium (frmMain As Form, ctlActor As Control, ctlPodium As Control)
Dim dxActor As Integer
Dim dyActor As Integer
Dim dyPodium As Integer
Dim dxScreen As Integer
Dim dyScreen As Integer

    'storing props in variables because prop lookup is slow
    'and we use these props a lot in calculations below
    dxScreen = Screen.Width
    dyScreen = Screen.Height

    'casting to longs so that won't overflow. vb will cast back on assignment
    dxActor = CLng(dxScreen * .2083)
    dyActor = CLng(dyScreen * .2083)
    dyPodium = CLng(dyScreen * .05)

    'position form
    'note that windowstate must be 0 (normal) because
    'maximized vb forms are actually 4 pixels larger than the screen
    'which causes scale control to misposition control and room image
    frmMain.WindowState = 0
    frmMain.Move 0, 0, dxScreen, dyScreen
    'position actor. actor is 20.83% of screen height and width
    ctlActor.Move dxScreen - dxActor, dyScreen - dyActor - dyPodium, dxActor, dyActor
    'position podium. podium is width of actor and 5% of screen height
    ctlPodium.Move dxScreen - dxActor, dyScreen - dyPodium, dxActor, dyPodium

End Sub

Sub PurgeFormCache ()

    Dim ifrm As Integer, ifrmMax As Integer

    If FWaitingForAnimToFinish() Then
        Exit Sub
    End If

    ifrmMax = 0
    For ifrm = 0 To frmMax
    If Not rgForm(ifrm) Is Nothing Then
    If rgForm(ifrm).Rgnwnd1.Cached And Not rgForm(ifrm).Visible Then
    ' unload this form
    Unload rgForm(ifrm)
    Set rgForm(ifrm) = Nothing
    Else
    ' Save this form in list
    If ifrm <> ifrmMax Then
        Set rgForm(ifrmMax) = rgForm(ifrm)
        Set rgForm(ifrm) = Nothing
    End If
    ifrmMax = ifrmMax + 1
    End If
    End If
    Next
    frmMax = ifrmMax - 1

End Sub

'returns a random number between 0 and number passed in
'
'rnd function is seeded by randomize call in utopiaInit()
Function rndm (lubnd As Long) As Integer
    rndm = Int((lubnd + 1) * Rnd)
End Function

'-----------------------------------------------------------------------
' Set the Dialog Cache size. This should be called directly after
' UtopiaInit if you want to change it.
'-----------------------------------------------------------------------
Sub SetDialogCacheSize (cDlg As Integer)

    ' bad allowable range? I don't know what the behaviour of setting
    ' this to zero will be so I don't allow it.
    If cDlg < 1 Or cDlg > CACHE_SIZE Then Exit Sub

    ' we have already cached more dialogs than the size of the cache
    ' requested. You should call this function directly after UtopiaInit
    ' for it to work correctly. but don't panic. We won't change it's size
    If cDlg < frmMax Then Exit Sub

    ' set cache size to cDlg dialogs
    gcDlgCache = cDlg

End Sub

Sub ShowAboutBox (ByVal hwndParent As Integer, ByVal szName As String, ByVal szCopyright As String, ByVal tipidKeyboard As Integer, ByVal tipidHOR As Integer, ByVal wFlags As Integer)

    Dim hr As Long

    On Error GoTo err_ShowAboutBox

    If gTipObject Is Nothing Then
    hr = UShowAboutBox(hwndParent, szName, szCopyright, 0&, tipidKeyboard, tipidHOR, wFlags)
    ' UNDONE:  check hr
    Else
    hr = gTipObject.ShowAboutBox(hwndParent, szName, szCopyright, tipidKeyboard, tipidHOR, wFlags)
    End If

    Exit Sub

err_ShowAboutBox:
    ' Check if gTipObject was not created or if
    ' tipID is an invalid tip.

    If Err = UERR_OLEOBJECTNOTSET Or Err = UERR_OLEAUTOMATION Or Err = UERR_TIP_E_INVALID Then
    UShowErrorTip hwndParent, UERR_GEN_BADSYSTEMSETUP, 0&
    Else
    UShowErrorTip hwndParent, Err, Error$
    End If

    Exit Sub

End Sub

'-----------------------------------------------------------------------
' Orient the dialog to point at the actor.
'
' Requires that the regional window control in your form is
' called rgnwnd1, and that the actor in frmParent is called Actor1.
'
' The unload event for the parent form (NOT the dialog) should contain:
'
'   RgnWndUnload hWnd
'
'-----------------------------------------------------------------------
Sub ShowActorDialog (frmDialog As Form, frmParent As Form)
    ' UNDONE - call PositionForm only when form is loaded
    PositionForm frmDialog.Rgnwnd1, frmParent.hWnd, frmParent.Actor1
    ShowDialog frmDialog
End Sub

'-----------------------------------------------------------------------
' Orient the dialog according to the object it points to.
'
'Requires that the regional window control in your form is
'called rgnwnd1.
'
'The unload event for the parent form (NOT the dialog) should contain:
'
'   RgnWndUnload hWnd
'
'-----------------------------------------------------------------------
Sub ShowDialog (frmDialog As Form)
    If Not FCacheDialog(frmDialog) Then
    ' CONSIDER:  This only happens if the cache is completely
    '   full of visible windows.  If this can happen in an app, then
    '   it should really increase the cache size.  Anyway,
    '   this code allows the form to be shown, but it won't
    '   be unloaded afterwards, and won't be purged when losing
    '   focus.  It will of course be reused if reshown.
    Load frmDialog
    End If

    frmDialog.Rgnwnd1.Cached = False      ' This shows the form

End Sub

'-----------------------------------------------------------------------
' Orient the dialog at parameter ctl
'
' Requires that the regional window control in your form is
' called rgnwnd1, and that ctl possesses top, left, width and height
' properties.
'
' The unload event for the parent form (NOT the dialog) should contain:
'
'   RgnWndUnload hWnd
'
'-----------------------------------------------------------------------
Sub ShowDialogAtCtl (frmDialog As Form, ByVal hwndParent As Integer, ctl As Control)
    PositionForm frmDialog.Rgnwnd1, hwndParent, ctl
    ShowDialog frmDialog
End Sub

' Purpose:
'   Position a balloon dialog to point at a control inside of another form and
'   then show the dialog.  NOTE: both forms must share the same parent window
' Parameters:
'  frmDialog As Form  -- dialog to position and show
'  frmParent As Form -- parent form for both frmDialog and frmTarget
'  frmTarget As Form  -- form containing the control we need to point at
'  ctlTarget As Control -- control we are targeting
'
Sub ShowDialogAtCtlInForm (frmDialog As Form, frmParent As Form, frmTarget As Form, ctlTarget As Control)

    PositionFormAtCtlInForm frmDialog.Rgnwnd1, frmParent.hWnd, frmTarget, ctlTarget
    ShowDialog frmDialog

End Sub

Sub ShowDialogAtForm (frmDialog As Form, ByVal hwndParent As Integer, f As Form)
    PositionFormAtForm frmDialog.Rgnwnd1, hwndParent, f
    ShowDialog frmDialog
End Sub

'-----------------------------------------------------------------------
' Orient the dialog at position x,y,dx,dy
'
' Requires that the regional window control in your form is
' called rgnwnd1.
'
' NOTE: positions should are relative to the frmParent window
'
' The unload event for the parent form (NOT the dialog) should contain:
'
'   RgnWndUnload hWnd
'
'-----------------------------------------------------------------------
Sub ShowDialogAtPos (frmDialog As Form, frmParent As Form, ByVal x As Integer, ByVal y As Integer, ByVal dx As Integer, ByVal dy As Integer)
  frmDialog.Rgnwnd1.ObjectHeight = dy
  frmDialog.Rgnwnd1.ObjectWidth = dx
  frmDialog.Rgnwnd1.ObjectX = x
  frmDialog.Rgnwnd1.ObjectY = y
  frmDialog.Rgnwnd1.ParentHwnd = frmParent.hWnd
  frmDialog.Rgnwnd1.AutoPos = 1
  ShowDialog frmDialog
End Sub

'-----------------------------------------------------------------------
' Shows the Hint-O-Rama.
'
' Parameters:
'   tipID:            ID of the hint-o-rama master tip
'   tipidConfirm:     ID of modal tip used to confirm whether or not to turn off HOR
'   hwndParent:       Parent for HOR dialogs.
'-----------------------------------------------------------------------
Sub ShowHintORama (tipID As Integer, tipidConfirm As Integer, ByVal hwndParent As Integer)

    Dim t As Long

    On Error GoTo err_ShowHintORama

    t = gTipObject.ShowHintORama(tipID, tipidConfirm, hwndParent)

    Exit Sub

err_ShowHintORama:
    ' Check if gTipObject was not created or if
    ' tipID is an invalid tip.

    If Err = UERR_OLEOBJECTNOTSET Or Err = UERR_OLEAUTOMATION Or Err = UERR_TIP_E_INVALID Then
    UShowErrorTip hwndParent, UERR_GEN_BADSYSTEMSETUP, 0&
    Else
    UShowErrorTip hwndParent, Err, Error$
    End If

    Exit Sub

End Sub

' Purpose:
'   Determine if a given title already exists in the database
' Parameters:
'   toc As Object -- should be a Toc object obtained from gUTObject.GetToc()
'   stTitle As String -- string to search for
' Returns:
'  True if stTitle exists, False otherwise
' History:
'  04-20-94  dlevy  Created
Function TocTitleExists (toc As Object, stTitle As String) As Integer
    Dim enum As Object
    Dim item As Object

    toc.SetFilter tocTitle, tocCmpEql, stTitle
    Set enum = toc.GetItems
    toc.SetFilter -1, 0, 0  ' Clear filter again

    If enum Is Nothing Then
    TocTitleExists = False
    Exit Function
    End If

    ' Review: Mike said he will change the Toc service to return nil when
    ' the search comes up empty, when he does that, the following code will
    ' not be needed

    Set item = enum.VBNext
    If item Is Nothing Then
    TocTitleExists = False
    Exit Function
    End If

    TocTitleExists = True

End Function

'-----------------------------------------------------------------------
' Removes (and caches) a visible dialog that's been shown with
' ShowDialog or it's siblings.
'-----------------------------------------------------------------------
Sub UnshowDialog (dlg As Form)
    dlg.Rgnwnd1.Cached = True
End Sub

'-----------------------------------------------------------------------
' Removes a modeless tip after it has been displayed.  Use TIPID_ALL to
' remove all tips.
'-----------------------------------------------------------------------
Sub UnshowTip (tipID As Integer)

    Dim hr As Long

    On Error Resume Next
    hr = gTipObject.UnshowTip(tipID)

End Sub

'-----------------------------------------------------------------------
' Initialize the Utopia.bas module.
'
'
' NOTE:  This function loads gUTObject and gUtopiaInitObject,
' which will call UtopiaInitialize(). Therefore, if you open a
' database, you must do so before calling this function.
'
' 12-12-94 Shaula  changed to return UERR error code from utopia initialize
'-----------------------------------------------------------------------
Function UtopiaInit () As Integer

    frmMax = -1
    hCursor = 0
    gcDlgCache = CACHE_SIZE     ' initialise number of dlgs in cache

    ' Any premature exit is failure:
    UtopiaInit = 51 'UERR_INTERNAL

    ' seed random number generator used by rndm function
    Randomize

    ' Get the Utopia Installation Directory
    GetUtopiaDir

    ' Load the UT Object and the Utopia Init object.
    ' NOTE:  To improve startup performance, we may wish to load
    ' these objects on demand.  However, coding is much easier to
    ' assume they're loaded.

    Set gUTObject = Nothing
    If Not GetUtopiaObject() Then
    Exit Function
    End If

    On Error Resume Next
    Set gUtopiaInitObject = gUTObject.GetUtopiaInitObject()
    If gUtopiaInitObject Is Nothing Then
    UtopiaInit = UGetLastError()
    Exit Function
    End If

    ' look for a success code set

    UtopiaInit = UGetLastError()

End Function

'-----------------------------------------------------------------------
' Uninitialize the Utopia.bas module.
'
' CONSIDER:  Call this UtopiaUninitialize, and have it call the
' UtopiaUninitalize in UTOPIA.DLL.
'-----------------------------------------------------------------------
Sub UtopiaUnInit ()

    ' release tip object
    Set gTipObject = Nothing

    ' release Utopia objects
    Set gUtopiaInitObject = Nothing
    Set gUTObject = Nothing

    ' tell ole2 to freeup unused dlls
'    CoFreeUnusedLibraries

End Sub

Sub WaitCursor ()
    hCursor = SetCursor(LoadCursor(0, IDC_WAIT))
End Sub

