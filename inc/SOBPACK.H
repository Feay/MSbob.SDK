
//---------------------------------------------------------------------------
// sobpack.h
//---------------------------------------------------------------------------
// Copyright (c) 1992-1993, Microsoft Corporation
//                 All Rights Reserved
// Information Contained Herein Is Proprietary and Confidential.
//---------------------------------------------------------------------------
//
// Owner:  Shaula Doyle
//
//---------------------------------------------------------------------------
#ifndef _SOBPACK_H_
#define _SOBPACK_H_

// VB-Event parameter macros (from MFC tech notes)

#define AFX_NUM_EVENTPARAM(type, lpParams) \
    (type FAR&)(**(type FAR* FAR*)lpParams)


STDAPI DoReminder(ULONG Alarm_Id);  //do clock reminder

//defined in init.cpp
//{{AFX_VBX_REGISTER()
	extern UINT NEAR VBN_CHANGE;
	extern UINT NEAR VBN_CLICK;
	extern UINT NEAR VBN_DATECLICK;
	extern UINT NEAR VBN_MONTHNAMECLICK;
	extern UINT NEAR VBN_SCROLL;
	extern UINT NEAR VBN_SPINNING;
//}}AFX_VBX_REGISTER
#endif // SOBPACK_H
