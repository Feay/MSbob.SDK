//---------------------------------------------------------------------------
// imageid.h
//---------------------------------------------------------------------------
// Copyright (c) 1992-1993, Microsoft Corporation
//                 All Rights Reserved
// Information Contained Herein Is Proprietary and Confidential.
//---------------------------------------------------------------------------
//
// Module description
//
// The constant ids of images and attributes in the Image Library are
// centralized here to facilitate maintainence.
//
//---------------------------------------------------------------------------
//
// Owner:  DarrinM
//
//---------------------------------------------------------------------------

// Used by SHELLSRV to indicate an image load error

const ULONG idiLoadError =      6;

// Used by HOME to form the background image of an application

const ULONG idiAppBox =         793;

// Used by HOME to preview nothing

const ULONG idiBlankImage =     815;

// Used by Birthday Party

const ULONG idiBoxClosed =      159;
const ULONG idiBoxOpen =        160;
const ULONG idiBanner =         162;
const ULONG idiConfettiL =      164;
const ULONG idiConfettiR =      161;

// Used by Calendar

const ULONG idiCalBackground =  226;
const ULONG idiCalBell =        952;
const ULONG idiCalCover =       228;
const ULONG idiCalFactbox =     229;
const ULONG idiCalScreen =      230;
const ULONG idiCalTab =         231;
const ULONG idiCalTabToDo =     232;
const ULONG idiCalToDoList =    233;
const ULONG idiCalMoonFOTD =    240;
const ULONG idiCalChkboxChk =   550;
const ULONG idiCalChkboxUnch =  551;

// Used by Podium

const ULONG ID_PODIUM       =   679;

// Image attribute ids

const ULONG idaBackground =     21;     // Alias "Room"
const ULONG idaHomeStyle =      62;     // Style:Homes
const ULONG idaOutsideView =    70;     // Shell:View
const ULONG idaAppBox =         23;     // Shell:Decorative:Program Box
const ULONG idaTraditional =    40;     // Style:Homes:Contemporary
const ULONG idaDoors =          5;      // Shell:Doors
const ULONG idaHaveMail =       90;     // Program:E-Mail:Mail Yes
const ULONG idaNoMail   =       91;     // Program:E-Mail:Mail No


//----------------------------------------------------------
//
//  Application IDs
//
//  CONSIDER:  Renaming this file to utopiaid.h
//
//----------------------------------------------------------

typedef DWORD APPID;

#define appidGeneric            ((APPID) 1)
#define appidDoor               ((APPID) 3)
#define appidCalendar           ((APPID) 5)
#define appidNotebook           ((APPID) 6)
#define appidGazoo              ((APPID) 7)
#define appidMessageBoard       ((APPID) 10)
#define appidMail               ((APPID) 12)
#define appidAddress            ((APPID) 30)
#define appidLetter             ((APPID) 31)
#define appidClock              ((APPID) 39)
#define appidBalloon            ((APPID) 40)
#define appidWnd                ((APPID) 47)
#define appidHandles            ((APPID) 48)
#define appidControlPanel       ((APPID) 51)
#define appidPictureViewer      ((APPID) 57)
#define appidBirthday           ((APPID) 58)
#define appidBanner             ((APPID) 60)
#define appidActor              ((APPID) 61)
#define appidAnimation          ((APPID) 66)
#define appidBackground         ((APPID) 67)
#define appidLabel              ((APPID) 179)
#define appidScanner            ((APPID) 180)
#define appidGarden             ((APPID) 181)
#define appidGeoSafari          ((APPID) 182)
#define appidChooser            ((APPID) 183)
#define appidShellSrv           ((APPID) 184)
#define appidHome               ((APPID) 185)
#define appidUCC                ((APPID) 186)
#define appidBackup             ((APPID) 187)
#define appidFinance            ((APPID) 188)
#define appidUPicOleObj         ((APPID) 190)
#define appidABookSrv           ((APPID) 192)
#define appidGeoSafariBS        ((APPID) 194)
