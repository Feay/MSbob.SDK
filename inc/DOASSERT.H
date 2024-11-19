//---------------------------------------------------------------------------
// doassert.h
//---------------------------------------------------------------------------
// Copyright (c) 1992-1993, Microsoft Corporation
//                 All Rights Reserved
// Information Contained Herein Is Proprietary and Confidential.
//---------------------------------------------------------------------------
// Contains assert .dll code
//
// Owner: mattsie
//
// History:
//  4/4/94     created.
//---------------------------------------------------------------------------


// our big boy
#ifdef __cplusplus
extern "C" {
#endif

int far pascal _export DoAssertSz(LPSTR szErr);
void far pascal _export SetAssertFilenameSz(LPSTR szfn);
void far pascal _export AssertTrap(int trapid, int action, FARPROC pfn);
int far pascal _export GetAssertSz(LPSTR sz, int cb);

#ifdef __cplusplus
}
#endif
