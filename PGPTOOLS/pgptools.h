/**********************************************************************
 *
 *  PGPTools - PM shell for PGP v5.0 for OS/2
 *
 *  Module   : PGPTOOLS.H
 *  Info     : Main module, header file
 *  Author   : Bernd Giesen
 *  Compiler : Watcom C/C++ v10.6
 *
 *  Copyright (c) 1999-2003 Bernd Giesen. All rights reserved.
 *
 *  This program is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU General Public License as
 *  published by the Free Software Foundation; either
 *  version 2 of the License, or (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 *  General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 *  MA 02111-1307, USA.
 *
 **********************************************************************
 *
 *  History:
 *
 *  220399 - Created
 *  210499 - string identifier added
 *           timer identifier added
 *  030599 - string identifier added
 *  110699 - EXE_TIMEOUT increased
 *  170699 - IDS_PGP_USER_ABORT added
 *  250699 - IDS_GENERAL_TAB added
 *           IDS_FILES_TAB added
 *  130799 - IDS_ONTOP_MENU added
 *  140799 - main window handle declared as external
 *  231199 - PGPKEYS-related IDs added
 *  150300 - defines added
 *  040400 - EXE_TIMEOUT increased
 *  080400 - Fix: start of enumeration for IDM_ defines moved from 1
 *           to 3, 1 and 2 seem to be reserved (by DID_OK(?) and
 *           DID_CANCEL)
 *  300900 - Prototype for RecalcWinPos() added
 *
 **********************************************************************/

#if !defined _PGPTOOLS_H
#define _PGPTOOLS_H

#define INCL_PM
#define INCL_WIN
#define INCL_GPI
#define INCL_DOSERRORS
#define INCL_DOSRESOURCES
#define INCL_DOSQUEUES
#define INCL_DOSMODULEMGR
#define INCL_DOSDATETIME
#define INCL_DOSMISC
#define INCL_DOSPROCESS
#define INCL_DOSSESMGR

/*****************/
/* Headerdateien */
/*****************/

#include <os2.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>
#include <dos.h>

#define QUE_NAME  "\\QUEUES\\pgptools.que"
#define APP_QUEUE "\\QUEUES\\pgpapp.que"

#define MENUSTRN_MAXLEN                 50
#define TITLESTRN_MAXLEN                60
#define TEXTSTRN_MAXLEN                 40
#define MSGSTRN_MAXLEN                  150
#define BUBBLESTRN_MAXLEN               100
#define LIST_ENTRY_LEN                  256

/* Icon IDs */
#define ID_DIALOG_ICON                  1
#define ID_PGPKEYS_ICON                 2
#define ID_SIGN_ICON                    3
#define ID_ENCRYPT_ICON                 4
#define ID_ENCRYPT_SIGN_ICON            5
#define ID_DECRYPT_VERIFY_ICON          6

#define ID_PGPKEYS_SMALL_BMP            7
#define ID_SIGN_SMALL_BMP               8
#define ID_ENCRYPT_SMALL_BMP            9
#define ID_ENCRYPT_SIGN_SMALL_BMP       10
#define ID_DECRYPT_VERIFY_SMALL_BMP     11

/* String IDs */
#define IDS_MAIN_TITLE                  1
#define IDS_PREFERENCES_MENU            2
#define IDS_ABOUT_MENU                  3
#define IDS_ABOUT_TITLE                 4
#define IDS_ABOUT_TEXT2                 5
#define IDS_ABOUT_TEXT3                 6
#define IDS_PREF_TITLE                  7
#define IDS_PGPPATH_MISSING             8
#define IDS_PUB_KEYFILE_NOT_EXIST       9
#define IDS_PRIV_KEYFILE_NOT_EXIST      10
#define IDS_WARNING                     11
#define IDS_CMDLINE_ERROR               12

#define IDS_SELECT_PUBKEY_TITLE         13
#define IDS_SELECT_PRIVKEY_TITLE        14
#define IDS_SELECT_RANDSEED_TITLE       15

#define IDS_SELECT_SIGNDATA_TITLE       16
#define IDS_SELECT_ENCRYPTDATA_TITLE    17
#define IDS_SELECT_ENC_SIGNDATA_TITLE   18
#define IDS_SELECT_DECVERIFYDATA_TITLE  19
#define IDS_INVALID_CLIPBOARD_DATA      20
#define IDS_NO_CLIPBOARD_ACCESS         21
#define IDS_GENERAL_PROCESS_FAILURE     22
#define IDS_ENTER_PASSPHRASE_WARNING    23
#define IDS_PGP_START_FAILED            24
#define IDS_PGP_EXECUTION_FAILED        25
#define IDS_SHOW_CLIPBRD_FAILED         26

#define IDS_BUBBLE_SIGNDATA_HELP        27
#define IDS_BUBBLE_ENCRYPTDATA_HELP     28
#define IDS_BUBBLE_ENC_SIGNDATA_HELP    29
#define IDS_BUBBLE_DECVERIFYDATA_HELP   30
#define IDS_BUBBLE_PGPKEYS_HELP         31

#define IDS_QUERY_TARGET_OVERWRITE      32
#define IDS_SELECT_TARGETFILE_TITLE     33
#define IDS_SELECT_FILE2CHECK_TITLE     34
#define IDS_PGP_EXECUTION_SUCCEEDED     35
#define IDS_HELP_TITLE                  36
#define IDS_NO_HELP_FOUND               37
#define IDS_ERROR_LOADING_HELP          38
#define IDS_NO_HELP_AVAIL               39
#define IDS_HELP_MENU                   40
#define IDS_PGP_USER_ABORT              41
#define IDS_LAUNCH_PGPKEYS_FAILED       42

#define IDS_GENERAL_TAB                 43
#define IDS_FILES_TAB                   44
#define IDS_ONTOP_MENU                  45
#define IDS_PGPKEYS_EXE                 46
#define IDS_PLEASE_RESTART              47
#define IDS_PLEASE_NOTE                 48
#define IDS_SHORT_MAIN_TITLE            49
#define IDS_RUN_EDITOR_FAILED           50
#define IDS_INIFILE_UPDATE_REQUIRED     51

/* Menu IDs */
#define ID_POPUP                        1
#define ID_POPUP_EXT                    2

/* 1 and 2 are reserved */
#define IDM_SIGN                        3
#define IDM_ENCRYPT                     4
#define IDM_ENCRYPT_AND_SIGN            5
#define IDM_DECRYPT_OR_VERIFY           6
#define IDM_EMPTY_CLIPBRD               7
#define IDM_SHOW_CLIPBRD                8
#define IDM_TEXTOUTPUT                  9
#define IDM_DETACHED                    10
#define IDM_ASCII_ARMOR                 11
#define IDM_ENCRYPT_TO_SELF             12
#define IDM_LAUNCH_PGPKEYS              13
#define IDM_TOGGLE_TITLEBAR             14
#define IDM_EXIT                        15

/* Message IDs */
#define WM_SIGN_DATA                    DID_SIGN
#define WM_ENCRYPT_DATA                 DID_ENCRYPT
#define WM_ENCRYPT_AND_SIGN_DATA        DID_ENCRYPT_AND_SIGN
#define WM_DECRYPT_OR_VERIFY_DATA       DID_DECRYPT_OR_VERIFY
#define WM_LAUNCH_PGPKEYS               DID_LAUNCH_PGPKEYS

#define WM_BROWSE_PUBLIC_FILE           DID_PUBLIC_BR_BUTTON
#define WM_BROWSE_PRIVATE_FILE          DID_PRIVATE_BR_BUTTON
#define WM_BROWSE_RANDOM_FILE           DID_RANDOM_BR_BUTTON

#define WM_RUN_STARTUP                  (WM_USER)
#define WM_POPUP_SETUP_WINDOW           (WM_USER+1)
#define WM_TOGGLE_FLOAT_ONTOP           (WM_USER+2)
#define WM_POPUP_ABOUT_WINDOW           (WM_USER+3)
#define WM_CHECK_FILES                  (WM_USER+4)
#define WM_CHECK_HIDESTATE              (WM_USER+5)
#define WM_SETFOCUS_TO_EB               (WM_USER+6)
#define WM_SHOW_HELP_CONTENTS           (WM_USER+7)
#define WM_CLEANUP_PGPKEYS              (WM_USER+8)
#define WM_SETFOCUS_TO_MAINWIN          (WM_USER+9)
#define WM_SWITCH_TITLEBAR              (WM_USER+10)
#define WM_RUN_EDITOR                   (WM_USER+11)

/* Timer IDs */
#define IDT_EXETIMER                    1
#define IDT_DELTIMER                    2
#define IDT_CREATE_BUBBLETIMER          3
#define IDT_DESTROY_BUBBLETIMER         4
#define IDT_CYCLE_TIMER                 5

/* Window IDs */
#define ID_BUBBLEHELPFRAME      600
#define ID_BUBBLEHELPBUBBLE     601
/* NOTE: the rest of the window ids is defined in the ressource header files */

/* Timeout values */
#define CREATE_BUBBLE_TIMEOUT   500
#define DESTROY_BUBBLE_TIMEOUT  3000
#define EXE_TIMEOUT             120000L
#define CYCLE_TIMEOUT           10

/* Prototypes and declarations */

typedef struct sIniCheck{
                          USHORT cb;
                          BOOL State;
                        } INICHECK, *PINICHECK;

extern const CHAR DefaultConfigFile[];
extern CHAR Msg[];
extern CHAR Title[];
extern CHAR PGPPath[];
extern CHAR PGPKeyServiceCommand[CCHMAXPATH];
extern CHAR PGPCommand[CCHMAXPATH];
extern ULONG Len;
extern BOOL PGPKeysToolExists;
extern HAB Hab;
extern HMODULE hRessourceModule;
extern HPOINTER hPtrDef,
                hPtrWait;
extern HWND hwndMainDialog;   /* the main window handle */

void ShortenSysMenu(HWND hwnd);
void CenterWindow(HWND hwnd);
BOOL FileExist(PSZ pFileName);
LONG FileSize(FILE *fp, PSZ Name);
void UpdateCaption(HWND hwnd, ULONG TitleID);
void RecalcWinPos(HWND hwnd);

#endif /* _PGPTOOLS_H */

