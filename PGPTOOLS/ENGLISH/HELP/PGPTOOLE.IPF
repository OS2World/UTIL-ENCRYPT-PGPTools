.* Dieses Dokument wurde mit Phelsuma/2 erstellt
:userdoc.
:title.PGPTools for OS/2 Help
:h1 res=1.The main window
:i1. Main window
.br
Using the main window of :color fc=DarkPink bc=default.PGPTools for OS/2:color fc=default bc=default. you have access to the following elements:
.br
:ul compact.
:li. 5 :link reftype=hd res=2.user buttons:elink.
:li. an :link reftype=hd res=3.extended system menu:elink.
:li. a :link reftype=hd res=4.popup menu:elink.
:eul.
.br
.* Ende Das Hauptfenster
.* -----------------------------------------------------------------------------

:h2 res=2.The user buttons
:i1 id=clipboard. Clipboard
:i1 id=buttons. User buttons
:i2 refid=buttons. Launch PGPKeys
:i2 refid=buttons. Sign
:i2 refid=buttons. Encrypt
:i2 refid=buttons. Encrypt and Sign
:i2 refid=buttons. decrypt or Verify
:i1 id=Info. Logging
:i2 refid=Info. Information window
:i2 refid=Info. Log window
:i1 id=actions. PGP actions
:i2 refid=actions. Cancelling
.br
:artwork align=center name='F:\WC10SRC\PGPTOOLS\ENGLISH\HELP\emainwin.bmp'.
.br
The 5 user pushbuttons for the control of PGP(Pretty Good Privacy) v5.0 for OS/2 have (arranged from left to right) the following meaning:
:ul compact.
:li. Launch PGPKeys
:li. Sign
:li. Encrypt
:li. Encrypt and sign
:li. Decrypt or verify
:eul.
.br
If the mouse pointer is located over one of the buttons for a certain time period without
a mouse button being pressed a bubble help text appears explaining the meaning of that button.
.br
The selection of "Launch PGPKeys" will start the since v1.42 integrated :link reftype=hd res=10.PGP key administration tool:elink. by Thomas Bohn.
The last 4 above-mentioned PGP actions are usually applied to existing files. However, :color fc=DarkPink bc=default.PGPTools for OS/2:color fc=default bc=default. offers the additional capability to apply these actions to the OS/2 clipboard as well, provided that the clipboard contains text data.
Otherwise an error message will appear. The data successfully processed by PGP will be copied to the clipboard again.
:p.
If the mouse pointer is located over the main window pressing the right mouse button (mouse button 2) will open a :link reftype=hd res=4.popup menu:elink..
Alternatively, it can be opened by pressing Shift+F10 if the main window has the input focus.
.br
When selecting one of the 4 PGP actions a file selection dialog is opened first, where you can select a file for being processed by PGP v5.0 for OS/2.
Alternatively, you're able to process clipboard (text!) data if available by pressing the push button "Clipboard".
After selecting the source medium the further way of processing depends on which PGP action has been currently selected.
If "Sign", "Encrypt and Sign" or "Decrypt/Verify" have been selected a dialog window appears next, where you must enter your PGP :link reftype=hd res=5.passphrase:elink. Otherwise a listbox window appears where you must :link reftype=hd res=6.select a key:elink. to encrypt the source medium to.
:p.
After processing any PGP action an information window appears containing a general message which tells if the current action failed or succeeded.
.br
Additionally, if the "Decrypt/Verify" action was selected, a
:link reftype=hd res=11.log window:elink.
appears after execution showing the exact PGP v5.0 for OS/2 output result of the decrypting or verifying process.
.br
Independent of the language of :color fc=DarkPink bc=default.PGPTools for OS/2:color fc=default bc=default. (which is available in English and in German as well) the window contents always appear in that language which PGP v5.0 for OS/2 is set to in its configuration file PGP.CFG (English by default).
:p.
Each currently running PGP action can be cancelled by pressing the
:color fc=Pink bc=default.ESC:color fc=default bc=default. key.
However, therefore the :color fc=DarkPink bc=default.PGPTools for OS/2:color fc=default bc=default. window must have the input focus!
:p.
.* Ende Benutzerkn�pfe
.* -----------------------------------------------------------------------------

:h2 res=3.The extended system menu
:i1.System menu
:i1.Always on top
.br
:artwork align=center name='F:\WC10SRC\PGPTOOLS\ENGLISH\HELP\esysmenu.bmp'.
.br
The main window's extended system menu contains a help menuitem, which opens the contents page of the online help, another item to get informations about the application and a menuitem to open the :link reftype=hd res=7.Preferences:elink. window as well.
.br
If the menuitem :hp1."Always on top":ehp1. is checked, the window will remain visible as the topmost window on the desktop.
This state can only be toggled here for the currently running session. If you want to save this state permanentely (as the initial state when launching :color fc=DarkPink bc=default.PGPTools for OS/2:color fc=default bc=default.) you must do that in the "Preferences" notebook on the "General" page.
.* Ende Systemmen�
.* -----------------------------------------------------------------------------

:h2 res=4.The popup menu
:i1. Popup menu
:i1. Title bar
:i2 refid=clipboard. Popup menu
:p.
If the mouse pointer is located over the :link reftype=hd res=1.main window:elink., pressing the right mouse button (mouse button 2) will open a popup menu. Alternatively, it can be opened by pressing :color fc=Pink bc=default.Shift+F10:color fc=default bc=default. if the main window has the input focus.
.br
:artwork align=center name='F:\WC10SRC\PGPTOOLS\ENGLISH\HELP\epopup.bmp'.
.br
Basically, this popup menu provides quick access to all clipboard actions, however, some PGP related switches can be activated or decactivated here as well (click :link reftype=hd res=5.here:elink. for more informations about).
:nt text='Note:'.
Even if the title bar is switched off by the corresponding popup menuitem, you can still use the accelerator keys known from the system menu, that is :color fc=Pink bc=default.Alt+F4:color fc=default bc=default. (Exit), :color fc=Pink bc=default.Alt+F5:color fc=default bc=default. (Restore), :color fc=Pink bc=default.Alt+F7:color fc=default bc=default. (Move) and :color fc=Pink bc=default.Alt+F9:color fc=default bc=default. (Minimize) as well.
:ent.

.br
.* Ende Popup-Men�
.* -----------------------------------------------------------------------------

:h1 res=7.Preferences
:i1 id=pref. Preferences
:i2 refid=pref.Files
:i2 refid=pref.Editor
:i2 refid=pref.Comment
:i2 refid=pref.Cache
:i2 refid=pref.PGP&period.CFG
:i2 refid=pref.Send key server
:i2 refid=switches. Always encrypt to self
:p.
The preferences notebook window is useful to keep the filenames of the public and secret(private) keyring and the random seed file as well currently used by PGP.
While launching :color fc=DarkPink bc=default.PGPTools for OS/2:color fc=default bc=default. the first time this window is opened automatically. :color fc=DarkPink bc=default.PGPTools for OS/2:color fc=default bc=default. scans the value of the environment variable PGPPATH (this must have already been set in the CONFIG.SYS file) und recommends the complete filenames (assembled by use of the PGPPATH value) by default.
:p.
.br
:hp7.The notebook page "General"&colon.
:ehp7.
:parml tsize=10 break=all compact.
:pt.:hp2.Comment&colon.:ehp2. :pd.Optional comment (max. 69 characters) which is added to the ASCII armor while signing and/or encrypting.
.br
:pt.:hp2.Send key server&colon.:ehp2. :pd.A server address can be entered here, where the :link reftype=hd res=10.PGP key administration tool:elink. is able to upload your public key to (predefined default address is&colon. "hkp&colon.&slash.&slash.wwwkeys&per.pgp&per.net").  
.br
:pt.:hp2.Editor&colon.:ehp2. :pd.This is to preset the command line for calling an editor which can be used to display decrypted/verified data in the
:link reftype=hd res=11.log window:elink.. The parameter %f is a placeholder for the data file to be displayed and must always be set. Default editor is the OS/2 system editor.
Using this placeholder makes the command line call more flexible to place other command line parameters at any location around the filename parameter, e.g. if some parameters need to be set in a certain order.
If the data file's name should contain space characters, the parameter %f must be delimited by double quote
characters at the beginning and the end of the filename ("%f")!  If the editor's path and/or filename should contain space characters, the filename must completely be delimited by double quote characters!
.br
:pt.:hp2.Keep passphrase in cache for&colon.:ehp2. :pd.Here you can enter the time period (hh&colon.mm&colon.ss) telling how long :color fc=DarkPink bc=default.PGPTools for OS/2:color fc=default bc=default. should keep a currently entered passphrase (your PGP password) in its memory.
This might be helpful, if you want to perform more than one consecutive PGP action without entering the passphrase again and again.

:color fc=Red bc=default.

:hp2.
:caution text='Attention!'.
:ehp2.
When setting the time period you should consider that keeping your PGP passphrase in memory is a severe security risk, e.g. if other people would have access to your system during this time!
:ecaution.

:color fc=default bc=default.
.br
After expiration of the time period the passphrase is deleted automatically, so it has to be entered again when the corresponding PGP action is selected the next time.
.br
:pt.:hp2.Always encrypt to self&colon.:ehp2.:pd.If on, the source data are additionally encrypted to your default key.
This is useful if you want to decrypt data again by yourself that you encrypted to another public key.
.br
:pt.:hp2.Window always on top&colon.:ehp2.:pd.If checked, :color fc=DarkPink bc=default.PGPTools for OS/2:color fc=default bc=default. will always float as the topmost window on the desktop.
.br
:pt.:hp2.Always display hint window&colon.:ehp2.:pd.If the complete PGP key administration package (PGPKeys) from Thomas Bohn or parts of it are missing, a message window with a respective message will appear during startup of :color fc=DarkPink bc=default.PGPTools for OS/2:color fc=default bc=default.. The apperance of this window can be permanently enabled or disabled here.
.br
:pt.:hp2.Small icons&colon.:ehp2.:pd.If enabled the main window of :color fc=DarkPink bc=default.PGPTools for OS/2:color fc=default bc=default. is displayed using small push buttons and icons.
:artwork align=center name='F:\WC10SRC\PGPTOOLS\ENGLISH\HELP\MAINSMT5.BMP'.
Please note, that changing this item does not take effect until :color fc=DarkPink bc=default.PGPTools for OS/2:color fc=default bc=default. has been terminated and restarted once.
:eparml.
:p.
.br
:hp7.The notebook page "Files"&colon.
:ehp7.
:parml tsize=10 break=all compact.

:pt.:hp2.Public keyring file&colon.:ehp2. :pd.Enter the complete filename including the path of the file containing the public keyring which PGP should use (default: PUBRING.PKR). Even if the filename contains space characters it must :hp5.not:ehp5. be delimited by double quote characters here!
.br
:pt.:hp2.Private keyring file&colon.:ehp2. :pd.Enter the complete filename including the path of the file containing the secret(private) keyring which PGP should use (default: SECRING.SKR). Even if the filename contains space characters it must :hp5.not:ehp5. be delimited by double quote characters here!
.br
:pt.:hp2.Random Seed file&colon.:ehp2. :pd.Enter the complete filename including the path of the random seed file which PGP should use (default: RANDSEED.BIN). Even if the filename contains space characters it must :hp5.not:ehp5. be delimited by double quote characters here!
:eparml.
:p.
.br
:hp7.Push buttons&colon.
:ehp7.
:parml tsize=10 break=all compact.
:pt.:hp2.Save:ehp2. :pd.This will close the preferences dialog and save the settings to the file PGPTOOLS.INI.
.br
:pt.:hp2.Cancel:ehp2. :pd.This will close the preferences dialog without saving the settings.
.br
:pt.:hp2.Help:ehp2. :pd.Displays the help window you're just reading.
:eparml.
.br
:color fc=Pink bc=default.
:nt text='Note:'.
Due to an obvious bug in PGP v5.0 for OS/2 the calling options for the public and secret keyring files seem to be ignored during a PGP call in some cases.
The only remedy is to replace the filenames for the public and secret keyring originally stored in PGP's configuration file PGP.CFG by those set up in the preferences window.
This is automatically done by :color fc=DarkPink bc=default.PGPTools for OS/2:color fc=Pink bc=default. after pressing the "Save" button.
However, a backup called PGP.BAK of the current file PGP.CFG is always made before
PGP.CFG is modified.
:p.
:color fc=Red bc=default.
In any case a backup copy of the complete PGP directory is strongly recommended
before using :color fc=DarkPink bc=default.PGPTools for OS/2:color fc=Red bc=default. the first time!
:ent.
:color fc=default bc=default.
.* Ende Einstellungen
.* -----------------------------------------------------------------------------
:h1 res=5 hide. Enter passphrase
:i1. Enter passphrase
:i1 id=switches. PGP switches
:i2 refid=switches. Text output
:i2 refid=switches. Detached signature
:i2 refid=switches. ASCII armor
:p.
The PGP passphrase is your password for using the secret key while signing and encrypting.
The desired key can be selected by the dropdown list (if more than one available).
:p.
By default the passphrase is always entered hidden, that is the entered characters are not displayed in readable form but replaced by a '*' each to protect them against peeking.
.br
However, for immediate control purposes the passphrase can be switched into a cleartext mode by disabling the "Hide typing" checkbox. Switching between cleartext and hidden mode can be done at any time.
:p.
Optionally you can enable/disable 3 checkboxes, which control the data processing by PGP v5.0 for OS/2. In enabled state the switches have the following meaning:
:p.
:parml tsize=10 break=all compact.
:pt.:hp2.Text output&colon.:ehp2.:pd.Turns on text mode.  This causes PGP to convert your input data to a platform-independent form.
It is primarily for use when moving files from one operating system to another.
.br
:pt.:hp2.Detached signature&colon.:ehp2.:pd.Creates a detached signature file (default extension ".sig") instead of combining the signature with the message in the same file.

.br
:nt text='Please note:'.
This checkbox is greyed out while using the clipboard, since the processed target data are always completely returned to the clipboard.
:ent.
.br
:pt.:hp2.ASCII armor&colon.:ehp2.:pd.Turns on "ASCII Armoring". This outputs a text-only version of your encrypted data. This makes the result safe for mailing, but about 30%
larger. Unlike previous versions of PGP, this also implicitly turns on clearsigning (wrapping the signature around your message, leaving your message in a readable form).
:eparml.
:p.
During the decrypting/verifying process these checkboxes are not available.
.* Ende Passphrase eingeben
.* -----------------------------------------------------------------------------
:h1 res=6 hide. Select key to encrypt to
:i1 id=key. Keys
:i2 refid=key. Selecting a key
:i2 refid=key. List box
:p.
You can select one or more PGP keys from the displayed listbox to encrypt the source data to. The list contains the key ID, the encryption algorithm the key was created with and the corresponding user ID. The abbreviation ":hp2.(priv):ehp2." indicates a key as a private/secret key.
:p.
Additionally to the key selection, you can enabled/disable the following option:
.br
:parml tsize=10 break=all compact.
:pt.:hp2.ASCII armor&colon.:ehp2.:pd.For more information about this switch click :link reftype=hd res=5.here:elink..
:nt text='Note:'.
This checkbox is not available if the PGP action "Encrypt and sign" has been selected.
In that case you'll find it as part of the ":link reftype=hd res=5.Enter passphrase:elink." dialog window.
:ent.
:eparml.

.* Ende Listbox
.* -----------------------------------------------------------------------------
:h1 res=8.Select source file
:p.
Select the source file you want to be processed by PGP. Dependent on the currently selected PGP action the source file has the following meaning&colon.
:p.
:parml tsize=15 break=fit compact.
:pt.:hp2.Sign:pd.
:pt.Encrypt:pd.
:pt.Encrypt &amp.
.br
Sign&colon.:ehp2.:pd.Select the source file that you want to sign or to encrypt or to encrypt &amp. sign. The target file then has one of the following filename extensions&colon.
.br
:sl.
:li.:hp2.&per.asc:ehp2. if an ASCII armored target file was created.
:li.:hp2.&per.pgp:ehp2. if a target file without ASCII armor was created.
:li.:hp2.&per.sig:ehp2. if a detached signature (without ASCII armor) for a source file was created.
:esl.
.br
:pt.:hp2.Decrypt or
.br
Verify&colon.:ehp2.:pd.
If you want to verify a detached signature (file extension :hp2.&per.asc:ehp2. or :hp2.&per.sig:ehp2.) please select the file containing the detached signature here.
.br
To decrypt a file please select the name of the encrypted source file (file extension :hp2.&per.asc:ehp2. or :hp2.&per.pgp:ehp2.).
:eparml.


.* Ende Quelldatei ausw�hlen
.* -----------------------------------------------------------------------------

:h1 res=9.Select target file
:p.
Select the target file you want to be processed by PGP. Dependent on the contents of the previously selected source file the selected target file has the following meaning&colon.
:p.
:parml tsize=10 break=fit compact.
:pt.:hp2.Source file contains a detached signature&colon.:ehp2.:pd.Please select the file to which the previously selected file with the detached signature (file extension :hp2.&per.asc:ehp2. bzw. :hp2.&per.sig:ehp2.) belongs to.
.br
:pt.:hp2.Source file contains PGP encrypted and/or PGP signed data&colon.:ehp2.:pd.
Please enter a name of the file which should later contain the decrypted data or raw  data without signature.
:eparml.

.* Ende Zieldatei ausw�hlen
.* -----------------------------------------------------------------------------

:h1 res=10.PGP key administration
:i1 id=pgpkeys. Key administration
:i1. PGPKeys
:i2 refid=pgpkeys. Related files
:i2 refid=pgpkeys. VROBJ.DLL
:p.
As of v1.42 of :color fc=DarkPink bc=default.PGPTools for OS/2:color fc=default bc=default. a key administration strongly yearned for by so many users has been integrated. The key administration tool is a standalone package called
:color fc=DarkBlue bc=default.
PGPKeys
:color fc=default bc=default.
created by Thomas Bohn. Currently, this package consists of at least 3 files:

:ul compact.
:li. PGPKEYS.EXE
:li. FILEREXX.DLL
:li. PGPKK.CMD
:eul.
.br
These 3 files must be located in the same directory where :color fc=DarkPink bc=default.PGPTools for OS/2:color fc=default bc=default. has been installed.
If one of these files is missing there the PGPKeys package is unable to run. In that case a respective :link reftype=hd res=7.message window:elink. appears at each start
of :color fc=DarkPink bc=default.PGPTools for OS/2:color fc=default bc=default., the "Launch PGPKeys" :link reftype=hd res=2.pushbutton:elink. is removed from the main window and in the preferences the :link reftype=hd res=7.Send key server:elink. entry is grayed out.
:p.
Additionally, the Watcom VX REXX runtime library VROBJ.DLL v2.1d is required. This file can be downloaded from the Internet or Fidonet etc.
and must be usually located in the directory C&colon.&bslash.OS2&bslash.DLL (assuming that C&colon. is your OS/2 boot partition).

.* Ende


:h1 res=11.The log window
:i1 id=logwin. Log window
:p.
After finishing a decrypt or verify action a log window appears showing the action's result.
If the target data of that action only consist of printable ASCII characters, you can launch an editor to load and show these data by pressing the push button "Edit decrypted/verified data".
If the target data consist of at least one non-printable character, the button is disabled.
:p.
You may want to select an editor in the
:link reftype=hd res=7.preferences:elink. dialog.
.* Ende

:euserdoc.
