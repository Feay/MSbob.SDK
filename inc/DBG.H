/////////////////////////////////////////////////////////////////////////////
// Debug.h
//
// WHAT IS IT?
// This file specifies an api that enhances mfc's diagnostic services.
//
// This api support Asserts with error levels and variable arguments.
// It also supports diagnostic output that is controlled by flags in
// an .ini file.  This allows you to adjust your debug output at run time
// and can sometimes help you find bugs without using codeview.
//
// HOW DO I USE IT?
//
// The debug code is available in the lib directory as debug.lib.  Link this
// into your code.  The source along with a sample file showing how to use
// this api are in the project \ehome\debug
//
// These are the main calls:
//
////////////////////////////////////////////////////////////////////////////
// Assert(BOOL fCheck, SeverityLevel slSeverity, LPCSTR szFormat, ...);
//
// Purpose:
//   Print out assert information, halt the program if necessary
//
// Parameters:
// BOOL fCheck -- the assert check goes here
// SeverityLevel slSeverity -- how serious is this assert
//      slFatal -- end program
//      slError -- ask user if they want to end program
//      slWarning -- warning information printed
//
// Note:
//   slError will generate a MessageBox asking you to continue or quit, but this will
//   only happen if you set the switch "PromptOnAssert" in the .ini file
//
// Example:
//   Assert(cCount >= cMax,slError,"overflow! cCount:%d >= cMax:%d",cCount,cMax);
//
/////////////////////////////////////////////////////////////////////////////
// CloseApp(SeverityLevel slSeverity)
//
// Purpose:
//   This provides a standard way to shut the program down
//
// Parameter:
// SeverityLevel slSeverity -- determines how harshly to shut the program down
//     slFatal -- calls AfxTerminate() which does a pretty abrupt abort()
//     slError -- tries to send a DestroyWindow message to the main program
//     other   -- same as slError
//
// Note:
//   This routine calls DebugBreak() before closing the program.
//
/////////////////////////////////////////////////////////////////////////////
// BOOL InitDebug(LPCSTR pszDebugFile, LPCSTR pszDebugSection)
//
// Purpose:
//   This specifies what .ini file and what section of the .ini to use.
//
// Parameters:
//   LPCSTR pszDebugFile -- .ini file to use.  If no file name is specified
//     the file used will be the app name with the extension ".ini".  Note
//     this assumes that the .ini file is in the same directory as the .exe file.
//     Otherwise, full path names are required
//     (eg. c:\ehome\\letter\\letter.ini).  Note the extra back slashes.
//
//   LPCSTR pszDebugSection -- section of the .ini file to use (eg. [ .. ] tag name).
//      Defaults to "Debug Flags"
//
// Return:
//   TRUE -- if debug output is enabled
//   FALSE -- if debug output is not enabled
//
//  Note:
//   This function has the side effect of turning on the MFC global
//   afxTraceEnabled flag.  No debug output occurs unless this flag is on.
//
/////////////////////////////////////////////////////////////////////////////
// void DebugLine(LPCSTR pszFlagName)
// void DebugLine(LPCSTR pszFlagName, LPCSTR pszFormat, ...)
// void Debug(LPCSTR pszFlagName)
// void Debug(LPCSTR pszFlagName, LPCSTR pszFormat, ...)
//
// Purpose:
//   These macros are used to output debug information.
//   DebugLine() puts a carriage return at the end and Debug() doesn't
//
// Parameters:
//   LPCSTR pszFlagName; -- This is the name of a tag in the .ini file.
//   LPCSTR format        -- This format is handed to wvsprintf()
//   ... other argments  -- Add arguments here as you would for wsprintf()
//
// Note:
//   Most flags should simply be the class name followed by the member name
//   (eg. "CStuff::DoIt").  If you use this convention it is possible to force all
//   members of a class to on by simply specifying the class name in the .ini file
//   (eg. CStuff=1 instead of CStuff::DoIt=1).  Note that this will only turn member
//   flags on, it is ignored if not present or off.
//
//   Also you can force DebugLine to output by setting pszFlagName to 0
//
// Example:
//    DebugLine("RandomClass::RandomFunct","This is a random value: %d",wRandomValue);
//
/////////////////////////////////////////////////////////////////////////////
// DebugDump(LPCSTR pszFlagName[,arg1 << arg2 ... << argn])
//
// Purpose:
//   This outputs to MFC's afxDump variable if the given flag is on
//
// Parameter:
//   LPCSTR pszFlagName -- flag to check
//
// Note:
//     C++ and MFC provide a mechanism to replace traditional printf style functions
//   for output. It involves over-riding the << operator to be "smart" about
//   the contents of any given object.  Please refer to the Diagnostics chapter
//   in the Class User's Guide for more information.
//     Although it takes some getting used to, it turns out that this form of
//   output is more powerful and flexible than the traditional
//   printf style.
//     Note that all of the arguments occur inside the DebugDump definition, this 
//   slightly unusual notation allows us to avoid having to laboriously put in
//   #ifdef _DEBUG .. #endif brackets around each and every DebugDump call.  Instead,
//   if you are compiling a retail version DebugDump simply resolves to nothing  
//     It probably would be a good idea if everyone used DebugDump whenever they have
//   arguments to dump.  Also, if you do go with this style of output, 
//   I would strongly suggest that you use DebugDump() instead
//   of writing directly to afxDump, because we may want to add some enhancements
//   to afxDump in the future.
//     As with the Debug macros, you can force output by setting pszFlagName to 0
//   You are responsible for putting your own carriage returns in with this one!
//
// Example:
//   CRect rBounds(0, 0, 10, 10);
//   DebugDump("RandomClass::RandomFunct", "This is really random: " << rBounds);
//
// WHAT ELSE SHOULD I KNOW?
//
// Please, only use the macros and functions defined above.
// Also, note that if _DEBUG is not defined the macros will be pre-processed
// out (this may require an extra pre-processing step). This removes the need to bracket
// each and every debug macro with #ifdef _DEFINE and #endif. But this only works
// if you have kept to just one line, otherwise you do have to bracket the debug
// code out.
//
// The best way to view debug output is to use the DBWin sample app provided in
// the Win3.1 SDK.
//
// For efficiency, the debug functions will only be called if the global MFC
// flag, afxTraceEnabled, is TRUE.  This flag is set in InitDebug().
// You can turn debugging off by putting the line DebugIsOn=0 into your
// .ini file.  This way if you don't want any debut output, you
// take only a very minimal performance hit.
//
// Internally, the debug code outputs to MFC's global afxDump.  This is a
// member of CDumpContext, which provides a handy way to dump out object info
// -- see the Diagnostics chapter in the Class Libraries User's Guide for a
// description.  The only problem with this is that afxDump will ONLY print
// to the screen or out to a file but not both.  Fortunately, the DBWin sample
// app allows you to save debug info to a file, so this alleviates the problem.
// Eventually, we might want to "fix" afxDump to support printing to both file
// and the screen at the same time.
//
// 
// History:
// 10-28-92 DLevy     Created
/////////////////////////////////////////////////////////////////////////////

#include "udebug.h"
#ifndef __DBG_H__
#define __DBG_H__

// defines

#ifdef _DEBUG

// global variables

extern LPCSTR gpszThisFile;
extern int gwThisLine;

// function prototypes

void DebugPrintLine(LPCSTR pszFlagName, LPCSTR pszFormat, ...);
void DebugPrintLine(LPCSTR pszFlagName);
void DebugPrint(LPCSTR pszFlagName, LPCSTR pszFormat, ...);
void DebugPrint(LPCSTR pszFlagName);

BOOL InitDebug(LPCSTR pszDebugFile = 0, LPCSTR pszDebugSection = "Debug Flags");
BOOL DebugIsFlagOn(LPCSTR pszFlagName);

// macros

#define DebugLine if (afxTraceEnabled) DebugPrintLine
#define Debug if (afxTraceEnabled) DebugPrint
#define DebugDump(pszFlag, Arguments) if (afxTraceEnabled && \
DebugIsFlagOn(pszFlag)) afxDump << pszFlag << " " << Arguments

#else

// Note this assumes the compiler is smart enough to recognize that this
// generates dead code -- and therefore the compiler ignores it
// unfortunately, it appears that the compiler will NOT generate an inline
// function for functions with a variable number of arguments...
void inline DebugLine(LPCSTR pszFlagName) {};
void inline DebugLine(LPCSTR pszFlagName, LPCSTR pszFormat, ...) {};
void inline Debug(LPCSTR pszFlagName) {};
void inline Debug(LPCSTR pszFlagName, LPCSTR pszFormat, ...) {};
void inline InitDebug(LPCSTR pszFile=0, LPCSTR pszSection=0) {};
void inline DebugIsFlagOn(LPCSTR pszFlagName);

#define DebugDump(pszFlag, Arguments) if (FALSE)
#endif


#endif // __DBG_H__
