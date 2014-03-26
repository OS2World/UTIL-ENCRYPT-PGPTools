/**********************************************************************
 *
 *  PGPTools - PM shell for PGP v5.0 for OS/2
 *
 *  Module   : BUBBLE.C
 *  Info     : Bubble help window
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
 *  200499 - Created
 *  220499 - HideBubbleHelp(): hide only if window is still visible
 *  240800 - SWP_ZORDER added in ShowBubbleHelp()
 *
 **********************************************************************/

#include "pgptools.h"

static HWND hwndBubbleFrame,
            hwndBubble,
            hwndBubbleFrameClient,
            hwndBubbleClient;

static LONG GetStringSize(HPS hps, PSZ szString);

/**********************************************************************
 * Function: CreateBubbleHelp
 * Info    : Create bubble help windows
 * Result  : -
 **********************************************************************/
void CreateBubbleHelp(void)
{
  ULONG ColorIndex;
  ULONG Style = FCF_BORDER;
  hwndBubbleFrame = WinCreateStdWindow(HWND_DESKTOP,
                                       FS_NOBYTEALIGN,
                                       &Style,
                                       WC_STATIC,
                                       "",
                                       SS_FGNDFRAME,
                                       NULLHANDLE,
                                       ID_BUBBLEHELPFRAME,
                                       &hwndBubbleFrameClient);

  Style = 0;
  hwndBubble = WinCreateStdWindow(hwndBubbleFrame,
                                  FS_NOBYTEALIGN,
                                  &Style,
                                  WC_STATIC,
                                  "",
                                  SS_TEXT|DT_LEFT|DT_WORDBREAK,
                                  NULLHANDLE,
                                  ID_BUBBLEHELPBUBBLE,
                                  &hwndBubbleClient);


  WinSetPresParam(hwndBubbleClient, PP_FONTNAMESIZE, 7, "8.Helv");

  ColorIndex = CLR_YELLOW;
  WinSetPresParam(hwndBubbleClient, PP_BACKGROUNDCOLORINDEX,
                  (ULONG)sizeof(LONG), (PVOID)&ColorIndex);

}

/**********************************************************************
 * Function: ShowBubbleHelp
 * Info    : Popup bubble help text
 * Result  : -
 **********************************************************************/

void ShowBubbleHelp(HWND hButton, PSZ pText)
{
  HPS hps;
  FONTMETRICS fm;
  LONG bubbleW,
       bubbleH,
       strSize;
  POINTL pointl;

  hps = WinGetPS(hwndBubbleClient);
  GpiQueryFontMetrics(hps, sizeof(FONTMETRICS), &fm);

  bubbleW = fm.lAveCharWidth*40; /* constant width */

  pointl.x = 0;
  pointl.y = 0;

  WinMapWindowPoints(hButton, HWND_DESKTOP, &pointl, 1);
  strSize = GetStringSize(hps, pText);
  bubbleH = max(fm.lMaxBaselineExt+2, (strSize/bubbleW+1) * fm.lMaxBaselineExt+2);
  strSize = min(strSize+4, bubbleW);
  WinSetWindowText(hwndBubbleClient, pText);

  /* set size and position */
  WinSetWindowPos(hwndBubbleFrame,
                  HWND_TOP,
                  pointl.x, pointl.y - bubbleH - 10,
                  strSize + 2, bubbleH + 2,
                  SWP_SIZE|SWP_MOVE);


  WinSetWindowPos(hwndBubble,
                  HWND_TOP,
                  1, 1,
                  strSize, bubbleH,
                  SWP_SIZE|SWP_MOVE);

  RecalcWinPos(hwndBubbleFrame);

  /* make bubble visible */
  WinSetWindowPos(hwndBubbleFrame,
                  HWND_TOP,
                  0,0,0,0,
                  SWP_ZORDER | SWP_SHOW);


  WinSetWindowPos(hwndBubble,
                  HWND_TOP,
                  0,0,0,0,
                  SWP_ZORDER | SWP_SHOW);


  WinReleasePS(hps);

}

/**********************************************************************
 * Function: HideBubbleHelp
 * Info    : Hide bubble help window
 * Result  : -
 **********************************************************************/
void HideBubbleHelp(void)
{
  if (!WinIsWindowVisible(hwndBubbleFrame))
   return;

  /* make bubble invisible */
  WinSetWindowPos(hwndBubbleFrame,
                  HWND_TOP,
                  0,0,0,0,
                  SWP_HIDE);


  WinSetWindowPos(hwndBubble,
                  HWND_TOP,
                  0,0,0,0,
                  SWP_HIDE);
}

/**********************************************************************
 * Function: uiGetStringSize
 * Info    : Query strings size for passed string
 * Result  : size of string
 **********************************************************************/
static LONG GetStringSize(HPS hps, PSZ szString)
{
 POINTL aptl[TXTBOX_COUNT];

 /* Breite der Zeichenkette in Pixel berechnen */

 if(!GpiQueryTextBox(hps, strlen( szString ), szString, TXTBOX_COUNT,
                       aptl))
  {
  return(0);
 }
 else
     return aptl[TXTBOX_CONCAT].x;
}


/**********************************************************************
 * Function: IsPtrInWindow
 * Info    : Checks if pinter is in window
 * Result  : TRUE if pointer is in window else FALSE
 **********************************************************************/

BOOL IsPtrInWindow(HWND hwnd)
{
 BOOL  fSuccess;         /* success indicator                    */
 POINTL ptlMouse;        /* mouse pointer position               */
 RECTL rclWork;          /* client area                          */

 /* get current mouse pointer position */
 WinQueryPointerPos(HWND_DESKTOP, &ptlMouse);

 /* map from desktop to client window */
 fSuccess = WinMapWindowPoints(HWND_DESKTOP, hwnd,
                               &ptlMouse, 1);

 /* check if new mouse position is inside the client area */
 WinQueryWindowRect(hwnd, &rclWork);
 if (WinPtInRect(Hab, &rclWork, &ptlMouse))
  return TRUE;

 return FALSE;

}

/**********************************************************************/
/**********************************************************************/
/* -- EOF -- */

