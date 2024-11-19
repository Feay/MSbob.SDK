//---------------------------------------------------------------------------
// uccprop.h
//---------------------------------------------------------------------------
// Copyright (c) 1992-1994, Microsoft Corporation
//                 All Rights Reserved
// Information Contained Herein Is Proprietary and Confidential.
//---------------------------------------------------------------------------
//
// Module description 
//
//   This is a common header file for all the ucc custom control property IDs,
//   Changes to the properties should be reflected here.
//
//---------------------------------------------------------------------------
//
// Owner:  Alice Seubert
//
//---------------------------------------------------------------------------

// Button Property ID:

enum {ipropButton_CtlName, ipropButton_Index, ipropButton_Left,
      ipropButton_Top, ipropButton_Width, ipropButton_Height,
      ipropButton_Visible, ipropButton_Parent, ipropButton_Tag,
      ipropButton_BorderOff, ipropButton_MousePtr, ipropButton_Caption,
      ipropButton_Enabled, ipropButton_FontBold, ipropButton_FontItalic,
      ipropButton_FontName, ipropButton_FontSize, ipropButton_FontStrike,
      ipropButton_FontUnder, ipropButton_ForeColor, ipropButton_TabIndex,
      ipropButton_TabStop, ipropButton_Type, ipropButton_Alignment,
      ipropButton_AnimFile, ipropButton_AnimKey, ipropButton_Delay,
      ipropButton_BaseButton, ipropButton_Default, ipropButton_Cancel,
      ipropButton_BackColor, ipropButton_Actor, ipropButton_Hwnd,
      ipropButton_Text, ipropButton_BackStyle};

// ChkBox Property IDs:
//
// NOTE: ipropChkBox_BoxChecked is equivalent to "Value" property.

enum {ipropChkBox_CtlName, ipropChkBox_Index, ipropChkBox_Left,
      ipropChkBox_Top, ipropChkBox_Width, ipropChkBox_Height,
      ipropChkBox_Visible, ipropChkBox_Parent, ipropChkBox_Tag,
      ipropChkBox_BorderOff, ipropChkBox_MousePtr, ipropChkBox_Caption,
      ipropChkBox_Enabled, ipropChkBox_FontBold, ipropChkBox_FontItalic,
      ipropChkBox_FontName, ipropChkBox_FontSize, ipropChkBox_FontStrike,
      ipropChkBox_FontUnder, ipropChkBox_ForeColor, ipropChkBox_TabIndex,
      ipropChkBox_TabStop, ipropChkBox_BoxChecked, ipropChkBox_Alignment,
      ipropChkBox_GroupNumber, ipropChkBox_GroupAllUp, ipropChkBox_BackColor,
      ipropChkBox_AnimFile, ipropChkBox_Actor, ipropChkBox_Hwnd, ipropChkBox_AnimKey,
      ipropChkBox_Text, ipropChkBox_BackStyle};

// StatTxt Property IDs:

enum {ipropStatTxt_CtlName, ipropStatTxt_Index, ipropStatTxt_Left,
      ipropStatTxt_Top, ipropStatTxt_Width, ipropStatTxt_Height,
      ipropStatTxt_Visible, ipropStatTxt_Parent, ipropStatTxt_Tag,
      ipropStatTxt_BorderOff, ipropStatTxt_MousePtr, ipropStatTxt_Caption,
      ipropStatTxt_Enabled, ipropStatTxt_FontBold, ipropStatTxt_FontItalic,
      ipropStatTxt_FontName, ipropStatTxt_FontSize, ipropStatTxt_FontStrike,
      ipropStatTxt_FontUnder, ipropStatTxt_ForeColor, ipropStatTxt_Alignment,
      ipropStatTxt_BackColor, ipropStatTxt_BackStyle, ipropStatTxt_Actor,
      ipropStatTxt_Text, ipropStatTxt_ClipIt, ipropStatTxt_VerHeiPercent};

// LstBox Property IDs:
//
// NOTE: ipropLstBox_SelItem is equivalent to "Selected" property.
//       ipropLstBox_Caption is equivalent to "TitleText" property.

enum {ipropLstBox_CtlName, ipropLstBox_Index, ipropLstBox_Left,
      ipropLstBox_Top, ipropLstBox_Width, ipropLstBox_Height,
      ipropLstBox_Visible, ipropLstBox_Parent, ipropLstBox_Tag,
      ipropLstBox_BorderOff, ipropLstBox_MousePtr, ipropLstBox_Caption,
      ipropLstBox_Enabled, ipropLstBox_FontBold, ipropLstBox_FontItalic,
      ipropLstBox_FontName, ipropLstBox_FontSize, ipropLstBox_FontStrike,
      ipropLstBox_FontUnder, ipropLstBox_ForeColor, ipropLstBox_BackColor,
      ipropLstBox_TabIndex, ipropLstBox_TabStop, ipropLstBox_DropDown,
      ipropLstBox_ItemData, ipropLstBox_ItemFontBold,
      ipropLstBox_ItemFontItalic, ipropLstBox_ItemFontName,
      ipropLstBox_ItemFontSize, ipropLstBox_ItemFontStrike,
      ipropLstBox_ItemFontUnder, ipropLstBox_ItemForeColor,
      ipropLstBox_ItemOutline, ipropLstBox_List, ipropLstBox_ListCount,
      ipropLstBox_NewIndex, ipropLstBox_SelCount, ipropLstBox_SelectionStyle,
      ipropLstBox_SelItem, ipropLstBox_SelList, ipropLstBox_Sorted,
      ipropLstBox_TopItem, ipropLstBox_ListIndex, ipropLstBox_Alignment,
      ipropLstBox_BackStyle, ipropLstBox_ButtonType, ipropLstBox_NoScroll,
      ipropLstBox_Hwnd};

// UEdit Property IDs:

enum {ipropUEdit_NAME, ipropUEdit_INDEX, ipropUEdit_PARENT,
      ipropUEdit_BACKCOLOR, ipropUEdit_LEFT, ipropUEdit_TOP,
      ipropUEdit_WIDTH, ipropUEdit_HEIGHT, ipropUEdit_ENABLED,
      ipropUEdit_VISIBLE, ipropUEdit_MOUSEPOINTER, ipropUEdit_FONTNAME,
      ipropUEdit_FONTSIZE, ipropUEdit_FONTBOLD, ipropUEdit_FONTITALIC,
      ipropUEdit_FONTSTRIKE, ipropUEdit_FONTUNDER, ipropUEdit_DRAG,
      ipropUEdit_DRAGICON, ipropUEdit_TABINDEX, ipropUEdit_TABSTOP,
      ipropUEdit_TAG, ipropUEdit_HWND, ipropUEdit_FORECOLOR,
      ipropUEdit_TEXT, ipropUEdit_BORDERSTYLEOFF, ipropUEdit_MAXLENGTH,
      ipropUEdit_PASSWORDCHAR, ipropUEdit_MULTILINE, ipropUEdit_SELLENGTH,
      ipropUEdit_SELSTART, ipropUEdit_SELTEXT, ipropUEdit_FRAMEWIDTH,
      ipropUEdit_SHADOWWIDTH, ipropUEdit_FRAMECOLOR, ipropUEdit_SHADOWCOLOR,
      ipropUEdit_EDGECOLOR, ipropUEdit_UNDERLINECOLOR, ipropUEdit_EDITSCROLL,
      ipropUEdit_TOPLINE, ipropUEdit_LINECOUNT, ipropUEdit_READONLY,
      ipropUEdit_PASSWORD, ipropUEdit_WANTRETURN, ipropUEdit_ALIGNMENT,
      ipropUEdit_LINESON, ipropUEdit_HIDESELECTION, ipropUEdit_SHOWTIPS};

// ActorC Property IDs:

enum {ipropActorC_Actor, ipropActorC_CtlName, ipropActorC_Index,
      ipropActorC_Left, ipropActorC_Top, ipropActorC_Width,
      ipropActorC_Height, ipropActorC_Visible, ipropActorC_Parent,
      ipropActorC_Tag, ipropActorC_MousePtr, ipropActorC_Action,
      ipropActorC_Autosize, ipropActorC_Guide, ipropActorC_Background,
      ipropActorC_PickMe, ipropActorC_Sync, ipropActorC_Helpfulness};

// Image Property IDs:

enum {ipropImageC_CTLNAME, ipropImageC_INDEX, ipropImageC_BACKCOLOR,
      ipropImageC_LEFT, ipropImageC_TOP, ipropImageC_WIDTH,
      ipropImageC_HEIGHT, ipropImageC_VISIBLE, ipropImageC_PARENT,
      ipropImageC_DRAGMODE, ipropImageC_DRAGICON, ipropImageC_TAG,
      ipropImageC_CREATEMASK, ipropImageC_CREATEBITMAP,
      ipropImageC_RETAINMETAFILE, ipropImageC_DISCARDABLE,
      ipropImageC_BORDER, ipropImageC_PICT, ipropImageC_PICTFILE,
      ipropImageC_PICTID, ipropImageC_CAPTION, ipropImageC_CAPTIONX,
      ipropImageC_CAPTIONY, ipropImageC_FONTNAME, ipropImageC_FONTBOLD,
      ipropImageC_FONTITALIC, ipropImageC_FONTSIZE, ipropImageC_FONTALIGN,
      ipropImageC_FONTVALIGN, ipropImageC_ITAG, ipropImageC_SHOWCAPTION,
      ipropImageC_CPICTFILE, ipropImageC_CPICTID, ipropImageC_CPICT,
      ipropImageC_XCPICT, ipropImageC_YCPICT, ipropImageC_WIDTHCPICT,
      ipropImageC_HEIGHTCPICT};

// Scale Property IDs:

enum {ipropScale_CTLNAME, ipropScale_INDEX, ipropScale_BACKCOLOR,
      ipropScale_LEFT, ipropScale_TOP, ipropScale_WIDTH, ipropScale_HEIGHT,
      ipropScale_VISIBLE, ipropScale_PARENT, ipropScale_DRAGMODE,
      ipropScale_DRAGICON, ipropScale_TAG, ipropScale_PICT,
      ipropScale_AUTOSIZE, ipropScale_PICTID, ipropScale_PICTFILE,
      ipropScale_CLIPCONTROL, ipropScale_TRANSPARENT,
      ipropScale_CREATEBITMAP, ipropScale_HWND};

// Rgnwnd Property IDs:
enum {ipropRgnwnd_ipropCTLNAME, ipropRgnwnd_ipropBACKCOLOR,
      ipropRgnwnd_ipropBORDERCOLOR, ipropRgnwnd_ipropDRAGMODE,
      ipropRgnwnd_ipropDRAGICON, ipropRgnwnd_ipropPARENT,
      ipropRgnwnd_ipropPICTURE, ipropRgnwnd_ipropTAG,
      ipropRgnwnd_ipropAUTOPOS, ipropRgnwnd_ipropAUTOCLOSE,
      ipropRgnwnd_ipropDIPSTYLE, ipropRgnwnd_ipropDIPORIENTATION,
      ipropRgnwnd_ipropDIPBASEWIDTH, ipropRgnwnd_ipropDIPBASESHIFT,
      ipropRgnwnd_ipropDIPHEIGHT, ipropRgnwnd_ipropDIPOFFSET,
      ipropRgnwnd_ipropOBJX, ipropRgnwnd_ipropOBJY,
      ipropRgnwnd_ipropOBJWIDTH, ipropRgnwnd_ipropOBJHEIGHT,
      ipropRgnwnd_ipropPARENTHWND, ipropRgnwnd_ipropBORDERWIDTH,
      ipropRgnwnd_ipropCORNERWIDTH, ipropRgnwnd_ipropCORNERHEIGHT,
      ipropRgnwnd_ipropMODALLEVEL, ipropRgnwnd_ipropCACHED,
      ipropRgnwnd_ipropCACHEONCLOSE, ipropRgnwnd_ipropBALLOONSTYLE,
      ipropRgnwnd_ipropDIPSIDE, ipropRgnwnd_ipropAUTOSCALE,
      ipropRgnwnd_ipropAUTOSCALEWIDTH, ipropRgnwnd_ipropAUTOSCALEHEIGHT};

// USink Property IDs:

enum {ipropUSink_CTLNAME, ipropUSink_INDEX, ipropUSink_BACKCOLOR,
      ipropUSink_LEFT, ipropUSink_TOP, ipropUSink_WIDTH, ipropUSink_HEIGHT,
      ipropUSink_VISIBLE, ipropUSink_PARENT, ipropUSink_DRAGMODE,
      ipropUSink_DRAGICON, ipropUSink_TAG};

// Address listbox Property IDs:

enum {ipropABVBX_CtlName, ipropABVBX_Index, ipropABVBX_Left, ipropABVBX_Top,
      ipropABVBX_Width, ipropABVBX_Height, ipropABVBX_Visible,
      ipropABVBX_Parent, ipropABVBX_Tag, ipropABVBX_BorderOff,
      ipropABVBX_MousePtr, ipropABVBX_Caption, ipropABVBX_Enabled,
      ipropABVBX_FontBold, ipropABVBX_FontItalic, ipropABVBX_FontName,
      ipropABVBX_FontSize, ipropABVBX_FontStrike, ipropABVBX_FontUnder,
      ipropABVBX_ForeColor, ipropABVBX_BackColor, ipropABVBX_TabIndex,
      ipropABVBX_TabStop, ipropABVBX_DropDown, ipropABVBX_ItemData,
      ipropABVBX_ItemFontBold, ipropABVBX_ItemFontItalic,
      ipropABVBX_ItemFontName, ipropABVBX_ItemFontSize,
      ipropABVBX_ItemFontStrike, ipropABVBX_ItemFontUnder,
      ipropABVBX_ItemForeColor, ipropABVBX_ItemOutline, ipropABVBX_List,
      ipropABVBX_ListCount, ipropABVBX_NewIndex, ipropABVBX_SelCount,
      ipropABVBX_SelectionStyle, ipropABVBX_SelItem, ipropABVBX_SelList,
      ipropABVBX_Sorted, ipropABVBX_TopItem, ipropABVBX_ListIndex,
      ipropABVBX_Alignment, ipropABVBX_BackStyle, ipropABVBX_ButtonType,
      ipropABVBX_NoScroll, ipropABVBX_Hwnd, ipropABVBX_AddressBook,
      ipropABVBX_Slave, ipropABVBX_BookId, ipropABVBX_Show,
      ipropABVBX_SlaveUpdate, ipropABVBX_SetABSrv, ipropABVBX_ListType,
      ipropABVBX_SetBook, ipropABVBX_UpdateDelay, ipropABVBX_AddressServer,
      ipropABVBX_SetList, ipropABVBX_Hctl,  ipropABVBX_PreSelList,  
      ipropABVBX_SelectAll, ipropABVBX_ExcludeId,  ipropABVBX_VBSlave,
      ipropABVBX_ABClear, ipropABVBX_SelListLong, ipropABVBX_Dirty,
      ipropABVBX_Additions, ipropABVBX_Deletions, ipropABVBX_AdditionCount,
      ipropABVBX_DeletionCount, ipropABVBX_Empty
 };

// MiniMonth Property IDs:

enum {ipropMM_CtlName, ipropMM_BackColor, 
      ipropMM_Left, ipropMM_Top, ipropMM_Width, ipropMM_Height, 
      ipropMM_Visible, ipropMM_Parent, 
      ipropMM_FontName, ipropMM_FontBold, ipropMM_FontItalic, ipropMM_FontSize,
      ipropMM_FontStrike, ipropMM_FontUnder, ipropMM_UBorder,
      ipropMM_Date, ipropMM_VisibleMonthName, ipropMM_VisibleToday};

// Tasklist Property IDs:

enum {ipropTL_CtlName, ipropTL_BackColor, 
      ipropTL_Left, ipropTL_Top, ipropTL_Width, ipropTL_Height, 
      ipropTL_Visible, ipropTL_Parent, 
      ipropTL_FontName, ipropTL_FontBold, ipropTL_FontItalic, ipropTL_FontSize,
      ipropTL_FontStrike, ipropTL_FontUnder, ipropTL_BorderOn, 
      ipropTL_TasklistID, ipropTL_AppID, ipropTL_EnableEdit, ipropTL_VisibleHeader,
      ipropTL_VisibleAddButton, ipropTL_EnableExtra,
      ipropTL_TitleText, ipropTL_EventHeader, ipropTL_ExtraHeader,
      ipropTL_ButtonCaption, ipropTL_ExtraPicture, ipropTL_Date,
      ipropTL_DateDisplay, ipropTL_DateWidth, ipropTL_ExtraWidth,
      ipropTL_Action, ipropTL_SearchText};   
      
// Table-of-contents-listbox Property IDs

enum {
      ipropCtlName, ipropIndex, ipropLeft, ipropTop, ipropWidth,
      ipropHeight, ipropVisible, ipropParent, ipropTag, ipropBorderOff,
      ipropMousePtr, ipropCaption, ipropEnabled, ipropFontBold,
      ipropFontItalic, ipropFontName, ipropFontSize, ipropFontStrike,
      ipropFontUnder, ipropForeColor, ipropBackColor, ipropTabIndex,
      ipropTabStop, ipropDropDown, ipropItemData, ipropItemFontBold,
      ipropItemFontItalic, ipropItemFontName, ipropItemFontSize,
      ipropItemFontStrike, ipropItemFontUnder, ipropItemForeColor,
      ipropItemOutline, ipropList, ipropListCount, ipropNewIndex,
      ipropSelCount, ipropSelectionStyle, ipropSelItem, ipropSelList,
      ipropSorted, ipropTopItem, ipropListIndex, ipropAlignment,
      ipropBackStyle, ipropButtonType, ipropNoScroll, ipropHwnd,

      propTOCSrvObj, propTOCSrvLong, propTOCShow, propTOCTypeId, propTOCSecurity,
      propTOCDispDate, propTOCIncludeBundle, propTOCSortDate, propTOCSrcDir, propTOCFilename,
      propTOCExcludeId, propTOCAppId
};

enum {
    ipropSLDR_CtlName, ipropSLDR_Index, ipropSLDR_Left, 
    ipropSLDR_Top, ipropSLDR_Width, ipropSLDR_Height, 
    ipropSLDR_Visible, ipropSLDR_Parent, ipropSLDR_Tag,
    ipropSLDR_MousePtr, ipropSLDR_Enabled, ipropSLDR_BackColor, 
    ipropSLDR_Hwnd, ipropSLDR_Delay, ipropSLDR_LargeChange, 
    ipropSLDR_Min, ipropSLDR_Max, ipropSLDR_Orientation, 
    ipropSLDR_SmallChange, ipropSLDR_ScrollType, ipropSLDR_Value,
    ipropSLDR_ButtonSize
};

enum {
    ipropDRV_CtlName, ipropDRV_Index, ipropDRV_Left, ipropDRV_Top, ipropDRV_Width,
    ipropDRV_Height, ipropDRV_Visible, ipropDRV_Parent, ipropDRV_Tag, ipropDRV_BorderOff,
    ipropDRV_MousePtr, ipropDRV_Title, ipropDRV_Enabled, ipropDRV_FontBold, 
    ipropDRV_FontItalic, ipropDRV_FontName, ipropDRV_FontSize, ipropDRV_FontStrike,
    ipropDRV_FontUnder, ipropDRV_ForeColor, ipropDRV_BackColor, ipropDRV_TabIndex,
    ipropDRV_TabStop, ipropDRV_DropDown, ipropDRV_ItemData, ipropDRV_ItemFontBold,
    ipropDRV_ItemFontItalic, ipropDRV_ItemFontName, ipropDRV_ItemFontSize,
    ipropDRV_ItemFontStrike, ipropDRV_ItemFontUnder, iproDRV_pItemForeColor,
    ipropDRV_ItemOutline, ipropDRV_List, ipropDRV_ListCount, ipropDRV_NewIndex,
    ipropDRV_SelCount, ipropDRV_SelectionStyle, ipropDRV_SelItem, ipropDRV_SelList,
    ipropDRV_orted, ipropDRV_TopItem, ipropDRV_ListIndex, ipropDRV_Alignment,
    ipropDRV_BackStyle, ipropDRV_ButtonType, ipropDRV_NoScroll, ipropDRV_Hwnd,

    ipropDRV_ShowAll
};


// Podium properties

enum {
    ipropPodium_CtlName, ipropPodium_Index, ipropPodium_Left, ipropPodium_Top, 
    ipropPodium_Width, ipropPodium_Height, ipropPodium_Visible, ipropPodium_Parent, 
    ipropPodium_Tag, ipropPodium_MousePtr, ipropPodium_Enabled, ipropPodium_ForceExit
};

