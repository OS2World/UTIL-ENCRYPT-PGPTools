/**********************************************************************
 *
 *  PGPTools - PM shell for PGP v5.0 for OS/2
 *
 *  Module   : PGPTOOLS.C
 *  Info     : Main module
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
 *  010499 - Preferences dialog implemented
 *  210499 - Bubble help implemented
 *  220499 - Popup menu implemented
 *  240599 - Different language handling disabled
 *  140699 - IDS_SELECT_FILE2CHECK_TITLE only used if
 *           'IsDetachedSignature' is true
 *  170699 - Mouse wait pointer displayed during PGP actions
 *           PGP action can be cancelled by pressing ESC
 *  230699 - Preferences procedures moved to PREFNB.C
 *  060799 - Fix (v1.21): Values in JobDesc structure must be preset
 *           by corresponding inifile values during startup
 *           (WM_RUN_STARTUP)
 *
 *  130799 - v1.30: DLLHOOK.H added, PGPDLLHooks added
 *           floatOnTop processing implemented
 *  140799 - Owner-window handles for WinMessageBox() changed
 *  160799 - Fix: WM_MOUSEMOVE in MainDlgProc() must also be processed
 *           by WinDefDlgProc()
 *           Fix: Application MUST NOT be "always on top" if window is
 *           minimized, otherwise it would eat up all CPU time (has to
 *           be evaluated why), so "always on top" action is additionally
 *           controlled by WinIsMinimize state
 *           Fix: Bool JobDesc-Params are now also updated in popup menu
 *
 *  231199 - v1.42: Optional "PGPKeys" support added,
 *           buildcnt.h included
 *  061299 - Last Window position is now restored at startup and
 *           saved when exiting
 *  271299 - PGPKeys hint window embedded
 *
 *  150300 - v1.43: SwitchTitlebar() added
 *  200300 - Fix: Button states are only enabled after closing settings
 *           dialog if PGPKeys is not currently running.
 *  290300 - Fix in Window proc for buttons: Main push buttons didn't
 *           return to default state/appearance when mouse pointer left
 *           their client areas.
 *  030400 - Added: WM_SYSCOMMAND branch in MainDlgProc() to trap
 *           sysmenu accelerator keys if title bar is switched off
 *  040400 - Fix: WM_CHAR in MainDlgProc() now returns with
 *           WinDefDlgProc(...) by default
 *           Fix: WinPostMsg(..., (MPARAM) WM_SETFOCUS_TO_MAINWIN, ...)
 *           in MainDlgProc() changed to WinSendMsg(...), otherwise
 *           hint window will never get the input focus!
 *           Fix: break in WM_MOUSEMOVE after WinSetPointer(...)
 *  050400 - New: Popup menu can now be opened by pressing Shift+F10
 *  060400 - Fix: Main window wasn't properly destroyed during
 *           termination in main function (memory leak!). A dialog
 *           window is only destroyed implicitely by WinDismissDlg()
 *           when it is opened by WinDlgBox() rather than WinLoadDlg()!)
 *         - Hardcoded "CMD.EXE" replaced by OS2Shell constant
 *  070400 - WM_CHAR message must also be separately processed in
 *           subclassed window proc!
 *  080400 - VK_ESC handling removed,it's done bei DID_CANCEL by default
 *           Focus set to appropriate main push button after ExecutePGP
 *           call
 *  250700 - v1.44 RetrieveShell() call included
 *  170800 - v1.45 Success messagebox action no longer appears upon
 *           finishing PGP decrypt/verify action.
 *  290800 - v1.46 Conditional start of IDT_CREATE_BUBBLE_TIMER
 *           in subclassed button windows implemented; main window is
 *           now periodically checked to be set on top of the desktop
 *           by IDT_CYCLE_TIMER only if the newly created
 *           "DoFloatOnTop" flag is TRUE.
 *  250101 - Fix in sending the WM_POPUP_SETUP_WINDOW message: The mp2
 *           parameter cannot be used in WM_COMMAND message to carry
 *           our IsNewStructure value, since mp2 maybe used by
 *           WM_COMMAND itself (e.g. if the message is sent by a menu
 *           entry or the command was initiated by a mouse click etc.).
 *           See COMMANDMSG type in PMWIN.H for details. So we use
 *           the unused (in a WM_COMMAND message only!) high word of
 *           the mp1 parameter instead.
 *  140602 - Function PGPPathFound() improved to properly handle path
 *           and filenames containing spaces.
 *
 *  010305 - SetupAboutText() modified
 *
 **********************************************************************/

#include "main_xx.h"
#include "about_xx.h"
#include "prefnbxx.h"
#include "keylstxx.h"
#include "command.h"
#include "version.h"
#include "pgptools.h"
#include "prefnb.h"
#include "profile.h"
#include "filedlg.h"
#include "bubble.h"
#include "keylist.h"
#include "pphrase.h"
#include "logwin.h"
#include "pgphelp.h"
#include "dllhook.h"
#include "buildcnt.h"
#include "hint.h"

/*************/
/* Constants */
/*************/

extern const char * pReadMe;

const char DefPublicKeyring[]  = "PUBRING.PKR";
const char DefPrivateKeyring[] = "SECRING.SKR";
const char DefRandomSeedFile[] = "RANDSEED.BIN";
const char DefaultConfigFile[] = "PGP.CFG";
const char HelpfileName[]      = "PGPTOOLS.HLP";

/* these three files must at least exist to use the PGPKeys Tool from Thomas Bohn */
static const char PGPKeysExe[] = "PGPKEYS.EXE";
static const char FileRexxDLL[] = "FILEREXX.DLL";
static const char PGPkkCmd[] = "PGPKK.CMD";

/***************/
/* Global vars */
/***************/

HAB             Hab;
HAPP            hApp = 0;
HWND            hwndMainDialog = NULLHANDLE;
HWND            hCurrentButton = NULLHANDLE,
                hLastButton = NULLHANDLE;
HMODULE         hRessourceModule = NULLHANDLE; /* get ressources from exe file by default */
HPOINTER        hPtrDef,
                hPtrWait;

char    PGPPath[_MAX_PATH];
char    Msg[MSGSTRN_MAXLEN+1];
char    Title[TITLESTRN_MAXLEN+1];
ULONG   Len;
GLOBALS *pGlobal = NULL;
BOOL PGPKeysToolExists = FALSE;


/**************/
/* Local vars */
/**************/

static char CurrentBubbleText[BUBBLESTRN_MAXLEN+1];
static BOOL SamePos = FALSE;
static BOOL UserAbort = FALSE;
static BOOL WinIsMinimized = FALSE;
static BOOL WasFloatOnTop = FALSE;
static BOOL DoFloatOnTop = FALSE;
static BOOL CreateBubbleTimerRunning = FALSE;
static struct sPosParams {
                            USHORT  cSize;
                            SWP     Swp;
                         } PosParams;

static SWP SwpFrame, SwpTitle;
static HWND hwndSys, hwndTitle, hwndMin;

/********************/
/* Local prototypes */
/********************/

static void CleanUp(int State, HAB Hab, HQUEUE hQueue, HMQ Hmq, QMSG QMsg, HMODULE hRes);
static void PrepareSysMenuItems(HWND hwnd);
static BOOL PGPPathFound(PSZ pPGPPath, ULONG Size);
static BOOL ParseCmdLine(int Count, char **ppStrn);
static void ShowPopupMenu(HWND hwnd);
static void SwitchPushButtonStates(HWND hwnd, BOOL State);
static void APIENTRY ExeTrap(void);
static void SwitchTitlebar(HWND hwndFrame, BOOL bOn);

/*********************/
/* Window procedures */
/*********************/

MRESULT EXPENTRY MainDlgProc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2);
MRESULT EXPENTRY AboutDlgProc(HWND hwnd,ULONG msg,MPARAM mp1,MPARAM mp2);
MRESULT EXPENTRY PrefDlgProc(HWND hwnd,ULONG msg,MPARAM mp1,MPARAM mp2);

/* Subclassing */
MRESULT EXPENTRY SignButtonWindowProc(HWND hwnd,ULONG msg,MPARAM mp1,MPARAM mp2);
PFNWP DefSignButtonWindowProc;
MRESULT EXPENTRY EncryptButtonWindowProc(HWND hwnd,ULONG msg,MPARAM mp1,MPARAM mp2);
PFNWP DefEncryptButtonWindowProc;
MRESULT EXPENTRY EncSignButtonWindowProc(HWND hwnd,ULONG msg,MPARAM mp1,MPARAM mp2);
PFNWP DefEncSignButtonWindowProc;
MRESULT EXPENTRY DecVerifyButtonWindowProc(HWND hwnd,ULONG msg,MPARAM mp1,MPARAM mp2);
PFNWP DefDecVerifyButtonWindowProc;
MRESULT EXPENTRY PGPKeysButtonWindowProc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2);
PFNWP DefPGPKeysButtonWindowProc;

/**********************************************************************
 * Function: main
 * Info    : application entry point
 * Result  : EXIT_FAILURE or EXIT_SUCCESS
 **********************************************************************/

int main(int argc, char *argv[])
{
/**************/
/* Local vars */
/**************/

        APIRET  rc;
        PID     OwnerPID;
        HQUEUE  hQueue;
        PSZ     pszQueueName = QUE_NAME;

        HMQ     Hmq;
        QMSG    QMsg;
        CHAR    szBuffer[256];
        BOOL    ParseResult;
        ULONG   MainWinID;

 Hab = WinInitialize (0);
 Hmq = WinCreateMsgQueue (Hab, 0);

 /* check if app is already running */
 if (NO_ERROR == (rc = DosOpenQueue(&OwnerPID, &hQueue, pszQueueName)))
 {
  HSWITCH hSwitch;

  /* get switch handle of owner PID */
  hSwitch = WinQuerySwitchHandle(NULLHANDLE, OwnerPID);
  if (hSwitch != NULLHANDLE)
   /* switch to current instance of application */
   WinSwitchToProgram(hSwitch);

  CleanUp(2, Hab, hQueue, Hmq, QMsg, hRessourceModule);
  return (EXIT_SUCCESS);

 }

 DosExitList(EXLST_ADD, (PFNEXITLIST)ExeTrap);   // trap exceptions to ensure hooks being released

 pGlobal = PGPDLLSetGlobals();                   // initialize global data pointer

 /* create a queue */
 rc = DosCreateQueue(&hQueue, QUE_FIFO | QUE_NOCONVERT_ADDRESS, pszQueueName);

 if (NO_ERROR != rc)
 {
  WinAlarm(HWND_DESKTOP, WA_ERROR);
  WinMessageBox(HWND_DESKTOP, NULLHANDLE, "Internal system error!", NULL, 0, MB_ERROR | MB_OK);
  CleanUp(1, Hab, hQueue, Hmq, QMsg, hRessourceModule);
  return EXIT_FAILURE;
 }

#if 0
 /* Check for current system language */
 PrfQueryProfileString(HINI_PROFILE, "PM_National", "iCountry","", szBuffer, 256);
 CCode = atoi(szBuffer);
#endif

 ParseResult = ParseCmdLine(argc, argv);

 rc = DosLoadModule(szBuffer, sizeof(szBuffer),
                    "pgptools", &hRessourceModule);

 if (NO_ERROR != rc)
 {
  WinAlarm(HWND_DESKTOP, WA_ERROR);
  WinMessageBox(HWND_DESKTOP, NULLHANDLE, "Error loading ressource DLL!", NULL, 0, MB_ERROR | MB_OK);
  CleanUp(3, Hab, hQueue, Hmq, QMsg, hRessourceModule);
  return EXIT_FAILURE;
 }

 if (FALSE == ParseResult)
 {
  CHAR MsgText[MSGSTRN_MAXLEN+1];
  LONG Len;
  Len = WinLoadString(Hab, hRessourceModule, IDS_CMDLINE_ERROR,
                      MSGSTRN_MAXLEN, MsgText);
  WinAlarm(HWND_DESKTOP, WA_ERROR);
  WinMessageBox(HWND_DESKTOP, NULLHANDLE, MsgText, NULL, 0, MB_ERROR | MB_OK);
  CleanUp(3, Hab, hQueue, Hmq, QMsg, hRessourceModule);
  return EXIT_FAILURE;
 }

 RetrieveShell(); /* Attempt to figure out the current command shell */

 if (!PGPPathFound(PGPPath, sizeof(PGPPath)))
 {
  CHAR MsgText[MSGSTRN_MAXLEN+1];
  LONG Len;
  Len = WinLoadString(Hab, hRessourceModule, IDS_PGPPATH_MISSING,
                      MSGSTRN_MAXLEN, MsgText);
  WinAlarm(HWND_DESKTOP, WA_ERROR);
  WinMessageBox(HWND_DESKTOP, NULLHANDLE, MsgText, NULL, 0, MB_ERROR | MB_OK);
  CleanUp(3, Hab, hQueue, Hmq, QMsg, hRessourceModule);
  return EXIT_FAILURE;
 }

 BuildTempFileNames();

 PGPKeysToolExists = FileExist( (PSZ) PGPKeysExe ) &&
                     FileExist( (PSZ) FileRexxDLL ) &&
                     FileExist( (PSZ) PGPkkCmd );

 CreateBubbleHelp();

 PosParams.cSize = sizeof(PosParams);
 if (RestoreLastWinPos(Hab))
    PosParams.Swp = ProfileData.Swp;

 if (IsSmallIconState(Hab))
    MainWinID = PGPKeysToolExists ? DID_PGPTOOLS_DLG_EXT_SMALL : DID_PGPTOOLS_DLG_SMALL;
 else
    MainWinID = PGPKeysToolExists ? DID_PGPTOOLS_DLG_EXT : DID_PGPTOOLS_DLG;

 /* load the main window */
 hwndMainDialog = WinLoadDlg(HWND_DESKTOP,
                             HWND_DESKTOP,
                             MainDlgProc,
                             hRessourceModule,
                             MainWinID,
                             (PVOID) &PosParams);

 if (NULLHANDLE == hwndMainDialog)
 {
  char strn[100];
  ERRORID eid = WinGetLastError(Hab);
  sprintf(strn, "Last Error: %ld(%lx), LOW: %d(%x), SEV(HIGH):%d(%x)", eid, eid,
          ERRORIDERROR(eid),
          ERRORIDERROR(eid),
          ERRORIDSEV(eid),
          ERRORIDSEV(eid));
  WinMessageBox(HWND_DESKTOP, NULLHANDLE, strn, "Error", 0, MB_ERROR | MB_OK);
  CleanUp(3, Hab, hQueue, Hmq, QMsg, hRessourceModule);
  return EXIT_FAILURE;
 }

 // Calculate new window coordinates if neccessary
 RecalcWinPos(hwndMainDialog);

 HelpInit(hwndMainDialog, (const PSZ) HelpfileName);
 PGPDLLInit(hwndMainDialog);

 WinPostMsg(hwndMainDialog, WM_COMMAND, (MPARAM) WM_RUN_STARTUP, (MPARAM) 0);

 while(WinGetDlgMsg(hwndMainDialog, &QMsg))
   WinDispatchMsg(Hab, &QMsg);

 WinQueryWindowPos(hwndMainDialog, &ProfileData.Swp);
 StoreLastWinPos(Hab);

 PGPDLLExit();
 HelpExit();

 WinDestroyWindow(hwndMainDialog);

 CleanUp(3, Hab, hQueue, Hmq, QMsg, hRessourceModule);

 return EXIT_SUCCESS;

}

/**********************************************************************
 * Function: ExeTrap
 * Info    : trap exceptions to ensure hooks being released
 * Result  : -
 **********************************************************************/

void APIENTRY ExeTrap(void)
{
    PGPDLLExit();
    DosExitList(EXLST_EXIT, (PFNEXITLIST)ExeTrap);
}

/**********************************************************************
 * Function: CleanUp
 * Info    : cleanup application's ressources depending on its
 *           initialization's progress
 * Result  : -
 **********************************************************************/
static void CleanUp(int State, HAB Hab, HQUEUE hQueue, HMQ Hmq, QMSG QMsg, HMODULE hRes)
{
  switch(State)
  {
    case 3:
      DosFreeModule(hRes);
      /* fall through! */
    case 2:
      DosCloseQueue(hQueue);
      /* fall through! */
    case 1:
      WinDestroyMsgQueue (Hmq);
      WinTerminate (Hab);
     break;
  }

  FreeKeyList(&pKeyListAnchor);
  FreeKeyList(&pOutKeyAnchor);

#if !defined DEBUG
  remove(TempFile);
  remove(TempOutFile);
  remove(TempLogFile);
  remove(TempKeyLog);
#endif

}

/**********************************************************************
 * Function: MainDlgProc
 * Info    : dialog event handler
 * Result  : TRUE or FALSE
 **********************************************************************/

MRESULT EXPENTRY MainDlgProc (HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2)
{

 HPOINTER hIcon;
 USHORT Cmd;
 struct sPosParams *pPosParams;
 INICHECK IsNewStructure;

 if(!IsPtrInWindow(hCurrentButton) ||
    ((msg >= WM_SIGN_DATA) && (msg <= WM_LAUNCH_PGPKEYS))
   )
 {
    SamePos = FALSE;
    HideBubbleHelp();
    WinStopTimer(Hab, hwnd,IDT_CREATE_BUBBLETIMER);
    WinStopTimer(Hab, hwnd,IDT_DESTROY_BUBBLETIMER);
    CreateBubbleTimerRunning = FALSE;
 }

 switch (msg)
      {

       case WM_INITDLG:
          pPosParams = (struct sPosParams *)PVOIDFROMMP(mp2);
          if ((0 < pPosParams->Swp.x) && (0 < pPosParams->Swp.y))
            WinSetWindowPos(hwnd, HWND_TOP,
                            pPosParams->Swp.x, pPosParams->Swp.y, 0, 0, SWP_MOVE );
         /*
          * Subclass push buttons to trap their
          * WM_MOUSEMOVE event for bubble help
          */
         DefPGPKeysButtonWindowProc = WinSubclassWindow(WinWindowFromID(hwnd, DID_LAUNCH_PGPKEYS),
                                                    (PFNWP) PGPKeysButtonWindowProc);
         DefSignButtonWindowProc = WinSubclassWindow(WinWindowFromID(hwnd, DID_SIGN),
                                                    (PFNWP) SignButtonWindowProc);
         DefEncryptButtonWindowProc = WinSubclassWindow(WinWindowFromID(hwnd, DID_ENCRYPT),
                                                    (PFNWP) EncryptButtonWindowProc);
         DefEncSignButtonWindowProc = WinSubclassWindow(WinWindowFromID(hwnd, DID_ENCRYPT_AND_SIGN),
                                                    (PFNWP) EncSignButtonWindowProc);
         DefDecVerifyButtonWindowProc = WinSubclassWindow(WinWindowFromID(hwnd, DID_DECRYPT_OR_VERIFY),
                                                    (PFNWP) DecVerifyButtonWindowProc);

//         hPtrDef  = WinQueryPointer(HWND_DESKTOP);
         hPtrDef = WinQuerySysPointer(HWND_DESKTOP, SPTR_ARROW, FALSE);
         hPtrWait = WinQuerySysPointer(HWND_DESKTOP, SPTR_WAIT, FALSE);
         hIcon = WinLoadPointer(HWND_DESKTOP, (HMODULE) 0, ID_DIALOG_ICON);
         PrepareMainSysMenuItems(hwnd);
         UpdateCaption(hwnd, ProfileData.Flags.SmallIcons ? IDS_SHORT_MAIN_TITLE : IDS_MAIN_TITLE);
         WinSendMsg(hwnd, WM_SETICON, MPFROMP (hIcon), NULL);
         WinStartTimer(Hab, hwnd, IDT_CYCLE_TIMER, CYCLE_TIMEOUT);
        break;


       case WM_MINMAXFRAME :
         {
            /* hide dialog window elements if window is being minimized */
            BOOL  fShow;      /* FALSE: dialog is minimized; TRUE: dialog is restored */
            HENUM henum;      /* handle for enumeration of all controls */
            HWND  hwndChild;

            fShow = !(((PSWP) mp1)->fl & SWP_MINIMIZE);

            WinEnableWindowUpdate (hwnd, FALSE);

            for (henum = WinBeginEnumWindows(hwnd);
                 (hwndChild = WinGetNextWindow(henum)) != NULLHANDLE; )
              WinShowWindow (hwndChild, fShow);

            WinEndEnumWindows (henum);
            WinEnableWindowUpdate (hwnd, TRUE);
            WinIsMinimized = !fShow;
         }
         break;


       case WM_CHAR:
         if ((SHORT1FROMMP(mp1) & KC_VIRTUALKEY) && (SHORT1FROMMP(mp1) & KC_KEYUP))
         {
          /* open popup menu by pressing Shift+F10 */
          if ((VK_F10 == SHORT2FROMMP(mp2)) && (SHORT1FROMMP(mp1) & KC_SHIFT))
          {
            ShowPopupMenu(hwnd);
            return (MRESULT) FALSE;
          }
         }
         /* process all other chars/keys as usual! */
         return WinDefDlgProc (hwnd, msg, mp1, mp2);
        break;


       case WM_MOUSEMOVE:
         if (ExecutionInProgress)
          WinSetPointer(HWND_DESKTOP, hPtrWait);
         else
          /* allow default mouse movement */
          return WinDefDlgProc (hwnd, msg, mp1, mp2);
        break;


       case WM_SYSCOMMAND:
         /*
          * This is necessary here to continue in supporting the system menu's key
          * combinations while titlebar is switched off
          */
         switch (SHORT1FROMMP(mp1))
         {

            case SC_CLOSE: /* Alt+F4 */
              WinPostMsg (hwnd, WM_CLOSE, (MPARAM) 0, (MPARAM) 0);
             break;

            case SC_MOVE: /* Alt+F7 */
               return (WinSendMsg(hwnd, WM_TRACKFRAME, (MPARAM) TF_MOVE, (MPARAM) 0));

            case SC_RESTORE: /* Alt+F5 */
               return (MRESULT)(WinSetWindowPos (hwnd, HWND_TOP, 0, 0, 0, 0, SWP_RESTORE));

            case SC_MINIMIZE: /* Alt+F9 */
               return (MRESULT)(WinSetWindowPos (hwnd, HWND_TOP, 0, 0, 0, 0, SWP_MINIMIZE));
#if 0
            /* not supported in this app! */
            case SC_MAXIMIZE: /* Alt+F10 */
               return (MRESULT)(WinSetWindowPos (hwnd, HWND_TOP, 0, 0, 0, 0, SWP_MAXIMIZE));
#endif
            default:
              return WinDefDlgProc(hwnd, msg, mp1, mp2);
         }
        break;


       case WM_COMMAND:
         Cmd = SHORT1FROMMP(mp1);
         switch(Cmd)
         {

           case DID_CANCEL:
              if (ExecutionInProgress)
              {
                UserAbort = TRUE;
                WinTerminateApp(hApp);
              }
              return (MRESULT) FALSE;
             break;

           case WM_RUN_STARTUP:
             {
               BOOL IsNewStructure = FALSE;
               if (!ReadParams(Hab, &IsNewStructure))
               {
                SetupDefaultFilenames();
                if (!PGPKeysToolExists && !ProfileData.Flags.SuppressHint)
                  DisplayHintWin(hwnd);

                WinSendMsg(hwnd, WM_COMMAND,
                          // To stow away the IsNewStructure value, we use
                          // the "unused" member (= the high word) of the
                          // mp1 parameter in a WM_COMMAND message (and only there!).
                          // See macro COMMANDMSG in API docs (PMWIN.H) for details.
                          (MPARAM) (MAKEULONG(WM_POPUP_SETUP_WINDOW, IsNewStructure)),
                          (MPARAM) 0);
               }
               else
               {
                 WinSendMsg(hwnd, WM_COMMAND, (MPARAM) WM_SWITCH_TITLEBAR, (MPARAM) 0);

                 if (!PGPKeysToolExists && !ProfileData.Flags.SuppressHint)
                  DisplayHintWin(hwnd);

                 SuppressPGPKeysHint = ProfileData.Flags.SuppressHint;

                 if (!FileExist(ProfileData.PublicKeyFile) ||
                     (0L == FileSize(NULL, ProfileData.PublicKeyFile)) ||
                     !FileExist(ProfileData.PrivateKeyFile) ||
                     (0L == FileSize(NULL, ProfileData.PrivateKeyFile))
                    )
                  WinSendMsg(hwnd, WM_COMMAND, (MPARAM) WM_POPUP_SETUP_WINDOW, (MPARAM) 0);
                 else
                 {
                   HWND hwndSysMenu = WinWindowFromID(hwnd, FID_SYSMENU);
                   /* Load JobDesc settings */
                   JobDesc.EncryptToSelf = ProfileData.Flags.PgpEncryptToSelf;
                   JobDesc.Detached      = ProfileData.Flags.PgpDetach;
                   JobDesc.TextOutput    = ProfileData.Flags.PgpTextOutput;
                   JobDesc.ASCIIArmor    = ProfileData.Flags.PgpASCIIArmor;
                   pGlobal->floatOnTop   = ProfileData.Flags.AlwaysOnTop;
                   WinSendMsg (hwndSysMenu, MM_SETITEMATTR,
                               MPFROM2SHORT (WM_TOGGLE_FLOAT_ONTOP, TRUE),
                               MPFROM2SHORT (MIA_CHECKED, pGlobal->floatOnTop ? MIA_CHECKED : 0));
                   CreateKeyLogFile(hwnd);
                 }
               }
             }
            break;

           case WM_SIGN_DATA:
             if (ExecutionInProgress)
                break;
             HideBubbleHelp();
             Len = WinLoadString(Hab, hRessourceModule, IDS_SELECT_SIGNDATA_TITLE,
                                 TITLESTRN_MAXLEN, Title);
             JobDesc.SrcType = SourceFileSelection(hwnd, JobDesc.SourceFile, Title);
             /* fall through */
           case IDM_SIGN:
             if (ExecutionInProgress)
                break;
             if (IDM_SIGN == Cmd)
             {
               JobDesc.SrcType = eNoSrc;
               if (NO_ERROR == CopyClipBoardData2TempFile())
               {
                JobDesc.SrcType = eClipBoard;
                strcpy(JobDesc.SourceFile, TempFile);
               }
             }
             if (eNoSrc != JobDesc.SrcType)
             {
               JobDesc.Job = eSign;
               if (!GetPassphrase(hwnd, &JobDesc))
                break;
               WinStartTimer(Hab, hwnd, IDT_DELTIMER, ProfileData.Flags.CacheTime*1000);
               ExecutePGP(hwnd, PGPCommand, NULL);
               WinSetFocus(HWND_DESKTOP, WinWindowFromID(hwnd, DID_SIGN));
             }
             SamePos = FALSE;
            break;

           case WM_ENCRYPT_DATA:
             if (ExecutionInProgress)
                break;
             HideBubbleHelp();
             Len = WinLoadString(Hab, hRessourceModule, IDS_SELECT_ENCRYPTDATA_TITLE,
                                 TITLESTRN_MAXLEN, Title);
             JobDesc.SrcType = SourceFileSelection(hwnd, JobDesc.SourceFile, Title);
             /* fall through */
           case IDM_ENCRYPT:
             if (ExecutionInProgress)
                break;
             if (IDM_ENCRYPT == Cmd)
             {
               JobDesc.SrcType = eNoSrc;
               if (NO_ERROR == CopyClipBoardData2TempFile())
               {
                JobDesc.SrcType = eClipBoard;
                strcpy(JobDesc.SourceFile, TempFile);
               }
             }
             if (eNoSrc != JobDesc.SrcType)
             {
              JobDesc.Job = eEncrypt;
              /* Select user ID to encrypt to */
              if (SelectKeyToEncrypt(hwnd))
              {
               ExecutePGP(hwnd, PGPCommand, NULL);
               WinSetFocus(HWND_DESKTOP, WinWindowFromID(hwnd, DID_ENCRYPT));
              }
             }
             SamePos = FALSE;
            break;

           case WM_ENCRYPT_AND_SIGN_DATA:
             if (ExecutionInProgress)
                break;
             HideBubbleHelp();
             Len = WinLoadString(Hab, hRessourceModule, IDS_SELECT_ENC_SIGNDATA_TITLE,
                                 TITLESTRN_MAXLEN, Title);
             JobDesc.SrcType = SourceFileSelection(hwnd, JobDesc.SourceFile, Title);
             /* fall through */
           case IDM_ENCRYPT_AND_SIGN:
             if (ExecutionInProgress)
                break;
             if (IDM_ENCRYPT_AND_SIGN == Cmd)
             {
               JobDesc.SrcType = eNoSrc;
               if (NO_ERROR == CopyClipBoardData2TempFile())
               {
                JobDesc.SrcType = eClipBoard;
                strcpy(JobDesc.SourceFile, TempFile);
               }
             }
             if (eNoSrc != JobDesc.SrcType)
             {
              JobDesc.Job = eEncSign;
              /* first get passphrase */
              if (!GetPassphrase(hwnd, &JobDesc))
               break;
              WinStartTimer(Hab, hwnd, IDT_DELTIMER, ProfileData.Flags.CacheTime*1000);
              /* Select user ID to encrypt to */
              if (SelectKeyToEncrypt(hwnd))
              {
                ExecutePGP(hwnd, PGPCommand, NULL);
                WinSetFocus(HWND_DESKTOP, WinWindowFromID(hwnd, DID_ENCRYPT_AND_SIGN));
              }
             }
             SamePos = FALSE;
            break;

           case WM_DECRYPT_OR_VERIFY_DATA:
             if (ExecutionInProgress)
                break;
             HideBubbleHelp();
             Len = WinLoadString(Hab, hRessourceModule, IDS_SELECT_DECVERIFYDATA_TITLE,
                                 TITLESTRN_MAXLEN, Title);
             JobDesc.SrcType = SourceFileSelection(hwnd, JobDesc.SourceFile, Title);
             /* fall through */
           case IDM_DECRYPT_OR_VERIFY:
             if (ExecutionInProgress)
                break;
             if (IDM_DECRYPT_OR_VERIFY == Cmd)
             {
               JobDesc.SrcType = eNoSrc;
               if (NO_ERROR == CopyClipBoardData2TempFile())
               {
                JobDesc.SrcType = eClipBoard;
                strcpy(JobDesc.SourceFile, TempFile);
               }
             }

             if (eNoSrc != JobDesc.SrcType) /* ready to decrypt/verify */
             {
               CHAR PPhraseBuffer[PPHRASE_SIZE];

               BOOL Result = NO_ERROR;
               BOOL VerifyOnly = IsSignature(JobDesc.SourceFile);
               JobDesc.Job = eDecVerify;

               if (!VerifyOnly)
               {
                /* first get passphrase */
                if (!GetPassphrase(hwnd, &JobDesc))
                 break;
                WinStartTimer(Hab, hwnd, IDT_DELTIMER, ProfileData.Flags.CacheTime*1000);
               }
               else
               {
                 /*
                  * since we haven't got a passphrase here (because we don't need any
                  * for verifying) we must avoid an empty passphrase string to
                  * satisfy the always present "-z" option! A dummy string will
                  * guarantee that. However, we must buffer the original due to
                  * proper cache timer handling and restore it later after
                  * execution.
                  */
                 strcpy(PPhraseBuffer, PPhraseText);
                 strcpy(PPhraseText, "Dummy");
               }

               if (JobDesc.SrcType != eClipBoard)
               {
                ULONG TitleId = IDS_SELECT_TARGETFILE_TITLE;
                if (VerifyOnly && IsDetachedSignature)
                 TitleId = IDS_SELECT_FILE2CHECK_TITLE;
                Len = WinLoadString(Hab, hRessourceModule, TitleId,
                                    TITLESTRN_MAXLEN, Title);
                strcpy(NewOutFileName, JobDesc.SourceFile);
                Result = QueryTargetFile(hwnd, NewOutFileName, Title, VerifyOnly);
               }
               if (NO_ERROR == Result)
               {
                ExecutePGP(hwnd, OS2Shell, NULL);
                WinSetFocus(HWND_DESKTOP, WinWindowFromID(hwnd, DID_DECRYPT_OR_VERIFY));
               }
               if (VerifyOnly)
               {
                /* restore the original passphrase string */
                strcpy(PPhraseText, PPhraseBuffer);
               }
             }
             SamePos = FALSE;
            break;

           case WM_SHOW_HELP_CONTENTS:
             DisplayHelp(HM_EXT_HELP);
            break;

           case WM_TOGGLE_FLOAT_ONTOP:
            {
             HWND hwndSysMenu = WinWindowFromID(hwnd, FID_SYSMENU);
             pGlobal->floatOnTop = !pGlobal->floatOnTop;
             WinSendMsg (hwndSysMenu, MM_SETITEMATTR,
                         MPFROM2SHORT (WM_TOGGLE_FLOAT_ONTOP, TRUE),
                         MPFROM2SHORT (MIA_CHECKED, pGlobal->floatOnTop ? MIA_CHECKED : 0));
            }
            break;

           case WM_CLEANUP_PGPKEYS:
             pGlobal->floatOnTop = WasFloatOnTop;
             SwitchPushButtonStates(hwnd, TRUE);
             CreateKeyLogFile(hwnd);
             PGPKeysInProgress = FALSE;
            break;

           case WM_POPUP_ABOUT_WINDOW:
             WinDlgBox(HWND_DESKTOP,
                       hwnd,
                       AboutDlgProc,
                       hRessourceModule,
                       DID_ABOUT_DLG,
                       NULL);
            break;

           case WM_POPUP_SETUP_WINDOW:
             IsNewStructure.cb = sizeof(IsNewStructure);
             IsNewStructure.State = (BOOL) COMMANDMSG(&msg)->unused;
             if (FALSE == WinDlgBox(HWND_DESKTOP,
                          hwnd,
                          PrefDlgProc,
                          hRessourceModule,
                          DID_PREF_NB_DLG,
                          &IsNewStructure)
                )
             {
               /* if preferences were not initially saved, terminate app */
               if ((FileExist(IniFileName)) &&
                   (0L == FileSize(NULL, IniFileName)))
                remove(IniFileName);
               WinSendMsg(hwnd, WM_CLOSE, (MPARAM) 0, (MPARAM)  0);
             }
             else
             {
              HWND hwndSysMenu = WinWindowFromID(hwnd, FID_SYSMENU);
              WinSendMsg (hwndSysMenu, MM_SETITEMATTR,
                          MPFROM2SHORT (WM_TOGGLE_FLOAT_ONTOP, TRUE),
                          MPFROM2SHORT (MIA_CHECKED, pGlobal->floatOnTop ? MIA_CHECKED : 0));

              if (!FileExist(ProfileData.PublicKeyFile) ||
                  (0L == FileSize(NULL, ProfileData.PublicKeyFile)) ||
                  !FileExist(ProfileData.PrivateKeyFile) ||
                  (0L == FileSize(NULL, ProfileData.PrivateKeyFile))
                 )
                SwitchPushButtonStates(hwnd, FALSE);
              else
               if (!PGPKeysInProgress)
                SwitchPushButtonStates(hwnd, TRUE);
              CreateKeyLogFile(hwnd);
             }
            break;

           case IDM_TEXTOUTPUT:
             ProfileData.Flags.PgpTextOutput = !ProfileData.Flags.PgpTextOutput;
             JobDesc.TextOutput = ProfileData.Flags.PgpTextOutput;
             WinSendMsg(hwnd, MM_SETITEMATTR,
                        MPFROM2SHORT(IDM_TEXTOUTPUT, TRUE),
                        MPFROM2SHORT(MIA_CHECKED,
                        ProfileData.Flags.PgpTextOutput ? MIA_CHECKED : 0));
            break;

           case IDM_DETACHED:
             ProfileData.Flags.PgpDetach = !ProfileData.Flags.PgpDetach;
             JobDesc.Detached = ProfileData.Flags.PgpDetach;
             WinSendMsg(hwnd, MM_SETITEMATTR,
                        MPFROM2SHORT(IDM_DETACHED, TRUE),
                        MPFROM2SHORT(MIA_CHECKED,
                        ProfileData.Flags.PgpDetach ? MIA_CHECKED : 0));
            break;

           case IDM_ASCII_ARMOR:
             ProfileData.Flags.PgpASCIIArmor = !ProfileData.Flags.PgpASCIIArmor;
             JobDesc.ASCIIArmor = ProfileData.Flags.PgpASCIIArmor;
             WinSendMsg(hwnd, MM_SETITEMATTR,
                        MPFROM2SHORT(IDM_ASCII_ARMOR, TRUE),
                        MPFROM2SHORT(MIA_CHECKED,
                        ProfileData.Flags.PgpASCIIArmor ? MIA_CHECKED : 0));
            break;

           case IDM_ENCRYPT_TO_SELF:
           {
             JobDesc.EncryptToSelf = !JobDesc.EncryptToSelf;
             WinSendMsg(hwnd, MM_SETITEMATTR,
                        MPFROM2SHORT(IDM_ENCRYPT_TO_SELF, TRUE),
                        MPFROM2SHORT(MIA_CHECKED,
                        JobDesc.EncryptToSelf ? MIA_CHECKED : 0));
            }
            break;

           case IDM_EMPTY_CLIPBRD:
             if (WinOpenClipbrd(Hab))
             {
               WinEmptyClipbrd(Hab);
               WinCloseClipbrd(Hab);
             }
            break;

           case IDM_TOGGLE_TITLEBAR:
             ProfileData.Flags.SetTitleBar = !ProfileData.Flags.SetTitleBar;
             // fall through!
           case WM_SWITCH_TITLEBAR:
             SwitchTitlebar(hwnd, ProfileData.Flags.SetTitleBar);
             WinSendMsg(hwnd, MM_SETITEMATTR,
                        MPFROM2SHORT(IDM_TOGGLE_TITLEBAR, TRUE),
                        MPFROM2SHORT(MIA_CHECKED,
                        ProfileData.Flags.SetTitleBar ? MIA_CHECKED : 0));
             WinSendMsg(hwnd, WM_COMMAND, (MPARAM) WM_SETFOCUS_TO_MAINWIN, (MPARAM) 0);
             StoreFlags(Hab);
            break;

           case WM_SETFOCUS_TO_MAINWIN:
             WinSetFocus(HWND_DESKTOP, hwnd);
           break;


           case IDM_SHOW_CLIPBRD:
             WasFloatOnTop = pGlobal->floatOnTop;
             pGlobal->floatOnTop = FALSE;
             ShowClipbrd(hwnd);
             if (0 == hApp) // Launch failed
               pGlobal->floatOnTop = WasFloatOnTop;
            break;

           case WM_LAUNCH_PGPKEYS:  // Push button
           case IDM_LAUNCH_PGPKEYS: // Popup menu
             if (ExecutionInProgress)
             {
                WinAlarm(HWND_DESKTOP, WA_ERROR);
                break;
             }

             WasFloatOnTop = pGlobal->floatOnTop;
             pGlobal->floatOnTop = FALSE;
             SwitchPushButtonStates(hwnd, FALSE);
             RunPGPKeys(hwnd);
             if (0 == hApp) // Launch failed
             {
               SwitchPushButtonStates(hwnd, TRUE);
               pGlobal->floatOnTop = WasFloatOnTop;
             }
            break;

           case IDM_EXIT:
             WinSendMsg(hwnd, WM_CLOSE, (MPARAM) 0, (MPARAM) 0);
            break;

           default:
             return (WinDefDlgProc(hwnd, msg, mp1, mp2));

         } /* switch WM_COMMAND */
        break;


       case WM_TIMER:
         WinStopTimer(Hab, hwnd, SHORT1FROMMP(mp1));
         switch(SHORT1FROMMP(mp1))
         {
           case IDT_EXETIMER: /* kill application, since it seems to wait for input */
             WinTerminateApp(hApp);
             WinSetPointer(HWND_DESKTOP, hPtrDef);
             hApp = 0;
             if (eClipBoard == JobDesc.SrcType)
              remove(TempFile);
             Len = WinLoadString(Hab, hRessourceModule,
                                 IDS_PGP_EXECUTION_FAILED,
                                 MSGSTRN_MAXLEN, Msg);
             WinMessageBox(HWND_DESKTOP, hwnd, Msg,
                           NULL, 0L, MB_OK | MB_WARNING);
            break;

           case IDT_DELTIMER: /* delete Passphrase */
             memset(PPhraseText, 0, sizeof(PPhraseText));
            break;

           case IDT_CREATE_BUBBLETIMER: /* show bubblehelp */
             CreateBubbleTimerRunning = FALSE;
             if(IsPtrInWindow(hCurrentButton))
             {
               if ((SamePos) && (hLastButton == hCurrentButton))
                break;

               SamePos = TRUE;
               hLastButton = hCurrentButton;
               ShowBubbleHelp(hCurrentButton, CurrentBubbleText);
               /*
                *  start timer after whose expiration bubble help
                *  window is going to be closed
                */
               WinStartTimer(Hab, hwnd, IDT_DESTROY_BUBBLETIMER,
                             DESTROY_BUBBLE_TIMEOUT);
             }
            break;

           case IDT_DESTROY_BUBBLETIMER: /* hide bubblehelp */
             HideBubbleHelp();
            break;

           case IDT_CYCLE_TIMER:
             WinStartTimer(Hab, hwnd, IDT_CYCLE_TIMER, CYCLE_TIMEOUT);
             if (DoFloatOnTop)
                /* Float on top */
                WinSetWindowPos(hwnd, HWND_TOP, 0, 0, 0, 0, SWP_ZORDER);
             DoFloatOnTop = FALSE;
            break;

         }
        break;


       case WM_APPTERMINATENOTIFY:
         if (!ExecutionInProgress) /* if no PGP task was currently running */
          if (PGPKeysInProgress)
          {
              WinPostMsg(hwnd, WM_COMMAND, (MPARAM) WM_CLEANUP_PGPKEYS, (MPARAM) 0);
              break;
          }
         ExecutionInProgress = FALSE;
         WinSetPointer(HWND_DESKTOP, hPtrDef);
         WinStopTimer(Hab, hwnd, IDT_EXETIMER);
         if (0 < hApp)       /* PGP was not terminated by timeout? */
         {
           CHAR  TitleStrn[TITLESTRN_MAXLEN+1];
           ULONG Result = NO_ERROR;
           switch(JobDesc.Job)
           {
             case eSign:
             case eEncrypt:
             case eEncSign:
             case eDecVerify:
               if (eClipBoard == JobDesc.SrcType)
                Result = CopyTempFileData2ClipBoard();
               else
               {
                if (UserAbort)
                 remove(NewOutFileName); /* delete target file on user abort */
                Result = (FileExist(NewOutFileName)) ? NO_ERROR : ERROR_OPEN_FAILED;
               }

               if (UserAbort || (NO_ERROR != Result))
               {
                 Len = WinLoadString(Hab, hRessourceModule,
                                     ((eEncrypt != JobDesc.Job) &&
                                      (eDecVerify != JobDesc.Job))
                                     ? IDS_PGP_EXECUTION_FAILED
                                     : IDS_PGP_START_FAILED,
                                     MSGSTRN_MAXLEN, Msg);
                 if (UserAbort)
                  Len = WinLoadString(Hab, hRessourceModule,
                                      IDS_PGP_USER_ABORT,
                                      MSGSTRN_MAXLEN, Msg);

                 UserAbort = FALSE;
                 WinMessageBox(HWND_DESKTOP, hwnd, Msg,
                               NULL, 0L, MB_OK | MB_WARNING);
               }
               else if (eDecVerify != JobDesc.Job)
                 {
                   Len = WinLoadString(Hab, hRessourceModule,
                                       IDS_PGP_EXECUTION_SUCCEEDED,
                                       MSGSTRN_MAXLEN, Msg);
                   Len = WinLoadString(Hab, hRessourceModule,
                                       IDS_MAIN_TITLE,
                                       TITLESTRN_MAXLEN, TitleStrn);
                   WinAlarm(HWND_DESKTOP, WA_NOTE);
                   WinMessageBox(HWND_DESKTOP, hwnd, Msg,
                                 TitleStrn, 0L, MB_OK | MB_INFORMATION);
                 }
               if ((eDecVerify == JobDesc.Job) &&
                   FileExist(TempLogFile))
               {
                 /* display log window */
                 DisplayLogfile(hwnd, TempLogFile,
                                (eClipBoard == JobDesc.SrcType) ? TempOutFile : NewOutFileName,
                                (eClipBoard == JobDesc.SrcType));
#if !defined DEBUG
                 remove(TempLogFile);
#endif
               }
              break;

             case eBuildList:
               BuildKeyList(TempKeyLog);
#if !defined DEBUG
               remove(TempKeyLog);
#endif
              break;

             default:
              break;
           }
         }
         WinSetPointer(HWND_DESKTOP, hPtrDef);
        break;


       case WM_HELP:
         DisplayHelp(IDL_GENERAL_HELP);
        break;

       case WM_RUN_EDITOR:
          RunEditor(ProfileData.EditorFile, (BOOL) mp1 ? TempOutFile : NewOutFileName );
        break;

       case WM_BUTTON2CLICK:
         ShowPopupMenu(hwnd);
        break;


       case WM_CLOSE:
         WinStopTimer(Hab, hwnd, IDT_EXETIMER);
         WinStopTimer(Hab, hwnd, IDT_DELTIMER);
         WinStopTimer(Hab, hwnd, IDT_CREATE_BUBBLETIMER);
         WinStopTimer(Hab, hwnd, IDT_DESTROY_BUBBLETIMER);
         WinDestroyPointer(hIcon);
         WinDismissDlg(hwnd, TRUE);
        break;

       default:
         if (!WinIsMinimized && (msg == pGlobal->wmu_FloatToTop))
           DoFloatOnTop = TRUE;
         return WinDefDlgProc (hwnd, msg, mp1, mp2);

      }

  return (MRESULT)FALSE;
}

/**********************************************************************
 * Function: SetupAboutText
 * Info    : Setup text areas in About dialog window
 * Result  : -
 **********************************************************************/
static void SetupAboutText(HWND hwnd)
{
 CHAR AboutText[TEXTSTRN_MAXLEN+1];
 LONG Len;
 PSZ pAboutText;
 HWND hText;

 hText = WinWindowFromID(hwnd, DID_ABOUT_TEXT1);
 Len = WinLoadString(Hab, hRessourceModule, IDS_MAIN_TITLE,
                     TEXTSTRN_MAXLEN, AboutText);
 if (0 != Len)
 {
  pAboutText = (PSZ) malloc((Len+strlen(VERSION_STRN)+strlen(BUILDCOUNT_STR)+15)*sizeof(CHAR));
  if (NULL != pAboutText)
  {
   strcpy(pAboutText, AboutText);
   strcat(pAboutText, " ");
   strcat(pAboutText, VERSION_STRN);
   strcat(pAboutText, " (Build: ");
   strcat(pAboutText,  BUILDCOUNT_STR);
   strcat(pAboutText, ")");
   WinSetWindowText(hText, pAboutText);
   free(pAboutText);
  }
 }
 hText = WinWindowFromID(hwnd, DID_ABOUT_TEXT2);
 Len = WinLoadString(Hab, hRessourceModule, IDS_ABOUT_TEXT2,
                     TEXTSTRN_MAXLEN, AboutText);
 if (0 != Len)
 {
  pAboutText = (PSZ) malloc((Len+1)*sizeof(CHAR));
  if (NULL != pAboutText)
  {
   strcpy(pAboutText, AboutText);
   WinSetWindowText(hText, pAboutText);
   free(pAboutText);
  }
 }
 hText = WinWindowFromID(hwnd, DID_ABOUT_TEXT3);
 Len = WinLoadString(Hab, hRessourceModule, IDS_ABOUT_TEXT3,
                     TEXTSTRN_MAXLEN, AboutText);
 if (0 != Len)
 {
  pAboutText = (PSZ) malloc((Len+1)*sizeof(CHAR));
  if (NULL != pAboutText)
  {
   strcpy(pAboutText, AboutText);
   WinSetWindowText(hText, pAboutText);
   free(pAboutText);
  }
 }

 hText = WinWindowFromID(hwnd, DID_ABOUT_TEXT4);
 WinSetPresParam(hText, PP_FONTNAMESIZE, 7, "8.Helv");
 WinSendMsg(hText, MLM_SETTEXTLIMIT, (MPARAM) strlen(pReadMe), (MPARAM) 0);
 WinSetWindowText(hText, (PSZ) pReadMe);

}

/**********************************************************************
 * Function: ShortenSysMenu
 * Info    : Removes all entries from the sys menu except for the move
 *           and close entry
 * Result  : -
 **********************************************************************/
void ShortenSysMenu(HWND hwnd)
{
   HWND     hSysMenu;
   MENUITEM Mi;
   ULONG    Pos;
   MRESULT  Id;
   SHORT    cItems;

   hSysMenu = WinWindowFromID(hwnd, FID_SYSMENU);
   WinSendMsg(hSysMenu, MM_QUERYITEM,
              MPFROM2SHORT(SC_SYSMENU, FALSE), MPFROMP((PCH) & Mi));
   Pos = 0L;
   cItems = (SHORT)WinSendMsg(Mi.hwndSubMenu, MM_QUERYITEMCOUNT,
                              (MPARAM)NULL, (MPARAM)NULL);
   while (cItems--)
   {
       Id = WinSendMsg(Mi.hwndSubMenu, MM_ITEMIDFROMPOSITION,
                       MPFROMLONG(Pos), (MPARAM)NULL);
       switch (SHORT1FROMMR(Id))
       {
       case SC_MOVE:
       case SC_CLOSE:
           Pos++;  /* Don't delete that one. */
           break;
       default:
           WinSendMsg(Mi.hwndSubMenu, MM_DELETEITEM,
                      MPFROM2SHORT((USHORT)Id, TRUE), (MPARAM)NULL);
       }
   }
}

/**********************************************************************
 * Function: AboutDlgProc
 * Info    : About dialog window
 * Result  : TRUE or FALSE
 **********************************************************************/

MRESULT EXPENTRY AboutDlgProc (HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2)
{

 switch (msg)
      {

       case WM_INITDLG:
         UpdateCaption(hwnd, IDS_ABOUT_TITLE);
         SetupAboutText(hwnd);
         ShortenSysMenu(hwnd);
         CenterWindow(hwnd);
        break;

       case WM_CLOSE:
         WinDismissDlg(hwnd, TRUE);
        break;

       default:
        return WinDefDlgProc (hwnd, msg, mp1, mp2);
      }

 return (MRESULT)FALSE;
}

/**********************************************************************
 * Function: PrepareSysMenuItems
 * Info    : Add system menu entries
 * Result  : -
 **********************************************************************/
static void PrepareMainSysMenuItems(HWND hwnd)
{

  HWND hwndSysMenu;
  CHAR  MenuStrn[MENUSTRN_MAXLEN+1];
  LONG Len;
  USHORT i ;
  MENUITEM mi;

  hwndSysMenu = WinWindowFromID(hwnd, FID_SYSMENU);
  i = SHORT1FROMMR(WinSendMsg(hwndSysMenu, MM_ITEMIDFROMPOSITION, NULL, NULL));
  WinSendMsg(hwndSysMenu, MM_QUERYITEM, MPFROM2SHORT(i, FALSE), MPFROMP(&mi));

  hwndSysMenu = mi.hwndSubMenu;

  mi.iPosition = MIT_END;
  mi.afStyle = MIS_SEPARATOR;
  mi.afAttribute = 0;
  mi.id = 0;
  mi.hwndSubMenu = NULLHANDLE;
  mi.hItem = NULL;
  WinSendMsg(hwndSysMenu, MM_INSERTITEM, (MPARAM) &mi, NULL);

  /* Always on top entry */
  Len = WinLoadString(Hab, hRessourceModule, IDS_ONTOP_MENU,
                      MENUSTRN_MAXLEN, MenuStrn);
  mi.afStyle = MIS_TEXT;
  if (NULL != pGlobal)
   if (pGlobal->floatOnTop)
    mi.afAttribute = MIA_CHECKED;
  mi.id = WM_TOGGLE_FLOAT_ONTOP;
  WinSendMsg(hwndSysMenu, MM_INSERTITEM, (MPARAM) &mi,
            (MPARAM) MenuStrn);

  /* Preferences entry */
  Len = WinLoadString(Hab, hRessourceModule, IDS_PREFERENCES_MENU,
                      MENUSTRN_MAXLEN, MenuStrn);
  mi.afStyle = MIS_TEXT;
  mi.afAttribute = 0;
  mi.id = WM_POPUP_SETUP_WINDOW;
  WinSendMsg(hwndSysMenu, MM_INSERTITEM, (MPARAM) &mi,
            (MPARAM) MenuStrn);

  /* Help entry */
  Len = WinLoadString(Hab, hRessourceModule, IDS_HELP_MENU,
                      MENUSTRN_MAXLEN, MenuStrn);
  mi.afStyle = MIS_TEXT;
  mi.afAttribute = 0;
  mi.id = WM_SHOW_HELP_CONTENTS;
  WinSendMsg(hwndSysMenu, MM_INSERTITEM, (MPARAM) &mi,
            (MPARAM) MenuStrn);

  /* About entry */
  Len = WinLoadString(Hab, hRessourceModule, IDS_ABOUT_MENU,
                      MENUSTRN_MAXLEN, MenuStrn);
  mi.afStyle = MIS_TEXT;
  mi.afAttribute = 0;
  mi.id = WM_POPUP_ABOUT_WINDOW;
  WinSendMsg(hwndSysMenu, MM_INSERTITEM, (MPARAM) &mi,
            (MPARAM) MenuStrn);

}

/**********************************************************************
 * Function: UpdateCaption
 * Info    : Update caption with native title text
 * Result  : -
 **********************************************************************/
void UpdateCaption(HWND hwnd, ULONG TitleID)
{
  CHAR  TitleStrn[TITLESTRN_MAXLEN+1];
  LONG Len;
  HWND hTitle = WinWindowFromID(hwnd, FID_TITLEBAR);
  Len = WinLoadString(Hab, hRessourceModule, TitleID,
                      TITLESTRN_MAXLEN, TitleStrn);
  WinSetWindowText(hTitle, TitleStrn);
}

/**********************************************************************
 * Function: CenterWindow
 * Info    : What do you think it will do? :-)
 * Result  : -
 **********************************************************************/
void CenterWindow(HWND hwnd)
{
  SHORT MaxX, MaxY, ix, iy;
  SWP Swp;

  MaxX = WinQuerySysValue(HWND_DESKTOP, SV_CXSCREEN);
  MaxY = WinQuerySysValue(HWND_DESKTOP, SV_CYSCREEN);
  /* Query width and height of dialog box                            */
  WinQueryWindowPos( hwnd, (PSWP)&Swp );

  /* Center dialog box within the Screen                             */
  ix = (SHORT)(( MaxX - Swp.cx ) / 2);
  iy = (SHORT)(( MaxY - Swp.cy ) / 2);
  WinSetWindowPos( hwnd, NULL, ix, iy, 0, 0, SWP_MOVE );
}

/**********************************************************************
 * Function: PGPPathFound
 * Info    : Searching where the environment var PGPPATH points to
 * Result  : -
 **********************************************************************/
static BOOL PGPPathFound(PSZ pPGPPath, ULONG Size)
{
  CHAR Buffer[CCHMAXPATH];

  PSZ p = getenv("PGPPATH"), p2;
  if (NULL == p)
   return FALSE;

  /* cut rest of path after semicolon if more than one path exists */
  p2 = strchr(p, ';');
  if (NULL != p2)
   *p2 = '\0';

  /* now cut trailing backslash if exists */
  if ('\\' == *(p+strlen(p)-1))
   *(p+strlen(p)-1) = '\0';

  memset(pPGPPath, 0, Size);
  strncpy(pPGPPath, p, Size);
//  strupr(pPGPPath);

  /*
   * add full path to PGPKeyServiceCommand and PGPCommand, if files exist
   * this will make it unnecessary to assume them to be located
   * in the PATH
   */

  if ('\"' == *pPGPPath)
    strcpy(pPGPPath, pPGPPath+1);
  p2 = pPGPPath + strlen(pPGPPath) - 1;
  if ('\"' == *p2)
    *p2 = '\0';

  strcpy(Buffer, pPGPPath);
  strcat(Buffer, "\\");
  strcat(Buffer, PGPKeyServiceCommand);

  if (FileExist(Buffer))
  {
    strcpy(PGPKeyServiceCommand, "\"");
    strcat(PGPKeyServiceCommand, Buffer);
    strcat(PGPKeyServiceCommand, "\"");
  }

  strcpy(Buffer, pPGPPath);
  strcat(Buffer, "\\");
  strcat(Buffer, PGPCommand);

  if (FileExist(Buffer))
  {
    strcpy(PGPCommand, "\"");
    strcat(PGPCommand, Buffer);
    strcat(PGPCommand, "\"");
  }

  return TRUE;
}

/**********************************************************************
 * Function: SetupDefaultFilenames
 * Info    : Assemble default filenames for keyrings and random seed
 *           files
 * Result  : -
 **********************************************************************/
static void SetupDefaultFilenames(void)
{
  FILE *fp;
  CHAR CfgFile[CCHMAXPATH], Line[128];
  BOOL PubRingFound = FALSE,
       SecRingFound = FALSE;
  PSZ p;

  if (*(PGPPath+strlen(PGPPath)) != '\\')
   strcat(PGPPath, "\\");

  strcpy(CfgFile, PGPPath);
  strcat(CfgFile, DefaultConfigFile);

  if (NULL != (fp = fopen(CfgFile, "rt")))
  {
    /* read keyring filenames from PGP configuration file */
    while(fgets(Line, 128, fp) != NULL)
    {

       if ('\n' == Line[strlen(Line)-1])
        Line[strlen(Line)-1] = 0; /* Cut trailing \n */

       if ((0 == strncmp(Line, "PubRing", 7)) ||
           (0 == strncmp(Line, "PUBRING", 7))
          )
       {
         p = strchr(Line, '=');;
         if (NULL != p)
         {
          while(' ' == *p++)
          {
            if (*p == '\n')
             break;
          }

          if (*p != '\n')
          {
           PubRingFound = TRUE;
           strcpy(ProfileData.PublicKeyFile, strupr(p));
          }
         }
       }

       if ((0 == strncmp(Line, "SecRing=", 7)) ||
           (0 == strncmp(Line, "SECRING=", 7))
          )
       {
         p = strchr(Line, '=');
         if (NULL != p)
         {
          while(' ' == *p++)
          {
            if (*p == '\n')
             break;
          }

          if (*p != '\n')
          {
           SecRingFound = TRUE;
           strcpy(ProfileData.PrivateKeyFile, strupr(p));
          }
         }
       }


    }/* while */

    fclose(fp);
  }

  if (!PubRingFound)
  {
    strcpy(ProfileData.PublicKeyFile, PGPPath);
    strcat(ProfileData.PublicKeyFile, DefPublicKeyring);
  }

  if (!SecRingFound)
  {
    strcpy(ProfileData.PrivateKeyFile, PGPPath);
    strcat(ProfileData.PrivateKeyFile, DefPrivateKeyring);
  }

  strcpy(ProfileData.RandomSeedFile, PGPPath);
  strcat(ProfileData.RandomSeedFile, DefRandomSeedFile);
}

/**********************************************************************
 * Function: FileExist
 * Info    : Check if file does exit
 * Result  : TRUE if file found else FALSE
 **********************************************************************/

BOOL FileExist(PSZ pFileName)
{
 BOOL Result = TRUE;
 FILE *fp;

 if (NULL == (fp = fopen(pFileName, "r")))
 {
  if (ENOENT == errno)
   return FALSE;
 }

 fclose(fp);

 return Result;

}

/**********************************************************************
 * Function: FileSize
 * Info    : Return size of given file
 * Result  : Size
 **********************************************************************/
LONG FileSize(FILE *fp, PSZ Name)
{
  BOOL CloseFile = FALSE;
  LONG save_pos, size_of_file;

  if (NULL == fp)
  {
    if (NULL == (fp = fopen(Name, "r")))
     return -1L;

    CloseFile = TRUE;
  }

  save_pos = ftell( fp );
  fseek( fp, 0L, SEEK_END );
  size_of_file = ftell( fp );
  fseek( fp, save_pos, SEEK_SET );

  if (CloseFile)
   fclose(fp);

  return( size_of_file );
}

/**********************************************************************
 * Function: ParseCmdLine
 * Info    : Parse commandline options
 * Result  : FALSE if error else TRUE
 **********************************************************************/

static BOOL ParseCmdLine(int Count, char **ppStrn)
{

 char *pArg;

 while(--Count > 0)
 {

  if ((*(pArg = ppStrn[Count]) != '-') && (*pArg !='/'))
  {
   strcpy(IniFileName, pArg);
   continue;
  }

  pArg = ++ppStrn[Count];  /* overread '-' or '/' */

  switch(toupper(*pArg))
  {

#if 0
   case 'L':
     if (*(pArg+1) == '=')
     {
      if ('D' == toupper(*(pArg+2)))
       CCode = 49;
      else
       CCode = 1;
     }
     else
      return FALSE;
    break;
#endif

   default:
    return FALSE;
  }

 }

 return TRUE;
}

/**********************************************************************
 * Function: SwitchPushButtonStates
 * Info    : Lock or unlock pushbutton (depending on current action)
 * Result  : -
 **********************************************************************/
static void SwitchPushButtonStates(HWND hwnd, BOOL State)
{
   if (PGPKeysToolExists)
     WinEnableWindow(WinWindowFromID(hwnd, DID_LAUNCH_PGPKEYS), State);
   WinEnableWindow(WinWindowFromID(hwnd, DID_SIGN), State);
   WinEnableWindow(WinWindowFromID(hwnd, DID_ENCRYPT), State);
   WinEnableWindow(WinWindowFromID(hwnd, DID_ENCRYPT_AND_SIGN), State);
   WinEnableWindow(WinWindowFromID(hwnd, DID_DECRYPT_OR_VERIFY), State);
}

/**********************************************************************
 * Function: PGPKeysButtonWindowProc
 * Info    : Subclassed window procedure for PGPKeys push button
 * Result  : TRUE or FALSE
 **********************************************************************/
MRESULT EXPENTRY PGPKeysButtonWindowProc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2)
{
   static HWND hwndParent;
   USHORT Cmd;

   switch(msg)
   {

    case WM_CREATE:
      hwndParent = WinQueryWindow(hwnd, QW_PARENT);
     break;

    case WM_BUTTON2CLICK:
      ShowPopupMenu(hwnd);
     break;

    case WM_COMMAND:
     switch(Cmd = SHORT1FROMMP(mp1))
     {
       case IDM_SIGN:
       case IDM_ENCRYPT:
       case IDM_ENCRYPT_AND_SIGN:
       case IDM_DECRYPT_OR_VERIFY:
       case IDM_EMPTY_CLIPBRD:
       case IDM_SHOW_CLIPBRD:
       case IDM_TEXTOUTPUT:
       case IDM_DETACHED:
       case IDM_ASCII_ARMOR:
       case IDM_ENCRYPT_TO_SELF:
       case IDM_LAUNCH_PGPKEYS:
       case IDM_TOGGLE_TITLEBAR:
       case IDM_EXIT:
         WinSendMsg(hwndParent, WM_COMMAND, (MPARAM) Cmd, (MPARAM) 0);
        break;
     }
     break;

    case WM_CHAR:
      if ((SHORT1FROMMP(mp1) & KC_VIRTUALKEY) && (SHORT1FROMMP(mp1) & KC_KEYUP))
      {
       /* open popup menu by pressing Shift+F10 */
       if ((VK_F10 == SHORT2FROMMP(mp2)) && (SHORT1FROMMP(mp1) & KC_SHIFT))
       {
         ShowPopupMenu(hwnd);
         return (MRESULT) FALSE;
       }
      }
      /* process all other chars/keys as usual! */
      return DefPGPKeysButtonWindowProc(hwnd, msg, mp1, mp2);
     break;

    /* check for mouse event */
    case WM_MOUSEMOVE:
      if (ExecutionInProgress)
      {
        WinSetPointer(HWND_DESKTOP, hPtrWait);
        break;
      }
      else
      {
        hwndParent = WinQueryWindow(hwnd, QW_PARENT);
        if (!CreateBubbleTimerRunning)
        {
          WinStartTimer(Hab, hwndParent, IDT_CREATE_BUBBLETIMER,
                        CREATE_BUBBLE_TIMEOUT);
          CreateBubbleTimerRunning = TRUE;
        }

        hCurrentButton = hwnd;
        Len = WinLoadString(Hab, hRessourceModule, IDS_BUBBLE_PGPKEYS_HELP,
                            BUBBLESTRN_MAXLEN, CurrentBubbleText);
      }
      // Fix: fall through to handle button action properly!

    default:
     return DefPGPKeysButtonWindowProc(hwnd, msg, mp1, mp2);

   }

  return (MRESULT) FALSE;

}

/**********************************************************************
 * Function: SignButtonWindowProc
 * Info    : Subclassed window procedure for sign push button
 * Result  : TRUE or FALSE
 **********************************************************************/
MRESULT EXPENTRY SignButtonWindowProc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2)
{
   static HWND hwndParent;
   USHORT Cmd;

   switch(msg)
   {

    case WM_CREATE:
      hwndParent = WinQueryWindow(hwnd, QW_PARENT);
     break;

    case WM_BUTTON2CLICK:
      ShowPopupMenu(hwnd);
     break;

    case WM_COMMAND:
     switch(Cmd = SHORT1FROMMP(mp1))
     {
       case IDM_SIGN:
       case IDM_ENCRYPT:
       case IDM_ENCRYPT_AND_SIGN:
       case IDM_DECRYPT_OR_VERIFY:
       case IDM_EMPTY_CLIPBRD:
       case IDM_SHOW_CLIPBRD:
       case IDM_TEXTOUTPUT:
       case IDM_DETACHED:
       case IDM_ASCII_ARMOR:
       case IDM_ENCRYPT_TO_SELF:
       case IDM_LAUNCH_PGPKEYS:
       case IDM_TOGGLE_TITLEBAR:
       case IDM_EXIT:
         WinSendMsg(hwndParent, WM_COMMAND, (MPARAM) Cmd, (MPARAM) 0);
        break;
     }
     break;

    case WM_CHAR:
      if ((SHORT1FROMMP(mp1) & KC_VIRTUALKEY) && (SHORT1FROMMP(mp1) & KC_KEYUP))
      {

       /* open popup menu by pressing Shift+F10 */
       if ((VK_F10 == SHORT2FROMMP(mp2)) && (SHORT1FROMMP(mp1) & KC_SHIFT))
       {
         ShowPopupMenu(hwnd);
         return (MRESULT) FALSE;
       }
      }
      /* process all other chars/keys as usual! */
      return DefSignButtonWindowProc(hwnd, msg, mp1, mp2);
     break;

    /* check for mouse event */
    case WM_MOUSEMOVE:
      if (ExecutionInProgress)
      {
        WinSetPointer(HWND_DESKTOP, hPtrWait);
        break;
      }
      else
      {
        hwndParent = WinQueryWindow(hwnd, QW_PARENT);
        if (!CreateBubbleTimerRunning)
        {
          WinStartTimer(Hab, hwndParent, IDT_CREATE_BUBBLETIMER,
                        CREATE_BUBBLE_TIMEOUT);
          CreateBubbleTimerRunning = TRUE;
        }

        hCurrentButton = hwnd;
        Len = WinLoadString(Hab, hRessourceModule, IDS_BUBBLE_SIGNDATA_HELP,
                            BUBBLESTRN_MAXLEN, CurrentBubbleText);
      }
      // Fix: fall through to handle button action properly!

    default:
     return DefSignButtonWindowProc(hwnd, msg, mp1, mp2);

   }

  return (MRESULT) FALSE;

}

/**********************************************************************
 * Function: EncryptButtonWindowProc
 * Info    : Subclassed window procedure for encrypt push button
 * Result  : TRUE or FALSE
 **********************************************************************/
MRESULT EXPENTRY EncryptButtonWindowProc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2)
{
   static HWND hwndParent;
   USHORT Cmd;

   switch(msg)
   {

    case WM_CREATE:
      hwndParent = WinQueryWindow(hwnd, QW_PARENT);
     break;

    case WM_BUTTON2CLICK:
      ShowPopupMenu(hwnd);
     break;

    case WM_COMMAND:
     switch(Cmd = SHORT1FROMMP(mp1))
     {
       case IDM_SIGN:
       case IDM_ENCRYPT:
       case IDM_ENCRYPT_AND_SIGN:
       case IDM_DECRYPT_OR_VERIFY:
       case IDM_EMPTY_CLIPBRD:
       case IDM_SHOW_CLIPBRD:
       case IDM_TEXTOUTPUT:
       case IDM_DETACHED:
       case IDM_ASCII_ARMOR:
       case IDM_ENCRYPT_TO_SELF:
       case IDM_LAUNCH_PGPKEYS:
       case IDM_TOGGLE_TITLEBAR:
       case IDM_EXIT:
         WinSendMsg(hwndParent, WM_COMMAND, (MPARAM) Cmd, (MPARAM) 0);
        break;
     }
     break;

    case WM_CHAR:
      if ((SHORT1FROMMP(mp1) & KC_VIRTUALKEY) && (SHORT1FROMMP(mp1) & KC_KEYUP))
      {

       /* open popup menu by pressing Shift+F10 */
       if ((VK_F10 == SHORT2FROMMP(mp2)) && (SHORT1FROMMP(mp1) & KC_SHIFT))
       {
         ShowPopupMenu(hwnd);
         return (MRESULT) FALSE;
       }
      }
      /* process all other chars/keys as usual! */
      return DefEncryptButtonWindowProc(hwnd, msg, mp1, mp2);
     break;

    /* check for mouse event */
    case WM_MOUSEMOVE:
      if (ExecutionInProgress)
      {
        WinSetPointer(HWND_DESKTOP, hPtrWait);
        break;
      }
      else
      {
        hwndParent = WinQueryWindow(hwnd, QW_PARENT);
        if (!CreateBubbleTimerRunning)
        {
          WinStartTimer(Hab, hwndParent, IDT_CREATE_BUBBLETIMER,
                        CREATE_BUBBLE_TIMEOUT);
          CreateBubbleTimerRunning = TRUE;
        }
        hCurrentButton = hwnd;
        Len = WinLoadString(Hab, hRessourceModule, IDS_BUBBLE_ENCRYPTDATA_HELP,
                            BUBBLESTRN_MAXLEN, CurrentBubbleText);
      }
      // Fix: fall through to handle button action properly!

     default:
      return DefEncryptButtonWindowProc(hwnd, msg, mp1, mp2);
   }

   return (MRESULT) FALSE;
}

/**********************************************************************
 * Function: EncSignButtonWindowProc
 * Info    : Subclassed window procedure for encrypt/sign push button
 * Result  : TRUE or FALSE
 **********************************************************************/
MRESULT EXPENTRY EncSignButtonWindowProc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2)
{
   static HWND hwndParent;
   USHORT Cmd;

   switch(msg)
   {

    case WM_CREATE:
      hwndParent = WinQueryWindow(hwnd, QW_PARENT);
     break;

    case WM_BUTTON2CLICK:
      ShowPopupMenu(hwnd);
     break;

    case WM_COMMAND:
     switch(Cmd = SHORT1FROMMP(mp1))
     {
       case IDM_SIGN:
       case IDM_ENCRYPT:
       case IDM_ENCRYPT_AND_SIGN:
       case IDM_DECRYPT_OR_VERIFY:
       case IDM_EMPTY_CLIPBRD:
       case IDM_SHOW_CLIPBRD:
       case IDM_TEXTOUTPUT:
       case IDM_DETACHED:
       case IDM_ASCII_ARMOR:
       case IDM_ENCRYPT_TO_SELF:
       case IDM_LAUNCH_PGPKEYS:
       case IDM_TOGGLE_TITLEBAR:
       case IDM_EXIT:
         WinSendMsg(hwndParent, WM_COMMAND, (MPARAM) Cmd, (MPARAM) 0);
        break;
     }
     break;

    case WM_CHAR:
      if ((SHORT1FROMMP(mp1) & KC_VIRTUALKEY) && (SHORT1FROMMP(mp1) & KC_KEYUP))
      {
       /* open popup menu by pressing Shift+F10 */
       if ((VK_F10 == SHORT2FROMMP(mp2)) && (SHORT1FROMMP(mp1) & KC_SHIFT))
       {
         ShowPopupMenu(hwnd);
         return (MRESULT) FALSE;
       }
      }
      /* process all other chars/keys as usual! */
      return DefEncSignButtonWindowProc(hwnd, msg, mp1, mp2);
     break;

    /* check for mouse event */
    case WM_MOUSEMOVE:
      if (ExecutionInProgress)
      {
        WinSetPointer(HWND_DESKTOP, hPtrWait);
        break;
      }
      else
      {
        hwndParent = WinQueryWindow(hwnd, QW_PARENT);
        if (!CreateBubbleTimerRunning)
        {
          WinStartTimer(Hab, hwndParent, IDT_CREATE_BUBBLETIMER,
                        CREATE_BUBBLE_TIMEOUT);
          CreateBubbleTimerRunning = TRUE;
        }
        hCurrentButton = hwnd;
        Len = WinLoadString(Hab, hRessourceModule, IDS_BUBBLE_ENC_SIGNDATA_HELP,
                            BUBBLESTRN_MAXLEN, CurrentBubbleText);
      }
      // Fix: fall through to handle button action properly!

     default:
      return DefEncSignButtonWindowProc(hwnd, msg, mp1, mp2);

   }

   return (MRESULT) FALSE;
}

/**********************************************************************
 * Function: DecVerifyButtonWindowProc
 * Info    : Subclassed window procedure for decrypt/verify push button
 * Result  : TRUE or FALSE
 **********************************************************************/
MRESULT EXPENTRY DecVerifyButtonWindowProc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2)
{
   static HWND hwndParent;
   USHORT Cmd;

   switch(msg)
   {
    case WM_CREATE:
      hwndParent = WinQueryWindow(hwnd, QW_PARENT);
     break;

    case WM_BUTTON2CLICK:
      ShowPopupMenu(hwnd);
     break;

    case WM_COMMAND:
     switch(Cmd = SHORT1FROMMP(mp1))
     {
       case IDM_SIGN:
       case IDM_ENCRYPT:
       case IDM_ENCRYPT_AND_SIGN:
       case IDM_DECRYPT_OR_VERIFY:
       case IDM_EMPTY_CLIPBRD:
       case IDM_SHOW_CLIPBRD:
       case IDM_TEXTOUTPUT:
       case IDM_DETACHED:
       case IDM_ASCII_ARMOR:
       case IDM_ENCRYPT_TO_SELF:
       case IDM_LAUNCH_PGPKEYS:
       case IDM_TOGGLE_TITLEBAR:
       case IDM_EXIT:
         WinSendMsg(hwndParent, WM_COMMAND, (MPARAM) Cmd, (MPARAM) 0);
        break;
     }
     break;

    case WM_CHAR:
      if ((SHORT1FROMMP(mp1) & KC_VIRTUALKEY) && (SHORT1FROMMP(mp1) & KC_KEYUP))
      {
       /* open popup menu by pressing Shift+F10 */
       if ((VK_F10 == SHORT2FROMMP(mp2)) && (SHORT1FROMMP(mp1) & KC_SHIFT))
       {
         ShowPopupMenu(hwnd);
         return (MRESULT) FALSE;
       }
      }
      /* process all other chars/keys as usual! */
      return DefDecVerifyButtonWindowProc(hwnd, msg, mp1, mp2);
     break;

    /* check for mouse event */
    case WM_MOUSEMOVE:
      if (ExecutionInProgress)
      {
        WinSetPointer(HWND_DESKTOP, hPtrWait);
        break;
      }
      else
      {
        hwndParent = WinQueryWindow(hwnd, QW_PARENT);
        if (!CreateBubbleTimerRunning)
        {
          WinStartTimer(Hab, hwndParent, IDT_CREATE_BUBBLETIMER,
                        CREATE_BUBBLE_TIMEOUT);
          CreateBubbleTimerRunning = TRUE;
        }
        hCurrentButton = hwnd;
        Len = WinLoadString(Hab, hRessourceModule, IDS_BUBBLE_DECVERIFYDATA_HELP,
                            BUBBLESTRN_MAXLEN, CurrentBubbleText);
      }
      // Fix: fall through to handle button action properly!

     default:
      return DefDecVerifyButtonWindowProc(hwnd, msg, mp1, mp2);

   }

   return (MRESULT) FALSE;
}

/**********************************************************************
 * Function: ShowPopupMenu
 * Info    : Opens popup menu upon right mouse click
 * Result  : -
 **********************************************************************/
static void ShowPopupMenu(HWND hwnd)
{
  HWND hwndParent,
       hwndPopup;
  POINTL ptl;


  hwndParent = WinQueryWindow(hwnd, QW_PARENT);

  {
    // Hide bubble help immediately when opening the popup menu
    SamePos = FALSE;
    HideBubbleHelp();
    WinStopTimer(Hab, hwndParent,IDT_CREATE_BUBBLETIMER);
    WinStopTimer(Hab, hwndParent,IDT_DESTROY_BUBBLETIMER);
    CreateBubbleTimerRunning = FALSE;
  }

  hwndPopup = WinLoadMenu(hwndParent, hRessourceModule, PGPKeysToolExists ? ID_POPUP_EXT : ID_POPUP);
  WinQueryPointerPos(HWND_DESKTOP, &ptl);
  WinMapWindowPoints(HWND_DESKTOP, hwndParent, &ptl, 1);
  WinPopupMenu(hwndParent, hwnd, hwndPopup,
               ptl.x+160, ptl.y+130,
               IDM_SIGN,
               PU_KEYBOARD | PU_POSITIONONITEM |
               PU_MOUSEBUTTON1 | PU_MOUSEBUTTON2 |
               PU_HCONSTRAIN | PU_VCONSTRAIN);

  WinSendMsg(hwndPopup, MM_SETITEMATTR,
             MPFROM2SHORT(IDM_TEXTOUTPUT, TRUE),
             MPFROM2SHORT(MIA_CHECKED, ProfileData.Flags.PgpTextOutput ? MIA_CHECKED : 0));
  WinSendMsg(hwndPopup, MM_SETITEMATTR,
             MPFROM2SHORT(IDM_DETACHED, TRUE),
             MPFROM2SHORT(MIA_CHECKED, ProfileData.Flags.PgpDetach ? MIA_CHECKED : 0));
  WinSendMsg(hwndPopup, MM_SETITEMATTR,
             MPFROM2SHORT(IDM_ASCII_ARMOR, TRUE),
             MPFROM2SHORT(MIA_CHECKED, ProfileData.Flags.PgpASCIIArmor ? MIA_CHECKED : 0));
  WinSendMsg(hwndPopup, MM_SETITEMATTR,
             MPFROM2SHORT(IDM_ENCRYPT_TO_SELF, TRUE),
             MPFROM2SHORT(MIA_CHECKED, JobDesc.EncryptToSelf ? MIA_CHECKED : 0));
  WinSendMsg(hwndPopup, MM_SETITEMATTR,
             MPFROM2SHORT(IDM_TOGGLE_TITLEBAR, TRUE),
             MPFROM2SHORT(MIA_CHECKED, ProfileData.Flags.SetTitleBar ? MIA_CHECKED : 0));
}

/**********************************************************************
 * Function: SwitchTitlebar
 * Info    : Turn of/off the title bar
 * Result  : -
 **********************************************************************/
static void SwitchTitlebar(HWND hwndFrame, BOOL bOn)
{

  /* Store current frame coordinates */
  WinQueryWindowPos(hwndFrame, &SwpFrame);

  if (!bOn)
  {
     /* hide controls */
     hwndTitle = WinWindowFromID(hwndFrame, FID_TITLEBAR);
     hwndSys   = WinWindowFromID(hwndFrame, FID_SYSMENU);
     hwndMin   = WinWindowFromID(hwndFrame, FID_MINMAX);

     /* Store Titlebar coordinates */
     WinQueryWindowPos(hwndTitle, &SwpTitle);

     WinSetParent(hwndTitle, HWND_OBJECT, FALSE );
     WinSetParent(hwndSys,   HWND_OBJECT, FALSE );
     WinSetParent(hwndMin,   HWND_OBJECT, FALSE );
  }
  else
  {
     /* restore controls */
     WinSetParent(hwndTitle, hwndFrame, FALSE);
     WinSetParent(hwndSys,   hwndFrame, FALSE);
     WinSetParent(hwndMin,   hwndFrame, FALSE);
  }

  WinSendMsg(hwndFrame, WM_UPDATEFRAME,
       (MPARAM)(FCF_TITLEBAR | FCF_SYSMENU | FCF_MINBUTTON), NULL);

  if (!bOn)
    WinSetWindowPos(hwndFrame, HWND_TOP, SwpFrame.x, SwpFrame.y,
                    SwpFrame.cx, SwpFrame.cy - SwpTitle.cy,
                    SWP_SIZE | SWP_SHOW);
  else
  {
    WinSetWindowPos(hwndFrame, HWND_TOP, SwpFrame.x, SwpFrame.y,
                    SwpFrame.cx, SwpFrame.cy + SwpTitle.cy,
                    SWP_SIZE | SWP_SHOW);

    // update status of checkable sys menu items
    WinSendMsg(hwndSys, MM_SETITEMATTR,
               MPFROM2SHORT (WM_TOGGLE_FLOAT_ONTOP, TRUE),
               MPFROM2SHORT (MIA_CHECKED, pGlobal->floatOnTop ? MIA_CHECKED : 0));

  }
}

/**********************************************************************
 * Function: RecalcWinPos
 * Info    : Recalculates the window position if necessary
 * Result  : -
 **********************************************************************/
void RecalcWinPos(HWND hwnd)
{
  SWP Swp;
  LONG cxScr = WinQuerySysValue(HWND_DESKTOP, SV_CXSCREEN);
  LONG cyScr = WinQuerySysValue(HWND_DESKTOP, SV_CYSCREEN);

  if (WinQueryWindowPos(hwnd, &Swp))
  {
    if (Swp.x + Swp.cx > cxScr)
        Swp.x = cxScr - Swp.cx;

    if (Swp.y + Swp.cy > cyScr)
        Swp.y = cyScr - Swp.cy;

    if (Swp.x < 0)
      Swp.x = 0;

    if (Swp.y < 0)
      Swp.y = 0;
  }

  WinSetWindowPos(hwnd, NULL, Swp.x, Swp.y, 0, 0, SWP_MOVE);
}

/**********************************************************************/
/**********************************************************************/
/* -- EOF -- */


