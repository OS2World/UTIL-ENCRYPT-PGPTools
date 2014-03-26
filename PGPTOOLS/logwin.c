/**********************************************************************
 *
 *  PGPTools - PM shell for PGP v5.0 for OS/2
 *
 *  Module   : LOGWIN.C
 *  Info     : Decrypt/verify result window
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
 *  120599 - Created
 *  271299 - Comments corrected
 *  300900 - DisplayLogfile() changed, message handling for
 *           DID_LOGWIN_RUN_EDITOR added
 *
 **********************************************************************/


#include "pgptools.h"
#include "pgphelp.h"
#include "logwinxx.h"
#include "logwin.h"

static PSZ pBuffer = NULL;
static LONG BufLen;
static BOOL EditClipBoard = FALSE;
static BOOL IsPrintable = TRUE;

MRESULT EXPENTRY LogwinDlgProc (HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2);

/**********************************************************************
 * Function: DisplayLogfile
 * Info    : Displaylog file after decrypting/verifying
 * Result  : TRUE, if log file should be removed after returning,
 *           else FALSE
 **********************************************************************/
BOOL DisplayLogfile(HWND hwnd, PSZ LogFile, PSZ TargetFile, BOOL FromClipBoard)
{
  BOOL Result;
  FILE *fp;
  int ch;
  PSZ pTemp;

  // Open log file
  if (NULL == (fp = fopen(LogFile, "rb")))
   return TRUE;

  BufLen = FileSize(fp, NULL);

  pBuffer = (PSZ) malloc(BufLen*sizeof(CHAR)+1);
  if (NULL == pBuffer)
  {
   fclose(fp);
   return TRUE;
  }

  pTemp = pBuffer;

  while(EOF != (ch = fgetc(fp)))
   *pTemp++ = ch;

  fclose(fp);

  // Check target file if it contains non-printable characters
  if (NULL != (fp = fopen(TargetFile, "rb")))
  {
    while(EOF != (ch = fgetc(fp)))
      if (!isprint(ch) &&
          (ch != 0x0D) && (ch != 0x0A)) // ignore CRLF!
      {
        IsPrintable = FALSE;
        break;
      }

    fclose(fp);
  }

  EditClipBoard = FromClipBoard;
  Result = (BOOL) WinDlgBox(HWND_DESKTOP,
                     hwnd,
                     LogwinDlgProc,
                     hRessourceModule,
                     DID_LOGWIN_DLG,
                     NULL);

  free(pBuffer);

  return Result;

}

/**********************************************************************
 * Function: LogWinDlgProc
 * Info    : Log dialog window
 * Result  : TRUE or FALSE
 **********************************************************************/

MRESULT EXPENTRY LogwinDlgProc (HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2)
{

 switch (msg)
 {

       case WM_INITDLG:
        {
         IPT ipt = 0;
         HWND hEditButton = WinWindowFromID(hwnd, DID_LOGWIN_RUN_EDITOR);

         CenterWindow(hwnd);
         ShortenSysMenu(hwnd);
         WinSendDlgItemMsg(hwnd,
                           DID_MLE_TEXT,
                           MLM_SETIMPORTEXPORT,
                           pBuffer,
                           (MPARAM) BufLen);
         WinSendDlgItemMsg(hwnd,
                           DID_MLE_TEXT,
                           MLM_SETTEXTLIMIT,
                           (MPARAM) BufLen,
                           NULL);
         WinSendDlgItemMsg(hwnd,
                           DID_MLE_TEXT,
                           MLM_IMPORT,
                           &ipt,
                           (MPARAM) BufLen);
         if (!IsPrintable && (NULLHANDLE != hEditButton))
            WinEnableWindow(hEditButton, FALSE);

        }
        break;

       case WM_HELP:
          DisplayHelp(IDL_LOGWIN_HELP);
        break;

       case WM_COMMAND:
         switch(SHORT1FROMMP(mp1))
         {

          case DID_OK:
              WinDismissDlg(hwnd, TRUE);
           break;

          case DID_LOGWIN_RUN_EDITOR:
           {
              HWND hwndOwner = WinQueryWindow(hwnd, QW_OWNER);
              WinDismissDlg(hwnd, !EditClipBoard);
              WinPostMsg(hwndOwner, WM_RUN_EDITOR, (MPARAM) EditClipBoard, 0L);
           }
           break;

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

