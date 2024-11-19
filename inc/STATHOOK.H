/*----------------------------------------------------------------------------*\
|   hook.h	- Windows message spy application			       |
|									       |
|   History:								       |
|       01/01/87 toddla     Created                                            |
|       04/14/87 toddla     Cleaned up                                         |
|       04/14/87 thomasf    Added STAT! timing functionality                   |
|									       |
\*----------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif

#define HM_WINNOTIFY  (WM_USER+20)
#define HM_HOOKNOTIFY (WM_USER+42)

/* reversed MSG minus time and pt */
typedef struct {
    LONG lParam;
    WORD wParam;
    WORD message;
    HWND hwnd;
} MSGR;
typedef MSGR *PMSGR;
typedef MSGR FAR *LPMSGR;

/*
 *  Hook flags used in the SetSpyWindow() and SetSpyHook() calls
 */
#define HF_SYNC     0x0001
#define HF_NOSYNC   0x0000

#define HWND_ALL    1

BOOL  FAR PASCAL  LogMsg(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
BOOL  FAR PASCAL  ReadMsgLog(LPMSGR lpMsg, LPDWORD lpTime);
BOOL  FAR PASCAL  SetStatTask(HTASK htskStat, HWND hwndNotify, WORD f);
BOOL  FAR PASCAL  UnSetStatTask(HTASK htskStat, HWND hwndNotify);
BOOL  FAR PASCAL  ClearMsgLog(void);
BOOL  FAR PASCAL  RewindMsgLog(void);

#define HM_BEGIN_EVENT	(WM_USER+0x7000)
#define HM_END_EVENT	(WM_USER+0x7001)

#ifdef __cplusplus
}
#endif


