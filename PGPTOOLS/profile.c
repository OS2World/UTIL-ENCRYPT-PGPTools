/**********************************************************************
 *
 *  PGPTools - PM shell for PGP v5.0 for OS/2
 *
 *  Module   : PROFILE.C
 *  Info     : Ini file handling
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
 *  130599 - ProfileData initialization updated
 *  130799 - ProfileData initialization updated
 *  251199 - PRFDATA restructured (separate filename keys)
 *  301199 - SendKeyServer key added
 *  041299 - Default value for SendKeyServer set
 *  051299 - Location/order of initial SendKeyServer value corrected to
 *           stay compatible with v1.30 structure
 *  271299 - SuppressHint flag and StoreFlags() added
 *  160300 - SetTitleBar flag added
 *  280900 - SmallIcons flag and IsSmallIconState() added
 *  190602 - Profile data: %f -> "%f"
 *
 **********************************************************************/

#include "pgptools.h"
#include "profile.h"
#include "version.h"

char IniFileName[_MAX_PATH] = "pgptools.ini";

// name of the universal profile key until PGPTools v1.30
char OldProfileKey130[] = "Params";

PRFDATA ProfileData = {
                        "",                             /* PublicKeyFile    */
                        "",                             /* PrivateKeyFile   */
                        "",                             /* RandomSeedFile   */
                        "Created by PGPTools for OS/2", /* ASCIIComment     */
                        {
                          FALSE,                        /* FirstSetupDone   */
                          TRUE,                         /* PgpTextOutput    */
                          TRUE,                         /* PgpDetach        */
                          TRUE,                         /* PgpASCIIArmor    */
                          TRUE,                         /* PgpEncryptToSelf */
                          120L,                         /* CacheTime 2 min. */
                          FALSE,                        /* AlwaysOnTop      */
                          FALSE,                        /* SuppressHint     */
                          TRUE,                         /* SetTitleBar      */
                          FALSE                         /* SmallIcons       */
                         },
                        "hkp://wwwkeys.pgp.net",        /* SendKeyServer    */
                        "e.exe \"%f\""                      /* Editor           */
                      };

/**********************************************************************
 * Function: WriteParams
 * Info    : write application's profile data
 * Result  : TRUE on success else FALSE
 **********************************************************************/

BOOL WriteParams(HAB hab)
{
 HINI hIni;
 BOOL rc;

 hIni = PrfOpenProfile(hab, (PSZ) IniFileName);
 if (hIni == NULLHANDLE)
  return FALSE;

 rc = PrfWriteProfileData(hIni, (PSZ) PrfAppName,
                          (PSZ) PrfPublicFileKey,
                          ProfileData.PublicKeyFile,
                          sizeof(ProfileData.PublicKeyFile));

 rc &= PrfWriteProfileData(hIni, (PSZ) PrfAppName,
                          (PSZ) PrfPrivateFileKey,
                           ProfileData.PrivateKeyFile,
                           sizeof(ProfileData.PrivateKeyFile));

 rc &= PrfWriteProfileData(hIni, (PSZ) PrfAppName,
                           (PSZ) PrfRandomFileKey,
                           ProfileData.RandomSeedFile,
                           sizeof(ProfileData.RandomSeedFile));

 rc &= PrfWriteProfileData(hIni, (PSZ) PrfAppName,
                           (PSZ) PrfCommentKey,
                           ProfileData.ASCIIComment,
                           sizeof(ProfileData.ASCIIComment));

 rc &= PrfWriteProfileData(hIni, (PSZ) PrfAppName,
                           (PSZ) PrfSendKeyServerKey,
                           ProfileData.SendKeyServer,
                           sizeof(ProfileData.SendKeyServer));

 rc &= PrfWriteProfileData(hIni, (PSZ) PrfAppName,
                           (PSZ) PrfEditorKey,
                           ProfileData.EditorFile,
                           sizeof(ProfileData.EditorFile));

 rc &= PrfWriteProfileData(hIni, (PSZ) PrfAppName, (PSZ) PrfWinPosKey,
                           &ProfileData.Swp, sizeof(ProfileData.Swp));
 PrfCloseProfile(hIni);

 rc &= StoreFlags(hIni);

 return rc;

}

/**********************************************************************
 * Function: ReadParams
 * Info    : read application's profile data
 * Result  : TRUE on success else FALSE
 **********************************************************************/

BOOL ReadParams(HAB hab, BOOL *pNewStructure)
{
 HINI hIni;
 BOOL rc, IniFileExists;
 ULONG KeyLen;
 char OrigASCIIComment[COMMENT_MAXLEN+1];

 IniFileExists = FileExist(IniFileName) &&  (0L < FileSize(NULL, IniFileName));
 *pNewStructure = FALSE;

 hIni = PrfOpenProfile(hab, (PSZ) IniFileName);
 if (hIni == NULLHANDLE)
  return FALSE;

 memset(&ProfileData.Swp, 0, sizeof(ProfileData.Swp));

 /*
  * Since profile (INI file) format (not the contents and the order!)
  * has changed as of v1.40, let's see if the current file is a v1.30
  * profile. If yes, read it for a last time, then delete the old key
  * and write the new keys.
  */
 KeyLen = sizeof(ProfileData);
 if ( PrfQueryProfileData(hIni, (PSZ) PrfAppName,
                          (PSZ) OldProfileKey130,
                          &ProfileData,
                          &KeyLen))
 {

    // first delete the v1.30 key named "Params"
    rc = PrfWriteProfileData(hIni, (PSZ) PrfAppName,
                            (PSZ) OldProfileKey130, NULL, 0L);
    WriteParams(hab);
    return TRUE;
 }

 KeyLen = sizeof(ProfileData.PublicKeyFile);
 rc = PrfQueryProfileData(hIni, (PSZ) PrfAppName,
                          (PSZ) PrfPublicFileKey,
                          ProfileData.PublicKeyFile,
                          &KeyLen);

 KeyLen = sizeof(ProfileData.PrivateKeyFile);
 rc &= PrfQueryProfileData(hIni, (PSZ) PrfAppName,
                           (PSZ) PrfPrivateFileKey,
                           ProfileData.PrivateKeyFile,
                           &KeyLen);

 KeyLen = sizeof(ProfileData.RandomSeedFile);
 rc &= PrfQueryProfileData(hIni, (PSZ) PrfAppName,
                           (PSZ) PrfRandomFileKey,
                           ProfileData.RandomSeedFile,
                           &KeyLen);

 strcpy(OrigASCIIComment, ProfileData.ASCIIComment);
 KeyLen = sizeof(ProfileData.ASCIIComment);
 rc &= PrfQueryProfileData(hIni, (PSZ) PrfAppName,
                           (PSZ) PrfCommentKey,
                           ProfileData.ASCIIComment,
                           &KeyLen);
 if (!IniFileExists)
 {
  strcat(ProfileData.ASCIIComment, " ");
  strcat(ProfileData.ASCIIComment, VERSION_STRN);
 }
 else
 {
    char *p = strstr(ProfileData.ASCIIComment, OrigASCIIComment);

    if (NULL != p)
    {
      strcpy(ProfileData.ASCIIComment, OrigASCIIComment);
      strcat(ProfileData.ASCIIComment, " ");
      strcat(ProfileData.ASCIIComment, VERSION_STRN);
    }
 }

 KeyLen = sizeof(ProfileData.SendKeyServer);
 rc &= PrfQueryProfileData(hIni, (PSZ) PrfAppName,
                           (PSZ) PrfSendKeyServerKey,
                           ProfileData.SendKeyServer,
                           &KeyLen);

 KeyLen = sizeof(ProfileData.EditorFile);
 rc &= PrfQueryProfileData(hIni, (PSZ) PrfAppName,
                           (PSZ) PrfEditorKey,
                           ProfileData.EditorFile,
                           &KeyLen);

 KeyLen = sizeof(ProfileData.Flags);
 rc &= PrfQueryProfileData(hIni, (PSZ) PrfAppName, (PSZ) PrfFlagsKey,
                           &ProfileData.Flags, &KeyLen);

 KeyLen = sizeof(ProfileData.Swp);
 rc &= PrfQueryProfileData(hIni, (PSZ) PrfAppName, (PSZ) PrfWinPosKey,
                           &ProfileData.Swp, &KeyLen);
 PrfCloseProfile(hIni);

 if (!ProfileData.Flags.FirstSetupDone)
  rc = FALSE;

 if (IniFileExists && !rc)
    *pNewStructure = TRUE;

 return rc;

}

/**********************************************************************
 * Function: StoreLastWinPos
 * Info    : Store application's last window position
 * Result  : TRUE on success else FALSE
 **********************************************************************/

BOOL StoreLastWinPos(HAB hab)
{
 HINI hIni;
 BOOL rc;

 hIni = PrfOpenProfile(hab, (PSZ) IniFileName);
 if (hIni == NULLHANDLE)
  return FALSE;

 rc = PrfWriteProfileData(hIni, (PSZ) PrfAppName, (PSZ) PrfWinPosKey,
                           &ProfileData.Swp, sizeof(ProfileData.Swp));
 PrfCloseProfile(hIni);

 return rc;
}

/**********************************************************************
 * Function: RestoreLastWinPos
 * Info    : Restore application's last window position
 * Result  : TRUE on success else FALSE
 **********************************************************************/

BOOL RestoreLastWinPos(HAB hab)
{
 HINI hIni;
 BOOL rc;
 ULONG KeyLen;

 hIni = PrfOpenProfile(hab, (PSZ) IniFileName);
 if (hIni == NULLHANDLE)
  return FALSE;

 KeyLen = sizeof(ProfileData.Swp);
 rc = PrfQueryProfileData(hIni, (PSZ) PrfAppName, (PSZ) PrfWinPosKey,
                          &ProfileData.Swp, &KeyLen);
 PrfCloseProfile(hIni);

 return rc;
}

/**********************************************************************
 * Function: StoreFlags
 * Info    : Store application's flags
 * Result  : TRUE on success else FALSE
 **********************************************************************/

BOOL StoreFlags(HAB hab)
{
 HINI hIni;
 BOOL rc;

 hIni = PrfOpenProfile(hab, (PSZ) IniFileName);
 if (hIni == NULLHANDLE)
  return FALSE;

 rc = PrfWriteProfileData(hIni, (PSZ) PrfAppName, (PSZ) PrfFlagsKey,
                          &ProfileData.Flags, sizeof(ProfileData.Flags));

 PrfCloseProfile(hIni);

 return rc;
}

/**********************************************************************
 * Function: IsSmallIconState
 * Info    : Checks if small icons should be displayed in the main
 *           window
 * Result  : TRUE if small icons should be used, else FALSE
 **********************************************************************/

BOOL IsSmallIconState(HAB hab)
{

 HINI hIni;
 BOOL rc;
 ULONG KeyLen;

 hIni = PrfOpenProfile(hab, (PSZ) IniFileName);
 if (hIni == NULLHANDLE)
  return FALSE;

 KeyLen = sizeof(ProfileData.Flags);
 rc = PrfQueryProfileData(hIni, (PSZ) PrfAppName, (PSZ) PrfFlagsKey,
                          &ProfileData.Flags, &KeyLen);
 PrfCloseProfile(hIni);

 /* Access succeeded, get small icon state */
 if (rc)
  rc = ProfileData.Flags.SmallIcons;

 return rc;

}

/**********************************************************************/
/**********************************************************************/
/* -- EOF -- */

