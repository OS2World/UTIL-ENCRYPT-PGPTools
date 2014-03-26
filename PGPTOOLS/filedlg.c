/**********************************************************************
 *
 *  PGPTools - PM shell for PGP v5.0 for OS/2
 *
 *  Module   : FILEDLG.C
 *  Info     : File dialog routines
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
 *  030499 - Created
 *  220499 - CopyTempFileData2ClipBoard() no longer static
 *  110599 - Fix in TgtSelDlgProc during file overwrite inquiry
 *  120599 - IsSignature() created
 *  110699 - WM_HELP branch added for source and target file dialogs
 *           pgphelp.h included
 *  140699 - IsDetachedSignature now public for external use in
 *           PGPTOOLS.C
 *  140799 - Owner-window handles for WinMessageBox() changed
 *  060400 - Hardcoded "CMD.EXE" replaced by OS2Shell constant
 *  170800 - Fix: "FileDlg.pszIDrive = PathBuffer2" assignment removed
 *           in SourceFileSelection(); caused any continuous use of
 *           this function to trap with SYS3175 when using UNC
 *           filename notation (bug report by Vitus Jensen) both
 *           times
 *  300800 - Filenames are no longer forced to uppercase letters,
 *           intellegent appending of case-sensitive extension in
 *           QueryTargetFile() added
 *
 **********************************************************************/

#include "main_xx.h"
#include "about_xx.h"
#include "command.h"
#include "pgptools.h"
#include "pref_xx.h"
#include "profile.h"
#include "filedlgx.h"
#include "filedlg.h"
#include "keylist.h"
#include "pgphelp.h"

const CHAR DefTempFile[]     = "~PGPTOOL.TMP";
const CHAR DefTempOutFile[]  = "~PGPTOOL.OUT";
const CHAR DefTempKeyLog[]   = "~PGPTOOL.KEY";
const CHAR DefTempLogFile[]  = "~PGPTOOL.LOG";
const CHAR SignatureStrn[]   = "BEGIN PGP SIGNATURE";
const CHAR SignatureStrn2[]  = "BEGIN PGP SIGNED MESSAGE";

CHAR TempFile[_MAX_PATH];
CHAR TempOutFile[_MAX_PATH];
CHAR TempLogFile[_MAX_PATH];
CHAR TempKeyLog[_MAX_PATH];
BOOL IsDetachedSignature = FALSE;

static CHAR PathBuffer[CCHMAXPATH] = "";
static CHAR PathBuffer2[CCHMAXPATH] = "";
MRESULT EXPENTRY SrcSelDlgProc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2);
MRESULT EXPENTRY TgtSelDlgProc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2);

/**********************************************************************
 * Function: BuildTempFileName
 * Info    : Assemble temporary file name
 * Result  : -
 **********************************************************************/

void BuildTempFileNames(void)
{
  CHAR *p;

  *TempFile = 0;
  *TempOutFile = 0;
  *TempLogFile = 0;
  *TempKeyLog = 0;

  p = getenv("TEMP");
  if (NULL == p)
   p = getenv("TMP");

  if (NULL != p)
  {
   strcpy(TempFile, p);
   strcpy(TempOutFile, p);
   strcpy(TempLogFile, p);
   strcpy(TempKeyLog, p);
   if (*(p+strlen(p)-1) != '\\')
   {
    strcat(TempFile, "\\");
    strcat(TempOutFile, "\\");
    strcat(TempLogFile, "\\");
    strcat(TempKeyLog, "\\");
   }
   strcat(TempFile, DefTempFile);
   strcat(TempOutFile, DefTempOutFile);
   strcat(TempLogFile, DefTempLogFile);
   strcat(TempKeyLog, DefTempKeyLog);
  }
  else
  {
   strcpy(TempFile, DefTempFile);
   strcpy(TempOutFile, DefTempOutFile);
   strcpy(TempLogFile, DefTempLogFile);
   strcpy(TempKeyLog, DefTempKeyLog);
  }


}

/**********************************************************************
 * Function: FileSettingsSelection
 * Info    : File Open dialog for selection of key ring and random seed
 *           files
 * Result  : FALSE if error else TRUE
 **********************************************************************/

BOOL FileSettingsSelection(HWND hwnd, PSZ pDefaultFile, PSZ pTitle, PSZ pFilter)
{

 FILEDLG FileDlg;                       /* File dialog info structure   */
 HWND hwndDlg;                          /* File dialog window           */
 BOOL rc = FALSE;
 CHAR Temp[CCHMAXPATH] = "", *p;

 /*****************************************************************/
 /* Initially set all fields to 0                                 */
 /*****************************************************************/

 memset(&FileDlg, 0, sizeof(FILEDLG));

 /*****************************************************************/
 /* Initialize those fields in the FILEDLG structure that are     */
 /* used by the application                                       */
 /*****************************************************************/

 FileDlg.cbSize = sizeof(FILEDLG);           /* Size of structure    */
 FileDlg.fl =  FDS_CENTER | FDS_OPEN_DIALOG;
                                             /* FDS_* flags          */
 FileDlg.pszTitle = pTitle;                  /* Dialog title string  */
 strcpy(FileDlg.szFullFile, pFilter);        /* Initial path,        */
                                             /* file name, or        */
                                             /* file filter          */

 if ((0 == strcmp(PathBuffer, "")) &&
     (0 != strcmp(pDefaultFile, "")) &&
     (NULL != pDefaultFile)
    )
  strcpy(PathBuffer, pDefaultFile);

 if (0 != strcmp(PathBuffer, ""))
 {
   strcpy(Temp, PathBuffer);
   p = strrchr(PathBuffer, '\\');
   if (NULL != p)
    *p = '\0';
   FileDlg.pszIDrive = PathBuffer;
 }

 hwndDlg = WinFileDlg(HWND_DESKTOP, hwnd, &FileDlg);

 if (hwndDlg && (FileDlg.lReturn == DID_OK))
 {
  strcpy(pDefaultFile, strupr(FileDlg.szFullFile));
  strcpy(PathBuffer, pDefaultFile);
  rc = TRUE;
 }
 else
 {
  strcpy(PathBuffer, Temp);
 }

 return rc;
}

/**********************************************************************
 * Function: SourceFileSelection
 * Info    : File Open dialog for selection of files to be processed by
 *           PGP
 * Result  : FALSE if error or cancelled else TRUE
 **********************************************************************/

tFSelType SourceFileSelection(HWND hwnd, PSZ pSourceFile, PSZ pTitle)
{

 FILEDLG FileDlg;                       /* File dialog info structure   */
 HWND hwndDlg;                          /* File dialog window           */
 tFSelType rc = eNoSrc;
 PSZ p;

 /*****************************************************************/
 /* Initially set all fields to 0                                 */
 /*****************************************************************/

 memset(&FileDlg, 0, sizeof(FILEDLG));

 /*****************************************************************/
 /* Initialize those fields in the FILEDLG structure that are     */
 /* used by the application                                       */
 /*****************************************************************/

 FileDlg.cbSize = sizeof(FILEDLG);           /* Size of structure    */
 FileDlg.fl =  FDS_CENTER | FDS_OPEN_DIALOG | FDS_CUSTOM | FDS_APPLYBUTTON | FDS_HELPBUTTON;

 FileDlg.pszTitle = pTitle;                  /* Dialog title string  */
 FileDlg.pfnDlgProc = SrcSelDlgProc;
 FileDlg.hMod = hRessourceModule;
 FileDlg.usDlgId = DID_FILE_DIALOG;

 strcpy(FileDlg.szFullFile, "");
 if (0 != strcmp(PathBuffer2, ""))
 {
   p = strrchr(PathBuffer2, '\\');
   if (NULL != p)
    *p = '\0';
   strcat(PathBuffer2, "\\");
   strcat(FileDlg.szFullFile, PathBuffer2);
 }

 strcat(FileDlg.szFullFile, "*");            /* Initial path,        */
 hwndDlg = WinFileDlg(HWND_DESKTOP, hwnd, &FileDlg);

 if (hwndDlg)
 {
   switch(FileDlg.lReturn)
   {
    case DID_OK:
      strcpy(pSourceFile, FileDlg.szFullFile);
      strcpy(PathBuffer2, pSourceFile);
      rc = eFile;
     break;

    case DID_APPLY_PB:
      rc = eClipBoard;
      strcpy(pSourceFile, TempFile);
     break;

    case DID_CANCEL:
    default:
      rc = eNoSrc;
     break;

   }

 }

 return rc;
}

/**********************************************************************
 * Function: SrcSelDlgProc
 * Info    : dialog event handler for source file selection
 * Result  : TRUE or FALSE
 **********************************************************************/
MRESULT EXPENTRY SrcSelDlgProc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2)
{

 static PFILEDLG pFileDlg;
 MRESULT rc = FALSE;
 USHORT Val;

 switch (msg)
 {

   case WM_INITDLG:
      CenterWindow(hwnd);
      /* Get pointer to FILEDLG structure */
      pFileDlg = (PFILEDLG) WinQueryWindowULong(hwnd, QWL_USER);
    break;

   case WM_HELP:
     DisplayHelp(IDL_SRCFILE_HELP);
    break;

   case WM_COMMAND:
    switch(Val = SHORT1FROMMP(mp1))
    {
      case DID_APPLY_PB:
        if (NO_ERROR == CopyClipBoardData2TempFile())
        {
         pFileDlg->lReturn = DID_APPLY_PB;
         WinDismissDlg(hwnd, TRUE);
         return (MRESULT) TRUE;
        }
       break;
    }
    /* fall through for appropriate DID_OK handling by default windows proc!  */

   default:
     rc = WinDefFileDlgProc (hwnd, msg, mp1, mp2);
 }

 return rc;

}

/**********************************************************************
 * Function: QueryTargetFile
 * Info    : File SaveAs dialog for selection of files to be processed
 *           by PGP decrypt/verify routines
 * Result  : FALSE if error or cancelled, else TRUE
 **********************************************************************/

ULONG QueryTargetFile(HWND hwnd, PSZ pSourceFile, PSZ pTitle, BOOL ForVerify)
{

 ULONG rc;
 FILEDLG FileDlg;                       /* File dialog info structure   */
 HWND hwndDlg;                          /* File dialog window           */
 PSZ p1, p2;

 /*****************************************************************/
 /* Initially set all fields to 0                                 */
 /*****************************************************************/

 memset(&FileDlg, 0, sizeof(FILEDLG));

 /*****************************************************************/
 /* Initialize those fields in the FILEDLG structure that are     */
 /* used by the application                                       */
 /*****************************************************************/

 FileDlg.cbSize = sizeof(FILEDLG);           /* Size of structure    */
 FileDlg.pszTitle = pTitle;                  /* Dialog title string  */
 FileDlg.pfnDlgProc = TgtSelDlgProc;

  p1 = strrchr(pSourceFile, '\\');
  p2 = strrchr(pSourceFile, '.');
  if ((NULL != p1) && (NULL != p2))
   if (p2 > p1)
    *p2 = '\0';

 FileDlg.fl =  FDS_CENTER | FDS_HELPBUTTON;
 if (!ForVerify)
 {
  FileDlg.fl |= FDS_SAVEAS_DIALOG;
 }
 else
 {
  FileDlg.fl |= FDS_OPEN_DIALOG;
  if ((NULL != p1) && (NULL != p2))
   if (p2 > p1)
   {
      char *p = p1; // p points now to the character before the first filename character (usually '\\')

      // check if filename contains any lowercase letters
      while(*p)
      {
        if ((*p >= 'a') && (*p <= 'z'))
        {
           // yes, so append a lowercase default extension
           strcpy(p2, ".txt");
           break;
        }
        ++p;
      }

      if (*p == '\0')
        // no, append an uppercase default extension
        strcpy(p2, ".TXT");
   }
 }

 strcpy(FileDlg.szFullFile, pSourceFile);   /* Initial path */
 hwndDlg = WinFileDlg(HWND_DESKTOP, hwnd, &FileDlg);

 if (hwndDlg)
 {
   switch(FileDlg.lReturn)
   {
    case DID_OK:
      strcpy(pSourceFile, FileDlg.szFullFile);
      strcpy(PathBuffer2, pSourceFile);
      rc = NO_ERROR;
     break;

    case DID_CANCEL:
    default:
      rc = ERROR_OPEN_FAILED;
     break;

   }

 }

 return rc;
}

/**********************************************************************
 * Function: TgtSelDlgProc
 * Info    : dialog event handler for target file selection
 * Result  : TRUE or FALSE
 **********************************************************************/
MRESULT EXPENTRY TgtSelDlgProc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2)
{

 static PFILEDLG pFileDlg2;
 CHAR Buffer[CCHMAXPATH+100];
 CHAR FileBuffer[CCHMAXPATH];
 CHAR PathBuffer3[CCHMAXPATH];
 CHAR Title[TITLESTRN_MAXLEN+1];
 BOOL SignedFile;

 MRESULT rc = FALSE;

 switch (msg)
 {

   case WM_INITDLG:
      CenterWindow(hwnd);
      pFileDlg2 = (PFILEDLG) WinQueryWindowULong(hwnd, QWL_USER);
    break;

   case WM_HELP:
     DisplayHelp(IDL_TGTFILE_HELP);
    break;

   case WM_COMMAND:
    switch(SHORT1FROMMP(mp1))
    {
      case DID_OK:
        strcpy(PathBuffer3, pFileDlg2->szFullFile);
        WinQueryWindowText(WinWindowFromID(hwnd, DID_FILENAME_ED),
                           sizeof(FileBuffer),
                           FileBuffer);
        strcat(PathBuffer3, FileBuffer);
        SignedFile = IsSignature(JobDesc.SourceFile);
        if (!SignedFile ||
            (SignedFile && !IsDetachedSignature)
           )
        {
          if(FileExist(PathBuffer3))
          {
            Len = WinLoadString(Hab, hRessourceModule, IDS_QUERY_TARGET_OVERWRITE,
                                MSGSTRN_MAXLEN, Msg);
            Len = WinLoadString(Hab, hRessourceModule, IDS_BUBBLE_DECVERIFYDATA_HELP,
                                TITLESTRN_MAXLEN, Title);
            sprintf(Buffer, Msg, PathBuffer3);
            if (MBID_YES == WinMessageBox(HWND_DESKTOP, hwnd,
                                          Buffer, "", 0, MB_ICONQUESTION | MB_YESNO))
            {
              if (0 == remove(PathBuffer3))
              {
               strcpy(pFileDlg2->szFullFile, PathBuffer3);
               pFileDlg2->lReturn = DID_OK;
               WinDismissDlg(hwnd, TRUE);
               return (MRESULT) TRUE;
              }
              pFileDlg2->lReturn = DID_CANCEL;
            }
            return (MRESULT) FALSE;
          }
        }
        else
        {
          /*
           * source file is a detached signature file that is to
           * be checked against the outfile, so there's no need to
           * query for outfile overwrite allowance
           */
          strcpy(pFileDlg2->szFullFile, PathBuffer3);
          pFileDlg2->lReturn = DID_OK;
          WinDismissDlg(hwnd, TRUE);
          return (MRESULT) TRUE;
        }
      /* fall through! */
    }

   default:
     rc = WinDefFileDlgProc (hwnd, msg, mp1, mp2);
 }

 return rc;

}

/**********************************************************************
 * Function: CopyClipBoardData2TempFile
 * Info    : Check clipboard for text data and copy them to temp file
 * Result  : NO_ERROR, ERROR_ACCESS_DENIED, ERROR_OPEN_FAILED
 **********************************************************************/
ULONG CopyClipBoardData2TempFile(void)
{

  ULONG Result = NO_ERROR, MsgID;
  PSZ pszMem;
  FILE *fp;
  int c;

  if (WinOpenClipbrd(Hab))
  {
    pszMem = (PSZ) WinQueryClipbrdData(Hab, CF_TEXT);
    if (NULL == pszMem)
     Result = ERROR_INVALID_DATA;
    else
    {
      if (NULL != (fp = fopen(TempFile, "wb")))
      {
        while (0 != (c = (int)(*pszMem)))
        {
         fputc(c, fp);
         ++pszMem;
        }
        fclose(fp);

      }
      else
       Result = ERROR_OPEN_FAILED;
    }

    WinCloseClipbrd(Hab);

  }
  else
   Result = ERROR_ACCESS_DENIED;

  if (NO_ERROR != Result)
  {
   switch(Result)
   {
    case ERROR_INVALID_DATA:
      MsgID = IDS_INVALID_CLIPBOARD_DATA;
     break;

    case ERROR_ACCESS_DENIED:
      MsgID = IDS_NO_CLIPBOARD_ACCESS;
     break;

    default:
      MsgID = IDS_GENERAL_PROCESS_FAILURE;
     break;

   }

   Len = WinLoadString(Hab, hRessourceModule, MsgID,
                       MSGSTRN_MAXLEN, Msg);
   WinMessageBox(HWND_DESKTOP, hwndMainDialog, Msg, NULL, 0, MB_ERROR | MB_OK);
  }
  return Result;

}

/**********************************************************************
 * Function: CopyTempFileData2ClipBoard
 * Info    : Copy PGP outfile data to clipboard
 * Result  : NO_ERROR, ERROR_ACCESS_DENIED, ERROR_OPEN_FAILED
 **********************************************************************/

ULONG CopyTempFileData2ClipBoard(void)
{
  APIRET rc;
  ULONG Result = NO_ERROR, MsgID;
  PSZ pszMem, p;
  FILE *fp;
  int c;

  if (NULL == (fp = fopen(TempOutFile, "rb")))
  {
   /* result handled by MainDlgProc() */
   return ERROR_OPEN_FAILED;
  }
  else
  {
    rc = DosAllocSharedMem((PVOID) &pszMem,
                           NULL, (ULONG)FileSize(fp, NULL)+1,
                           PAG_WRITE | PAG_COMMIT | OBJ_GIVEABLE);

    if (NO_ERROR != rc)
    {
     Result = ERROR_OPEN_FAILED;
    }
    else
    {
     p = pszMem;
     while (EOF != (c = fgetc(fp)))
      *p++ = (CHAR) c;
    }

    fclose(fp);

    *p = 0; /* signal end of data! */

    if (WinOpenClipbrd(Hab))
    {

      WinEmptyClipbrd(Hab);
      if (FALSE == WinSetClipbrdData(Hab,
                                     (ULONG) pszMem,
                                     CF_TEXT,
                                     CFI_POINTER))
       Result = ERROR_ACCESS_DENIED;

      WinCloseClipbrd(Hab);

    }
    else
     Result = ERROR_ACCESS_DENIED;

  }
  if (NO_ERROR != Result)
  {
     switch(Result)
     {

      case ERROR_ACCESS_DENIED:
        MsgID = IDS_NO_CLIPBOARD_ACCESS;
       break;

      default:
        MsgID = IDS_GENERAL_PROCESS_FAILURE;
       break;

     }

     Len = WinLoadString(Hab, hRessourceModule, MsgID,
                         MSGSTRN_MAXLEN, Msg);
     WinMessageBox(HWND_DESKTOP, hwndMainDialog, Msg, NULL, 0L, MB_ERROR | MB_OK);
  }

  return Result;
}

/**********************************************************************
 * Function: CreateKeyLogFile
 * Info    : Create PGP key logfiles to setup PGPTools window lists
 * Result  : TRUE or FALSE
 **********************************************************************/
void CreateKeyLogFile(HWND hwnd)
{
  CHAR Commandline[PARAM_LEN];

  FreeKeyList(&pKeyListAnchor);
  FreeKeyList(&pOutKeyAnchor);
  strcpy(Commandline, "/C ");
  strcat(Commandline, "\"");
  strcat(Commandline, PGPKeyServiceCommand);
  strcat(Commandline, " -l >");
  strcat(Commandline, TempKeyLog);
  strcat(Commandline, "\"");
  JobDesc.Job = eBuildList;
  ExecutePGP(hwnd, OS2Shell, Commandline);
}

/**********************************************************************
 * Function: IsSignature
 * Info    : Checks if SrcFile is a detached signature file
 * Result  : TRUE or FALSE
 **********************************************************************/
BOOL IsSignature(PSZ SrcFile)
{
  FILE *fp;
  PSZ p1, p2;
  CHAR Line[80];
  BOOL Result = FALSE;

  IsDetachedSignature = FALSE;

  p1 = strrchr(SrcFile, '\\');
  p2 = strrchr(SrcFile, '.');
  if ((NULL != p1) && (NULL != p2))
   if (p2 > p1)
   {
     if (0 == stricmp(p2, ".sig"))
     {
      /* extension .sig found assuming it's a detached signature file */
      IsDetachedSignature = TRUE;
      return TRUE;
     }
   }

  if (NULL == (fp = fopen(SrcFile, "rt")))
   return FALSE;

  if (NULL != fgets(Line, 80, fp))
  {
   if (NULL != strstr(strupr(Line), SignatureStrn))
   {
    /* signature cleartext found assuming it's a detached signature file */
    Result = TRUE;
    IsDetachedSignature = TRUE;
   }

   if (NULL != strstr(strupr(Line), SignatureStrn2))
    Result = TRUE;
  }

  fclose(fp);

  return Result;
}

/**********************************************************************/
/**********************************************************************/
/* -- EOF -- */

