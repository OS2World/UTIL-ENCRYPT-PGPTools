.* Dieses Dokument wurde mit Phelsuma/2 erstellt
:userdoc.
:title.PGPTools for OS/2 Documentation
:h1 res=1000.Introduction
:font facename='Tms Rmn' size=32x24.
:hp2.
.ce PGPTools for OS/2 v1.50
:ehp2.
:font facename='Tms Rmn' size=20x10.
.ce Copyright ¸ 1999-2003 by Bernd Giesen. All rights reserved.
.ce Distributed under the terms of the GNU General Public License
:font facename=default.
:p.
.br
:color fc=DarkPink bc=default.PGPTools for OS/2:color fc=default bc=default. is a 32-bit OS/2 PM application, which should help you to ease the daily use of the encryption software :hp2.:artwork runin
name='World.BMP'.:link reftype=launch object='NETSCAPE.EXE'
data='http://www.pgpi.com'.PGP:elink.:ehp2. (Pretty Good Privacy)
:fn id=A. You can link directly out of this document to the related URL if the
Netscape Navigator v2.02 for OS/2 or the Netscape Communicator v4.x for OS/2 is properly running on your system and you're currently connected to the Internet.
:efn.
:link refid=A reftype=fn.*:elink..
:p.
:nt text='Important!'.
:color fc=Red bc=default.
:hp2.To be able to use :color fc=DarkPink bc=default.PGPTools for OS/2:color fc=Red bc=default., you must have already installed and properly set up :color fc=default bc=default.PGP v5.0 for OS/2:color fc=Red bc=default. on your system!:ehp2.
:color fc=default bc=default.
You can obtain this software version :hp2.:artwork runin name='World.BMP'.:link reftype=launch object='NETSCAPE.EXE' data='http://www.openpgp.net'.here:elink.:ehp2..
:ent.
:p.
:color fc=DarkPink bc=default.PGPTools for OS/2:color fc=default bc=default. does not contain any PGP source code. It works only as a graphical user interface (GUI)/frontend for PGP v5.0 for OS/2.
That means that the functionality of :color fc=DarkPink bc=default.PGPTools for OS/2:color fc=default bc=default. depends on the capabilitites of PGP itself.
.br
As of v1.42 a PGP key administration - eagerly awaited by so many users - has been integrated into :color fc=DarkPink bc=default.PGPTools for OS/2:color fc=default bc=default.. It's a standalone software package called :color fc=DarkPink bc=default.PGPKeys:color fc=default bc=default. created by Thomas Bohn, which can be launched directly from within :color fc=DarkPink bc=default.PGPTools for OS/2:color fc=default bc=default..
:p.
:color fc=DarkPink bc=default.PGPTools for OS/2:color fc=default bc=default. was developed and tested under OS/2 Warp 4 (incl. Fixpack #14) and PGP v5.0 for OS/2 (GA). Theoretically, it should also run under OS/2 Warp 3.
.br
.* Ende
:h1 res=1010.Installation/Deinstallation
:i1. Deinstallation
:i1. Installation
:p.
When you are reading these lines, you have already installed :color fc=DarkPink bc=default.PGPTools for OS/2:color fc=default bc=default. successfully. &colon.-)
.br
You can start :color fc=DarkPink bc=default.PGPTools for OS/2:color fc=default bc=default. by selecting the corresponding symbol
:artwork name='LOCK.BMP' runin.
in the "PGPTools for OS/2" folder. A context-sensitive online help is always available by pressing the F1 key.
:p.
If you would like to uninstall :color fc=DarkPink bc=default.PGPTools for OS/2:color fc=default bc=default., run the (Un-)Installation utility
:artwork name='INSTALL.BMP' runin.
in the "PGPTools for OS/2" folder, where you select the menuitem ":hp2.Delete:ehp2." in the ":hp2.Action:ehp2." pulldown menu. This will remove all installed files, folders and WPS objects of :color fc=DarkPink bc=default.PGPTools for OS/2:color fc=default bc=default..
:nt text='Note:'.
No system files or system settings are changed, neither during the installation nor during the deinstallation!
:ent.

.* Ende

:h1 res=1020.Before you start to use PGPTools for OS/2
:i1. Documentation
:i1 id=1. Environment variable
:i2 refid=1. CMD.EXE
:i2 refid=1. COMSPEC
:i2 refid=1. CONFIG.SYS
:i2 refid=1. OS2_SHELL
:i2 refid=1. PATH
:i2 refid=1. PGPPATH
:p.
:hp5.Please pay attention to the following hints before you're going to use PGPTools for OS/2 the first time:ehp5.&colon.
:p.
As already mentioned in the
:link reftype=hd res=1000.introduction:elink.
you must have successfully installed the encryption software :hp2.PGP v5.0 for OS/2:ehp2. before you can use :color fc=DarkPink bc=default.PGPTools for OS/2:color fc=default bc=default.. If not already done so, you must create a valid key pair (your public and your secret key), then. This can be done now in a comfortable way by directly launching :color fc=DarkPink bc=default.PGPKeys:color fc=default bc=default. from within :color fc=DarkPink bc=default.PGPTools for OS/2:color fc=default bc=default..
:p.
A description of the installation of PGP v5.0 for OS/2 and its key management
would be too extensive for this documentation. I would like to refer to the appropriate PGP literature which is available at the following links
:link refid=A reftype=fn.*:elink.&colon.
:ul.
:li.:hp2.:artwork runin
name='World.BMP'.:link reftype=launch object='NETSCAPE.EXE'
data='http://www.openpgp.net'.http&colon.&slash.&slash.www&per.openpgp&per.net:elink.:ehp2.
:li.:hp2.:artwork runin
name='World.BMP'.:link reftype=launch object='NETSCAPE.EXE'
data='http://www.pgpi.com'.http&colon.&slash.&slash.www&per.pgpi&per.com:elink.:ehp2.
:eul.
:p.
In any case it is required (for PGP itself and for :color fc=DarkPink bc=default.PGPTools for OS/2:color fc=default bc=default. as well) that you'll set the environment variable :hp2.PGPPATH:ehp2., which contains the fully qualified pathname where the PGP v5.0 for OS/2 executable PGP.EXE is located by editing the CONFIG.SYS file.
:p.
As of v1.44 :color fc=DarkPink bc=default.PGPTools for OS/2:color fc=default bc=default. retrieves the currently used command processor by evaluating the environment variable :hp2.COMSPEC:ehp2.. If this is not set, the environment variable :hp2.OS2_SHELL:ehp2. is evaluated. If this also fails, the OS/2 default command processor :hp2.CMD.EXE:ehp2. is being used.
.br
However, using alternative command processor (e.g. 4OS2) instead of CMD.EXE requires that this alternative command processor also supports the commandline option "/C",
which moreover must have the same meaning as with CMD.EXE. You'll find more detailed informations about in the
:link reftype=launch object='view.exe' data='cmdref.inf cmd'.OS/2 online help:elink., respectively in the documentation of the alternative command processor.
:p.
At last, you must extend the (usually already existing) environment variable :hp2.PATH:ehp2. in the CONFIG.SYS file with the fully qualified pathname of the directory where PGP v5.0 for OS/2 is located.

:nt text='Examples:'. (assuming "C&colon.&bslash.PGP50" is the directory, where PGP v5.0 for OS/2 has been previously installed to)
:xmp.
SET PGPPATH=C&colon.&bslash.PGP50
SET PATH=C&colon.&bslash.PGP50;&percent.PATH&percent.
:exmp.
:ent.
Finally, you must reboot your system to let the changes take effect!
.br
.br
.* Ende

:h1 res=1030.License
:i1. License
:p.
As of version v1.50 :color fc=DarkPink bc=default.PGPTools for OS/2:color fc=default bc=default. is distributed under the terms of the :hp2.GNU General Public License:ehp2.. This means:
:p.
This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation;
 either version 2 of the License, or (at your option) any later version.
:p.
This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
See the GNU General Public License for more details.
:p.
You should have received a copy of the GNU General Public License along with this program; if not, write to the Free Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307, USA.
:p.
:nt text='Please note:'.
The use of the key administration tool :color fc=DarkPink bc=default.PGPKeys:color fc=default bc=default. from Thomas Bohn (integrated as of v1.42) is subject to its own license agreement (see PGPKEYS.LIC)!
:ent.

.* Ende

:h1 res=1050.Contact
:i1. Author
:nt text='Author:'.
Bernd Giesen
.br
Nirmer Str. 81
.br
D-52080 Aachen
.br
GERMANY
:p.
:hp2.Email&colon.:ehp2.
:link reftype=launch object='NETSCAPE.EXE' data='mailto:Bernd.Giesen@t-online.de?subject=PGPTools for OS/2'.Bernd&per.Giesen@t-online&per.de:elink.
.br
:hp2.Homepage&colon.:ehp2.
:artwork runin name='World.BMP'.
:link reftype=launch object='NETSCAPE.EXE' data='http://home.t-online.de/home/Bernd.Giesen/index_e.html'.http&colon.&slash.&slash.home&per.t-online&per.de&slash.home&slash.Bernd&per.Giesen:elink.
:ent.
:p.

:nt text='Please note:'.
If you've questions or problems regarding :color fc=DarkPink bc=default.PGPKeys:color fc=default bc=default., please contact its author Thomas Bohn directly, not me! This guarantees a simple and fast handling in your own's interest.
:p.
:hp2.Email&colon.:ehp2.
:link reftype=launch object='NETSCAPE.EXE' data='mailto:Thomas@Bohn-Stralsund.de?subject=PGPKeys for OS/2'.Thomas@Bohn-Stralsund&per.de:elink.
.br
:hp2.Homepage&colon.:ehp2.
:artwork runin name='World.BMP'.
:link reftype=launch object='NETSCAPE.EXE' data='http://Bohn-Stralsund.de'.http&colon.&slash.&slash.Bohn-Stralsund&per.de:elink.
:ent.
.* Ende

:h1 res=1060.Known bugs
:i1.Known bugs
:p.
When you're using a public key to encrypt to the first time before you've assigned a confidence level to that key, the encryption via :color fc=DarkPink bc=default.PGPTools for OS/2:color fc=default bc=default. will fail.

:nt text='Solution:'.
Assign a proper confidence level to the related key using the corresponding PGP key management command or alternatively confirm the missing confidence level by :hp5.once:ehp5. encrypting a document to that key by using the corresponding PGP encryption command :hp5.on the command line:ehp5..
PGP will keep the confirmation for the missing confidence level in mind, so that further encryptions via :color fc=DarkPink bc=default.PGPTools for OS/2:color fc=default bc=default. will succeed in future.
:ent.

.* Ende

:h1 res=1070.History/Changes
:p.
:parml tsize=10 compact.
.********************************** v1.50 ********************************
:pt.v1.50&colon.:pd.
:parml tsize=5 break=none compact.
:pt.NEW&colon.:pd.:color fc=DarkPink bc=default.PGPTools for OS/2:color fc=default bc=default. is now distributed under the terms of the :hp2.GNU General Public License:ehp2.. See the file "COPYING" or "GPL.HTM" for details.
.br
:eparml.
.********************************** v1.49 ********************************
:pt.v1.49&colon.:pd.
:parml tsize=5 break=none compact.
:pt.FIX&colon.:pd.:color fc=DarkPink bc=default.PGPTools for OS/2:color fc=default bc=default. now accepts long file and directory names containing space characters.
This also applies to the keyring filenames and to the editor's filename as well (see important notes in the online help of the "Preferences" dialog)
.br
:eparml.
.********************************** v1.48 ********************************
:pt.v1.48&colon.:pd.
:parml tsize=5 break=none compact.
:pt.FIX&colon.:pd.Just a minor fix: In most cases the message :hp1."The initialization file
must be updated. Please check your settings and save them again!":ehp1. appeared
while opening the "Preferences" dialog from the system menu, even if an update
was not really necessary.
.br
:eparml.
.********************************** v1.47 ********************************
:pt.v1.47&colon.:pd.
:parml tsize=5 break=none compact.
:pt.NEW&colon.:pd.Optionally, a :color fc=DarkPink bc=default.PGPTools for OS/2:color fc=default bc=default. toolbar using small push buttons is now available.
.br
:pt.NEW&colon.:pd.After decypting/verifying a text editor can be called from the log window to immediately display the decrypted/verified data.
Therefore, any editor (or any alternative PM application) can be configured in the preferences dialog.
.br
.br
:pt.FIX&colon.:pd.There appeared wrong bitmaps on the 4 toolbar pushbuttons in the German release of :color fc=DarkPink bc=default.PGPTools for OS/2:color fc=default bc=default. if the PGPKeys package wasn't installed.
.br
:pt.FIX&colon.:pd.Some bubblehelp texts were partially cut off when the main window was located too close at the screen borders.
.br
:eparml.
.********************************** v1.46 ********************************
:pt.v1.46&colon.:pd.
:parml tsize=5 break=none compact.
:pt.CHG&colon.:pd.Improved (more moderate) behaviour of the application if the main window should always float
on top of the desktop.
.br
:pt.CHG&colon.:pd.Filenames are no longer forced to be displayed in upper case letters in the edit field of the 2nd file selection dialog during verification/decryption.
.br
.br
:pt.FIX&colon.:pd.The push buttons' bubble help windows now appear correctly again and always in foreground.
.br
:eparml.
.********************************** v1.45 ********************************
:pt.v1.45&colon.:pd.
:parml tsize=5 break=none compact.
:pt.CHG&colon.:pd.Extra success message box no longer appears upon finishing a PGP decrypt/verify action since
another action's result window is already displayed.
.br
.br
:pt.FIX&colon.:pd.Using UNC filenames in the file selection dialog caused a SYS3175 when continuing to use the file selection dialog in this way.
.br
:eparml.
.********************************** v1.44 ********************************
:pt.v1.44&colon.:pd.
:parml tsize=5 break=none compact.
:pt.CHG&colon.:pd.The command processor to call PGP for OS/2 is no longer fixed preset to "CMD.EXE", but is now retrieved by evaluating the environment settings COMSPEC, respectively OS2_SHELL.
This makes it possible to also use alternative command processors e.g. like 4OS2. If the evaluation fails, the default command processor "CMD.EXE" is continued to be used.
:p.
:hp2.See also&colon.:ehp2.
:link reftype=hd res=1020.Before you start to use PGPTools for OS/2:elink.
.br
:eparml.
.********************************** v1.43 ********************************
:pt.v1.43&colon.:pd.
:parml tsize=5 break=none compact.
:pt.NEW&colon.:pd.The main window's title bar can now optionally be switched on or off in the popup menu. The title bar's current state is automatically stored in PGPTOOLS.INI.
The :color fc=Pink bc=default.Alt:color fc=default bc=default. key combinations known from the system menu can also be used if the title bar is switched off.
The popup menu can now be activated manually by pressing :color fc=Pink bc=default.Shift+F10:color fc=default bc=default. if the main window has the input focus.
.br
:pt.NEW&colon.:pd.During the installation a program object for :color fc=DarkPink bc=default.PGPKeys for OS/2:color fc=default bc=default. is created in the program folder, so that it can be directly launched from there.
.br
.br
:pt.CHG&colon.:pd.During a currently running PGP action, no other PGP action can be simultaniously executed any longer.
Pressing a corresponding pushbutton in the main window or selecting an entry in the popup menu will be ignored in this case.
.br
.br
:pt.FIX&colon.:pd.When :color fc=DarkPink bc=default.PGPTools for OS/2:color fc=default bc=default. was launched it did not appear in the window list.
.br
:pt.FIX&colon.:pd.The state of any pushbutton in the main window wasn't reset properly, if the mouse cursor was moved out of the pushbutton area while the left mouse button was pressed.
Starting the selection of a PGP action in this way could not be aborted (although it usually should be possible so).
.br
:pt.FIX&colon.:pd.Keyboard input (e.g. the cursor keys) was locked in the main window.
.br
:pt.FIX&colon.:pd.The mouse cursor appears correctly again as a wait cursor within the main window area while a PGP action is performed.
.br
:pt.FIX&colon.:pd.Memory leak fixed.
.br
:eparml.
.br
.********************************** v1.42 ********************************
:pt.v1.42&colon.:pd.
:parml tsize=5 break=none compact.
:pt.NEW&colon.:pd.Integration of an eagerly awaited PGP key administration (:color fc=DarkPink bc=default.PGPKeys:color fc=default bc=default. by Thomas Bohn). It can be launched by the newly added pushbutton "Launch PGPKeys" or by the popup menu.
.br
:pt.NEW&colon.:pd.The preferences notebook (on the "General" page) was expanded with a "Always display hint window" checkbox and a "Send key server" entry. If the checkbox is enabled and the :color fc=DarkPink bc=default.PGPKeys:color fc=default bc=default. package is not available or incomplete for some reason (see :color fc=DarkPink bc=default.PGPTools for OS/2:color fc=default bc=default. online help for more details) a respective message window will appear upon each startup of :color fc=DarkPink bc=default.PGPTools for OS/2:color fc=default bc=default.. In "Send key server" a server address (URL) can be entered where the key administration :color fc=DarkPink bc=default.PGPKeys:color fc=default bc=default. will upload the PGP public key to (default address&colon. hkp&colon.&slash.&slash.wwwkeys&per.pgp&per.net).
.br
:pt.NEW&colon.:pd.:color fc=DarkPink bc=default.PGPTools for OS/2:color fc=default bc=default. now restores its last window position on the desktop.
.br
.br
:pt.FIX&colon.:pd.If the environment variable PGPPATH contains more than one path entry (each separated by a semicolon), only the :hp5.first:ehp5. one will be considered for use with :color fc=DarkPink bc=default.PGPTools for OS/2:color fc=default bc=default..
:eparml.
.br
.********************************** v1.30 ********************************
:pt.v1.30&colon.:pd.
:parml tsize=5 break=none compact.
:pt.NEW&colon.:pd.The system menu and the preferences notebook (on the "General" page) were expanded with the "(Window) always on top" item.
In the system menu this setting can be toggled for the current session, whereas in the preferences notebook this setting may be saved permanentely.
.br
If enabled, :color fc=DarkPink bc=default.PGPTools for OS/2:color fc=default bc=default. is caused to always remain the topmost window on the desktop unless if minimized.
:pt.NEW&colon.:pd.In the key selection listbox window the encryption algorithm, that was used to create the key, is now additionally displayed.
.br
.br
:pt.CHG&colon.:pd.By great user request I decided to now display private/secret keys in the key selection listbox, too.
:pt.CHG&colon.:pd.The listbox elements were rearranged. For a better/clear appearance another font (System VIO 10) was selected.
.br
.br
:pt.FIX&colon.:pd.In minimized state the symbol of :color fc=DarkPink bc=default.PGPTools for OS/2:color fc=default bc=default. could no longer be moved by mouse.
:pt.FIX&colon.:pd.The state of some checkable settings in the popup menu were not always considered correctly during execution of the corresponding PGP actions.
:eparml.
.br
.********************************** v1.21 ********************************
:pt.v1.21&colon.:pd.
:parml tsize=5 break=none compact.
:pt.FIX&colon.:pd.The stored state of the "Always encrypt to self" setting was not evaluated/loaded correctly during startup, only if this setting was saved first during a program run in the preferences notebook before encrypting a message.
:eparml.
.br
.********************************** v1.20 ********************************
:pt.v1.20&colon.:pd.
:parml tsize=5 break=none compact.
:pt.NEW&colon.:pd.A currently running PGP action can always be terminated by pressing the :color fc=Pink bc=default.ESC:color fc=default bc=default. key (where the :color fc=DarkPink bc=default.PGPTools for OS/2:color fc=default bc=default. window must have the input focus!).
:pt.NEW&colon.:pd.During a running PGP action the mouse pointer is displayed as a wait cursor (clock) within the :color fc=DarkPink bc=default.PGPTools for OS/2:color fc=default bc=default. window.
:pt.NEW&colon.:pd.A context-sensitive online help is now available for the file selection dialog windows.
.br
.br
:pt.CHG&colon.:pd.The preferences window is now a notebook rather than a simple dialog window.
:pt.CHG&colon.:pd.The timeout for an automatic termination of a currently running PGP action has been increased up to 60s. This should be enough to also process very large files.
:pt.CHG&colon.:pd.Selecting the passphrase entryfield will now directly mark an existing passphrase.
.br
.br
:pt.FIX&colon. :pd.The passphrase's entryfield ist now properly positioned within the dialog window, even with different screen resolutions.
:eparml.
.br
.********************************** v1.01 ********************************
:pt.v1.01&colon.:pd.First public release
:eparml.

.* Ende

:h1 res=1080.Trademarks
:p.
:ul.
:li. OS/2 and Warp are registered trademarks of IBM International Business Machines, Inc.
:li. All other trademarks are property of their respective owners.
:eul.

.* Ende

:h1 res=1090.Credits
:p.
Thanks to IBM for providing us OS/2 and to William H. Geiger III for the OS/2 port of Pretty Good Privacy v5.0.
:p.
Many special thanks to Thomas Bohn who did a great deal in developing and providing his graphical PGP key administration frontend :color fc=DarkPink bc=default.PGPKeys:color fc=default bc=default..
.* Ende

:euserdoc.
