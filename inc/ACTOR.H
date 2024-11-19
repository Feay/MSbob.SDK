//-------------------------------------------------------------
//
// ACTOR.H
//
//-------------------------------------------------------------
//
//  This is a public utopia header file.
//
//-------------------------------------------------------------
//
//    This header file provides the APIs and abstract interfaces
// for using both Actors (aka characters, wizards) and Animations.
// In the future, animations may be broken out to a different
// project.
//
//-------------------------------------------------------------
//
//  Owner:  LarryPo
//
//-------------------------------------------------------------

#ifndef __ACTOR_H__
#define __ACTOR_H__

#include <uerror.h> 
#include <actions.h>

typedef WORD ACTION;
typedef WORD PHRASE;

//---------------------------------------------------------------------
//
// Predefined actions
//
//---------------------------------------------------------------------


#define actionShow          ((ACTION)  0)
#define actionStop          ((ACTION) -1) 
#define actionPause         ((ACTION) -2)   // Not implemented V1, same as actionStop
#define actionResume        ((ACTION) -3)

// Blank image

#define imageNil            ((IMAGE) -1)    
#define soundNil            ((SOUND) -1)


//----------------------------------------------------------
//
//  The Utopia Paint Message
//
//  This message is a special message registered by Utopia services to 
//  provide transparent windows.  In this message, wParam is the HDC to
//  draw into, while lParam points to the rectangle to draw.
//
//  NOTE:  The HDC is an offscreen DC that has its origin set using SetWindowOrg().
//  Therefore, the recipient of this paint message should not assume origin
//  of (0, 0) -- i.e., use OffsetWindowOrg() rather than SetWindowOrg().
//  Also, by convention the recipient should only draw itself, and not any
//  of its children.  Therefore, overlapping transparent windows are 
//  not supported.
//
//----------------------------------------------------------

#define szRegisteredPaint    "UtopiaPaint"

#define ON_REGISTERED_PAINT(nMessageVariable, memberFxn) \
    { 0xC000, 0, (UINT)(UINT NEAR*)(&nMessageVariable), \
        /*implied 'AfxSig_lwl'*/ \
        (AFX_PMSG)(AFX_PMSGW)(AFX_PMSGV2)(AFX_PMSGV)memberFxn },


// To use this message, you must first declare the following global variable:
//
// static const UINT NEAR nRegisteredPaint = RegisterWindowMessage(szRegisteredPaint); 
//
// To call this message, just call ::SendMessage(hwnd, nRegisteredPaint, hdc, lprect);
//
// To respond to this message with MFC, add the following function to your CWnd derived
// class:  
//
//    afx_msg LRESULT OnRegisteredPaint(HDC hdc, LPRECT lprect);
// 
// Then, add the following to your message map, after the //}}AFX_MSG_MAP line:
//
//    ON_REGISTERED_PAINT(nRegisteredPaint, OnRegisteredPaint)
//
//---------------------------------------------------------------------


// This is the name of the registered message that gets sent to all windows
// to indicate a change of character.  The message is sent once with wParam = FALSE
// to change the PC streams, and then again with wParam = TRUE to allow any windows
// to resnippettize their character strings.

#define rgchChangePC     "UtopiaChangePC" 

// Defined in crgn.cpp.  If you don't link with crgn.lib (or crgnd.lib), then you need
// to declare this yourself as follows:
// UINT NEAR REGMSG_CHANGEPC = RegisterWindowMessage(rgchChangePC);

extern UINT NEAR REGMSG_CHANGEPC;


////////////////
//
//  Animation Interfaces
//
////////////////

// Flags for IAnimation::PlayAction
#define fAsync          0x0000
#define fSync           0x0001      
#define fFirstImage     0x0002
#define fOnBackground   0x0004

// Actor Autosize parameter

typedef enum {
    AAS_NONE = 0, 
    AAS_PIXEL,
    AAS_DIALOG,
    AAS_SCREEN,
    AAS_GUIDE,
} ACTORAUTOSIZE;    


//--------------------------------------------------------------------------
// EnumACTION Interface

#undef  INTERFACE
#define INTERFACE   IEnumACTION

DECLARE_INTERFACE_(IEnumACTION, IUnknown)
{
    STDMETHOD(Next)(THIS_ ULONG celt, ACTION *prgv, ULONG FAR* pceltFetched)
            PURE;
    STDMETHOD(Skip)(THIS_ ULONG celt) PURE;
    STDMETHOD(Reset)(THIS) PURE;
    STDMETHOD(Clone)(THIS_ IEnumACTION FAR* FAR* ppenm) PURE;
};

//--------------------------------------------------------------------------
// IAnimation Interface

#undef INTERFACE
#define INTERFACE IAnimation

DECLARE_INTERFACE_(IAnimation, IUnknown)
{
    // *** IUnknown methods ***
    STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef) (THIS)  PURE;
    STDMETHOD_(ULONG,Release) (THIS) PURE;

    // *** IAnimation methods ***
    STDMETHOD(PlayAction) (THIS_ ACTION action, WORD wFlags) PURE;
    STDMETHOD_(WORD, GetAction) (THIS) PURE;
    STDMETHOD(DrawFrame) (THIS_ HDC hdc) PURE;
    STDMETHOD(SetRect) (THIS_ LPRECT prc, ACTORAUTOSIZE aas) PURE;
    STDMETHOD(GetRect) (THIS_ LPRECT prc) PURE;
    STDMETHOD(GetTextRect) (THIS_ LPRECT prc) PURE;
    STDMETHOD(IsIntersecting) (THIS_ const POINT FAR* ppt) PURE;
    STDMETHOD(EnumActions) (THIS_ IEnumACTION ** ppEnum) PURE;

};

typedef IAnimation FAR* LPANIMATION;

#undef INTERFACE
#define INTERFACE IAnimationSite

DECLARE_INTERFACE_(IAnimationSite, IUnknown)
{
    // *** IUnknown methods ***
    STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef) (THIS)  PURE;
    STDMETHOD_(ULONG,Release) (THIS) PURE;

    // *** IAnimationSite methods ***
    STDMETHOD(OnFrame) (THIS_ LPANIMATION pAnimation, LPCRECT prcPos) PURE;
    STDMETHOD(ActionFinished) (THIS_ LPANIMATION pAnimation) PURE;
};

typedef IAnimationSite FAR* LPANIMATIONSITE;


////////////////
//
//  Animation APIs
//
////////////////     

STDAPI OpenAnimation(LPCSTR szFilename, LPCSTR szAnim, LPANIMATIONSITE pAnimSite, 
        HWND hwnd, LPRECT lprc, ACTORAUTOSIZE aas, LPANIMATION FAR* ppAnimation);

//---------------------------------------------------------------------
//
//  Actor Interfaces
//
//  The following section describes the interfaces involved in using
//  actors.
//
//---------------------------------------------------------------------

//--------------------------
//
//  Types used in interfaces
//
//--------------------------

#undef INTERFACE
#define INTERFACE IActor

DECLARE_INTERFACE_(IActor, IAnimation)
{
    // *** IUnknown methods ***
    STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef) (THIS)  PURE;
    STDMETHOD_(ULONG,Release) (THIS) PURE;

    // *** IAnimation methods ***
    STDMETHOD(PlayAction) (THIS_ ACTION action, WORD wFlags) PURE;
    STDMETHOD_(WORD, GetAction) (THIS) PURE;
    STDMETHOD(DrawFrame) (THIS_ HDC hdc) PURE;
    STDMETHOD(SetRect) (THIS_ LPRECT prc, ACTORAUTOSIZE aas) PURE;
    STDMETHOD(GetRect) (THIS_ LPRECT prc) PURE;
    STDMETHOD(GetTextRect) (THIS_ LPRECT prc) PURE;
    STDMETHOD(IsIntersecting) (THIS_ const POINT FAR* ppt) PURE;
    STDMETHOD(EnumActions) (THIS_ IEnumACTION ** ppEnum) PURE;

    // *** IActor methods ***
    STDMETHOD(GetPhrase) (THIS_ PHRASE phrase, BSTR FAR* pbstrOut) PURE; 
    STDMETHOD(SetGuide) (THIS_ BOOL fSet, LPCRECT prc) PURE;
    STDMETHOD_(WORD, GetHelpfulness) (THIS) PURE;

};

typedef IActor FAR* LPACTOR;


////////////////
//
//  Actor APIs
//
////////////////

STDAPI OpenActor(LPCSTR szFilename, LPANIMATIONSITE pAnimSite, HWND hwnd,
        LPRECT lprc, ACTORAUTOSIZE aas, LPACTOR FAR* ppActor);

STDAPI ResolveSubphrases(LPACTOR pActor, LPCSTR szIn, BSTR FAR* pbstrOut);

STDAPI SetPersonalCharacter(LPCSTR szFilename);  

STDAPI GetGuide(LPACTOR FAR* ppActor, LPRECT prc);

STDAPI_(BOOL) FIsGuide(LPACTOR pActor);  

#define WaitUntilActionFinished(pActor) \
        ((pActor)->GetAction() != actionIdle ? (pActor)->PlayAction(actionResume, fSync) : NOERROR)


////////////////
//
//  Parsing APIs
//
////////////////

// szIn is a null terminated string.  szOut should point to a buffer at least
// as big as the string in szIn.  Note that szOut may contain embedded null characters
// that do not signify the end of the string; therefore, you must use *pcchOut for
// the size of the string returned in szOut.

STDAPI ParseSubphrases(LPCSTR szIn, BSTR FAR* pbstrOut); 


// Internal APIs
//
// These functions are not exported and should not be called by anyone outside of utopia.dll

WORD PCHelpfulness();
void UpdatePC();


//---------------------------------------------------------------------
//
//  The Actor File Format
//
//  The following sections contain structures used in the Actor File Format.
//
//---------------------------------------------------------------------


#define wMagicActor     0x504C
#define wVerMaj1        1
#define wVerMin0        0

struct FLATACTORDIRHEADER {
    WORD wMagic;
    WORD wVerMaj;
    WORD wVerMin;
    WORD cFiles;
    WORD cbFileDir;
};

// cFiles + 1 array of lcbStart (rglcbStart[cFiles] = lcbEnd)

// cbFileDir bytes of file names

// Additional info for later versions

typedef enum {
    atPC = 1,
    atSpecialist,
    atButtonSingle,
    atButtonDouble,
    atSOB,
    atAnimation,
} ANIMTYPE;    
    
    
typedef WORD IMAGE;
typedef WORD SOUND;

typedef enum {
    sexFemale = 1,
    sexMale,
    sexIndeterminate
} SEX;


struct FLATACTORHEADER { 
    WORD wVersion;
    ANIMTYPE at;
    IMAGE imageShow;
    ACTION actionDefault;
    POINT ptSizeTwips;
    POINT ptSizePixels;
    POINT ptPercentScreen; 
    
    WORD wHelpfulness;
    SEX sex;
    RECT rcIntro;
    IMAGE imageBackground; 
    
    WORD cxStart;
    WORD cxTile;
    
    // Offsets relative to beginning of this structure
    
    ULONG lcbImages;
    ULONG lcbImageDir;
    ULONG lcbSounds;
    ULONG lcbSoundDir;
    ULONG lcbAnims;
    ULONG lcbAnimDir; 
    
    ULONG lcbPhrases;
    ULONG lcbPhraseDir;
};        



//-------------------------------
//
//  Phrase and Action directory formats
//
//
//  The Phrase and Action Directories both start with a DIRHEADER structure,
//  giving the the count of phrase or action id values.  This
//  is followed by an array of DIRINFO structures, one for each phrase or
//  action id value.  The DIRINFO structure gives the phrase or action id
//  value, the number of definitions for that id, and the cumulative number
//  of definitions for all previous id values.  After these structures is
//  an array of DIRPTR structures, one per phrase or action definition, giving
//  the size of that definition, and its offset into the phrase or action
//  file.
//
//  The formula for determining the offset to the DIRPTR for the first definition
//  of a phrase or action id, given the DIRINFO structure, is:
//
//       sizeof(DIRHEADER) + sizeof(DIRINFO) * DIRHEADER.cIdMac +
//                  sizeof(DIRPTR) * DIRINFO.cDirPtr;
//
//-------------------------------


typedef struct {
    WORD cIdMac;
    WORD reserved;      // Must be 0
} DIRHEADER;

typedef struct {
    WORD id;
    WORD cDefs;
    WORD cDirPtr;
} DIRINFO;

typedef struct {
    DWORD libOffset;
    WORD cbSize;
} DIRPTR;


//---------------------------------------------------------------------
//
//  The Animation File Format
//
//  The following sections contain structures used in the Animation File Format
//
//---------------------------------------------------------------------


// The format of an animation in the animation data file consists of
//
//    ANIMDATA
//       ANIMEVENT[animdata.cEventMac]

// Animation event types

#define eventImage      0
#define eventBranch     1
#define eventSound      2


// Animation event record

#define wVersionAnim1      (0x100)


typedef struct {
    WORD  eventType;

    //WORD  w1;      //   Duration      Destination     Sound number
    //WORD  w2;      //   Offset        Probability     volume/rate

    union {
        // Image event:
        struct {
            IMAGE image;
            WORD wDuration;
        };
        // Branch event:
        struct {
            WORD iEventDest;
            WORD wProbability;
        };
        // Sound event:
        struct {
            SOUND sound;
            BYTE bVolume;
            BYTE bRate;
        };
    };

} ANIMEVENT, FAR* LPANIMEVENT;

typedef struct {
    WORD        wVersion;
    WORD        cEventMac;
    ANIMEVENT   rgAnimEvent[1];
} ANIMDATA, FAR* LPANIMDATA;


// Frame part data:

#define typeImageParts      0x14

typedef struct {
    WORD        image;
    RECT        rect;
} PARTINFO, FAR* LPPARTINFO;

typedef struct {
    WORD        wType;      // Indicates image is composed of other images
    WORD        cImageMac;
    PARTINFO    rgPartInfo[1];
} PARTDATA, FAR* LPPARTDATA;

//-------------------------------
//
//  szPhrases format
//
//-------------------------------

//
//  Subphrase Tokens
//

typedef enum {
    sptPhrase = 1,
    sptPhrasePC,
    sptPhraseUser,
    sptSexUser,
    sptSexPC,
    sptAgeUser,
    sptLevelUser,
    sptTime,  
    sptEscape,
    sptMax = 0x1F,
} SPT;


// Data for subphrase tokens:

#pragma pack(1)

struct SPDATAESCAPE {
    BYTE spt;
    char ch;
};

struct SPDATAPHRASE {
    BYTE spt;
    WORD cbData;
    PHRASE phrase;
};

struct SPDATAGENDER { 
    BYTE spt;
    WORD cbData;
    WORD rgich[4];
};
    
struct BND {
    WORD bound;       // Age or time boundary
    WORD ich;         // Index to phrase, as byte offset from start of SPDATA structure
};

struct SPDATABOUND {
    BYTE spt;
    WORD cbData;
    WORD cbnd;
    BND rgbnd[1]; 
};           

struct SPDATA {  
    BYTE spt;
    WORD cbData;  
    union {  
        PHRASE phrase;   // Phrase ID for sptPhrase, sptPhrasePC, or sptPhraseUser
        WORD rgich[4];   // Indexes to phrases, as byte offsets from start of SPDATA structure. 
                         // This is followed by the phrases themselves.
        struct {
            WORD cbnd;   // Number of age or time boundaries for sptAgeUser or sptTime
            BND rgbnd[1];
        }; 
        struct {
            WORD cchDefault;      // Default phrase when unknown in V1.
            char rgchDefault[1];
        };    
    };
}; 

#pragma pack()               


#endif // __ACTOR_H__

