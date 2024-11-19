/////////////////////////////////////////////////////////////////////////////
// USTRING.H
//
// Utopia string definitions
//
// Perhaps future UString class
//
// History:
// 07-28-93 FordM       Created
/////////////////////////////////////////////////////////////////////////////


#ifndef __USTRING_H__
#define __USTRING_H__

#include <string.h>

STDAPI_(BOOL) FindString(LPCSTR pszSource, LPCSTR pszSearch);
STDAPI_(BOOL) NormalizeString(CString &s);
STDAPI_(void) CopyStrProp(char *pszDst, const char *pszSrc, long cchMax);

/////////////////////////////////////////////////////////////////////////////
//


#endif  // ifdef __USTRING_H__
