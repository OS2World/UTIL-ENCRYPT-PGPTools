/**********************************************************************
 *
 *  PGPTools - PM shell for PGP v5.0 for OS/2
 *
 *  Module   : PGPTOOLS.C
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
 *
 **********************************************************************/

#include "prefnbxx.h"
#include "command.h"
#include "pgptools.h"


BOOL InitializeNoteBook(HWND hwnd)
{
   HWND hwndPage;
   ULONG ulPageId;
   ULONG ipt = 0;
   CHAR pszMleBuffer[512];
   PSZ   pszNoteBookText = "TEST";

   /*
    * Insert the first page.
    */
   ulPageId = (LONG)WinSendDlgItemMsg(hwnd, IDC_NOTEBOOK,
        BKM_INSERTPAGE, NULL,
        MPFROM2SHORT((BKA_STATUSTEXTON | BKA_AUTOPAGESIZE | BKA_MAJOR),
        BKA_LAST));

   if ( !ulPageId)
     return FALSE;

   if ( !WinSendDlgItemMsg(hwnd, IDC_NOTEBOOK,
        BKM_SETSTATUSLINETEXT, MPFROMLONG(ulPageId),
        MPFROMP("Page 1 of 2")))
     return FALSE;

   if ( !WinSendDlgItemMsg(hwnd, IDC_NOTEBOOK,
        BKM_SETTABTEXT, MPFROMLONG(ulPageId),
        MPFROMP("~1")))
     return FALSE;

   hwndPage =
   WinCreateWindow(               /* parent-window handle                    */
      hwnd,                       /* pointer to registered class name        */
      WC_STATIC,                  /* pointer to window text                  */
      "#6",                       /* window style                            */
      WS_VISIBLE | SS_BITMAP,     /* horizontal position of window           */
      0,                          /* vertical position of window             */
      0,                          /* window width                            */
      0,                          /* window height                           */
      0,                          /* owner-window handle                     */
      NULLHANDLE,                 /* handle to sibling window                */
      HWND_TOP,                   /* window identifier                       */
      0,                          /* pointer to buffer                       */
      NULL,                       /* pointer to structure with pres. params. */
      NULL);

   if (!hwndPage)
     return FALSE;

   if ( !WinSendDlgItemMsg(hwnd, IDC_NOTEBOOK,
         BKM_SETPAGEWINDOWHWND, MPFROMLONG(ulPageId),
         MPFROMHWND(hwndPage)))
     return FALSE;

   /*
    * Insert the second page.
    */
    ulPageId = (LONG)WinSendDlgItemMsg(hwnd, IDC_NOTEBOOK,
         BKM_INSERTPAGE, NULL,
         MPFROM2SHORT((BKA_STATUSTEXTON | BKA_AUTOPAGESIZE | BKA_MAJOR),
         BKA_LAST));

   if (!ulPageId)
     return FALSE;

   if ( !WinSendDlgItemMsg(hwnd, IDC_NOTEBOOK,
         BKM_SETSTATUSLINETEXT, MPFROMLONG(ulPageId),
         MPFROMP("Page 2 of 2")))
     return FALSE;

   if ( !WinSendDlgItemMsg(hwnd, IDC_NOTEBOOK,
        BKM_SETTABTEXT, MPFROMLONG(ulPageId),
        MPFROMP("~2")))
     return FALSE;

   hwndPage =
   WinCreateWindow(
      hwnd,                       /* parent-window handle                    */
      WC_MLE,                     /* pointer to registered class name        */
      NULL,                       /* pointer to window text                  */
      WS_VISIBLE | MLS_WORDWRAP | /* window style                            */
         MLS_READONLY,
      0,                          /* horizontal position of window           */
      0,                          /* vertical position of window             */
      0,                          /* window width                            */
      0,                          /* window height                           */
      NULLHANDLE,                 /* owner-window handle                     */
      HWND_TOP,                   /* handle to sibling window                */
      0,                          /* window identifier                       */
      NULL,                       /* pointer to buffer                       */
      NULL);                      /* pointer to structure with pres. params. */

   if (!hwndPage)
     return FALSE;

   if ( !WinSendMsg(hwndPage, MLM_SETIMPORTEXPORT,
         MPFROMP(pszMleBuffer),
         MPFROMSHORT(sizeof(pszMleBuffer))))
     return FALSE;

     memset(pszMleBuffer,'\0',sizeof(pszMleBuffer));
     strcpy(pszMleBuffer, pszNoteBookText);

   if ( !WinSendMsg(hwndPage, MLM_IMPORT, &ipt,
         MPFROMSHORT(sizeof(pszMleBuffer))))
     return FALSE;

   if( !WinSendDlgItemMsg(hwnd, IDC_NOTEBOOK,
         BKM_SETPAGEWINDOWHWND, MPFROMLONG(ulPageId),
         MPFROMHWND(hwndPage)))
     return FALSE;

   return TRUE;
}                                       /* End of InitializeNotebook    */


