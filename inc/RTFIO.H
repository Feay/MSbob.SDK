/*****************************************************************************
*                                                                            *
*  RTF.H                                                                     *
*                                                                            *
*  Copyright (C) Microsoft Corporation 1990.                                 *
*  All Rights reserved.                                                      *
*                                                                            *
******************************************************************************
*                                                                            *
*  Module Intent                                                             *
*                                                                            *
*   Public header file for RTF parser.  Also requires rtftoken.h.               *
*                                                                            *
******************************************************************************
*                                                                            *
*  Testing Notes                                                             *
*
*   NOTE:  If you include stdio.h yourself, include it before you
* include rtf.h.
*
*                                                                            *
******************************************************************************
*                                                                            *
*  Current Owner:  Larry Powelson                                            *
*                                                                            *
******************************************************************************
*                                                                            *
*  Released by Development:  01/01/90                                        *
*                                                                            *
*****************************************************************************/

#ifndef _FILE_DEFINED
#undef NULL             /* NULL redefined in stdio.h */
#include <stdio.h>
#endif  /* _FILE_DEFINED */

/*****************************************************************************
*                                                                            *
*                               Defines                                      *
*                                                                            *
*****************************************************************************/

/* Miscellaneous constants */
#define cchFontNameMax    20
#define cfteIncr          10
#define ccteIncr          10

/* Maximum number of ungettable characters, without seeks */
#define cchUngetMax        5

/* FP of beginning of file. */
#define fpStartFile        0L

/*****************************************************************************
*                                                                            *
*                               Typedefs                                     *
*                                                                            *
*****************************************************************************/

/*   The file rtftoken.h enumerates the type TOK.  The symbols corresponding
 * to these tokens are defined in symbol.c.  */
#include <rtftoken.h>

/* Argument types. 
 */
typedef enum
  {
  artNone,        /* No argument */
  artInt,         /* Integer */
  artIgnore,      /* Ignore arguments */
  artString,      /* String */
  artFontTable,   /* Fonttable information */
  artHexnum,      /* Hexadecimal number, converted to artInt when parsed */
  artColorTable,  /* Color table information */
  artPict,        /* Picture (used internally) */
  artUnimplemented,/* Picture type unavailable with this version */
  artWbitmap,     /* Windows bitmap */
  artWmetafile,   /* Windows metafile */
  artMacpict,     /* Macintosh picture */
  artDIB,         /* device independent bitmap */

  /* The following are unimplemented and treated as artNone: */

  artTime,        /* Time, converted to time_t format */
  artStyles,      /* Stylesheet information */
  } ART;


/* Font table entry.
 */
typedef struct
  {
  INT   fid;                      /* Fond ID number */
  TOK   tokType;                  /* Font type (tokFroman, tokFswiss, etc) */
  char  szName[cchFontNameMax];   /* Font name */
  } FTE, * PFTE;


/* Font table.
 */
typedef struct
  {
  INT   cfte;             /* Number of font entries */
  FTE   rgfte[cfteIncr];  /* Variable length array of font entries. */
  } FNTBL;

#define CbSizeFntbl(cfte)  (sizeof(INT) + cfte * sizeof(FTE))

/* Color table entry.  Values of red, green, and blue are 0-255.
 *   Color number is the same as the index into the color table.
 */
typedef struct
  {
  unsigned char red, green, blue;
  } CTE;


/* Color table.
 */
typedef struct
  {
  INT ccte;             /* Number of color table entries */
  CTE rgcte[ccteIncr];  /* Variable length array of color table entries */
  } CTBL;

#define CbSizeCtbl(cfte)  (sizeof(INT) + cfte * sizeof(CTE))

/* Following definition copied here from src\bitmap\_bitmap.h. */
/* Doubleword RGB definition.  This is the same as RGBQUAD in
 * Windows 3.0, but we use our own definition for the sake of
 * Windows 2.X. */
typedef struct
  {
  BYTE rgbBlue, rgbGreen, rgbRed, rgbUnused;
  } FAR * QRGBQUAD;


/* Bitmap (from windows.h), with additional fields added for extra
 * information contained in RTF files.
 *
 * NOTE:  This structure is also used for metafiles, DIBs, and quickdraw
 * pictures.
 */
typedef struct 
  {
  short    bmType;          /* mm field for metafiles */
  short    bmWidth;         /* xExt field for metafiles */
  short    bmHeight;        /* yExt field for metafiles */
  short    bmWidthBytes;
  BYTE     bmPlanes;
  BYTE     bmBitsPixel;
  LPSTR    bmBits;

  /* Extra info: */
  long     lcbBits;         /* Size of bmBits field above */
  UINT     fSingle : 1;     /* Single border */
  UINT     fDouble : 1;     /* Double border */
  UINT     fThick  : 1;     /* Thick border */
  UINT     fShadow : 1;     /* Shadowed border */
  UINT     fDotted : 1;     /* Dotted border */
  UINT     fHairline : 1;   /* Hairline border */
  PT       ptGoal;          /* Desired width and height, in twips */
  PT       ptScale;         /* Scaling value, from 1 to 100 */
  RCT      rctCrop;         /* Cropping, in twips */

  /* Needed for DIBs: */
  DWORD    biClrUsed;       /* Number of colours used in image */ 
  DWORD    biClrImportant;  /* Number of important colours in image */
  QRGBQUAD qrgbquad;        /* Pointer to variable-length colour table */
    
  } RTF_BITMAP;

/* Argument value.  Union of all possible argument types.
 */
typedef union
  {
  INT num;

  /* The following arguments point to space allocated with malloc().  
   *   It is the responsibility of the application to free this space. */
  char * sz;             /* Pointer to a null terminated string. */
  FNTBL * pfntbl;        /* Pointer to font table */
  CTBL * pctbl;          /* Pointer to color table */
  RTF_BITMAP * pbitmap;  /* Pointer to Windows bitmap, with extra info. */

  /* Additional types not yet implemented */

  } ARG;            /* Token Argument */


/* Lexeme. 
 *   This structure is returned by LexFromPbuf(), and should contain
 * all the information read from the RTF file in a condensed, easily
 * accessed form.
 */
typedef struct
  {
  TOK tok;          /* Token identifier */
  ART art;          /* Type of argument */
  ARG arg;          /* Actual argument */
  } LEX, * PLEX;

/****************************************************************
*
*     Basic Implementation of an Interface to read the data
*     we need to parse.  This implementation is based on
*     C's file stream handling code
*
*     BUF functions assume that the stream was open by the caller,
*     and will be closed by the caller.
*
****************************************************************/

/****************************************************************
*
*     I/O types
*
****************************************************************/

/* BUF state.  Actually, it's a file position, as 
 * returned by ftell().  If any parsing state information 
 * gets added, it must go here, too. */
typedef long FP;

typedef struct _BUF BUF, *PBUF;

typedef BOOL	(PASCAL * PFN_FBufError)	(PBUF pbuf);
typedef BOOL	(PASCAL * PFN_FSeekFpBuf)	(int seek, long fpOffset, PBUF pbuf);
typedef FP		(PASCAL * PFN_FpTellBuf)	(PBUF pbuf);
typedef CHAR 	(PASCAL * PFN_ChGetBuf)	(PBUF pbuf);
typedef BOOL 	(PASCAL * PFN_FReadRgchBuf)(char *pbReadBuf, short cchRead, PBUF pbuf);

struct _BUF
    {
    FP fpLastToken;  /* File position of last token read, for ungetting */
    FP fpLastLexeme; /* File position of last lexeme read. */

    /* Character set */
    TOK tokCharacterSet;

    /* Unget stack */
    char rgchUnget[cchUngetMax];
    INT cchUnget;

    PFN_FBufError       FBufError;
    PFN_FSeekFpBuf      FSeekFpBuf;
    PFN_FpTellBuf       FpTellBuf;
    PFN_ChGetBuf		ChGetBuf;
    PFN_FReadRgchBuf    FReadRgchBuf;
    };

typedef struct
    {
#ifdef __cplusplus
	BUF buf;
#else
	BUF;
#endif
	
    FILE * pfile;
    } BUF_STM, *PBUF_STM;

void PASCAL DefineBufInterface(PBUF pbuf,
PFN_FBufError pfnFBufError,
PFN_FSeekFpBuf pfnFSeekFpBuf,
PFN_FpTellBuf pfnFpTellBuf,
PFN_ChGetBuf pfnChGetBuf,
PFN_FReadRgchBuf pfnFReadRgchBuf);

/*****************************************************************************
*                                                                            *
*                               Prototypes                                   *
*                                                                            *
*****************************************************************************/


/* Name:            BufOpenStream
 *
 * Arguments:       name of file
 *
 * Purpose:         Opens a buffer for parsing an RTF file.
 * 
 * Return value:    buffer to be used in future calls to the
 *                  RTF parser.
 */
BUF_STM PASCAL BufOpenStream (char * sz);


/* Name:            CloseBufStream
 *
 * Arguments:       Buffer successfully opened by BufOpenStream, above.
 *
 * Purpose:         Closes an input buffer and recovers the file handle.
 * 
 * Return value:    none.
 */
void PASCAL CloseBufStream(PBUF_STM pbuf);


/* Name:            LexFromPbuf
 *
 * Arguments:       Pointer to a valid buffer.
 *
 * Purpose:         Retrieves the next lexeme from the input buffer.
 * 
 * Return value:    A lexeme, describing what token was read, what
 *                  argument that token expects, and the value of the
 *                  argument read, or the default value for that token
 *                  if no argument was found.
 */
LEX PASCAL LexFromPbuf (PBUF pbuf);


/* Name:            UngetLexeme
 *
 * Arguments:       A pointer to a valid buffer.
 *
 * Purpose:         Puts the last lexeme read back on the input stream,
 *                  so that it will be retrieved again with the next
 *                  call to LexFromPbuf().
 * 
 * Return value:    none.
 *
 * Notes:           Only one lexeme may be put back on an input stream
 *                  at a time.
 */
void PASCAL UngetLexeme (PBUF pbuf);


/* Name:            FreeLexArg
 *
 * Arguments:       A pointer to a lexeme.
 *
 * Purpose:         Frees any memory that was allocated for the given
 *                  lexeme's argument.
 * 
 * Return value:    None.
 */
void PASCAL FreeLexArg (PLEX plex);

/* Name:            FMeta2Dib
 *
 * Arguments:       A metafile lexeme.
 *
 * Purpose:         If there is exactly one DIB in the metafile, it is
 *                  extracted.
 *
 * Return value:    fTrue if a DIB was extracted, metafile lexeme now a
 *                  DIB lexeme; fFalse otherwise.
 */
BOOL PASCAL FMeta2Dib( PLEX plex );


/* This macro will assert if LexFromPbuf() has been called without
 * calling FreeLexArg() on the returned lexeme.
 */
extern BOOL PASCAL fRTFBufferFree;
#define AssertRTFBufferFree()       AssertF( fRTFBufferFree == fTrue )


/******* REQUIRED MEMBER FUNCTIONS FOR ALL BUFF'S ******************/


/***************************************************************************
 * Name:            BOOL FBufError(PBUF pbuf)
 *
 * Arguments:       Buffer openned by BufOpenStream, above.
 *
 * Purpose:         Determines whether buffer was successfully opened and
 *                  is in a valid state from which to parse lexemes.  
 *                  Buffer may be in an invalid state due to serious I/O
 *                  error, or because it is not in RTF format.
 * 
 * Return value:    Boolean, fTrue if buffer is in an invalid state.
 */

#define FBufError(pbuf) (pbuf)->FBufError(pbuf)

/***************************************************************************
 *
 *   NAME: BOOL SeekFpBuf(int seek, long fpOffset, PBUF pbuf)
 -
 *  Purpose:
 *
 *  Move absolutely, or relatively, within a buffer.
 *
 *  seek, is either SEEK_CUR or SEEK_SET.  Seek CUR means to move relative
 *  to the current position.  SEEK_SET means to move absolutely in the file.
 *
 *  Returns fTrue is successful.
 *
 ***************************************************************************/


/***************************************************************************
 *
 -  Name:        FpTellBuf
 -
 *  Purpose:
 *
 *	Reveal the current file position.
 *
 ***************************************************************************/


/***************************************************************************
 *
 -  Name:        ChGetBuf
 -
 *  Purpose:
 *     Read a single character from the current position in the file.
 *
 ***************************************************************************/


/***************************************************************************
 *
 -  Name:        FReadRgchBuf
 -
 *  Purpose:
 *     Read cchRead characters from the current location in the stream.
 *
 *  Arguments:
 *    
 *  Read the characters into pbReadBuf.  Read up to cchRead characters.
 *  Return fTrue if we were able to read this many characters.
 *
 ***************************************************************************/

