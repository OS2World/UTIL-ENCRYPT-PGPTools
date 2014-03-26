/**********************************************************************
 *
 *  PGPTools - PM shell for PGP v5.0 for OS/2
 *
 *  Module   : COMMAND.H
 *  Info     : Commandline related routines (Header)
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
 *  090499 - Created
 *  170699 - Declarations added
 *  231199 - Prototype for RunPGPKeys() added
 *  241199 - hApp handle declarations added
 *  060400 - Hardcoded "CMD.EXE" replaced by OS2Shell constant
 *  250700 - Prototype for RetrieveShell() added
 *
 **********************************************************************/

#if !defined _COMMAND_H
#define _COMMAND_H

#include "pgptools.h"

typedef enum
{
        /* order must NOT be changed! */
        eSign=0,
        eEncrypt,
        eEncSign,
        eDecVerify,
        eBuildList,
        eNoJob
} tJobType;

typedef enum
{
        eNoSrc,
        eFile,
        eClipBoard
} tFSelType;

typedef struct sJobDesc
{
        tJobType Job;
        tFSelType SrcType;
        BOOL Detached;
        BOOL TextOutput;
        BOOL ASCIIArmor;
        BOOL EncryptToSelf;
        CHAR SourceFile[CCHMAXPATH];
} tJobDesc;

#define PARAM_LEN       1024

extern CHAR OS2Shell[];

extern tJobDesc JobDesc;
extern CHAR PGPKeyServiceCommand[];
extern CHAR PGPCommand[];
extern CHAR NewOutFileName[];
extern BOOL ExecutionInProgress;
extern BOOL PGPKeysInProgress;

BOOL RetrieveShell(void);
void ExecutePGP(HWND hwnd, PSZ Command, PSZ Params);
void ShowClipbrd(HWND hwnd);
void RunEditor(PSZ ExeName, PSZ Params);
void RunPGPKeys(HWND hwnd);

#endif /* _COMMAND_H */
