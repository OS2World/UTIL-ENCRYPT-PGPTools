/**********************************************************************
 *
 *  PGPTools - PM shell for PGP v5.0 for OS/2
 *
 *  Module   : PPHRASE.H
 *  Info     : Passphrase obtaining dialog (Header)
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
 *
 **********************************************************************/

#if !defined _PPHRASE_H
#define _PPHRASE_H

typedef struct
{
  USHORT cb;
  tJobType JobType;
  tFSelType SrcType;
} PPhraseDlgData, *pPPhraseDlgData;

#define PPHRASE_SIZE    1024

extern tKeyElement PrivKeyToSign;
extern CHAR PPhraseText[PPHRASE_SIZE];
void InsertListEntries(HWND hwnd);
BOOL GetPassphrase(HWND hwnd, tJobDesc *Job);

#endif /* _PPHRASE_H */
