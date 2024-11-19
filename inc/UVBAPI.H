//---------------------------------------------------------------------------
// uvbapi.h
//---------------------------------------------------------------------------
// Copyright (c) 1992-1993, Microsoft Corporation
//                 All Rights Reserved
// Information Contained Herein Is Proprietary and Confidential.
//---------------------------------------------------------------------------
//
// Module description     
//
//   This header file describes the VBXEntry structure, which should be
// placed in the VBINITCC and custom control procedure of any control that
// wishes to be usable from a DLL.
//
//---------------------------------------------------------------------------
//
// Owner:  Larry Powelson
//                                 
//---------------------------------------------------------------------------

#ifndef __UVBAPI_H__
#define __UVBAPI_H__   

extern "C" LPVOID __cdecl g_lpfnApiVectorCur;
extern "C" struct VBXEntry * __cdecl g_pveCur;

extern "C" LPVOID PASCAL GetVBApiVector(void);

struct VBXEntry {
    VBXEntry()
    {
        // Init the new vector.
        if (s_lpfnApiVector) {
            m_lpfnApiVector = s_lpfnApiVector;
            s_lpfnApiVector = NULL;
        } else
            m_lpfnApiVector = *(LPVOID __based(__segname("_STACK")) *)0x20;

	Push();
    }

    VBXEntry(LPVOID lpfnApiVector)
    {
        // Init the new vector.
        m_lpfnApiVector = lpfnApiVector;

	Push();
    }
    
    ~VBXEntry()
    {
	Pop();
    }

    void Push(void)
    {
	VBXEntry *& pveCur = (VBXEntry *& ) s_mapve[(WORD)(__segment) this];
#ifdef _DEBUG
	int dummy;
	Assert(((__segment) this == (__segment) &dummy),slError,
	    "VBXEntry should only be used as a local variable");
#endif

	// Push last VBXEntry and make this one the top of the stack.
        m_pveLast = pveCur;
	pveCur = this;

	// Init the cache used by ApiVector in \uvbapi\vbapilib.asm
	g_pveCur = this;
	g_lpfnApiVectorCur = m_lpfnApiVector;
    }

    void Pop(void)
    {
	// Init the cache used by ApiVector in \uvbapi\vbapilib.asm
	g_pveCur = m_pveLast;
	g_lpfnApiVectorCur = g_pveCur ? g_pveCur->m_lpfnApiVector : NULL;

        // restore api vector to its original contents
	s_mapve[(WORD)(__segment) this] = m_pveLast;
    }

    friend LPVOID PASCAL GetVBApiVector(void);

    LPVOID GetApiVector(void)
    {
	return m_lpfnApiVector;
    }

#if 0
    static LPVOID GetCurApiVector(void);
#endif

private:
    LPVOID m_lpfnApiVector;
    VBXEntry *m_pveLast;

    static CMapWordToPtr s_mapve;
public:    
    static LPVOID s_lpfnApiVector;
}; 

extern "C" VOID FAR PASCAL _export VBSETAPIENTRY(LPVOID lpfnApiVector);  

// Use this macro to call any function that contains a VBXEntry variable
// from another function in your VBX:

#define CallVbxEntry(x)  \
    VBSETAPIENTRY(g_pveCur->GetApiVector()), x

#endif // __UVBAPI_H__

