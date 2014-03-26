/**********************************************************************
 *
 *  PGPTools - PM shell for PGP v5.0 for OS/2
 *
 *  Module   : COMMAND.C
 *  Info     : Commandline related routines
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
 *  170699 - ExecutionInProgress created
 *  140799 - Owner-window handles for WinMessageBox() changed
 *  231199 - LaunchWinApp() and RunPGPKeys() added, ShowClipbrd()
 *           modified, WinAppInProgress created
 *  241199 - App handles to support LaunchPGPKeys() and ShowClipbrd()
 *           added
 *  051299 - Call syntax for PGPKeys now loaded from resource file
 *  060400 - Hardcoded "CMD.EXE" replaced by OS2Shell constant
 *  080400 - some PROGDETAILS values added
 *  250700 - Function RetrieveShell() added
 *  140602 - Function BuildParamLine and ExecutePGP() improved to
 *           properly handle path and filenames containing spaces.
 *
 **********************************************************************/

#include "main_xx.h"
#include "about_xx.h"
#include "pgptools.h"
#include "pref_xx.h"
#include "profile.h"
#include "filedlgx.h"
#include "command.h"
#include "filedlg.h"
#include "keylist.h"
#include "pphrase.h"

tJobDesc JobDesc = {
                     eNoJob,
                     eNoSrc,
                     FALSE,
                     FALSE
                   };
extern HAPP hApp;


const PSZ ClipBoardExe       = "clipos2.exe";
static const PSZ DefOS2Shell = "cmd.exe";

BOOL ExecutionInProgress     = FALSE;
BOOL PGPKeysInProgress       = FALSE;
CHAR PGPKeyServiceCommand[CCHMAXPATH]  = "pgpk.exe";
CHAR PGPCommand[CCHMAXPATH]            = "pgp.exe";
CHAR NewOutFileName[CCHMAXPATH];
CHAR OS2Shell[CCHMAXPATH];

static CHAR *PGPSubCommand[] = {
                                  "s ",
                                  "e ",
                                  "e -s ",
                                  "v "
                                };
static CHAR ParamLine[PARAM_LEN];

/**********************************************************************
 * Function: RetrieveShell
 * Info    : Attempts to retrieve the currently active shell by
 *           evaluating the COMSPEC environment variable. If this fails
 *           the environment variable OS2_SHELL is checked. If this
 *           also fails, CMD.EXE is set as the default shell.
 * Result  : TRUE on success, else FALSE
 **********************************************************************/
BOOL RetrieveShell(void)
{
    char *p;

    strcpy(OS2Shell, DefOS2Shell);

    p = getenv("COMSPEC");

    if ((NULL == p) || (0 == *p))
    {
          p = getenv("OS2_SHELL");
          if ((NULL == p) || (0 == *p))
            return FALSE;
    }

    strcpy(OS2Shell, p);

    return TRUE;
}

/**********************************************************************
 * Function: TargetFileExist
 * Info    : Check if target file does exist
 * Result  : TRUE if it does exist, else FALSE
 **********************************************************************/
BOOL TargetFileExist(PSZ InFileName, PSZ DestExt, PSZ OutFileName)
{
  PSZ p1, p2;

  strcpy(OutFileName, InFileName);
  p1 = strrchr(OutFileName, '\\');
  p2 = strrchr(OutFileName, '.');
  if ((NULL != p1) && (NULL != p2))
   if (p2 > p1)
    *p2 = '\0';

  strcat(OutFileName, DestExt);

  if (FileExist(OutFileName))
   return TRUE;

  return FALSE;
}

/**********************************************************************
 * Function: OverwriteTarget
 * Info    : Query user for overwriting target
 * Result  : TRUE for overwrite, else FALSE, if FALSE a modified
 *           target filename is returned
 **********************************************************************/
BOOL OverwriteTarget(PSZ NewOutFileName)
{
   PSZ p1, p2;
   CHAR Buffer[CCHMAXPATH+100], Ext[5];
   CHAR Title[TITLESTRN_MAXLEN];
   USHORT Index = 0;
   ULONG TitleID;

   switch(JobDesc.Job)
   {
     case eSign:      TitleID = IDS_BUBBLE_SIGNDATA_HELP; break;
     case eEncrypt:   TitleID = IDS_BUBBLE_ENCRYPTDATA_HELP; break;
     case eEncSign:   TitleID = IDS_BUBBLE_ENC_SIGNDATA_HELP; break;
     case eDecVerify: TitleID = IDS_BUBBLE_DECVERIFYDATA_HELP; break;

   }

   Len = WinLoadString(Hab, hRessourceModule, IDS_QUERY_TARGET_OVERWRITE,
                       MSGSTRN_MAXLEN, Msg);
   Len = WinLoadString(Hab, hRessourceModule, TitleID,
                       TITLESTRN_MAXLEN, Title);
   sprintf(Buffer, Msg, NewOutFileName);
   if (MBID_YES == WinMessageBox(HWND_DESKTOP, hwndMainDialog,
                                 Buffer, Title, 0, MB_ICONQUESTION | MB_YESNO))
    return TRUE;

   p1 = strrchr(NewOutFileName, '\\');
   p2 = strrchr(NewOutFileName, '.');
   if ((NULL != p1) && (NULL != p2))
    if (p2 > p1)
     *p2 = '\0';

   strcpy(Buffer, NewOutFileName);
   do
   {
     strcpy(Buffer, NewOutFileName);
     sprintf(Ext, ".%03d", Index++);
     strcat(Buffer, Ext);
   }while(FileExist(Buffer));

   strcat(NewOutFileName, Ext);
   return FALSE;
}

/**********************************************************************
 * Function: BuildParamLine
 * Info    : Assemble PGP command line parameters
 * Result  : -
 **********************************************************************/

static BOOL BuildParamLine(void)
{

  tKeyElement *pElement = pOutKeyAnchor;
  CHAR DestExt[] = ".PGP";

  if (eDecVerify == JobDesc.Job)
  {
   strcpy(ParamLine, "/C ");
   strcat(ParamLine, "\"");
   strcat(ParamLine, PGPCommand);
   strcat(ParamLine, " ");
   strcat(ParamLine, PGPSubCommand[JobDesc.Job]);
  }
  else
   strcpy(ParamLine, PGPSubCommand[JobDesc.Job]);

  if ((eEncrypt == JobDesc.Job) || (eEncSign == JobDesc.Job))
  {
    while(NULL != pElement)
    {
      strcat(ParamLine, "-r ");
      strcat(ParamLine, pElement->KeyID);
      strcat(ParamLine, " ");

      pElement = pElement->pNext;
    }
  }

  if ((JobDesc.ASCIIArmor ||
       JobDesc.TextOutput ||
       (JobDesc.Detached &&
        (eClipBoard != JobDesc.SrcType))) &&
      (eDecVerify != JobDesc.Job)
     )
   strcat(ParamLine, "-");

  if ((JobDesc.ASCIIArmor) &&
      (eDecVerify != JobDesc.Job)
     )
  {
   strcat(ParamLine, "a");
   strcpy(DestExt, ".ASC");
  }

  if ((JobDesc.TextOutput) &&
      (eDecVerify != JobDesc.Job)
     )
   strcat(ParamLine, "t");

  if ((JobDesc.Detached) &&
      (eClipBoard != JobDesc.SrcType) &&
      (eSign == JobDesc.Job)
     )
  {
   strcat(ParamLine, "b");
   if (!JobDesc.ASCIIArmor)
    strcpy(DestExt, ".SIG");
  }


  if ((eSign == JobDesc.Job) ||
      (eEncSign == JobDesc.Job)
     )
  {
   strcat(ParamLine, " -u ");
   strcat(ParamLine, PrivKeyToSign.KeyID);
  }

  if ((eSign == JobDesc.Job) ||
      (eEncSign == JobDesc.Job) ||
      (eDecVerify == JobDesc.Job)
     )
  {
   strcat(ParamLine, " -z\"");
   strcat(ParamLine, PPhraseText);
   strcat(ParamLine, "\"");
  }

  if (((eEncrypt == JobDesc.Job) ||
       (eEncSign == JobDesc.Job)) &&
       JobDesc.EncryptToSelf
     )
  {
   strcat(ParamLine, " +encrypttoself");
  }

  strcat(ParamLine, " +randseed=\"");
  strcat(ParamLine, ProfileData.RandomSeedFile);
  strcat(ParamLine, "\"");
  strcat(ParamLine, " +batchmode +force"); /* force batch mode (that hopefully works) */

  /* Add comment if available */
  if ((0 != strcmp(ProfileData.ASCIIComment, "")) &&
      ((JobDesc.ASCIIArmor) || (eClipBoard == JobDesc.SrcType))
     )
  {
   strcat(ParamLine, " +comment=\"");
   strcat(ParamLine, ProfileData.ASCIIComment);
   strcat(ParamLine, "\"");
  }

  strcat(ParamLine, " ");
  strcat(ParamLine, "\"");
  strcat(ParamLine, JobDesc.SourceFile);
  strcat(ParamLine, "\"");

  /* Use temporary outfile for clipboard operations */
  if (eClipBoard == JobDesc.SrcType)
  {
    if (FileExist(TempOutFile))
     remove(TempOutFile);
    strcat(ParamLine, " -o ");
    strcat(ParamLine, "\"");
    strcat(ParamLine, TempOutFile);
    strcat(ParamLine, "\"");
  }
  else
  {
    if (eDecVerify == JobDesc.Job)
    {
      /* target file was inquired by filedlg */
      strcat(ParamLine, " -o ");
      strcat(ParamLine, "\"");
      strcat(ParamLine, NewOutFileName);
      strcat(ParamLine, "\"");
    }
    else
    {
      memset(NewOutFileName, 0, sizeof(NewOutFileName));
      if (TargetFileExist(JobDesc.SourceFile, DestExt, NewOutFileName))
      {
       if (!OverwriteTarget(NewOutFileName))
       {
        strcat(ParamLine, " -o ");
        strcat(ParamLine, "\"");
        strcat(ParamLine, NewOutFileName);
        strcat(ParamLine, "\"");
       }
       else
        remove(NewOutFileName);
      }
    }
  }

  if (eDecVerify == JobDesc.Job)
  {
    strcat(ParamLine, " 2> ");        /* redirect stderr to log file */
    strcat(ParamLine, "\"");
    strcat(ParamLine, TempLogFile);
    strcat(ParamLine, "\"");
  }

  return TRUE;
}

/**********************************************************************
 * Function: ExecutePGP
 * Info    : Execute selected data with PGP
 * Result  : -
 **********************************************************************/

void ExecutePGP(HWND hwnd, PSZ Command, PSZ Params)
{
#if defined DEBUG
  FILE *fp_dbg;
#endif
  CHAR CmdBuffer[CCHMAXPATH];
  CHAR ParamBuffer[CCHMAXPATH];
  PROGDETAILS Details;
  BOOL Result = TRUE;

  if (NULL == Command)
   return;

  if ((NULL == Params) ||
      (eEncrypt == JobDesc.Job) ||
      (eEncSign == JobDesc.Job) ||
      (eDecVerify == JobDesc.Job))
   Result = BuildParamLine();
  else
   strcpy(ParamLine, Params);

  if (NULL == strstr(OS2Shell, Command))
  {
      strcpy(CmdBuffer, OS2Shell);
      strcpy(ParamBuffer, "/C \"");
      strcat(ParamBuffer, Command);
      strcat(ParamBuffer, " ");
      strcat(ParamBuffer, ParamLine);
      strcat(ParamBuffer, "\"");
  }
  else
  {
      strcpy(CmdBuffer, Command);
      strcpy(ParamBuffer, ParamLine);
  }

#if defined DEBUG
  if (NULL != (fp_dbg = fopen("C:\\TEMP\\cmdline.cmd", "wt")))
  {

    fputs(CmdBuffer, fp_dbg);
    fputc(' ', fp_dbg);
    fputs(ParamBuffer, fp_dbg);
    fputc('\n', fp_dbg);
    fclose(fp_dbg);
  }
#endif

  Details.Length = sizeof(PROGDETAILS);
  Details.progt.progc =  PROG_WINDOWABLEVIO;
  Details.progt.fbVisible = SHE_INVISIBLE;
  Details.pszTitle = "";
  Details.pszExecutable = CmdBuffer;
  Details.pszParameters = NULL;
  Details.pszStartupDir = NULL;
  Details.pszIcon = NULL;
  Details.pszEnvironment = "\0\0";
  Details.swpInitial.hwnd = hwnd;
  Details.swpInitial.hwndInsertBehind = HWND_TOP;
  Details.swpInitial.fl = SWP_ACTIVATE |
                          SWP_MOVE |
                          SWP_SIZE |
#if !defined DEBUG
                          SWP_HIDE;
#else
                          SWP_SHOW;

  Details.swpInitial.x = 100;
  Details.swpInitial.y = 100;
  Details.swpInitial.cx = 200;
  Details.swpInitial.cy = 150;
#endif

  WinStartTimer(Hab, hwnd, IDT_EXETIMER, EXE_TIMEOUT);
  hApp = WinStartApp(hwnd,
                     &Details,
                     ParamBuffer,
                     NULL,
                     SAF_STARTCHILDAPP);

  if (0 == hApp)
  {
    WinStopTimer(Hab, hwnd, IDT_EXETIMER);
    Len = WinLoadString(Hab, hRessourceModule, IDS_PGP_START_FAILED,
                        MSGSTRN_MAXLEN, Msg);
    WinMessageBox(HWND_DESKTOP, hwnd, Msg, NULL, 0L, MB_OK | MB_ERROR);
  }
  else
  {
    ExecutionInProgress = TRUE;
    WinSetPointer(HWND_DESKTOP, hPtrWait);
  }
}

/**********************************************************************
 * Function: LaunchWinApp
 * Info    : Launch windowed application
 * Result  : -
 **********************************************************************/

void LaunchWinApp(HWND hwnd, const PSZ pExeName,
                  const PSZ pParameter, ULONG swpFlags)
{
  SHORT MaxX, MaxY, ix, iy;
  PROGDETAILS Details;

  Details.Length = sizeof(PROGDETAILS);
  Details.progt.progc =  PROG_DEFAULT;
  Details.progt.fbVisible = SHE_VISIBLE;
  Details.pszTitle = "";
  Details.pszExecutable = pExeName;
  Details.pszParameters = NULL;
  Details.pszStartupDir = NULL;
  Details.pszIcon = NULL;
  Details.pszEnvironment = "\0\0";
  Details.swpInitial.fl = swpFlags | SWP_ACTIVATE |
                          SWP_MOVE |
                          SWP_SIZE;
  MaxX = WinQuerySysValue(HWND_DESKTOP, SV_CXSCREEN);
  MaxY = WinQuerySysValue(HWND_DESKTOP, SV_CYSCREEN);

  /* Center dialog box within the Screen                             */
  ix = (SHORT)(( MaxX/4 ) / 2);
  iy = (SHORT)(( MaxY/4 ) / 2);

  Details.swpInitial.x = ix;
  Details.swpInitial.y = iy;
  Details.swpInitial.cx = MaxX - MaxX/4;
  Details.swpInitial.cy = MaxY - MaxY/4;
  Details.swpInitial.hwndInsertBehind = HWND_TOP;

  hApp = WinStartApp(hwnd,
                     &Details,
                     pParameter,
                     NULL,
                     SAF_STARTCHILDAPP);


}

/**********************************************************************
 * Function: ShowClipbrd
 * Info    : Show clipboard
 * Result  : -
 **********************************************************************/

void ShowClipbrd(HWND hwnd)
{

  LaunchWinApp(NULLHANDLE, ClipBoardExe, NULL, SWP_SHOW);

  if (0 == hApp)
  {
    Len = WinLoadString(Hab, hRessourceModule, IDS_SHOW_CLIPBRD_FAILED,
                        MSGSTRN_MAXLEN, Msg);
    WinMessageBox(HWND_DESKTOP, hwndMainDialog, Msg, NULL, 0L, MB_OK | MB_ERROR);
  }

}

/**********************************************************************
 * Function: RunEditor
 * Info    : Runs a user-defined editor to edit a decrypted message
 * Result  : -
 **********************************************************************/

void RunEditor(PSZ ExeName, PSZ FileToEdit)
{
  BOOL bQuoted = FALSE;
  int ExeLen = strlen(ExeName);
  char *pBuffer = (char *) malloc((ExeLen+1)*sizeof(char));
  char *pExe = (char *) malloc((ExeLen+1)*sizeof(char));
  char *pParams = NULL;

  if ((NULL != pBuffer) && (NULL != pExe))
  {

    char *p = NULL;

    strcpy(pExe, ExeName);

    if ('\"' == *pExe) // Is editor's filename encapsulated by double quote chars?
    {
      int i;

      strcpy(pExe, ExeName+1);
      bQuoted = TRUE;

      p = pExe;

      for (i = 1; i < ExeLen + 1; i++)
      {
        if ('\"' == *p)
        {
          strcpy(pBuffer, p);
          *p = 0; // Cut executable name from param list
          break;
        }
        ++p;
      }

      p = strtok(pBuffer, " ");
    }
    else
    {
      strcpy(pBuffer, ExeName);
      p = strtok(pBuffer, " ");
      strcpy(pExe, pBuffer);
    }

    if (NULL != p)
    {
      pParams = (char *) malloc((strlen(ExeName)+strlen(FileToEdit)+1 + 5)*sizeof(char));
      if ((NULL != pExe) && (NULL != pParams))
      {
         *pParams = 0; /* !!! */

         while(NULL != (p = strtok(NULL, " ")))
         {

           if (0 == strcmp("%f", p))
           {
             strcat(pParams, FileToEdit);
           }
           else
            if (0 == strcmp("\"%f\"", p))
            {
              strcat(pParams, "\"");
              strcat(pParams, FileToEdit);
              strcat(pParams, "\"");
            }
            else
              strcat(pParams, p);

           strcat(pParams, " ");
         }

         *(pParams+strlen(pParams)-1) = '\0';   // delete last space character
      }
    }
  }

  if ((NULL != pExe) && (0 != *pExe) && (NULL != pParams))
    LaunchWinApp(NULLHANDLE, pExe, pParams, SWP_SHOW);

  if (0 == hApp)
  {
    Len = WinLoadString(Hab, hRessourceModule, IDS_RUN_EDITOR_FAILED,
                        MSGSTRN_MAXLEN, Msg);
    WinMessageBox(HWND_DESKTOP, hwndMainDialog, Msg, NULL, 0L, MB_OK | MB_ERROR);
  }

  free(pParams);
  free(pExe);
  free(pBuffer);
}

/**********************************************************************
 * Function: RunPGPKeys
 * Info    : Launch PGPKeys
 * Result  : -
 **********************************************************************/

void RunPGPKeys(HWND hwnd)
{

  Len = WinLoadString(Hab, hRessourceModule, IDS_PGPKEYS_EXE,
                      MSGSTRN_MAXLEN, Msg);
  if ( 0 != Len )
  {
    PSZ pParameter = (PSZ) malloc((strlen(Msg)+4)*sizeof(CHAR));

    if (NULL != pParameter)
    {
      sprintf(pParameter, "/C %s", Msg);
      LaunchWinApp(hwnd, OS2Shell, pParameter, SWP_HIDE);
      free(pParameter);
    }
  }
  else
   hApp = 0;

  PGPKeysInProgress = FALSE;

  if (0 == hApp)
  {
    Len = WinLoadString(Hab, hRessourceModule, IDS_LAUNCH_PGPKEYS_FAILED,
                        MSGSTRN_MAXLEN, Msg);
    WinMessageBox(HWND_DESKTOP, hwndMainDialog, Msg, NULL, 0L, MB_OK | MB_ERROR);
  }
  else
    PGPKeysInProgress = TRUE;
}

/**********************************************************************/
/**********************************************************************/
/* -- EOF -- */

