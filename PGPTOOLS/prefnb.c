/**********************************************************************
 *
 *  PGPTools - PM shell for PGP v5.0 for OS/2
 *
 *  Module   : PREFNB.C
 *  Info     : Preferences notebook
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
 *  210699 - Created
 *  250699 - Notebook pages added
 *  260699 - Fix: Ressources pointed to by the pPointerDialog pointers
 *           must be freed at latest when notebook is being closed
 *  140799 - Owner-window handles for WinMessageBox() changed
 *  160799 - SC_CLOSE command trapped in dialog window proc
 *           and redirected to invoke DID_CANCEL action
 *  271299 - DID_SHOW_HINT_WINDOW in "General" notebook page added
 *  280900 - DID_SMALL_ICONS in "General" notebook page added
 *
 **********************************************************************/

#include "prefnbxx.h"
#include "command.h"
#include "profile.h"
#include "filedlg.h"
#include "pgphelp.h"
#include "pgptools.h"
#include "dllhook.h"
#include "hint.h"

extern GLOBALS *pGlobal;

MRESULT EXPENTRY PrefGeneralDlgProc (HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2);
MRESULT EXPENTRY PrefFilesDlgProc (HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2);
static BOOL UpdatePgpCfgFile(void);

static PRFDATA TempData;
static HWND hwndGeneralWindow;
static HWND hwndFilesWindow;
static ULONG ulGeneralPageId;
static ULONG ulFilesPageId;
static PDLGTEMPLATE pPointerDialog1 = NULL,
                    pPointerDialog2 = NULL;
static BOOL LastIconState;

/**********************************************************************
 * Function: UpdatePgpCfgFile
 * Info    : Updates PGP.CFG with public and private key filenames
 *           after making a backup copy
 *           Due to an obvious bug in PGP v5.0 GA release pgpk.exe
 *           ignores to process keyring files passed by commandline
 *           options "+pubring=" and "+secring=". Therefore we must
 *           update the PGP.CFG file.
 *
 * Result  : TRUE or FALSE
 **********************************************************************/

static BOOL UpdatePgpCfgFile(void)
{
  FILE *fpIn, *fpOut;
  BOOL PubRingFound = FALSE,
       SecRingFound = FALSE;
  CHAR Name[CCHMAXPATH],
       OldName[CCHMAXPATH],
       Line[128];

  strcpy(Name, PGPPath);
  strcpy(OldName, Name);
  strcat(OldName, "\\PGP.BAK");
  strcat(Name, "\\");
  strcat(Name, DefaultConfigFile);

  if (FileExist(OldName))
   remove(OldName);
  rename(Name, OldName); /* rename PGP.CFG to PGP.BAK */

  if (NULL == (fpIn = fopen(OldName, "rt")))
   return FALSE;
  if (NULL == (fpOut = fopen(Name, "wt")))
  {
   fclose(fpIn);
   rename(OldName, Name); /* rename PGP.BAK to PGP.CFG again */
   return FALSE;
  }

  while(fgets(Line, 128, fpIn) != NULL)
  {
   if ((0 == strncmp(Line, "PubRing", 7)) ||
       (0 == strncmp(Line, "PUBRING", 7))
      )
   {
     PubRingFound = TRUE;
     strcpy(Line, "PubRing=");
     strcat(Line, ProfileData.PublicKeyFile);
     strcat(Line, "\n");
   }
   else
    if ((0 == strncmp(Line, "SecRing=", 7)) ||
        (0 == strncmp(Line, "SECRING=", 7))
       )
    {
      SecRingFound = TRUE;
      strcpy(Line, "SecRing=");
      strcat(Line, ProfileData.PrivateKeyFile);
      strcat(Line, "\n");
    }

   fputs(Line, fpOut);

  }

  fclose(fpIn);

  if (!PubRingFound)
  {
    strcpy(Line, "PubRing=");
    strcat(Line, ProfileData.PublicKeyFile);
    strcat(Line, "\n");
    fputs(Line, fpOut);
  }

  if (!SecRingFound)
  {
    strcpy(Line, "SecRing=");
    strcat(Line, ProfileData.PrivateKeyFile);
    strcat(Line, "\n");

    fputs(Line, fpOut);
  }

  fclose(fpOut);

  return TRUE;

}

/**********************************************************************
 * Function: LoadNoteBookPages
 * Info    : Load notebook pages
 * Result  :
 **********************************************************************/
static BOOL LoadNoteBookPages(HWND hwndNoteBook)
{

  /* Insert "General" page */
  if (NO_ERROR != DosGetResource(hRessourceModule,
                                 RT_DIALOG,
                                 DID_GENERAL_DLG,
                                 &pPointerDialog1))
  {
   pPointerDialog1 = NULL;
   return FALSE;
  }

  ulGeneralPageId = (LONG)WinSendDlgItemMsg(hwndNoteBook, DID_PREF_NOTEBOOK,
       BKM_INSERTPAGE, NULL,
       MPFROM2SHORT((BKA_STATUSTEXTON | BKA_AUTOPAGESIZE | BKA_MAJOR),
       BKA_LAST));

  if ( !ulGeneralPageId)
  {
    DosFreeResource(&pPointerDialog1);
    pPointerDialog1 = NULL;
    return FALSE;
  }

#if 0
  if ( !WinSendDlgItemMsg(hwndNoteBook, DID_PREF_NOTEBOOK,
       BKM_SETSTATUSLINETEXT, MPFROMLONG(ulGeneralPageId),
       MPFROMP("Page 1 of 2")))
    return FALSE;
#endif

  Len = WinLoadString(Hab, hRessourceModule, IDS_GENERAL_TAB,
                      TITLESTRN_MAXLEN, Title);

  if (!WinSendDlgItemMsg(hwndNoteBook, DID_PREF_NOTEBOOK,
      BKM_SETTABTEXT, MPFROMLONG(ulGeneralPageId), Title))
  {
    DosFreeResource(&pPointerDialog1);
    pPointerDialog1 = NULL;
    return FALSE;
  }

  hwndGeneralWindow = WinCreateDlg(hwndNoteBook,
                                   hwndNoteBook,
                                   PrefGeneralDlgProc,
                                   pPointerDialog1,
                                   NULL);
 if (NULLHANDLE != hwndGeneralWindow)
  WinSendDlgItemMsg(hwndNoteBook, DID_PREF_NOTEBOOK,
                    BKM_SETPAGEWINDOWHWND,
                    MPFROMLONG(ulGeneralPageId),
                    MPFROMHWND(hwndGeneralWindow));
 else
 {
    DosFreeResource(&pPointerDialog1);
    pPointerDialog1 = NULL;
    return FALSE;
 }

  /* Insert "Files" page */
 if (NO_ERROR != DosGetResource(hRessourceModule,
                                RT_DIALOG,
                                DID_FILES_DLG,
                                &pPointerDialog2))
 {
    DosFreeResource(&pPointerDialog1);
    pPointerDialog1 = NULL;
    pPointerDialog2 = NULL;
    return FALSE;
 }

  ulFilesPageId = (LONG)WinSendDlgItemMsg(hwndNoteBook, DID_PREF_NOTEBOOK,
       BKM_INSERTPAGE, NULL,
       MPFROM2SHORT((BKA_STATUSTEXTON | BKA_AUTOPAGESIZE | BKA_MAJOR),
       BKA_LAST));

  if (!ulFilesPageId)
  {
    DosFreeResource(&pPointerDialog1);
    DosFreeResource(&pPointerDialog2);
    pPointerDialog1 = NULL;
    pPointerDialog2 = NULL;
    return FALSE;
  }

  Len = WinLoadString(Hab, hRessourceModule, IDS_FILES_TAB,
                      TITLESTRN_MAXLEN, Title);

  if (!WinSendDlgItemMsg(hwndNoteBook, DID_PREF_NOTEBOOK,
      BKM_SETTABTEXT, MPFROMLONG(ulFilesPageId), Title))
  {
    DosFreeResource(&pPointerDialog1);
    DosFreeResource(&pPointerDialog2);
    pPointerDialog1 = NULL;
    pPointerDialog2 = NULL;
    return FALSE;
  }

  hwndFilesWindow = WinCreateDlg(hwndNoteBook,
                                 hwndNoteBook,
                                 PrefFilesDlgProc,
                                 pPointerDialog2,
                                 NULL);
 if (NULLHANDLE != hwndFilesWindow)
  WinSendDlgItemMsg(hwndNoteBook, DID_PREF_NOTEBOOK,
                    BKM_SETPAGEWINDOWHWND,
                    MPFROMLONG(ulFilesPageId),
                    MPFROMHWND(hwndFilesWindow));
 else
 {
   DosFreeResource(&pPointerDialog1);
   DosFreeResource(&pPointerDialog2);
   pPointerDialog1 = NULL;
   pPointerDialog2 = NULL;
   return FALSE;
 }

 return TRUE;
}

/**********************************************************************
 * Function: PrefSetStrings
 * Info    : (Re)Set strings preferences from profile structure
 * Result  :
 **********************************************************************/
static void PrefSetStrings(HWND hwnd, PRFDATA *pTempData)
{
 HWND hwndText;

 /* Set text entries and entry maxlen */
 hwndText = WinWindowFromID(hwnd, DID_PUBLIC_FILE_STRN);
 WinSetWindowText(hwndText, pTempData->PublicKeyFile);

 hwndText = WinWindowFromID(hwnd, DID_PRIVATE_FILE_STRN);
 WinSetWindowText(hwndText, pTempData->PrivateKeyFile);

 hwndText = WinWindowFromID(hwnd, DID_RANDOM_FILE_STRN);
 WinSetWindowText(hwndText, pTempData->RandomSeedFile);

}

/**********************************************************************
 * Function: PrefSaveParams
 * Info    : Save preferences data to profile settings
 * Result  :
 **********************************************************************/
static void PrefSaveParams(HWND hwnd, PRFDATA *pTempData)
{
 HWND hwndText;
 LONG h, m, s;

 hwndText = WinWindowFromID(hwndGeneralWindow, DID_COMMENT_STRN);
 WinQueryWindowText(hwndText, sizeof(pTempData->ASCIIComment),
                    pTempData->ASCIIComment);

 hwndText = WinWindowFromID(hwndGeneralWindow, DID_SEND_KEYSRV_STRN);
 WinQueryWindowText(hwndText, sizeof(pTempData->SendKeyServer),
                    pTempData->SendKeyServer);

 hwndText = WinWindowFromID(hwndGeneralWindow, DID_EDITOR_STRN);
 WinQueryWindowText(hwndText, sizeof(pTempData->EditorFile),
                    pTempData->EditorFile);

 WinSendDlgItemMsg(hwndGeneralWindow, DID_CACHE_SPIN_HOUR, SPBM_QUERYVALUE,
                   (MPARAM) &h, MPFROM2SHORT(NULL, SPBQ_ALWAYSUPDATE));
 WinSendDlgItemMsg(hwndGeneralWindow, DID_CACHE_SPIN_MIN, SPBM_QUERYVALUE,
                   (MPARAM) &m, MPFROM2SHORT(NULL, SPBQ_ALWAYSUPDATE));
 WinSendDlgItemMsg(hwndGeneralWindow, DID_CACHE_SPIN_SEC, SPBM_QUERYVALUE,
                   (MPARAM) &s, MPFROM2SHORT(NULL, SPBQ_ALWAYSUPDATE));

 pTempData->Flags.CacheTime = (ULONG)(h*3600+m*60+s);
 JobDesc.EncryptToSelf =
 pTempData->Flags.PgpEncryptToSelf = (BOOL) WinSendDlgItemMsg(hwndGeneralWindow,
                                                        DID_ENCRYPT_TO_SELF,
                                                        BM_QUERYCHECK,
                                                        NULL,
                                                        NULL);
 pGlobal->floatOnTop =
 pTempData->Flags.AlwaysOnTop      = (BOOL) WinSendDlgItemMsg(hwndGeneralWindow,
                                                        DID_ALWAYS_ON_TOP,
                                                        BM_QUERYCHECK,
                                                        NULL,
                                                        NULL);

 SuppressPGPKeysHint =
 pTempData->Flags.SuppressHint     = !(BOOL) WinSendDlgItemMsg(hwndGeneralWindow,
                                                        DID_SHOW_HINT_WINDOW,
                                                        BM_QUERYCHECK,
                                                        NULL,
                                                        NULL);

 pTempData->Flags.SmallIcons       = (BOOL) WinSendDlgItemMsg(hwndGeneralWindow,
                                                        DID_SMALL_ICONS,
                                                        BM_QUERYCHECK,
                                                        NULL,
                                                        NULL);

 hwndText = WinWindowFromID(hwndFilesWindow, DID_PUBLIC_FILE_STRN);
 WinQueryWindowText(hwndText, sizeof(pTempData->PublicKeyFile),
                    pTempData->PublicKeyFile);

 hwndText = WinWindowFromID(hwndFilesWindow, DID_PRIVATE_FILE_STRN);
 WinQueryWindowText(hwndText, sizeof(pTempData->PrivateKeyFile),
                    pTempData->PrivateKeyFile);

 hwndText = WinWindowFromID(hwndFilesWindow, DID_RANDOM_FILE_STRN);
 WinQueryWindowText(hwndText, sizeof(pTempData->RandomSeedFile),
                    pTempData->RandomSeedFile);

}

/**********************************************************************
 * Function: FileWarning
 * Info    : Display warning about missing key files
 * Result  : -
 **********************************************************************/

static void FileWarning(PSZ pFileName, ULONG MsgID)
{
  PSZ pStrn;

  if (NULL == pFileName)
   return;

  Len = WinLoadString(Hab, hRessourceModule, IDS_WARNING,
                      TITLESTRN_MAXLEN, Title);
  Len = WinLoadString(Hab, hRessourceModule, MsgID,
                      MSGSTRN_MAXLEN, Msg);
  pStrn = (PSZ) malloc((Len+strlen(pFileName)+1)*sizeof(CHAR));
  if (NULL != pStrn)
  {
   sprintf(pStrn, Msg, pFileName);
   WinAlarm(HWND_DESKTOP, WA_WARNING);
   WinMessageBox(HWND_DESKTOP, hwndMainDialog, pStrn, Title, 0, MB_WARNING | MB_OK);
   free(pStrn);
  }
}

/**********************************************************************
 * Function: PrefDlgProc
 * Info    : Preferences dialog window
 * Result  : TRUE or FALSE
 **********************************************************************/

MRESULT EXPENTRY PrefDlgProc (HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2)
{
 static BOOL DisMiss = FALSE;
 BOOL IsError;

 switch (msg)
      {

       case WM_INITDLG:
        {
         PINICHECK pIsNewStructure = (PINICHECK) mp2;
         memcpy(&TempData, &ProfileData, sizeof(ProfileData));
         UpdateCaption(hwnd, IDS_PREF_TITLE);
         ShortenSysMenu(hwnd);
         CenterWindow(hwnd);
         if (!LoadNoteBookPages(hwnd))
         {
          WinAlarm(HWND_DESKTOP, WA_ERROR);
          WinMessageBox(HWND_DESKTOP, hwnd, "Internal system error!", NULL, 0, MB_ERROR | MB_OK);
          WinPostMsg(hwnd, WM_CLOSE, (MPARAM) 0, (MPARAM) 0);
         }
         else
         {
           DisMiss = FALSE;
           WinPostMsg(hwnd, WM_COMMAND, (MPARAM) WM_CHECK_FILES, (MPARAM) 0);
         }
         LastIconState = TempData.Flags.SmallIcons;
         if (pIsNewStructure->State)
         {
            Len = WinLoadString(Hab, hRessourceModule, IDS_PLEASE_NOTE,
                                TITLESTRN_MAXLEN, Title);
            Len = WinLoadString(Hab, hRessourceModule, IDS_INIFILE_UPDATE_REQUIRED,
                                MSGSTRN_MAXLEN, Msg);
            WinMessageBox(HWND_DESKTOP, hwnd, Msg, Title, 0, MB_ICONEXCLAMATION | MB_OK);
         }
        }
        break;

       case WM_SYSCOMMAND:
         switch(SHORT1FROMMP(mp1))
         {
           case SC_CLOSE:
              WinSendMsg(hwnd, WM_COMMAND, (MPARAM) DID_CANCEL, (MPARAM) 0);
            break;

           default:
            return WinDefDlgProc (hwnd, msg, mp1, mp2);
         }
        break;

       case WM_COMMAND:
         switch(SHORT1FROMMP(mp1))
         {
           case DID_OK:
             DisMiss = TRUE;
             PrefSaveParams(hwnd, &TempData);
             WinSendMsg(hwnd, WM_COMMAND, (MPARAM) WM_CHECK_FILES, (MPARAM) 0);
            break;

           case DID_CANCEL:
             WinDismissDlg(hwnd, (ProfileData.Flags.FirstSetupDone) ? TRUE : FALSE);
            break;

           case WM_CHECK_FILES:
             IsError = FALSE;
             if (!FileExist(TempData.PublicKeyFile) ||
                 (0L == FileSize(NULL, TempData.PublicKeyFile))
                )
             {
               WinSendMsg(WinWindowFromID(hwnd, DID_PREF_NOTEBOOK),
                          BKM_TURNTOPAGE,
                          (MPARAM) ulFilesPageId,
                          NULL);
               FileWarning(TempData.PublicKeyFile, IDS_PUB_KEYFILE_NOT_EXIST);
               IsError = TRUE;
             }
             if (!FileExist(TempData.PrivateKeyFile) ||
                  (0L == FileSize(NULL, TempData.PrivateKeyFile))
                 )
             {
               WinSendMsg(WinWindowFromID(hwnd, DID_PREF_NOTEBOOK),
                          BKM_TURNTOPAGE,
                          (MPARAM) ulFilesPageId,
                          NULL);
               FileWarning(TempData.PrivateKeyFile, IDS_PRIV_KEYFILE_NOT_EXIST);
               IsError = TRUE;
             }

             if (!IsError && DisMiss)
             {
               /* now write profile after successful setup */
               memcpy(&ProfileData, &TempData, sizeof(ProfileData));
               ProfileData.Flags.SuppressHint = SuppressPGPKeysHint;
               ProfileData.Flags.FirstSetupDone = TRUE;
               WriteParams(Hab);
               UpdatePgpCfgFile();
               WinDismissDlg(hwnd, TRUE);
               if (LastIconState != TempData.Flags.SmallIcons)
               {
                  LONG Len;
                  Len = WinLoadString(Hab, hRessourceModule, IDS_PLEASE_NOTE,
                                      TITLESTRN_MAXLEN, Title);
                  Len = WinLoadString(Hab, hRessourceModule, IDS_PLEASE_RESTART,
                                      MSGSTRN_MAXLEN, Msg);
                  WinMessageBox(HWND_DESKTOP, hwnd, Msg, Title, 0, MB_ICONASTERISK | MB_OK);
               }
             }

             if (!ProfileData.Flags.FirstSetupDone)
               WinSendMsg(WinWindowFromID(hwnd, DID_PREF_NOTEBOOK),
                          BKM_TURNTOPAGE,
                          (MPARAM) ulFilesPageId,
                          NULL);
            break; /* WM_CHECK_FILES */
         }
        break;

       case WM_HELP:
         DisplayHelp(IDL_SETTINGS_HELP);
        break;

       case WM_CLOSE:
        if (NULL != pPointerDialog1)
        {
         DosFreeResource(&pPointerDialog1);
         pPointerDialog1 = NULL;
        }
        if (NULL != pPointerDialog2)
        {
         DosFreeResource(&pPointerDialog2);
         pPointerDialog2 = NULL;
        }
        /* no break: fall through to default branch!!! */

       default:
        return WinDefDlgProc (hwnd, msg, mp1, mp2);
      }

 return (MRESULT)FALSE;
}

/**********************************************************************
 * Function: PrefFilesDlgProc
 * Info    : Files preferences dialog window
 * Result  : TRUE or FALSE
 **********************************************************************/

MRESULT EXPENTRY PrefFilesDlgProc (HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2)
{

 switch (msg)
      {

       case WM_INITDLG:
         WinSendDlgItemMsg(hwnd, DID_PUBLIC_FILE_STRN, EM_SETTEXTLIMIT,
                           MPFROMSHORT(CCHMAXPATH), NULL);
         WinSendDlgItemMsg(hwnd, DID_PRIVATE_FILE_STRN, EM_SETTEXTLIMIT,
                           MPFROMSHORT(CCHMAXPATH), NULL);
         WinSendDlgItemMsg(hwnd, DID_RANDOM_FILE_STRN, EM_SETTEXTLIMIT,
                           MPFROMSHORT(CCHMAXPATH), NULL);
         PrefSetStrings(hwnd, &TempData);
        break;

       case WM_COMMAND:
         switch(SHORT1FROMMP(mp1))
         {

           case WM_BROWSE_PUBLIC_FILE:
             Len = WinLoadString(Hab, hRessourceModule, IDS_SELECT_PUBKEY_TITLE,
                                 TITLESTRN_MAXLEN, Title);

             FileSettingsSelection(hwnd, TempData.PublicKeyFile, Title, "*.pkr");
             PrefSetStrings(hwnd, &TempData);
            return (MRESULT)TRUE;

           case WM_BROWSE_PRIVATE_FILE:
             Len = WinLoadString(Hab, hRessourceModule, IDS_SELECT_PRIVKEY_TITLE,
                                 TITLESTRN_MAXLEN, Title);

             FileSettingsSelection(hwnd, TempData.PrivateKeyFile, Title, "*.skr");
             PrefSetStrings(hwnd, &TempData);
            return (MRESULT)TRUE;

           case WM_BROWSE_RANDOM_FILE:
             Len = WinLoadString(Hab, hRessourceModule, IDS_SELECT_RANDSEED_TITLE,
                                 TITLESTRN_MAXLEN, Title);

             FileSettingsSelection(hwnd, TempData.RandomSeedFile, Title, "*.bin");
             PrefSetStrings(hwnd, &TempData);
            return (MRESULT)TRUE;
         }
        break;

       default:
        return WinDefDlgProc (hwnd, msg, mp1, mp2);
      }

 return (MRESULT)FALSE;
}

/**********************************************************************
 * Function: PrefGeneralDlgProc
 * Info    : General preferences dialog window
 * Result  : TRUE or FALSE
 **********************************************************************/

MRESULT EXPENTRY PrefGeneralDlgProc (HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2)
{
 ULONG h, m, s;

 switch (msg)
      {

       case WM_INITDLG:
         WinSendDlgItemMsg(hwnd, DID_COMMENT_STRN, EM_SETTEXTLIMIT,
                           MPFROMSHORT(COMMENT_MAXLEN), NULL);
         WinSendDlgItemMsg(hwnd, DID_SEND_KEYSRV_STRN, EM_SETTEXTLIMIT,
                           MPFROMSHORT(CCHMAXPATH), NULL);
         WinSendDlgItemMsg(hwnd, DID_EDITOR_STRN, EM_SETTEXTLIMIT,
                           MPFROMSHORT(CCHMAXPATH), NULL);
         WinSendDlgItemMsg(hwnd, DID_CACHE_SPIN_HOUR, SPBM_SETLIMITS,
                           (MPARAM) 100, (MPARAM) 0);
         WinSendDlgItemMsg(hwnd, DID_CACHE_SPIN_MIN, SPBM_SETLIMITS,
                           (MPARAM) 59, (MPARAM) 0);
         WinSendDlgItemMsg(hwnd, DID_CACHE_SPIN_SEC, SPBM_SETLIMITS,
                           (MPARAM) 59, (MPARAM) 0);
         h = ProfileData.Flags.CacheTime / 3600;
         m = (ProfileData.Flags.CacheTime % 3600) / 60;
         s = (ProfileData.Flags.CacheTime % 3600) % 60;

         WinSendDlgItemMsg(hwnd, DID_CACHE_SPIN_HOUR, SPBM_SPINUP,
                           (MPARAM) h, NULL);
         WinSendDlgItemMsg(hwnd, DID_CACHE_SPIN_MIN, SPBM_SPINUP,
                           (MPARAM) m, NULL);
         WinSendDlgItemMsg(hwnd, DID_CACHE_SPIN_SEC, SPBM_SPINUP,
                           (MPARAM) s, NULL);
         WinSetWindowText(WinWindowFromID(hwnd, DID_COMMENT_STRN),
                          TempData.ASCIIComment);
         WinSetWindowText(WinWindowFromID(hwnd, DID_SEND_KEYSRV_STRN),
                          TempData.SendKeyServer);
         WinSetWindowText(WinWindowFromID(hwnd, DID_EDITOR_STRN),
                          TempData.EditorFile);
         WinCheckButton(hwnd, DID_ENCRYPT_TO_SELF, TempData.Flags.PgpEncryptToSelf);
         WinCheckButton(hwnd, DID_ALWAYS_ON_TOP, TempData.Flags.AlwaysOnTop);
         WinCheckButton(hwnd, DID_SHOW_HINT_WINDOW, !TempData.Flags.SuppressHint);
         WinCheckButton(hwnd, DID_SMALL_ICONS, TempData.Flags.SmallIcons);
         if (!PGPKeysToolExists)
         {
           WinEnableWindow(WinWindowFromID(hwnd, DID_SEND_KEYSRV_GRP), FALSE);
           WinEnableWindow(WinWindowFromID(hwnd, DID_SEND_KEYSRV_STRN), FALSE);
         }
        break;

       default:
        return WinDefDlgProc (hwnd, msg, mp1, mp2);
      }

 return (MRESULT)FALSE;
}
/**********************************************************************/
/**********************************************************************/
/* -- EOF -- */

