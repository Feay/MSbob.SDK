//---------------------------------------------------------------------------
// image.h
//---------------------------------------------------------------------------
// Copyright (c) 1992-1993, Microsoft Corporation
//                 All Rights Reserved
// Information Contained Herein Is Proprietary and Confidential.
//---------------------------------------------------------------------------
//
// Module description
//
// Public header file for the IImage interface.
//
//---------------------------------------------------------------------------
//
// Owner:  Larry Powelson
//
//---------------------------------------------------------------------------

#ifndef __IMAGE_H__
#define __IMAGE_H__

#define IMAGE_E_DISCARDED    MAKE_SCODE(SEVERITY_ERROR,   FACILITY_ITF, 1)

typedef LPBITMAPINFOHEADER PDIB;
#define DibColors(pdib) ((RGBQUAD FAR *)((LPBYTE)(pdib) + (int)(pdib)->biSize))
#define DibPtr(pdib)    (LPVOID)(DibColors(pdib) + (UINT)(pdib)->biClrUsed)

#define crBalloon       RGB(255, 255, 220)
#define crTransparent   RGB(4, 4, 4)        // 2%, 2%, 2%
#define crShadow        RGB(2, 2, 2)        // 1%, 1%, 1%
#define crInfo          RGB(2, 255, 253)    // 1%, 100%, 99%
#define irgbTransparent 10


typedef struct pictinfo {
    HMETAFILE   hmf;              // Metafile handle
    RECT       bbox;              // Bounding rectange in MF units
    WORD      cxyPelsPerInch;     // Number of MF units per inch
} PICTINFO;

typedef PICTINFO FAR *PPICTINFO;


typedef struct {
    DWORD ff;
    int cx, cy;
    int cxDefault, cyDefault;
    void huge *pvDIBits;
    unsigned long cbDIBits;
    HMETAFILE hmf;
    int xOrg, yOrg, cxUntrans, cyUntrans, cxyPelsPerInch;
    RECT rcInfo;
    COLORREF crBackColor;
} IMAGEINFO, FAR* LPIMAGEINFO;

#define fImgCreateMask          0x0001  // Create device dependent mask bitmap
#define fImgCreateDDBitmap      0x0002  // Create device dependent bitmap (DDB)
#define fImgRetainMetaFile      0x0004
#define fImgDiscardable         0x0008
#define fImgClientOwner         0x0010  // For use with CreateImageFromDDB/MetaFile only
#define fImgCreateDIBitmap      0x0020  // Create device independent bitmap (DIB)
#define fImgTransparent         0x0040  // Forces fImgCreateMask if fImgCreateDDBitmap
#define fImgNotCached           0x0080  // Don't cache image in image cache
#define fImgUpdateCache         0x0100  // Image is new and hasn't been cached

// UNDONE:  Move these to UERROR.H:
#define IMAGE_E_INVALID        MAKE_SCODE(SEVERITY_ERROR,   FACILITY_ITF, 0)  // Invalid image file
#define IMAGE_E_ILLEGAL        MAKE_SCODE(SEVERITY_ERROR,   FACILITY_ITF, 1)  // Illegal operation

//---------------------------------------------------------------------------
//
// The IFile Interface
//
// This interface is only used for images.  Perhaps it should be renamed IImageFile.
// It abstracts the differences from reading images from DOS files, docfile streams,
// Jet databases, and possibly others.  The reason this is used instead of IStream
// is because we want Open() and Close() methods for DOS files so we don't have
// to leave the file open.
//
//---------------------------------------------------------------------------

#undef  INTERFACE
#define INTERFACE IFile

DECLARE_INTERFACE_(IFile, IUnknown)
{
    // *** IUnknown methods ***
    STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef) (THIS)  PURE;
    STDMETHOD_(ULONG,Release) (THIS) PURE;

    // *** IFile methods ***
    STDMETHOD_(ULONG,LcbSize) (THIS) PURE;
    STDMETHOD(Seek) (THIS_ LONG pos, WORD wOrigin) PURE;
    STDMETHOD(Read) (THIS_ VOID HUGEP *pv, ULONG lcb) PURE;

    STDMETHOD(Open) (THIS) PURE;
    STDMETHOD(Close) (THIS) PURE;

    STDMETHOD(Create) (THIS) PURE;
    STDMETHOD(Write) (THIS_ VOID HUGEP *pv, ULONG lcb) PURE;

    STDMETHOD(GetFilePath)(THIS_ LPSTR szFilePath, USHORT cbMax) PURE;
};

typedef IFile FAR* LPFILE;


//---------------------------------------------------------------------------
//
// The UImage Interface
//
//---------------------------------------------------------------------------

#undef  INTERFACE
#define INTERFACE   IImage

DECLARE_INTERFACE_(IImage, IUnknown)
{
    // *** IUnknown methods ***
    STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef) (THIS)  PURE;
    STDMETHOD_(ULONG,Release) (THIS) PURE;

    // *** UImage methods ***
    STDMETHOD(CompositeImage) (THIS_ IImage FAR* pimg, const RECT FAR* prc) PURE;
    STDMETHOD(Paint) (THIS_ HDC hdc, int x, int y, int cx, int cy,
            const RECT FAR* prcBounds) PURE;
    STDMETHOD(IsIntersecting) (THIS_ const POINT FAR* ppt) PURE;
    STDMETHOD(SetFlags) (THIS_ DWORD ff) PURE;
    STDMETHOD(SetBackColor) (THIS_ COLORREF crColor) PURE;
    STDMETHOD(SetSize) (THIS_ int cx, int cy) PURE;
    STDMETHOD(GetSize) (THIS_ POINT FAR* ppt) PURE;
    STDMETHOD(GetImageInfo) (THIS_ IMAGEINFO FAR* pimgi) PURE;
    STDMETHOD_(void, ReleaseImageInfo) (THIS) PURE;
    STDMETHOD(GetInfoRect)(THIS_ LPRECT prc, SHORT cx, SHORT cy) PURE;
    STDMETHOD(SetInfoRect)(THIS_ RECT rc) PURE;
    STDMETHOD(CopyTo)(THIS_ LPSTREAM pstream) PURE;
    STDMETHOD(SaveTo)(THIS_ LPFILE pfile) PURE;
    STDMETHOD(SetFile)(THIS_ LPFILE pfile) PURE;
    STDMETHOD(SetCacheFlags)(THIS_ DWORD ff) PURE;
};

typedef IImage FAR* LPIMAGE;

//---------------------------------------------------------------------------
//
// UImage Object Creation APIs
//
//---------------------------------------------------------------------------

STDAPI CreateImageFromFile(LPCSTR szFilename, DWORD ff, int cx, int cy,
        LPIMAGE FAR* ppimg);
STDAPI CreateImageFromStream(LPSTREAM pstream, LONG libOffset, DWORD lcbSize,
        DWORD ff, int cx, int cy, LPIMAGE FAR* ppimg);
STDAPI CreateImageFromResource(HINSTANCE hinst, LPCSTR szName, LPCSTR szType,
        DWORD ff, int cx, int cy, LPIMAGE FAR* ppimg);
STDAPI CreateImageFromDDB(HBITMAP hbm, DWORD ff, int cx, int cy,
        LPIMAGE FAR* ppimg);
STDAPI CreateImageFromDIB(PDIB pdib, DWORD ff, int cx, int cy,
        LPIMAGE FAR* ppimg);
STDAPI CreateImageFromMetaFile(LPMETAFILEPICT pmfp, DWORD ff, int cx, int cy,
        LPIMAGE FAR* ppimg);
STDAPI CreateImageFromPictInfo(PPICTINFO ppi, DWORD ff, int cx, int cy,
        LPIMAGE FAR* ppimg);
STDAPI CreateImageFromIFile(LPFILE pfile, DWORD ff, int cx, int cy,
        LPIMAGE FAR* ppimg);
STDAPI CreateImageFromIcon(HICON hicn, DWORD ff, LPIMAGE FAR *ppimg);
STDAPI CreateImage(DWORD ff, int cx, int cy, LPIMAGE FAR* ppimg);

STDAPI CreateIFileFromStream(LPSTREAM pstream, LONG libOffset, DWORD lcbSize,
        LPFILE FAR * ppfile);
  
STDAPI CreateImageFromDIBBits(LPVOID pvDIBBits, unsigned long cbDIBBits,
	DWORD ff, int cx, int cy, LPIMAGE FAR *ppimg);

// NOTE: See ipicture.h for CreateImageFromID

//---------------------------------------------------------------------------
//
// Stage (DIB) DC & related APIs
//
//---------------------------------------------------------------------------

STDAPI_(HDC) GetStageDC(BITMAPINFO **ppbmi, void huge **ppvBits);
STDAPI_(void) ReleaseStageDC();
STDAPI_(BOOL) TransparentDIBits(BITMAPINFO far *pBufferHeader,
        void huge *pBufferBits, const RECT *prcBounds, int nXOriginDest,
        int nYOriginDest, void const far *pBits,
        BITMAPINFO const far *pBitmapInfo, int TransparentColor);
STDAPI_(void) hmemset(void huge *pv, BYTE b, unsigned long cb);
STDAPI_(void) UStretchBlt(HDC hdcDst, int xDst, int yDst, int cxDst, int cyDst,
        HDC hdcSrc, int xSrc, int ySrc, int cxSrc, int cySrc);
STDAPI_(void) StretchTransparentDIBits(
    LPBITMAPINFOHEADER biDst,   //  --> BITMAPINFO of destination
    LPVOID  lpDst,          //  --> to destination bits
    int DstX,           //  Destination origin - x coordinate
    int DstY,           //  Destination origin - y coordinate
    int DstXE,          //  x extent of the BLT
    int DstYE,          //  y extent of the BLT
    LPBITMAPINFOHEADER biSrc,   //  --> BITMAPINFO of source
    LPVOID  lpSrc,          //  --> to source bits
    int SrcX,           //  Source origin - x coordinate
    int SrcY,           //  Source origin - y coordinate
    int SrcXE,          //  x extent of the BLT
    int SrcYE,           // y extent of the BLT
    char unsigned TransparentColor);        // transparent color
STDAPI_(void) CompositeViaStage(IImage *pimgDst, IImage *pimgSrc);
STDAPI ImageBlt(IImage *pimgDst, int xDst, int yDst,
        IImage *pimgSrc, int xSrc, int ySrc, BOOL fTransparent);


//---------------------------------------------------------------------------
//
// Universal Palette & related APIs
//
//---------------------------------------------------------------------------

STDAPI_(HPALETTE) GetUniversalPalette();
STDAPI_(BOOL) UPlayMetaFile(HDC hdc, HMETAFILE hmf, BOOL fMask);
STDAPI_(HBRUSH) CreateDitheredBrush(HDC hdc, COLORREF cr);

//---------------------------------------------------------------------------
//
// Graphic Import Filter Helpers
//
//---------------------------------------------------------------------------

STDAPI GetGraphicImportFilterString(LPSTR szFilters, USHORT cbMax);

//---------------------------------------------------------------------------
//
// Other useful routines
//
//---------------------------------------------------------------------------
BOOL FMemDC(HDC hdc);

#endif // !__IMAGE_H__
