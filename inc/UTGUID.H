/////////////////////////////////////////////////////////////////////////////
//                               UTGUID.H
/////////////////////////////////////////////////////////////////////////////
//
//    This file contains all the guaranteed unique IDs to be used by the
//  Utopia team.  GUIDs are used for custom interfaces as well as for
//  class IDs.  Add your own in the obvious fashion.
//
//    Our allocated range is for 256 GUID values.  If the increment number
//  will exceed this, we will need to request for a new allocation range.
//
/////////////////////////////////////////////////////////////////////////////

#define DEFINE_UTOPIAGUID(name, l) \
    DEFINE_GUID(name, 0x00020700L + (l), 0, 0, 0xC0,0,0,0,0,0,0,0x46)


// Utopia Object Creator

DEFINE_UTOPIAGUID(clsidUtopia, 1);

// Clock ids 2 - 4

DEFINE_UTOPIAGUID(clsidClock, 2);


// QDoc ids 5 - 30

DEFINE_UTOPIAGUID(clsidQDoc,5);
DEFINE_UTOPIAGUID(IID_IDocView,6);
DEFINE_UTOPIAGUID(IID_IControl,7);
DEFINE_UTOPIAGUID(IID_IText,8);
DEFINE_UTOPIAGUID(IID_IFrame,9);
DEFINE_UTOPIAGUID(IID_ISpell,10);
DEFINE_UTOPIAGUID(IID_ITed, 11);
DEFINE_UTOPIAGUID(IID_IQDispatch, 12);
DEFINE_UTOPIAGUID(IID_IClipboard, 13);
DEFINE_UTOPIAGUID(IID_IMailMerge, 14);

// Actor ids 31 - 40

DEFINE_UTOPIAGUID(IID_IActor, 31);
DEFINE_UTOPIAGUID(IID_IActorSite, 32);

DEFINE_UTOPIAGUID(IID_IAnimation, 33);
DEFINE_UTOPIAGUID(IID_IAnimationSite, 34);
DEFINE_UTOPIAGUID(IID_IAnimCache, 35);

DEFINE_UTOPIAGUID(IID_IImage, 36);
DEFINE_UTOPIAGUID(IID_IFile, 37);

// Picture service ids 41-47 (0x29 - 0x2f)

DEFINE_UTOPIAGUID(clsidArtserv, 41);  // 0x29   //UNDONE Not used?
DEFINE_UTOPIAGUID(clsidBorder, 42);   // 0x2A   //UNDONE Not used?
DEFINE_UTOPIAGUID(IID_IBorder, 43);   // 0x2B   //UNDONE Not used?
DEFINE_UTOPIAGUID(IID_IPictureServer, 44);   // 0x2c
DEFINE_UTOPIAGUID(IID_IEnumID, 45);   // 0x2d

DEFINE_UTOPIAGUID(clsidUPicOleObj, 46); // 0x2e
DEFINE_UTOPIAGUID(IID_IPictureID, 47); // 0x2f

// Calendar ids 50-69 (0x32 - 0x45)

DEFINE_UTOPIAGUID(IID_ICal, 50);        // 0x32
DEFINE_UTOPIAGUID(IID_IEvent, 51);      // 0x33
DEFINE_UTOPIAGUID(IID_ISchedule, 52);   // 0x34
DEFINE_UTOPIAGUID(IID_IAlarm, 53);      // 0x35
DEFINE_UTOPIAGUID(IID_IEventSink, 54);  // 0x36
DEFINE_UTOPIAGUID(IID_IAlarmSink, 55);  // 0x37
DEFINE_UTOPIAGUID(IID_ICalVB, 56);      // 0x38
DEFINE_UTOPIAGUID(IID_IEventVB, 57);    // 0x39
DEFINE_UTOPIAGUID(IID_ISchedVB, 58);    // 0x3a
DEFINE_UTOPIAGUID(IID_IAlarmVB, 59);    // 0x3b


// System ids 70-89 (0x46 - 0x59)

DEFINE_UTOPIAGUID(IID_IEnum, 70);       // 0x46
DEFINE_UTOPIAGUID(IID_IEnumVB, 71);     // 0x47
DEFINE_UTOPIAGUID(IID_IEnumVBVARIANT, 72); // 0x48
DEFINE_UTOPIAGUID(IID_IEnumVBT, 72);       // 0x49 // soon to be merged into IEnumVB

// Mail ids are 90-109 (0x5A - 0x6D)

DEFINE_UTOPIAGUID(IID_IUMailSession, 90);       // 0x5A
//DEFINE_UTOPIAGUID(IID_IUMailAware, 91);         // 0x5B
DEFINE_UTOPIAGUID(IID_IUMailRecip, 92);        // 0x5C
DEFINE_UTOPIAGUID(IID_IUMailFolder, 93);        // 0x5D
DEFINE_UTOPIAGUID(IID_IUMailSummary, 94);       // 0x5E
DEFINE_UTOPIAGUID(IID_IUMailMessage, 95);       // 0x5F
DEFINE_UTOPIAGUID(IID_IUMailAttach, 96);         // 0x60
DEFINE_UTOPIAGUID(IID_IUMailAdmin, 97);         // 0x61


// Address Book Ids 110-114 (0x6e - 0x72 )

DEFINE_UTOPIAGUID(IID_IABookSrv, 110);   // 0x6e
DEFINE_UTOPIAGUID(IID_IBook, 111);       // 0x6f
DEFINE_UTOPIAGUID(IID_IPerson, 112);     // 0x70
DEFINE_UTOPIAGUID(IID_IAbEnum, 113);

// Shell Service Ids 115-130

DEFINE_UTOPIAGUID(IID_IHome, 115);
DEFINE_UTOPIAGUID(IID_IRoom, 116);
DEFINE_UTOPIAGUID(IID_ISob, 117);
DEFINE_UTOPIAGUID(IID_ISobUI, 118);

// System Servid Ids 131-145

DEFINE_UTOPIAGUID(IID_ISystem, 131);
DEFINE_UTOPIAGUID(IID_IUtopiaApp, 132);
DEFINE_UTOPIAGUID(IID_ITask, 133);
DEFINE_UTOPIAGUID(IID_IUser, 134);
DEFINE_UTOPIAGUID(IID_ISysSink, 135);
DEFINE_UTOPIAGUID(IID_IToc, 136);        // 0x6e
DEFINE_UTOPIAGUID(IID_IItem, 137);       // 0x6f   

// Tip service Ids 146-150

DEFINE_UTOPIAGUID(IID_ITip, 146);
    
// Hi-fidelity timer Ids 151-155

DEFINE_UTOPIAGUID(IID_ITimer, 151);
DEFINE_UTOPIAGUID(IID_ITimerSink, 152);
    

// Miscellaneous ids are 200-255 (0xC8 - 0xFF)
DEFINE_UTOPIAGUID(IID_IGetStruct, 200); // 0xC8
DEFINE_UTOPIAGUID(IID_IClsid, 201);     // 0xC9
DEFINE_UTOPIAGUID(IID_IVBOleVerb, 202); // 0xCa
