//---------------------------------------------------------------------------
// scanner.h
//---------------------------------------------------------------------------
// Copyright (c) 1993-1994, Microsoft Corporation
//                 All Rights Reserved
// Information Contained Herein Is Proprietary and Confidential.
//---------------------------------------------------------------------------
//
// Public header file for the Scanner lib code
//
//---------------------------------------------------------------------------
//
// Owner:  Ford Martin
//
// History:
// 08-04-94 FordM       Created.
//---------------------------------------------------------------------------

#ifndef __SCANNER_H_
#define __SCANNER_H_


// Prototypes

BOOL ScanInit();
void ScanTerminate();
void ScanLogon(BOOL fLogon);
void DoScan(BOOL fInit);

void ScannerCallBack(WPARAM wp, LPARAM lp);
#define PM_SCANNER      (WM_USER + 0x102)  

//---------------------------------------------------------------------------
#endif // __SCANNER_H__
