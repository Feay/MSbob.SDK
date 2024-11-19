//---------------------------------------------------------------------------
// udebug.cpp
//---------------------------------------------------------------------------
// Copyright (c) 1992-1993, Microsoft Corporation
//                 All Rights Reserved
// Information Contained Herein Is Proprietary and Confidential.
//---------------------------------------------------------------------------
// Contains assertion stuff.
//
// Owner: daviddow
// History:
//  2/32/93     created.
//---------------------------------------------------------------------------

#ifndef _udebug_defined
#define _udebug_defined

#undef ASSERT
#undef VERIFY 

enum SeverityLevel { slFatal, slError, slWarning, slTrace };

#ifdef _DEBUG
void PASCAL AssertProc(BOOL fCheck, SeverityLevel slSeverity, LPCSTR lpcstrFile, int iline, LPCSTR lpcstrError);
void PASCAL CloseApp(SeverityLevel slSeverity);

#define Assert(fCheck, slSev, lpstrError) \
    AssertProc(fCheck, slSev, __FILE__, __LINE__, lpstrError)
#define Verify(fCheck, slSev, lpstrError) \
    AssertProc(fCheck, slSev, __FILE__, __LINE__, lpstrError)
#else
#define Assert(fCheck, slSev, lpstrError) ;
#define Verify(fCheck, slSev, lpstrError) fCheck;
#endif      

#endif // _udebug_defined
