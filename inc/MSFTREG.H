/*******************************************************************
 *
 * MSFTREG.H
 *
 * Copyright (C) Microsoft Corporation 1993.
 * All Rights reserved.
 *
 *******************************************************************
 *
 * Description: Header for modem communications.  Main use is for uploading
 *              strings to a host machine running same DLL.  Included
 *              also are routines for binary transfers.
 *
 * Current Owner: David Johnston, davej
 *
 *******************************************************************
 *
 * Known bugs: 
 *             
 * Considerations: Binary receives will overwrite an existing file 
 *                 of same name
 *                 Assumes connection is valid at a common baud rate
 *******************************************************************
 *
 * How it could be Improved:  Implement YModem batch sending.
 *
 *******************************************************************
 *
 * Revision History:
 *
 * 06/22/93 davej       created
 *
 ******************************************************************/
 

// Protocols for BinarySendFile() and BinaryReceiveFiles()
#define PROT_XMODEM   0  
#define PROT_YMODEM   1
#define PROT_XMODEM1K 2 

// Modem types supported, send this to RegHasModem() to see if one exists
#define REG_COM 1
#define REG_HAYES 2

// Error codes

#define REGERR_OK               0

#define REGERR_APPABORT         -1  // application requested abort
#define REGERR_INVALIDMODEMTYPE -2  // unknown modem type parameter
#define REGERR_INVALIDPARAMS    -3  // misc. invalid params, usually com id.
#define REGERR_NODEVICES        -4  // RegDetectModem - no modems found.

#define REGERR_NOCARRIER        -10 // RegDial - modem reported NO CARRIER
#define REGERR_NODIALTONE       -11 // RegDial - modem reported NO DIALTONE
#define REGERR_BUSY             -12 // RegDial - modem reported BUSY
#define REGERR_NOANSWER         -13 // RegDial - modem reported NO ANSWER
#define REGERR_ERROR            -14 // RegDial - modem reported ERROR
#define REGERR_UNKNOWN          -15 // RegAutoAnswer - misc. error
#define REGERR_TIMEOUT          -17 // no chars received within spec'ed time

#define REGERR_RETRIES          -20 // xmodem - retry limit reached.
#define REGERR_CANCELLED        -21 // xmodem - "cancel" block received.
#define REGERR_CANTCREATEFILE   -22 // xmodem recieve - can't create file
#define REGERR_FILENOTFOUND     -23 // xmodem send - can't open file
#define REGERR_STRINGTOOLONG    -24 // xmodem - string exceeds block size

// PH not needed. #define REGERR_CLEAREDDTR     -16  


// Notification codes: Message = WM_REGNOTIFY
//                      wParam = code below 
//                      lParam = optional data 
//
// Since nWaitForNextChar() has the following code to allow other tasks to run,
// it is a good idea to use the notification mode by including an HWND in the
// BinarySendFiles() and BinaryReceiveFile():
//
//      if (PeekMessage(&msg,0,WM_NULL,WM_NULL,PM_REMOVE))
//          DispatchMessage(&msg);

#define WM_REGNOTIFY WM_USER+1 // message to send to window for notificaitons

#define REGN_INIT          0 //       nProtocol = LOWORD(lParam)  (PROT_xxx codes)
                             //      nDirection = HIWORD(lParam)  (0=recv, 1=send)
#define REGN_OPENSENDFILE  1 //    lpszFileName = (LPSTR)lParam
#define REGN_OPENRECVFILE  2 //    lpszFileName = (LPSTR)lParam 
#define REGN_CLOSESENDFILE 3 //    lpszFileName = (LPSTR)lParam
#define REGN_CLOSERECVFILE 4 //    lpszFileName = (LPSTR)lParam
#define REGN_READBLOCK     5 //   nTotalBytesRd = (long)lParam
#define REGN_WROTEBLOCK    6 //   nTotalBytesWr = (long)lParam  
#define REGN_VERBOSE       7 //         nRegerr = LOWORD(lParam)
#define REGN_DONE          8 //         nRegerr = LOWORD(lParam)  (REGERR_xxx codes)
                             //      nDirection = HIWORD(lParam)  (0=recv, 1=send)
#define REGN_RECVFILENAME 9  //    lpszFileName = (LPSTR)lParam
#define REGN_YMODEMLENGTH 10 //       lFileSize = (long)lParam 


// verbose messages for REGN_VERBOSE
#define REGERR_RESETCOMM      -100 
#define REGERR_SENTZEROBLOCK  -101
#define REGERR_RECVZEROBLOCK  -102 
#define REGERR_SEND1024       -103
#define REGERR_SEND128        -104
#define REGERR_TRY128         -105  // trying to send blocks of 128 instead of 1024
#define REGERR_NOACKFROMEOT   -106  // never received ACK after sending EOT
#define REGERR_YMODEMDONE     -107  // sent last Ymodem block "0" of null, no more files to send
#define REGERR_SENDINGANYWAY  -108  // timed out waiting for start of send, initiating xfer
#define REGERR_TROUBLEZERO    -109  // trouble sending YModem 0 block, still trying
#define REGERR_SWITCHXMODEM   -110  // Switching to XModem instead of YModem
#define REGERR_NOC            -111  // 'C' never sent to intiate next file to send


////////////////////////////////////////////////////////////////
// Resets input and output queues by flushing them

int FAR PASCAL __export RegReset(int idcom);

//////////////////////////////////////////////////////////////
// commno: COM device number (1,2,...)
// Returns baud rate if successfully set, or
//              zero if could not set baud rate.
// Pass in a 0 for wOverrideRate to give best baud rate,
// or pass in actual baud rate desired, and function will return
// it if successful, or 0 if not.

WORD FAR PASCAL __export RegSetBestBaudRate(int commno, WORD wOverrideRate);

////////////////////////////////////////////////////////////////////
// All available com devices are returned, with the bit position
// corresponding to the com device number set if it is available, or
// cleared if not.  Bit 0 = COM1, Bit 1 = COM2, ... Bit 8 = COM9

WORD FAR PASCAL __export RegGetAvailableComs(void);

/////////////////////////////////////////////////////////////////////
// Wait up to dwWait milliseconds for a reply, after that time
// anything sent back will be placed in lpszRecv up to nMaxRecvLen bytes
// 

int FAR PASCAL __export RegSendStringGetAnswer (int nCommId, LPSTR lpszSend, LPSTR lpszRecv, int cbRecv, DWORD dwWait, BOOL fExclusive);

int FAR PASCAL __export RegGetAnswer (int nCommId, LPSTR lpszRecv, int nMaxRecvLen, DWORD dwWait, BOOL fExclusive);


///////////////////////////////////////////////////////////////////////////
// Set wForceCom to 0 to check all com devices, or particular com device
// Set wForceBaud to 0 to check all baud rates, or set to a particular rate
// Set wModemType to either REG_COM or REG_HAYES                
//
// Actual com device number, and baud rate are returned
//
// REGERR_NODEVICES is returned if no matches found,
// else 0 of OK


int CALLBACK __export RegDetectModem (LPWORD pwForceCom, LPWORD pwForceBaud, WORD wModemType, BOOL fExclusive);


// TAKEN OUT, AND REPLACED BY RegDetectModem
///////////////////////////////////////////////////////////////////
// Check all valid COM ports for an answer from a Hayes compatible modem
// by sending an ATS0=0 to all valid COM ports, and waiting 1 second for
// an "OK" response from the modem.
// returns com_port (1,2,...) if user has a modem, 0 otherwise.
// wModemType either REG_COM or REG_HAYES
//
// If more modem types besides Hayes are needed, they can be scanned for here
// and remembered in a DLL global var?

//int FAR PASCAL __export RegHasModem(WORD wForcebaud, WORD wModemType);

///////////////////////////////////////////////////////////////////
// Find a valid com port
// returns com_port (1,2,...) if user has a valid com port, 0 otherwise.

//int FAR PASCAL __export RegHasComPort(WORD wForcebaud);

///////////////////////////////////////////////////////////////
// Open port number returned from RegHasModem or RegHasComPort 
// returns 1 if given invalid port number,
// returns negative if error opening com port
// returns 0 if OK

int FAR PASCAL __export RegOpenPort(int nPort, WORD wForcebaud, BOOL fResetModem, BOOL fExclusive);

/////////////////////////////////////////////////
// Close previously opened com port
// returns 1 if already closed
// returns 0 if closed OK
// returns negative if problem closing

int FAR PASCAL __export RegClosePort(int portid);

////////////////////////////////////////////////////////
// Send hang up string to modem  (+ATH)

int FAR PASCAL __export RegHangUp(int nCommId, WORD fModemType, BOOL fExclusive);

////////////////////////////////////////////////////////
// Send Auto Answer string to modem  (ATA)

int FAR PASCAL __export RegAutoAnswer(int nCommId, WORD fModemType, BOOL fExclusive);

////////////////////////////////////////////////////////
// Notify window with WM_COMMNOTIFY when input que has data
// TRUE to turn on waiting, FALSE to cancel waiting

int FAR PASCAL __export RegWait(int idcom,HWND hWnd,BOOL enable);

///////////////////////////////////////////////////////
// Dial the given number, and wait a maximum of timeout to
// receive a string matching the string 'expecting'
// For example, expecting = "Username:"
// If found, all other input is flushed, and it is your turn to send something
// After dialing, call RegWait() to wait for a response on the other end
// Use RegTalk() to enter usernames, passwords, and navigate host system

int FAR PASCAL __export RegDial (int nCommId, LPSTR lpszNumber, WORD wModemType, DWORD dwWait, BOOL fExclusive);

//////////////////////////////////////////////////////////////
// Wait up to timeout mills for lpszExpecting to come in on the line
// (extranneous bytes sent are purged).   Once the string has been
// received, lpszResponse is sent

int FAR PASCAL __export RegTalk(int idcom,long lTimeout, LPSTR lpszExpecting, LPSTR lpszResponse);

////////////////////////////////////////////////////////////////
// After picking up the phone, send the 'greeting' string, and
// wait for the caller to send the 'expecting' string.

int FAR PASCAL __export RegAnswer(int idcom, int comport, LPSTR greeting, LPSTR expecting);

///////////////////////////////////////////////////////////////
// Send data, (field and string)

int FAR PASCAL __export RegSendData(int idcom,LPSTR field, LPSTR data);

///////////////////////////////////////////////////////////////
// Send data, (field and string)

int FAR PASCAL __export RegReceiveData(int idcom,LPSTR field, LPSTR data);

/////////////////////////////////////////////////////////////////
// Send information relating to user's system setup
//int FAR PASCAL __export RegSendMachineInfo(int idcom);

///////////////////////////////////////////////////////////////
// Return TRUE if today's date is later than the date specified
int FAR PASCAL __export RegHasExpired(int month, int day, int year); 

////////////////////////////////////////////////////////////////
// send filename via YModem.  Host must be prepared to receive before calling
// Will be adding HWND param for sending WM_USER's for status feedback
int FAR PASCAL __export BinarySendFile(int CommId, LPSTR filename, int iProtocol, HWND hWnd);

////////////////////////////////////////////////////////////////
// senf filename via YModem.  Host must be prepared to receive before calling
// Will be adding HWND param for sending WM_USER's for status feedback
int FAR PASCAL __export BinaryReceiveFiles(int CommId, LPSTR path, int iProtocol, HWND hWnd);

/////////////////////////////////////////////////////////////////
// Cancels the send or receive operation
int FAR PASCAL __export BinaryCancel(int CommId);
