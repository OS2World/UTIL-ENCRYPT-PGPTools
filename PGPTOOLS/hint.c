/**********************************************************************
 *
 *  PGPTools - PM shell for PGP v5.0 for OS/2
 *
 *  Module   : HINT.C
 *  Info     : Show PGPKeys warning window
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
 *  271299 - Created
 *  040300 - ShortenSysMenu() call removed
 *
 **********************************************************************/


#include "pgptools.h"
#include "profile.h"
#include "hint_xx.h"
#include "hint.h"

BOOL SuppressPGPKeysHint = FALSE;

MRESULT EXPENTRY HintWinDlgProc (HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2);

/**********************************************************************
 * Function: DisplayHintWin
 * Info    : Show PGPKeys warning window
 * Result  : -
 **********************************************************************/
void DisplayHintWin(HWND hwnd)
{
  WinDlgBox(HWND_DESKTOP,
            hwnd,
            HintWinDlgProc,
            hRessourceModule,
            IDD_PGPKEYS_HINT_DLG,
            NULL);
}

/**********************************************************************
 * Function: HintWinDlgProc
 * Info    : PGPKeys hint dialog window
 * Result  : TRUE or FALSE
 **********************************************************************/

MRESULT EXPENTRY HintWinDlgProc (HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2)
{

 switch (msg)
      {

       case WM_INITDLG:
         CenterWindow(hwnd);
        break;

       case WM_COMMAND:
         switch(SHORT1FROMMP(mp1))
         {

          case DID_OK:
            ProfileData.Flags.SuppressHint =
            SuppressPGPKeysHint = (BOOL) WinSendDlgItemMsg(hwnd,
                                                          IDD_PGPKEYS_HINT_ENABLE,
                                                          BM_QUERYCHECK,
                                                          NULL,
                                                          NULL);

            StoreFlags(Hab);
            WinDismissDlg(hwnd, TRUE);
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

