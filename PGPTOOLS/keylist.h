/**********************************************************************
 *
 *  PGPTools - PM shell for PGP v5.0 for OS/2
 *
 *  Module   : KEYLIST.H
 *  Info     : Key list management (Header file)
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
 *  280499 - Created
 *  140799 - tKeyElement expanded
 *
 **********************************************************************/

#if !defined _KEYLIST_H
#define _KEYLIST_H

typedef enum
{
  eInvalidKey,
  ePrivKey,
  ePubKey,
} tKeyType;


typedef struct sKeyElement
{
  tKeyType KeyType;
  CHAR KeyAlgorithm[4];
  CHAR KeyID[20];
  CHAR UserID[100];
  struct sKeyElement *pNext;
} tKeyElement;

#define KEYID_OFFSET        10
#define KEYID_SIZE          10
#define KEY_ALGORITHM_OFFSET  43
#define KEY_ALGORITHM_SIZE    3
#define USERID_OFFSET       5

#define INIT_ELEMENT(x)                                                \
                (x).KeyType = eInvalidKey,                             \
                (x).pNext   = NULL,                                    \
                memset((x).KeyAlgorithm, 0, sizeof((x).KeyAlgorithm)), \
                memset((x).KeyID, 0, sizeof((x).KeyID)),               \
                memset((x).UserID, 0, sizeof((x).UserID))


extern tKeyElement *pKeyListAnchor;
extern tKeyElement *pOutKeyAnchor;

void FreeKeyList(tKeyElement **pAnchor);
BOOL BuildKeyList(PSZ Filename);
BOOL SelectKeyToEncrypt(HWND hwnd);
BOOL KeyFoundInList(tKeyElement *pAnchor, PSZ Listtext, tKeyElement *pKeyData);

#endif /* _KEYLIST_H */

