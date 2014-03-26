/**********************************************************************
 *
 *  PGPTools - PM shell for PGP v5.0 for OS/2
 *
 *  Module   : PGPHELP.H
 *  Info     : Online help system (header)
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
 *  160599 - IDL_ macros modified
 *  100699 - IDL_ macros added
 *  281299 - IDL_ macros added
 *  300900 - IDL_ macros added
 *
 **********************************************************************/
#if !defined _PGPHELP_H
#define _PGPHELP_H

#define IDL_GENERAL_HELP        1
#define IDL_BUTTON_HELP         2
#define IDL_SYSMENU_HELP        3
#define IDL_POPUP_HELP          4
#define IDL_PASSPHRASE_HELP     5
#define IDL_LISTBOX_HELP        6
#define IDL_SETTINGS_HELP       7
#define IDL_SRCFILE_HELP        8
#define IDL_TGTFILE_HELP        9
#define IDL_PGPKEYS_HELP        10
#define IDL_LOGWIN_HELP         11

void HelpInit(HWND hwndFrame, const PSZ HelpFile);
void HelpExit(void);
void DisplayHelp(ULONG Id);

#endif /* _PGPHELP_H */
