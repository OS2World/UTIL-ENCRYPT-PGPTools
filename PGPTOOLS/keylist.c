/**********************************************************************
 *
 *  PGPTools - PM shell for PGP v5.0 for OS/2
 *
 *  Module   : KEYLIST.C
 *  Info     : Key list management, not a nice method to handle the keys
 *             but it saves us from embedding original PGP code
 *             to evaluate the keyrings
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
 *  280499 - Created
 *  250699 - Checkbox DID_ENCRYPT_TO_SELF moved to preferences notebook
 *  140799 - Owner-window handles for WinMessageBox() changed,
 *           also the private key(s) is/are displayed in the listbox
 *           now, listbox entries are now re-arranged in another order
 *           and with a non-proportional font (System VIO 10pt.) if
 *           available
 *  160799 - SC_CLOSE command trapped in dialog window proc
 *           and redirected to invoke DID_CANCEL action
 *
 **********************************************************************/

#include "pgptools.h"
#include "command.h"
#include "profile.h"
#include "keylist.h"
#include "keylstxx.h"
#include "pgphelp.h"

static const CHAR RSAToken[]     = "RSA";
static const CHAR DSSToken[]     = "DSS";
static const CHAR UnknownToken[] = "???";
static const CHAR ListboxFont[]  = "10.System VIO";

tKeyElement *pKeyListAnchor = NULL;
tKeyElement *pOutKeyAnchor = NULL;

MRESULT EXPENTRY KeyListDlgProc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2);

/**********************************************************************
 * Function: FreeKeyList
 * Info    : Free list ressources
 * Result  : -
 **********************************************************************/

void FreeKeyList(tKeyElement **pAnchor)
{
  tKeyElement *pNext,
              *pList = *pAnchor;

  while(pList != NULL)
  {
   pNext = pList->pNext;
   free(pList);
   pList = pNext;
  }

  *pAnchor = NULL;
}

/**********************************************************************
 * Function: AddEntryToList
 * Info    : Add key data to list
 * Result  : FALSE if error, else TRUE
 **********************************************************************/

static BOOL AddEntryToList(tKeyElement KeyData, tKeyElement **pAnchor)
{

  tKeyElement *pNewEntry,
              *pList = *pAnchor;

  if (NULL != pList)
   while(NULL != pList->pNext)          /* search list end */
    pList = pList->pNext;

  pNewEntry = (tKeyElement *) malloc(sizeof(tKeyElement));

  if (NULL == pNewEntry)
   return FALSE;

  pNewEntry->KeyType = KeyData.KeyType;
  strcpy(pNewEntry->KeyAlgorithm, KeyData.KeyAlgorithm);
  strcpy(pNewEntry->KeyID, KeyData.KeyID);
  strcpy(pNewEntry->UserID, KeyData.UserID);
  pNewEntry->pNext = NULL;

  if (NULL == *pAnchor)
   *pAnchor = pNewEntry;
  else
   pList->pNext = pNewEntry;        /* neuen Eintrag einketten */

  return TRUE;

}

/**********************************************************************
 * Function: KeyFoundInList
 * Info    :
 * Result  : FALSE if error, else TRUE
 **********************************************************************/

BOOL KeyFoundInList(tKeyElement *pAnchor, PSZ Listtext, tKeyElement *pKeyData)
{
  const CHAR Delimiter[] = "0x";

  tKeyElement *pEntry = pAnchor;
  PSZ p;

  p = strstr(Listtext, Delimiter);
  if ((NULL == p) || (NULL == pKeyData))
   return FALSE;

  while(NULL != pEntry)
  {
    if(0 == strncmp(pEntry->KeyID, p, KEYID_SIZE))
    {
     memcpy((tKeyElement *)pKeyData, (tKeyElement *)pEntry, sizeof(tKeyElement));
     return TRUE;
    }
    pEntry = pEntry->pNext;
  }

  return FALSE;

}

/**********************************************************************
 * Function: BuildKeyList
 * Info    : Create list of keys from keyfiles
 * Result  : FALSE if error, else TRUE
 **********************************************************************/

BOOL BuildKeyList(PSZ Filename)
{
  FILE *fp;
  CHAR Line[128];
  BOOL Result = FALSE;
  tKeyElement Key;

  if (NULL != (fp = fopen(Filename, "rt")))
   while (NULL != fgets(Line, 128, fp))
   {
     if ((0 == strncmp(Line, "pub", 3)) ||
         (0 == strncmp(Line, "”ff", 3)) ||
         (0 == strncmp(Line, "öff", 3)) ||
         (0 == strncmp(Line, "prv", 3)) ||
         (0 == strncmp(Line, "sec", 3))
        )
     {
       if ((0 == strncmp(Line, "sec", 3)) ||
           (0 == strncmp(Line, "prv", 3))
          )
         Key.KeyType = ePrivKey;
       else
         Key.KeyType = ePubKey;

       strncpy(Key.KeyID, &Line[KEYID_OFFSET], sizeof(Key.KeyID));
       Key.KeyID[KEYID_SIZE] = '\0';

       strncpy(Key.KeyAlgorithm, &Line[KEY_ALGORITHM_OFFSET], sizeof(Key.KeyAlgorithm));
       Key.KeyAlgorithm[KEY_ALGORITHM_SIZE] = '\0';

       if ((0 != strcmp(Key.KeyAlgorithm, RSAToken)) &&
           (0 != strcmp(Key.KeyAlgorithm, DSSToken))
          )
          strcpy(Key.KeyAlgorithm, UnknownToken);

       while (NULL != fgets(Line, 128, fp))
       {
         if (0 == strncmp(Line, "uid", 3))
         {
           Line[strlen(Line)-1] = 0; /* Cut trailing \n */
           strncpy(Key.UserID, &Line[USERID_OFFSET], sizeof(Key.UserID));
           Key.UserID[sizeof(Key.UserID)] = '\0';
           Result = AddEntryToList(Key, &pKeyListAnchor);
           break;
         }
       }

       if (FALSE == Result) /* an error has occured */
        break;
     } /* valid paragraph */
   } /* while */

  fclose(fp);

  return Result;
}

/**********************************************************************
 * Function: SelectKeyToEncrypt
 * Info    : Open listbox window to select public key to encrypt to
 * Result  : -
 **********************************************************************/

BOOL SelectKeyToEncrypt(HWND hwnd)
{

  FreeKeyList(&pOutKeyAnchor);                  /* clear outkey list */
  return WinDlgBox(HWND_DESKTOP,
                   hwnd,
                   KeyListDlgProc,
                   hRessourceModule,
                   DID_ENCRYPT_DLG,
                   NULL);

}

/**********************************************************************
 * Function: FontAvail
 * Info    : Check if font passed by pFontstrn is available
 * Result  : TRUE if suitable font found, else FALSE
 **********************************************************************/

BOOL FontAvail(HWND hwnd, const CHAR * pFontStrn)
{
  HPS hps;
  BOOL Result = FALSE;
  PFONTMETRICS pFont, pfm;
  SHORT FontSize;
  LONG maxFonts, i,
       lTemp = 0L;
  PSZ pFontBuffer, p;


  if (NO_ERROR != DosAllocMem((void *) &pFontBuffer, (ULONG) ((strlen(pFontStrn)+1)*sizeof(CHAR)),
                              PAG_COMMIT | PAG_READ | PAG_WRITE))
   return FALSE;

  strcpy(pFontBuffer,pFontStrn);
  p = strchr(pFontBuffer, '.');

  if (NULL == p)
  {
   DosFreeMem(pFontBuffer);
   return FALSE;
  }

  *p = '\0';
  FontSize = atoi(pFontBuffer);

  hps = WinGetPS(hwnd);

  /* p+1 points now to the font's facename */
  maxFonts = GpiQueryFonts(hps, QF_PUBLIC, p+1, &lTemp, sizeof(FONTMETRICS), NULL);

  if (NO_ERROR != DosAllocMem((void *) &pFont, (ULONG) (maxFonts * sizeof(FONTMETRICS)),
                              PAG_COMMIT | PAG_READ | PAG_WRITE))
  {
    DosFreeMem(pFontBuffer);
    WinReleasePS(hps);
    return FALSE;
  }

  GpiQueryFonts(hps, QF_PUBLIC, p+1, &maxFonts, sizeof(FONTMETRICS), pFont);

  pfm = pFont;
  for (i=0; i < maxFonts; i++)
  {
    if (FontSize*10 == pfm->sNominalPointSize)
    {
     Result = TRUE;
     break;
    }
    pfm++;
  }

  DosFreeMem(pFont);
  DosFreeMem(pFontBuffer);
  WinReleasePS(hps);

  return Result;
}

/**********************************************************************
 * Function: KeyListDlgProc
 * Info    : Keylist dialog window
 * Result  : TRUE or FALSE
 **********************************************************************/

MRESULT EXPENTRY KeyListDlgProc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2)
{

 BOOL rc;
 tKeyElement *pElement = pKeyListAnchor;
 CHAR ElementText[LIST_ENTRY_LEN];
 SHORT Selection, NumOfSel = 0;

 switch (msg)
      {

       case WM_INITDLG:
         ShortenSysMenu(hwnd);
         CenterWindow(hwnd);
         WinSendDlgItemMsg(hwnd,
                           DID_ENCRYPT_LISTBOX,
                           EM_SETTEXTLIMIT,
                           MPFROMSHORT (LIST_ENTRY_LEN),
                           NULL);

         if (FontAvail(WinWindowFromID(hwnd, DID_ENCRYPT_LISTBOX), ListboxFont))
         {
          rc =  WinSetPresParam(WinWindowFromID(hwnd, DID_ENCRYPT_LISTBOX),
                                PP_FONTNAMESIZE, sizeof(ListboxFont)+1,
                                (PSZ) ListboxFont);
          rc =  WinSetPresParam(WinWindowFromID(hwnd, DID_ENCRYPT_CAPTION),
                                PP_FONTNAMESIZE, sizeof(ListboxFont)+1,
                                (PSZ) ListboxFont);
         }
         else
          /*
           * destroy listbox caption, since it wouldn't fit with the list
           * box entry positions anyway
           */
          WinDestroyWindow(WinWindowFromID(hwnd, DID_ENCRYPT_CAPTION));

         while (NULL != pElement)
         {
           if (ePrivKey != pElement->KeyType)
            sprintf(ElementText, "%-14s%-4s%8s%s",
                    pElement->KeyID,
                    pElement->KeyAlgorithm,
                    " ",
                    pElement->UserID);
           else
            sprintf(ElementText, "%-14s%-4s(priv)%2s%s",
                    pElement->KeyID,
                    pElement->KeyAlgorithm,
                    " ",
                    pElement->UserID);
           WinSendDlgItemMsg(hwnd,
                             DID_ENCRYPT_LISTBOX,
                             LM_INSERTITEM,
                             MPFROMSHORT (LIT_END),
                             ElementText);

           pElement = pElement->pNext;
         }

         /*
          * don't show ASCII armor checkbox here if Job == EncSign since it
          * already has been processed in the Passphrase dialog then
          */
         if (eEncrypt == JobDesc.Job)
          WinCheckButton(hwnd, DID_ENCRYPT_ASCII, ProfileData.Flags.PgpASCIIArmor);
         else
          WinDestroyWindow(WinWindowFromID(hwnd, DID_ENCRYPT_ASCII));
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
            {

              tKeyElement Entry;
              SHORT i,
                    StartIndex = LIT_FIRST;
              SHORT Count = (SHORT) WinSendDlgItemMsg(hwnd,
                                                      DID_ENCRYPT_LISTBOX,
                                                      LM_QUERYITEMCOUNT,
                                                      NULL, NULL);
              for (i=0; i<Count; i++)
              {

               Selection = (SHORT) WinSendDlgItemMsg(hwnd,
                                                     DID_ENCRYPT_LISTBOX,
                                                     LM_QUERYSELECTION,
                                                     MPFROMSHORT(StartIndex),
                                                     NULL);
               if (LIT_NONE != Selection)
               {
                 WinSendDlgItemMsg(hwnd,
                                   DID_ENCRYPT_LISTBOX,
                                   LM_QUERYITEMTEXT,
                                   MPFROM2SHORT(Selection ,sizeof(ElementText)),
                                   ElementText);
                 if (KeyFoundInList(pKeyListAnchor, ElementText, &Entry))
                  if (FALSE == AddEntryToList(Entry, &pOutKeyAnchor))
                  {
                    Len = WinLoadString(Hab, hRessourceModule,
                                        IDS_GENERAL_PROCESS_FAILURE,
                                        MSGSTRN_MAXLEN, Msg);
                    WinMessageBox(HWND_DESKTOP, hwnd, Msg, NULL, 0, MB_ERROR | MB_OK);
                    WinDismissDlg(hwnd, FALSE);
                    break;
                  }
                 ++NumOfSel;
                 StartIndex = Selection;
               }
               else
                break;

              } /* for */

              if (0 == NumOfSel) /* no entries selected */
                WinAlarm(HWND_DESKTOP, WA_NOTE);
              else
              {
                if (eEncrypt == JobDesc.Job)
                {
                 JobDesc.ASCIIArmor =
                 ProfileData.Flags.PgpASCIIArmor = (BOOL) WinSendDlgItemMsg(hwnd,
                                                                            DID_ENCRYPT_ASCII,
                                                                            BM_QUERYCHECK,
                                                                            NULL,
                                                                            NULL);
                }
                JobDesc.TextOutput = FALSE;
                JobDesc.Detached = FALSE;
                WinDismissDlg(hwnd, TRUE);
              }
            }
            break;

           case DID_CANCEL:
             WinDismissDlg(hwnd, FALSE);
            break;
         }
        break;

       case WM_HELP:
         DisplayHelp(IDL_LISTBOX_HELP);
        break;

       default:
        return WinDefDlgProc (hwnd, msg, mp1, mp2);
      }

 return (MRESULT)FALSE;
}

/**********************************************************************/
/**********************************************************************/
/* -- EOF -- */

