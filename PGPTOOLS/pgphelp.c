/**********************************************************************
 *
 *  PGPTools - PM shell for PGP v5.0 for OS/2
 *
 *  Module   : PGPHELP.C
 *  Info     : Online help system
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
 *  130599 - Created
 *  260699 - version.h included
 *  140799 - Owner-window handles for WinMessageBox() changed
 *
 **********************************************************************/

#include "pgptools.h"
#include "pgphelp.h"
#include "version.h"

static BOOL fHelpEnabled = FALSE;
static HWND hwndHelpInstance;
static HELPTABLE HTable[] = { 0, NULL, 0 };
static CHAR HelpTitle[TITLESTRN_MAXLEN+1];

/*------------------------------------------------------------------------*/

void HelpInit(HWND hwndFrame, const PSZ HelpFile)
{
    CHAR TitleText[TITLESTRN_MAXLEN+1];
    HELPINIT hini;

    /* if we return because of an error, Help will be disabled */
    fHelpEnabled = FALSE;

    /* inititalize help init structure */
    hini.cb = sizeof(HELPINIT);
    hini.ulReturnCode = 0L;

    hini.pszTutorialName = (PSZ)NULL;   /* if tutorial added, add name here */

    hini.phtHelpTable = (PHELPTABLE)NULLHANDLE;
    hini.hmodHelpTableModule = (HMODULE)0;
    hini.hmodAccelActionBarModule = (HMODULE)0;
    hini.idAccelTable = 0;
    hini.idActionBar = 0;

    Len = WinLoadString(Hab, hRessourceModule, IDS_HELP_TITLE,
                        TITLESTRN_MAXLEN, TitleText);
    sprintf(HelpTitle, TitleText, VERSION_STRN);

    hini.pszHelpWindowTitle = (PSZ) HelpTitle;

   /* if debugging, show panel ids, else don't */
#ifdef DEBUG
    hini.fShowPanelId = CMIC_SHOW_PANEL_ID;
#else
    hini.fShowPanelId = CMIC_HIDE_PANEL_ID;
#endif

    hini.pszHelpLibraryName = HelpFile;

    /* creating help instance */
    hwndHelpInstance = WinCreateHelpInstance(Hab, &hini);

    if(!hwndHelpInstance || hini.ulReturnCode)
    {
      Len = WinLoadString(Hab, hRessourceModule, IDS_NO_HELP_FOUND,
                          MSGSTRN_MAXLEN, Msg);
      WinMessageBox(HWND_DESKTOP, hwndFrame,
                    Msg, HelpTitle, 0, MB_WARNING | MB_OK | MB_SYSTEMMODAL);
      return;
    }

    fHelpEnabled = WinCreateHelpTable(hwndHelpInstance, (PHELPTABLE) HTable);

    /* associate help instance with main frame */
    if(!WinAssociateHelpInstance(hwndHelpInstance, hwndFrame))
    {
      fHelpEnabled = FALSE;
      Len = WinLoadString(Hab, hRessourceModule, IDS_ERROR_LOADING_HELP,
                          MSGSTRN_MAXLEN, Msg);
      WinMessageBox(HWND_DESKTOP, hwndFrame,
                    Msg, HelpTitle, 0, MB_WARNING | MB_OK | MB_SYSTEMMODAL);
    }

}

/*------------------------------------------------------------------------*/

void HelpExit(void)
{

  if (fHelpEnabled)
   WinDestroyHelpInstance(hwndHelpInstance);
}

/*------------------------------------------------------------------------*/

void DisplayHelp(ULONG Id)
{
  if (fHelpEnabled)
  {
   if (Id >= HM_MSG_BASE)
   {
    switch(Id)
    {
     case HM_HELP_INDEX:
       WinSendMsg(hwndHelpInstance, HM_HELP_INDEX, NULL, NULL);
      break;

     case HM_EXT_HELP:
       WinSendMsg(hwndHelpInstance, HM_HELP_CONTENTS, NULL, NULL);
      break;

     case HM_DISPLAY_HELP:
       WinSendMsg(hwndHelpInstance, HM_DISPLAY_HELP, NULL, NULL);
      break;

     case HM_KEYS_HELP:
       WinSendMsg(hwndHelpInstance, HM_KEYS_HELP, NULL, NULL);
      break;
    }
   }
   else
    WinSendMsg(hwndHelpInstance, HM_DISPLAY_HELP,
               MPFROM2SHORT(Id, NULL),
               MPFROMSHORT(HM_RESOURCEID));
  }
  else
  {
   Len = WinLoadString(Hab, hRessourceModule, IDS_NO_HELP_AVAIL,
                       MSGSTRN_MAXLEN, Msg);
   WinMessageBox(HWND_DESKTOP, hwndMainDialog,
                 Msg, HelpTitle, 0, MB_ERROR | MB_OK);
  }

}

/**********************************************************************/
/**********************************************************************/
/* -- EOF -- */

