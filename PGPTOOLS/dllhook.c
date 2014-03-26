/**********************************************************************
 *
 *  PGPTools - PM shell for PGP v5.0 for OS/2
 *
 *  Module   : DLLHOOK.C
 *  Info     : Message hook routines of the DLL
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
 *  130799 - Created
 *  050400 - 'Hooked' identifier initialized by default
 *
 **********************************************************************/

#define INCL_WIN
#define INCL_DOSMODULEMGR

#include <os2.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dllhook.h"

HAB             hab;
BOOL            Hooked = FALSE;    /* flag set when hooks are enabled          */
HMODULE         hRessourceModule;  /* handle to the dll module                 */
HWND            hwndPGPClient;     /* handle to our client proc in xray.c      */
HATOMTBL        hAtomTblSystem;    /* handle to system atom table              */
GLOBALS         Global;            /* global data in the dll                   */
                                   /* we sent a pointer to it in PGPDLLInit()  */
HMQ hmqType = NULLHANDLE;          /* use NULLHANDLE for system wide hooks     */


/**********************************************************************
 * Function: PGPHookSendMsg
 * Info    : Send Message hook. Don't do any processing in here,
 *           especially calling WinPostMsg(). Simply post a msg to
 *           ourself for processing in our client proc
 * Result  : -
 **********************************************************************/

static void EXPENTRY PGPHookSendMsg(HAB habAnchor, PSMHSTRUCT psmh, BOOL fInterTask)
{
    switch(psmh->msg)
    {
        case WM_WINDOWPOSCHANGED:
         /*
          * When any window changes position , we notify our client
          * proc to move itself to the top of all windows
          */
         if (Global.floatOnTop)
           WinPostMsg(hwndPGPClient, Global.wmu_FloatToTop, 0, 0);
    }
}

/**********************************************************************
 * Function: PGPDLLInit
 * Info    : Enable Message hook
 * Result  : TRUE, on error FALSE
 **********************************************************************/

BOOL EXPENTRY PGPDLLInit(HWND hwnd)
{
    hwndPGPClient = hwnd; /* save client hwnd so we can post msgs to it */

    if (!Hooked)
    {
        /* create unique message ids (can't use WM_USER in hooks) */
        hAtomTblSystem = WinQuerySystemAtomTable();
        srand((UINT)hwnd);
        sprintf(Global.szFloatToTop,"PGPToolsFloatToTop%d",rand());
        Global.wmu_FloatToTop = WinAddAtom(hAtomTblSystem, Global.szFloatToTop);
        if(DosQueryModuleHandle("pgptools", &hRessourceModule))
           return FALSE;
        hab = WinQueryAnchorBlock(hwnd);
        WinSetHook(hab, hmqType, HK_SENDMSG, (PFN)PGPHookSendMsg, hRessourceModule);
        Hooked = TRUE;
    }

    return TRUE;
}

/**********************************************************************
 * Function: PGPDLLExit
 * Info    : Disable message hook
 * Result  : TRUE
 **********************************************************************/

BOOL EXPENTRY PGPDLLExit(void)
{
    if (Hooked)
    {
        WinReleaseHook(hab, hmqType, HK_SENDMSG, (PFN)PGPHookSendMsg, hRessourceModule);
        WinDeleteAtom(hAtomTblSystem, Global.wmu_FloatToTop);
        Hooked = FALSE;
    }

    return TRUE;
}

/**********************************************************************
 * Function: PGPDLLSetGlobals
 * Info    : return pointer to shared data structure
 * Result  : Pointer to Global
 **********************************************************************/

GLOBALS * EXPENTRY PGPDLLSetGlobals(void)
{
    return &Global;   /* allow client access to the dlls global data */
}

/**********************************************************************/
/**********************************************************************/
/* -- EOF -- */


