//---------------------------------------------------------------------------
// ipicture.h
//---------------------------------------------------------------------------
// Copyright (c) 1992-1993, Microsoft Corporation
//                 All Rights Reserved
// Information Contained Herein Is Proprietary and Confidential.
//---------------------------------------------------------------------------
//
// Module description
//
//
//---------------------------------------------------------------------------
//
// Owner:  Gustav Jansson
//
//---------------------------------------------------------------------------

#ifndef __IPICTURE_H__
#define __IPICTURE_H__

#include <image.h>

//---------------------------------------------------------------------------
//
// Constants
//
//---------------------------------------------------------------------------

#define MAXSUBATTRIBUTE 32
#define MAXPATH         256
#define MAX_ENUM_PIC_ATTRIBUTES 6

#define CX_THUMBNAIL 64
#define CY_THUMBNAIL 64

//---------------------------------------------------------------------------
//
// IEnumID
//
//---------------------------------------------------------------------------

#undef  INTERFACE
#define INTERFACE IEnumID

DECLARE_INTERFACE_(IEnumID, IUnknown)
{
    STDMETHOD(Next)(THIS_ ULONG celt, ULONG *prgID, ULONG FAR* pceltFetched) PURE;
    STDMETHOD(Skip)(THIS_ ULONG celt) PURE;
    STDMETHOD(Reset)(THIS) PURE;
    STDMETHOD(Clone)(THIS_ IEnumID FAR* FAR* ppEnumID) PURE;
};

#undef  INTERFACE
#define INTERFACE IPicMgrClientSite

DECLARE_INTERFACE_(IPicMgrClientSite, IUnknown)
{
    // *** IPicMgrClientSite methods ***
    STDMETHOD_(HWND,GetParent)(THIS) PURE;
    STDMETHOD_(void,SetCategoryID)(THIS_ ULONG idPic) PURE;
    STDMETHOD_(void,SetPictureID)(THIS_ ULONG idPic) PURE;
    STDMETHOD_(void,OnClosePicMgr)(THIS_ BOOL fSave) PURE;
};

typedef IPicMgrClientSite FAR *PPicMgrClientSite;

#undef  INTERFACE
#define INTERFACE IPicOleObjDisp

DECLARE_INTERFACE(IPicOleObjDisp)
  {
    // *** IPicOleObjDisp methods ***
    STDMETHOD_(void,SetPictureID)(THIS_ ULONG idPic) PURE;
    STDMETHOD_(ULONG,GetPictureID)(THIS) PURE;
    STDMETHOD_(void,SetCategoryID)(THIS_ ULONG idCat) PURE;
    STDMETHOD_(ULONG,GetCategoryID)(THIS) PURE;
    STDMETHOD_(void,SetCategory)(THIS_ BSTR szCat) PURE;
    STDMETHOD_(BSTR,GetCategory)(THIS) PURE;
    STDMETHOD_(void,SetOriginalHeight)(THIS_ ULONG cy) PURE;
    STDMETHOD_(ULONG,GetOriginalHeight)(THIS) PURE;
    STDMETHOD_(void,SetOriginalWidth)(THIS_ ULONG cx) PURE;
    STDMETHOD_(ULONG,GetOriginalWidth)(THIS) PURE;
  };

//---------------------------------------------------------------------------
//
// IPictureServer interface
//
//---------------------------------------------------------------------------

const ULONG fPicLocked      = 0x0001;
const ULONG fPicKeepAsFile  = 0x0002;
const ULONG fPicAnimation   = 0x0004;
const ULONG fPicOptimize    = 0x0010;  //requires DLLs we won't ship

#undef  INTERFACE
#define INTERFACE IPictureServer

DECLARE_INTERFACE_(IPictureServer, IUnknown)
{
    // *** IUnknown methods ***
    STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef) (THIS)  PURE;
    STDMETHOD_(ULONG,Release) (THIS) PURE;

    // *** IPictureServer methods ***

    // Picture Store Methods
    STDMETHOD(AddNewPicture) (THIS_ LPSTR szDescription, LPSTR szFilename,
            ULONG *pidPic, ULONG ff) PURE;
    STDMETHOD(DeletePicture) (THIS_ ULONG idPic) PURE;
    STDMETHOD(GetPictureIFile) (THIS_ ULONG idPic, IFile FAR* FAR*ppifile) PURE;
    STDMETHOD(GetPictureIImage) (THIS_ ULONG idPic, DWORD flags, int cx, int cy,
                            LPIMAGE FAR* ppImage) PURE;
    STDMETHOD(GetPictureDescription) (THIS_ ULONG idPic, LPSTR rgchBuf,
            int cbMax) PURE;
    STDMETHOD(GetPicturePath) (THIS_ ULONG idPic, LPSTR rgchBuf, int cbMax) PURE;
    STDMETHOD(GetThumbnail) (THIS_ ULONG idPic, LPIMAGE FAR * ppImage) PURE;
    STDMETHOD(GetAnimationPath) (THIS_ ULONG idPic, LPSTR rgchBuf, int cbMax) PURE;

    STDMETHOD(GetPictureFlags) (THIS_ ULONG idPic, ULONG *pff) PURE;
    STDMETHOD(SetPictureFlags) (THIS_ ULONG idPic, ULONG ff) PURE;

    // Picture-Attribtue methods
    STDMETHOD(AddAttribute) (THIS_ ULONG idPic, LPSTR szAttribute) PURE;
    STDMETHOD(AddAttributeID) (THIS_ ULONG idPic, ULONG idAttribute) PURE;
    STDMETHOD(RemoveAttributeID) (THIS_ ULONG idPic, ULONG idAttribute) PURE;
    STDMETHOD(RemoveAttributeIDFromAllPics)(ULONG idAttr) PURE;

    STDMETHOD(EnumPicAttributes) (THIS_ ULONG idPic,
            IEnumID FAR* FAR* ppEnumAttributes) PURE;
    // NOTE: EnumPicAttributes list ALL attributes.  This is NOT same as passing 0 for idParent in
    // EnumPicAttributesOfParent.  That would only enumerate root attributes that the pictures has.
    // UNDONE Clarify in documentation.
    STDMETHOD(EnumPicAttributesOfParent) (THIS_ ULONG idPic,
            ULONG idAttributeParent, IEnumID FAR* FAR* ppEnumAttributes) PURE;

    STDMETHOD(CopyAttributes) (THIS_ ULONG idPicSource, ULONG idPicDest) PURE;

    // Attribute Management methods
    STDMETHOD(GetAttributeID) (THIS_ ULONG idAttributeParent,
            LPSTR szAttribute, ULONG *pidAttribute, BOOL fCreate) PURE;
    STDMETHOD(GetAttributeIDFromPath) (THIS_ LPSTR AttributePath,
            ULONG *pidAttribute, BOOL fCreate) PURE;

    STDMETHOD(GetAttributeParent) (THIS_ ULONG idAttribute,
            ULONG *pidAttributeParent) PURE;

    STDMETHOD(GetSubattributeText) (THIS_ ULONG idAttribute, LPSTR rgchBuf,
            int cbMax) PURE;
    STDMETHOD(GetAttributeText) (THIS_ ULONG idAttribute, LPSTR rgchBuf,
            int cbMax) PURE;
    STDMETHOD(DeleteAttribute)(ULONG idAttr) PURE;

    STDMETHOD(EnumAttributes) (THIS_ ULONG idAttributeParent,
            IEnumID FAR* FAR* ppEnumAttributes) PURE;

    // Picture enumeration methods
    STDMETHOD(EnumPicsWithAttributes) (THIS_ IEnumID FAR* FAR* ppEnumPictures,
            const int cAttributes, const ULONG FAR * rgAttributes) PURE;
    
    // Picture Manager methods
    STDMETHOD(OpenPicMgr)(THIS_ PPicMgrClientSite pPicMgrClientSite,
            ULONG idCat, ULONG idPic) PURE;
};

STDAPI OpenPictureServer(IPictureServer FAR* FAR* ppPicServer);

STDAPI CreateImageFromID(DWORD imageID, DWORD ff, int cx, int cy,
        LPIMAGE FAR* ppimg);

STDAPI MetaOptimize(char *lpszSrcFile, char *lpszDestFile);


//---------------------------------------------------------------------------
//
// IPictureServer errors
//
//---------------------------------------------------------------------------

#define PIC_E_INVALIDPICID          MAKE_SCODE(SEVERITY_ERROR, FACILITY_ITF, 1)

#define PIC_E_ATTRIBUTE_NOT_FOUND   MAKE_SCODE(SEVERITY_ERROR, FACILITY_ITF, 2)

#define PIC_E_DATABASE_ERROR        MAKE_SCODE(SEVERITY_ERROR, FACILITY_ITF, 3)

#define PIC_E_FILE_NOT_FOUND        MAKE_SCODE(SEVERITY_ERROR, FACILITY_ITF, 4)

#define PIC_E_NOTDELETABLE          MAKE_SCODE(SEVERITY_ERROR, FACILITY_ITF, 5)

#endif  // ifdef __IPICTURE_H__
