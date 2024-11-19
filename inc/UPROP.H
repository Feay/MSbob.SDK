////////////////////////////////////////////////////////////////////////////
// UPROP.H
//
//
//
// History:
// 03-22-93 DarrinM     Created.
/////////////////////////////////////////////////////////////////////////////

#ifndef __UPROP_H__
#define __UPROP_H__

#define cchPropMax  25      // Max length of a property name.

// UNUSED: #define  propUniversalPalette    (char *)1
#define propName                (char *)2
#define propId                  (char *)3
#define propFlags               (char *)4
#define propType                (char *)5
#define propSobUIPath           (char *)6
#define propExePath             (char *)7
#define propCommand             (char *)8
#define propCmdData             (char *)9
#define propFileId              (char *)10
#define propEventId             (char *)11
#define propSob                 (char *)12
#define propUtopiaApp           (char *)13
#define propCurrentRoomId       (char *)14
#define propSecurity            (char *)15
#define propCreatorId           (char *)16
#define propPassword            (char *)17
#define propDesignStyleId       (char *)18
#define propAddr1               (char *)19
#define propAddr2               (char *)20
#define propAddrCity            (char *)21
#define propAddrState           (char *)22
#define propAddrPostalCode      (char *)23
#define propAddrCountry         (char *)24
#define propAddrCompany         (char *)25
#define propPhoneHome           (char *)26
#define propPhoneFax            (char *)27
#define propPhoneModem          (char *)28
#define propRoom                (char *)29
#define propSobUI               (char *)31
#define propTag                 (char *)32
#define propX                   (char *)33
#define propY                   (char *)34
#define propZ                   (char *)35
#define propWidth               (char *)36
#define propHeight              (char *)37
#define propImageId             (char *)38
#define propDir                 (char *)39
#define propSobUIId             (char *)40
#define propHwnd                (char *)41
#define propTarget              (char *)42
#define propStemX               (char *)43
#define propStemY               (char *)44
#define propPosition            (char *)45      // for Advise purposes
#define propDescription         (char *)47
#define propLogonRoomId         (char *)48
#define propDestRoomId          (char *)49
#define propPrevRoomId          (char *)50
#define propImageCatId          (char *)51
#define propOwnerId             (char *)52
#define propTypeId              (char *)53
#define propImage               (char *)54
// UNUSED: #define propWizardRect          (char *)55      // temporary
#define propWizard              (char *)56
// UNUSED: #define propAppInst             (char *)57
#define propCDAIData            (char *)58
#define propActorCache          (char *)59
#define propActorPath           (char *)60
#define propUser                (char *)61
#define propWizardPath          (char *)62
#define propBonus               (char *)63
#define propActor               (char *)64
#define propMailUnopenedImage   (char *)65
#define propMailOpenedImage     (char *)66
#define propMailUnsentImage     (char *)67
#define propMailFlags           (char *)68
#define propMailClass           (char *)69
#define propSessionId           (char *)70
#define propCursor              (char *)71
#define propWaveMixSession      (char *)72
#define propDialogCount         (char *)73
#define propPictureServer       (char *)74
#define propHTask               (char *)75      // for Test team
#define propHwndDaemon          (char *)76
#define propRectangle           (char *)77
#define propFirstName           (char *)78
#define propLastName            (char *)79
#define propGender              (char *)80
#define propBirthday            (char *)81
#define propPasswordOwnerId     (char *)82
#define propAnimation           (char *)83
#define propAnimationPath       (char *)84
#define propRemoveDate          (char *)85
#define propBackgroundId        (char *)86
#define propHometown            (char *)87
#define propTimezone            (char *)88
#define propEMailName           (char *)89
#define propEMailDefaultUser    (char *)90
#define propLastBday            (char *)91
#define propTimer               (char *)92
#define propAppData             (char *)93
#define propVolume              (char *)94
#define propPreviewId           (char *)95
#define evtLogon                (char *)96
#define evtLogoff               (char *)97
#define evtTimeChange           (char *)98
#define propSobId               (char *)99
#define propUNotifCallback      (char *)100

#endif  // ifndef __UPROP_H__
