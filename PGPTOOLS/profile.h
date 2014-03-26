/**********************************************************************
 *
 *  PGPTools - PM shell for PGP v5.0 for OS/2
 *
 *  Module   : PROFILE.H
 *  Info     : Ini file handling (Header file)
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
 *  010499 - Created
 *  070499 - PRFDATA extended
 *  090499 - PRFDATA changed
 *  110499 - PRFDATA extended
 *  270499 - Comment length fixed
 *  160599 - PRFDATA extended
 *  130799 - PRFDATA extended
 *  251199 - PRFDATA restructured (separate filename keys)
 *  301199 - SendKeyServer key added
 *  051299 - Location/order of SendKeyServer key corrected to stay
 *           compatible with v1.30 structure
 *  061299 - WindowPosition key added
 *  271299 - SuppressHint flag and prototype for StoreFlags() added
 *  160300 - SetTitleBar flag added
 *  280900 - SmallIcons flag and prototype for IsSmallIconState()
 *           added
 *  300900 - EditorFile key added
 *
 **********************************************************************/

#if !defined _PROFILE_H
#define _PROFILE_H

/* PGP doesn't allow a comment size more than 69 characters */
#define COMMENT_MAXLEN          69

typedef struct sPRFFLAGS
{
  BOOL FirstSetupDone;
  BOOL PgpTextOutput;
  BOOL PgpDetach;
  BOOL PgpASCIIArmor;
  BOOL PgpEncryptToSelf;
  ULONG CacheTime;
  BOOL AlwaysOnTop;
  BOOL SuppressHint;
  BOOL SetTitleBar;
  BOOL SmallIcons;
} PRFFLAGS;

typedef struct sPRFDATA
{
  char PublicKeyFile[CCHMAXPATH+1];
  char PrivateKeyFile[CCHMAXPATH+1];
  char RandomSeedFile[CCHMAXPATH+1];
  char ASCIIComment[COMMENT_MAXLEN+1];
  PRFFLAGS Flags;
  char SendKeyServer[CCHMAXPATH+1]; /* must be placed after Flags to be compatible to v1.30!!! */
  char EditorFile[CCHMAXPATH+1];
  SWP  Swp;
} PRFDATA;

#define PrfAppName           "PGPTools"
#define PrfPublicFileKey     "PublicKeyFile"
#define PrfPrivateFileKey    "PrivateKeyFile"
#define PrfRandomFileKey     "RandomSeedFile"
#define PrfCommentKey        "Comment"
#define PrfSendKeyServerKey  "SendKeyServer"
#define PrfEditorKey         "Editor"
#define PrfFlagsKey          "Flags"
#define PrfWinPosKey         "WindowPosition"

extern PRFDATA ProfileData;
extern char IniFileName[_MAX_PATH];

BOOL WriteParams(HAB hab);
BOOL ReadParams(HAB hab, BOOL *pNewStructure);
BOOL StoreLastWinPos(HAB hab);
BOOL RestoreLastWinPos(HAB hab);
BOOL StoreFlags(HAB hab);
BOOL IsSmallIconState(HAB hab);

#endif /* _PROFILE_H */
