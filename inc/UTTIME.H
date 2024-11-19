//////////////////////////////////////////////////////////////////////////////
// UTTIME.H
//
// UTime class - derived from CTime
// DATE conversion function prototypes
//
// History:
// 05-06-93 FordM       Created.
/////////////////////////////////////////////////////////////////////////////

#ifndef __UTTIME_H__
#define __UTTIME_H__ 

typedef double DATE;

// Date constants 

#define nSecPerDay 86400L

// CTime class time range

#define dateMin 25569.0     // Jan 1, 1970  00:00:00
#define dateMax 49709.999   // Feb 4, 2036  23:59:00

#define yyMin 1970
#define yyMax 2036
#define mmMax 2     // iff yy = yyMax
#define ddMax 4     // iff yy = yyMax and mm = mmMax

struct MINFO                // Month display info computed by GetMonthInfo
{
    int  nStartDay;         // Start day of month (Sun=1, Mon=2, etc)
    int  nDays;             // Number of days in the month
    int  nCalRows;          // Number of calendar rows needed
    BOOL fStartsSunday;     // True if Sunday is first day in calendar, else Monday
};

#ifdef __cplusplus

class UTime : public CTime    //time
{
public: 
    // Constructors
    
    _export UTime();
    _export UTime(const CTime& time);
    _export UTime(const UTime& time);
    _export UTime(time_t time);
    _export UTime(int yy, int mm, int dd, int hh, int mn, int ss);
    static UTime _export PASCAL GetCurrentTime();

    // Additional constructors
     
    _export UTime(const DATE& date);
    
    // Additional operators
    
    const UTime& _export operator=(const DATE& date);
    _export operator DATE () const;
    
    // Additional functions

    UTime _export DateOnly();
    void _export AddSeconds (long nSeconds);
    void _export AddMonths(int dMonths);
    void _export AddSemiMonths(int dSemiMonths);
    void _export SetDayOfMonth(int ddSet);
    void _export GetMonthInfo(MINFO *pminfo);
    void _export GetString(LPSTR pch, int istr);
    void _export FormatIntl(LPSTR pch, int ifmt = 1);
};

// GetString istr values

#define istrMonth       1
#define istrMedMonth    2
#define istrDay         4
#define istrMedDay      5
#define istrShortDay    6

// FormatIntl ifmt values

#define ifmtShortDate   1
#define ifmtLongDate    2

// uttime.cpp prototypes

DATE DateFromCTime(const CTime & time);
CTime CTimeFromDate(const DATE & date);
void EnsureDateRange(DATE & date);
BOOL IsDateInRange(DATE & date);
int GetCountrySetting();
BOOL _export IsLeapYear(int yy);
int _export GetMonthDays(int yy, int mm);
void _export GetDateString(LPSTR pch, int istr, int ival);

extern "C" {
#endif

// The UDS structure is taken from Access EB code

typedef struct
{
    int     yy;                 /* 100 - 9999 */
    int     mm;                 /*   1 - 12   */
    int     dd;                 /*   1 - 31   */
    int     hh;                 /*   0 - 23   */
    int     mn;                 /*   0 - 59   */
    int     ss;                 /*   0 - 59   */
    int     wkdy;               /*   1 - 7    */
    int     y;                  /*   1 - 366  */
} UDS;                          // Unpacked Date Structure
typedef UDS *PUDS;

// packdate.c function prototypes (EB functions)

BOOL FAR PASCAL PackDate(UDS *puds, double *fl, BOOL fValidDate);
BOOL FAR PASCAL UnpackDate(UDS *puds, double *fl);

#ifdef  __cplusplus
}
#endif


/////////////////////////////////////////////////////////////////////////////
//


#endif  // ifdef __UTTIME_H__
  
