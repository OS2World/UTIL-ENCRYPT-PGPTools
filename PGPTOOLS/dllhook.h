/**********************************************************************
 *
 *  PGPTools - PM shell for PGP v5.0 for OS/2
 *
 *  Module   : DLLHOOK.H
 *  Info     : DLL hook related definitions an declarations
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
 *
 **********************************************************************/

#if !defined _DLLHOOK_H
#define _DLLHOOK_H

/* global data - to be shared between dll and exe */
typedef struct
{
    BOOL floatOnTop;            // float on top of desktop
    ATOM wmu_FloatToTop;        // float our window to top of others
    CHAR szFloatToTop[40];      // unique string identifier for system atom
} GLOBALS;

BOOL EXPENTRY PGPDLLInit(HWND);
BOOL EXPENTRY PGPDLLExit(void);
GLOBALS *EXPENTRY PGPDLLSetGlobals(void);

#endif /* _DLLHOOK_H */
