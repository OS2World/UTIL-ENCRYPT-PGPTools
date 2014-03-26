/**********************************************************************
 *
 *  PGPTools - PM shell for PGP v5.0 for OS/2
 *
 *  Module   : PPHRASE.C
 *  Info     : Passphrase obtaining dialog
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
 *  110499 - Created
 *  230499 - PassphraseDlgProc() modified
 *  100699 - Positioning of added passphrase entryfield fixed, should
 *           now work properly with different screen resolutions
 *         - passphrase text (if existing) is now selected by default
 *           using EM_SETSEL message
 *  210699 - Fix in positioning the passphrase entryfield
 *  140799 - Owner-window handles for WinMessageBox() changed
 *  160799 - SC_CLOSE command trapped in dialog window proc
 *           and redirected to invoke DID_CANCEL action
 *
 **********************************************************************/

#include "pgptools.h"
#include "command.h"
#include "profile.h"
#include "pphrasex.h"
#include "filedlg.h"
#include "keylist.h"
#include "pphrase.h"
#include "pgphelp.h"

tKeyElement PrivKeyToSign;
CHAR PPhraseText[PPHRASE_SIZE] = "";

void AddEntryField(HWND hwnd, BOOL HideText);

MRESULT EXPENTRY PassphraseDlgProc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2);

/* Subclassing */
MRESULT EXPENTRY HideCheckboxWindowProc(HWND hwnd,ULONG msg,MPARAM mp1,MPARAM mp2);
PFNWP DefHideCheckboxWindowProc;

/**********************************************************************
 * Function: GetPassphrase
 * Info    : Get passphrase for signing purposes
 * Result  : TRUE if OK, else FALSE
 **********************************************************************/
BOOL GetPassphrase(HWND hwnd, tJobDesc *CurJob)
{
  PPhraseDlgData DlgData;

  DlgData.cb = sizeof(PPhraseDlgData);
  DlgData.JobType = CurJob->Job;
  DlgData.SrcType = CurJob->SrcType;

  INIT_ELEMENT(PrivKeyToSign);

  return (BOOL) WinDlgBox(HWND_DESKTOP,
                          hwnd,
                          PassphraseDlgProc,
                          hRessourceModule,
                          DID_PASSPHRASE_DLG,
                          (PVOID)&DlgData);
}


/**********************************************************************
 * Function: PassphraseDlgProc
 * Info    : Dialog window procedure to get passphrase for signing
 * Result  : TRUE or FALSE
 **********************************************************************/
MRESULT EXPENTRY PassphraseDlgProc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2)
{

 static pPPhraseDlgData pCurData; /* MUST be static here! */
 HWND hHidePhraseBox;
 CHAR TempPPhrase[PPHRASE_SIZE] = "";
 CHAR ElementText[LIST_ENTRY_LEN];

 switch (msg)
 {
    case WM_INITDLG:
      ShortenSysMenu(hwnd);
      CenterWindow(hwnd);
      WinCheckButton(hwnd, DID_PASSPHRASE_TEXT, ProfileData.Flags.PgpTextOutput);
      WinCheckButton(hwnd, DID_PASSPHRASE_ASCII, ProfileData.Flags.PgpASCIIArmor);
      WinCheckButton(hwnd, DID_PASSPHRASE_DETACH, ProfileData.Flags.PgpDetach);
      /* always recommend to type passphrase hidden */
      WinCheckButton(hwnd, DID_PASSPHRASE_HIDE, TRUE);
      /* Get pointer to PPhraseDlgData structure */
      pCurData = PVOIDFROMMP(mp2);
      if (eClipBoard == pCurData->SrcType)
      {
         WinEnableWindow(WinWindowFromID(hwnd, DID_PASSPHRASE_DETACH), FALSE);
      }

      if ((eEncSign == pCurData->JobType) ||
          (eDecVerify == pCurData->JobType)
         )
      {
       WinDestroyWindow(WinWindowFromID(hwnd, DID_PASSPHRASE_TEXT));
       WinDestroyWindow(WinWindowFromID(hwnd, DID_PASSPHRASE_DETACH));
       if (eDecVerify == pCurData->JobType)
        WinDestroyWindow(WinWindowFromID(hwnd, DID_PASSPHRASE_ASCII));
      }

      /* subclassing hide typing checkbox */
      hHidePhraseBox = WinWindowFromID(hwnd, DID_PASSPHRASE_HIDE);
      DefHideCheckboxWindowProc = WinSubclassWindow(hHidePhraseBox,
                                                    (PFNWP) HideCheckboxWindowProc);
      WinSendDlgItemMsg(hwnd,
                        DID_PASSPHRASE_KEY_CB,
                        EM_SETTEXTLIMIT,
                        MPFROMSHORT (LIST_ENTRY_LEN),
                        NULL);
      InsertListEntries(hwnd);
      AddEntryField(hwnd, TRUE); /* override the existing entryfield */
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
          WinQueryWindowText(WinWindowFromID(hwnd, DID_PASSPHRASE_KEY_CB),
                             sizeof(ElementText), ElementText);

          if (!KeyFoundInList(pKeyListAnchor, ElementText, &PrivKeyToSign))
          {
            Len = WinLoadString(Hab, hRessourceModule,
                                IDS_GENERAL_PROCESS_FAILURE,
                                MSGSTRN_MAXLEN, Msg);
            WinMessageBox(HWND_DESKTOP, hwnd, Msg, NULL, 0, MB_ERROR | MB_OK);
            WinDismissDlg(hwnd, FALSE);
            break;
          }

          WinQueryWindowText(WinWindowFromID(hwnd, DID_PASSPHRASE_EB),
                             sizeof(TempPPhrase), TempPPhrase);

          if (0 == strcmp(TempPPhrase, ""))
          {
            Len = WinLoadString(Hab, hRessourceModule, IDS_ENTER_PASSPHRASE_WARNING,
                                MSGSTRN_MAXLEN, Msg);
            WinMessageBox(HWND_DESKTOP, hwnd, Msg, NULL, 0L, MB_OK | MB_WARNING);
            break;
          }

          if ((eEncSign != pCurData->JobType) &&
              (eDecVerify != pCurData->JobType)
             )
          {
            if (eClipBoard != pCurData->SrcType)
            {
             JobDesc.Detached =
             ProfileData.Flags.PgpDetach     = (BOOL) WinSendDlgItemMsg(hwnd,
                                                                        DID_PASSPHRASE_DETACH,
                                                                        BM_QUERYCHECK,
                                                                        NULL,
                                                                        NULL);

            }
            else
             JobDesc.Detached = FALSE;

            JobDesc.TextOutput =
            ProfileData.Flags.PgpTextOutput = (BOOL) WinSendDlgItemMsg(hwnd,
                                                                       DID_PASSPHRASE_TEXT,
                                                                       BM_QUERYCHECK,
                                                                       NULL,
                                                                       NULL);
          }
          else
          {
            JobDesc.TextOutput = FALSE;
            JobDesc.Detached = FALSE;
          }

          if (eDecVerify != pCurData->JobType)
          {
            JobDesc.ASCIIArmor =
            ProfileData.Flags.PgpASCIIArmor = (BOOL) WinSendDlgItemMsg(hwnd,
                                                                       DID_PASSPHRASE_ASCII,
                                                                       BM_QUERYCHECK,
                                                                       NULL,
                                                                       NULL);
          }
          else
           JobDesc.ASCIIArmor = FALSE;

          strcpy(PPhraseText, TempPPhrase);
          WinDismissDlg(hwnd, TRUE);
         break;

        case DID_CANCEL:
          WinDismissDlg(hwnd, FALSE);
         break;

        case WM_CHECK_HIDESTATE:
          AddEntryField(hwnd,
                        WinQueryButtonCheckstate(hwnd, DID_PASSPHRASE_HIDE));
         break;

        case WM_SETFOCUS_TO_EB:
          WinSetFocus(HWND_DESKTOP, WinWindowFromID(hwnd, DID_PASSPHRASE_EB));
         break;

      }
     break;

    case WM_HELP:
      DisplayHelp(IDL_PASSPHRASE_HELP);
     break;

    default:
      return WinDefDlgProc (hwnd, msg, mp1, mp2);

 }

 return (MRESULT) FALSE;

}

/**********************************************************************
 * Function: HideCheckboxWindowProc
 * Info    : Subclassed window procedure for hide checkbox
 * Result  : TRUE or FALSE
 **********************************************************************/
MRESULT EXPENTRY HideCheckboxWindowProc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2)
{
   HWND hwndParent;

   switch(msg)
   {

    /* check for pressed hotkey and mouse event */
    case WM_CHAR:
     if (SHORT1FROMMP(mp1) & KC_VIRTUALKEY)
      if (SHORT2FROMMP(mp2) == VK_TAB) /* trap TAB key */
       break;
      /*
       * fall through to send window message!
       */

    case WM_BUTTON1CLICK:
      hwndParent = WinQueryWindow(hwnd, QW_PARENT);
      WinSendMsg(hwndParent, WM_COMMAND, (MPARAM) WM_CHECK_HIDESTATE, (MPARAM) 0);
      /*
       * fall through to allow rest of proper window handling
       * etc.
       */

   }

  return DefHideCheckboxWindowProc(hwnd, msg, mp1, mp2);
}

/**********************************************************************
 * Function: AddEntryField
 * Info    : Add entryfield to enter passphrase. Done in this way to
 *           modify the window's style dependent on the HideText flag.
 * Result  : -
 **********************************************************************/
void AddEntryField(HWND hwnd, BOOL HideText)
{

   HPS hps;
   FONTMETRICS fm;
   POINTL pointl;
   LONG FieldLen;

   HWND hPhraseEntry;
   ULONG Style;
   CHAR TempPPhrase[PPHRASE_SIZE] = "";

   pointl.x = 0;
   pointl.y = 0;

   hPhraseEntry = WinWindowFromID(hwnd, DID_PASSPHRASE_EB);

   if (NULLHANDLE != hPhraseEntry)
   {

     hps = WinGetPS(hPhraseEntry);

     GpiQueryFontMetrics(hps, sizeof(FONTMETRICS), &fm);

     FieldLen = fm.lAveCharWidth*80; /* constant width */

     WinQueryWindowText(hPhraseEntry, sizeof(TempPPhrase),
                        TempPPhrase);

     if (0 != strcmp(TempPPhrase, ""))
      strcpy(PPhraseText, TempPPhrase);

     WinReleasePS(hps);

     /*
      * Even if the entryfield coordinates are already given
      * by the default dialog window they must be set with fixed values
      * here since a WinMapWindowPoints/WinMapDlgPoints calculation
      * cumulatively always adds a small pixel offset value that causes
      * the entryfield to be finally moved outside of the dialog window
      * while toggling the hide status! Who knows why?
      */

     pointl.x=15;
     pointl.y=53;

     WinMapDlgPoints(hPhraseEntry, &pointl, 1, TRUE);

     WinDestroyWindow(hPhraseEntry);

   }
   else
    return;

   Style = ES_MARGIN | ES_AUTOSCROLL | WS_TABSTOP | WS_GROUP;
   if (HideText)
    Style |= ES_UNREADABLE;

   hPhraseEntry = WinCreateWindow(hwnd,
                                  WC_ENTRYFIELD,
                                  "",
                                  Style,
                                  pointl.x,
                                  pointl.y,
                                  FieldLen,
                                  fm.lMaxBaselineExt+2,
                                  hwnd,
                                  HWND_TOP,
                                  DID_PASSPHRASE_EB,
                                  NULL,
                                  NULL);

   WinSendDlgItemMsg(hwnd, DID_PASSPHRASE_EB, EM_SETTEXTLIMIT,
                     MPFROMSHORT(PPHRASE_SIZE), NULL);
   WinSetWindowText(hPhraseEntry, PPhraseText);
   WinSendDlgItemMsg(hwnd, DID_PASSPHRASE_EB, EM_SETSEL,
                     MPFROM2SHORT (0,PPHRASE_SIZE+1), NULL);
   WinShowWindow(hPhraseEntry, TRUE);

   /* set focus to passphrase entryfield */
   WinPostMsg(hwnd, WM_COMMAND, (MPARAM) WM_SETFOCUS_TO_EB, (MPARAM) 0);

}

/**********************************************************************
 * Function: InsertCBoxEntries
 * Info    : Fill up combo box with secret keys to sign with
 * Result  : -
 **********************************************************************/
void InsertListEntries(HWND hwnd)
{
  BOOL Init = FALSE;
  tKeyElement *pElement = pKeyListAnchor;
  CHAR ElementText[256];

  while (NULL != pElement)
  {
    if (ePrivKey == pElement->KeyType)
    {
      sprintf(ElementText, "%s (ID: %s)", pElement->UserID, pElement->KeyID);
      WinSendDlgItemMsg (hwnd,
                         DID_PASSPHRASE_KEY_CB,
                         LM_INSERTITEM,
                         MPFROMSHORT (LIT_END),
                         ElementText);
       if (!Init)
       {
        WinSetWindowText(WinWindowFromID(hwnd, DID_PASSPHRASE_KEY_CB),
                         ElementText);
        Init = TRUE;
       }
    }

    pElement = pElement->pNext;
  }

}

/**********************************************************************/
/**********************************************************************/
/* -- EOF -- */

