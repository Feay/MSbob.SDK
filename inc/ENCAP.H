//---------------------------------------------------------------------------
//  encap.h
//---------------------------------------------------------------------------
//  Copyright (c) 1993, Microsoft Corporation.  All Rights Reserved
//  Information Contained Herein Is Proprietary and Confidential.
//---------------------------------------------------------------------------
//
//  internal definitions for Workgroup Mail attributes.
//  for more detailed information see the MAPI documentation
//  on Transport Neutral Encapsulation (WinMail.DAT) version 1.0 Spec.
//
//  Owner: scotts
//
//  History:
//  06-17-93 scotts     Created.
//---------------------------------------------------------------------------


//
//  !!!! NOTE !!!!
//
//  the definitions below are copied from the WinMail.DAT spec document
//  and should be replaced by the actual "released" MAPI include files
//  either when we move to MAPI support or when such files are available
//

// MAPI (WORGROUP) Encapsulation Format Structures for WinMail.DAT
#define kWMSignature            0x223E9F78      // winmail.dat signature
#define kWMMessAttrib           1               // attribute is for message
#define kWMAttachAttrib         2               // attribute is for attachment
#define kcbWMAttrib             9               // size of attribute header
#define kcbCheckSum             2               // size of checksum data
#define kbFirstAttrib           6               // offset of first attribute in file

// attribute type defines used in upper 16-bits of message attributes (FYI)
#define atpString               0x0001          // null terminated string
#define atpText                 0x0002          // null terminated string with EOL control
#define atpDate                 0x0003          // 14-byte binary date/time structure
#define atpShort                0x0004          // 16-bit signed integer
#define atpLong                 0x0005          // 32-bit signed integer
#define atpByte                 0x0006          // 8-bit signed integer
#define atpWord                 0x0007          // 16-bit unsigned integer
#define atpDword                0x0008          // 32-bit unsigned integer
#define atpGrsz                 0x0009          // list of null-terminated char strings ending with double-null
#define atpTextizeMap           0x000A          // binary structure defining text output rendering of message

// message attributes
#define kWMMSubject             0x00018004      // subject of message
#define kWMMSentDate            0x00038005      // date message was sent
#define kWMMMessClass           0x00068008      // message class
#define kWMMConvID              0x0001800B      // conversation thread id
#define kWMMBody                0x0002800C      // message body text

// private message attributes
// NOTE:  I'VE INVENTED THESE ATTRIBUTES ON MY OWN AND WORKGROUP
// MAIL WILL KNOW NOTHING ABOUT THEM, FURTHER, THEY SHOULD NOT
// CLASH WITH ANY UNINVENTED WORKGROUP ATTRIBUTE ID'S.
#define kWMMUMailMessClass      0x00087FFF      // umail mess class (i.e. 'MESS')
#define kWMMUMailDeliveryCharge 0x00017FFE      // delivery charge string
#define kWMMUMailTransportID    0x00057FFD      // transort identifier

// attachment attributes
#define kWMAData                0x0006800F      // actual content of the attachment
#define kWMATitle               0x00018010      // title 8.3 for atypFile, class name for atypOLE
#define kWMAMetaFile            0x00068011      // for atypFile only
#define kWMACreateDate          0x00038011      // creation date of attachment
#define kWMAModDate             0x00038012      // modification date of attachment
#define kWMATransFilename       0x00019001      // pseudo-attribute: display filename
#define kWMARenddata            0x00069002      // pseudo-attribute: rendering position in body

// attachment data types
#define atypFile                0               // attached file
#define atypOle                 1               // embedded OLE 1.0 object
#define atypPicture             2               // embedded metafile

// attachment data rendering information
typedef struct AttachmentRenddataRecord {
    short           atyp;                       // attachment type
    long            bchPos;                     // character pos. in body
    short           dxWidth;                    // width in pixels of rend. data
    short           dyHeight;                   // height in pixels of rend. data
    long            dwFlags;                    // object specific flags
} ARR;

// winmail attribute record
typedef struct WinmailAttributeRecord {
    long            bfile;                      // file offset to attribute
    long            cbattr;                     // size of attribute data only
} WAR;
