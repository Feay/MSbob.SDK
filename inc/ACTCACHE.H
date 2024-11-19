//---------------------------------------------------------------------------
// actcache.h
//---------------------------------------------------------------------------
// Copyright (c) 1992-1993, Microsoft Corporation
//                 All Rights Reserved
// Information Contained Herein Is Proprietary and Confidential.
//---------------------------------------------------------------------------
//
// Module description 
//
//    This is a private header file for use by syssrv and actor ONLY.  
// The structure defined here is stored in the UTask structure, and 
// released when UTask is destroyed.  Syssrv also calls 
// IActorCache::ChangePersonalCharacter in every Utopia task when
// the personal character gets changed.  
//
// This file also contains constants used to remote IActor interfaces
// for the Utopia Guide.
//
//---------------------------------------------------------------------------
//
// Owner:  Larry Powelson
//
//---------------------------------------------------------------------------

#ifndef __ACTCACHE_H__
#define __ACTCACHE_H__   

#include <actor.h>

#define WM_GUIDEMETHOD      WM_USER

// Constants for remoting Guide.  To call a remote method, send the task's
// daemon window a message with msg = WM_GUIDEMETHOD, wParam = methodFoo, and
// lParam depending on wParam:
//
//     wParam            lParam
//   methodPlayAction    MAKELONG(action, wFlags)
//   methodGetAction     NULL
//   methodGetPhrase     &getPhraseData, where getPhraseData is in globally shared memory.

struct GETPHRASEDATA {
    PHRASE phrase;
    HANDLE hPhraseOut;   // Handle to terminated string allocated with GlobalAlloc
};                                                                                         



typedef enum 
{
    methodPlayAction = 1,
    methodGetAction,
    methodGetPhrase,
} GUIDEMETHOD;    

//--------------------------------------------------------------------------
// IActorCache Interface
// 

#undef  INTERFACE
#define INTERFACE   IActorCache

DECLARE_INTERFACE_(IActorCache, IUnknown)
{
    // *** IUnknown methods ***
    STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef) (THIS)  PURE;
    STDMETHOD_(ULONG,Release) (THIS) PURE;

    // *** IActorCache methods ***                                             

    STDMETHOD(OnActivateApp) (THIS_ BOOL fActive) PURE; 
    STDMETHOD_(LONG, DoGuideMethod) (THIS_ WORD method, LONG data) PURE;
};


#endif  // ifdef __ACTCACHE_H__
