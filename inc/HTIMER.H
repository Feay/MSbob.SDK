//---------------------------------------------------------------------------
// htimer.h
//---------------------------------------------------------------------------
// Copyright (c) 1992-1993, Microsoft Corporation
//                 All Rights Reserved
// Information Contained Herein Is Proprietary and Confidential.
//---------------------------------------------------------------------------
//
// Module description 
//
//    This is the public header file for high fidelity timing services.
//
//---------------------------------------------------------------------------
//
// Owner:  Ford Martin
//
// History:
// 04-15-94 FordM       Created.
//---------------------------------------------------------------------------

#ifndef __PUBHTIMER_H__
#define __PUBHTIMER_H__


// Declare these here so they can be defined in any order.

struct ITimer;
struct ITimerSink;
typedef ITimer FAR* LPTIMER;
typedef ITimerSink FAR* LPTIMERSINK;

//--------------------------------------------------------------------------
// ITimer Interface
// 

#undef  INTERFACE
#define INTERFACE   ITimer

DECLARE_INTERFACE_(ITimer, IUnknown)
{
    // *** IUnknown methods ***
    STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef) (THIS)  PURE;
    STDMETHOD_(ULONG,Release) (THIS) PURE;

    // *** ITimer methods ***                                             

    STDMETHOD_(void, OnTimer) (THIS_ DWORD dwTime) PURE;
    STDMETHOD(SetTimer) (THIS_ DWORD time, DWORD timeRepeat, DWORD lData, 
            DWORD * pid, LPTIMERSINK pTimerSink) PURE;
    STDMETHOD(KillTimer) (THIS_ DWORD id) PURE; 
    STDMETHOD_(void, RemoveTimerSink) (THIS_ LPTIMERSINK pTimerSink) PURE;
};


//--------------------------------------------------------------------------
// ITimerSink Interface

#undef  INTERFACE
#define INTERFACE   ITimerSink

DECLARE_INTERFACE_(ITimerSink, IUnknown)
{
    // *** IUnknown methods ***
    STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef) (THIS)  PURE;
    STDMETHOD_(ULONG,Release) (THIS) PURE;

    // *** ITimerSink methods ***                                             
    STDMETHOD_(void, OnTimer) (THIS_ DWORD lData) PURE;
};

//--------------------------------------------------------------------------
// Object retrieval API

STDAPI GetTimer(LPTIMER *ppTimer);


//--------------------------------------------------------------------------

#define idHTmrNil       ((DWORD) 0)
#define dwTimeMin       14  // Maximum expected latency

//--------------------------------------
//
//  Helper macro
//
//--------------------------------------

#define FTimeIsGreater(t1, t2)   ((long)((DWORD) (t1) - (DWORD) (t2)) > 0)


#endif  // ifdef __PUBHTIMER_H__
