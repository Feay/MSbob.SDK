//---------------------------------------------------------------------------
// uprefs.h
//---------------------------------------------------------------------------
// Copyright (c) 1993-1994, Microsoft Corporation
//                 All Rights Reserved
// Information Contained Herein Is Proprietary and Confidential.
//---------------------------------------------------------------------------
//
// Definition of user preferences class
//  UPrefs      - base class for saving user prefs
//
//---------------------------------------------------------------------------
//
// Owner:  Ford Martin
//
//
// History:
// 02-21-94 FordM       Created.
//---------------------------------------------------------------------------

#ifndef __UPREFS_H_
#define __UPREFS_H_


//---------------------------------------------------------------------------
// UPrefs class
//---------------------------------------------------------------------------

class UPrefs : public CObject
{
public:
    _export UPrefs(DBID idApp, DBID idUser);
    virtual _export ~UPrefs();

    void _export Init(DBID idApp, DBID idUser);

protected:
    BOOL _export Load(void *pvData, ULONG cbData);
    BOOL _export Save();

private:
    BOOL FindRecord();

protected:        
    DBID m_idApp;
    DBID m_idUser;
private:
    void *m_pvData;
    ULONG m_cbData;
    CTable *m_ptb;
};

//---------------------------------------------------------------------------
//
#endif // __UPREFS_H_
