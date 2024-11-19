///////////////////////////////////////////////////////////////
//
// ULIB.H
//
///////////////////////////////////////////////////////////////
//
//    This header file provides common services and classes for
// constuction Utopia libraries.
//
///////////////////////////////////////////////////////////////

#ifndef __ULIB__
#define __ULIB__

class UtopiaDLL : public CWinApp {
private:
    friend class UtopiaLib;
    virtual BOOL InitInstance();
    virtual int ExitInstance();
};

extern UtopiaDLL ThisDLL;

class UtopiaLib {
protected:
    friend class UtopiaDLL;
    virtual BOOL InitInstance() = 0;
    virtual int ExitInstance() = 0;

    UtopiaLib(char FAR *libName, int initOrder);
    char FAR *m_libName;

    // Pass through to UtopiaDLL's EnableVBX for standalone DLLs.
    void EnableVBX() { ThisDLL.EnableVBX(); }
};

extern BOOL gfMergedDll;    // true iff linked as part of a merged DLL

// Resource id ranges of .libs. These ids can't collide.
//
//              Dialogs             Strings                 Bitmap              New base
//
// ABOOKSRV     110-134             1072-1083               104-107              9000
// SYSSRV       500-501             1026-1083                                   10000
// UIMAGE       none                none                                        11000
// ACTOR        none                none                                        12000
// UPICTURE     103-211             none                                        13000
// TIPPAGE      101-112             1500-1528                                   14000
// SYSDLG       100-111,500-505     225-234, 1012-1025, 2026-2027               15000
// UCC          105                 1272-1274, 21000-21004  112, 8070-8076      16000
// UTOBJECT     none                none                                        17000
// SHELLSRV     103-108, 609-643                                                18000
// SOBPACK      101-114             3-24                                        19000

// Initialization order definitions:  These macros define the order in which
// the various initialization routines are invoked from a merged DLL.  The
// libraries are init'ed in increasing numerical order.  Zero is first,
// one is second, etc.

#define SYSSRV_INIT_ORD         0
#define UIMAGE_INIT_ORD         1
#define ACTOR_INIT_ORD          2
#define UPICTURE_INIT_ORD       3
#define TIPPAGE_INIT_ORD        4
#define SYSDLG_INIT_ORD         5
#define UCC_INIT_ORD            6
#define UTOBJECT_INIT_ORD       7
#define SHELLSRV_INIT_ORD       8
#define SOBPACK_INIT_ORD        9
#define ABOOKSRV_INIT_ORD       10

#define MAXIMUM_INIT_ORDER  10


#endif //__ULIB__
