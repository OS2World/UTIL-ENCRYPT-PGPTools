.* Dieses Dokument wurde mit Phelsuma/2 erstellt
:userdoc.
:title.PGPTools fr OS/2 Dokumentation
:h1 res=1000.Einleitung
:font facename='Tms Rmn' size=32x24.
:hp2.
.ce PGPTools fr OS/2 v1.50
:ehp2.
:font facename='Tms Rmn' size=20x10.
.ce Copyright ¸ 1999-2003 by Bernd Giesen. Alle Rechte vorbehalten.
.ce Ver”ffentlicht unter den Bestimmungen der GNU General Public License
:font facename=default.
:p.
.br
:color fc=DarkPink bc=default.PGPTools fr OS/2:color fc=default bc=default. ist eine 32-bit OS/2 PM-Applikation, welche die t„gliche
Bedienung der Kryptographie-Software :hp2.:artwork runin
name='World.BMP'.:link reftype=launch object='NETSCAPE.EXE'
data='http://www.pgpi.com'.PGP:elink.:ehp2. (Pretty Good Privacy)
:fn id=A. Sie k”nnen die URLs direkt aus diesem Dokument heraus im Internet aufrufen, wenn Sie den Netscape Navigator v2.02 fr OS/2 oder den Netscape Communicator v4.x fr OS/2 auf Ihrem System installiert haben und eine aktive Internetverbindung haben.
:efn.
:link refid=A reftype=fn.*:elink. vereinfachen soll.
:p.
:nt text='Wichtig!'.
:color fc=Red bc=default.
:hp2.Um :color fc=DarkPink bc=default.PGPTools fr OS/2:color fc=Red bc=default. benutzen zu k”nnen, muá :color fc=default bc=default.PGP v5.0 fr OS/2:color fc=Red bc=default. auf Ihrem Rechner installiert und einsatzbereit sein!:ehp2.
:color fc=default bc=default.
Diese Version ist z.B. :hp2.:artwork runin name='World.BMP'.:link reftype=launch object='NETSCAPE.EXE' data='http://www.openpgp.net'.hier:elink.:ehp2. erh„ltlich.
:ent.
:p.
:color fc=DarkPink bc=default.PGPTools fr OS/2:color fc=default bc=default. enth„lt selbst keinen PGP-Quellcode und arbeitet lediglich als grafische Bedienoberfl„che fr PGP v5.0 fr OS/2.
Somit unterliegt :color fc=DarkPink bc=default.PGPTools fr OS/2:color fc=default bc=default. allen Restriktionen, die durch die
PGP-Version selbst vorgegeben sind.
.br
Auf vielfachen Wunsch der Benutzer ist ab Version v1.42 erstmals eine PGP-Schlsselverwaltung integriert worden.
Hierbei handelt es sich um ein eigenst„ndiges Software-Paket namens :color fc=DarkPink bc=default.PGPKeys:color fc=default bc=default. von Thomas Bohn, welches direkt aus :color fc=DarkPink bc=default.PGPTools fr OS/2:color fc=default bc=default. heraus gestartet werden kann.
:p.
:color fc=DarkPink bc=default.PGPTools fr OS/2:color fc=default bc=default. wurde entwickelt und getestet unter OS/2 Warp 4 (inkl. Fixpack #14) und PGP v5.0 fr OS/2 (GA). Theoretisch sollte es auch unter OS/2 Warp 3 funktionieren.
.br
.* Ende
:h1 res=1010.Installation/Deinstallation
:i1. Deinstallation
:i1. Installation
:p.
Wenn Sie diese Zeilen lesen, dann haben Sie :color fc=DarkPink bc=default.PGPTools fr OS/2:color fc=default bc=default. bereits erfolgreich installiert. &colon.-)
.br
Starten Sie :color fc=DarkPink bc=default.PGPTools fr OS/2:color fc=default bc=default. einfach ber das zugeh”rige Symbol
:artwork name='LOCK.BMP' runin.
im Ordner "PGPTools fr OS/2". Eine kontextsensitive Online-Hilfe ist jederzeit durch Druck auf die Taste F1 verfgbar.
:p.
Falls Sie :color fc=DarkPink bc=default.PGPTools fr OS/2:color fc=default bc=default. wieder deinstallieren wollen, rufen Sie im Ordner "PGPTools fr OS/2" einfach das (De-)Installationsprogramm
:artwork name='INSTALL.BMP' runin.
 auf und
w„hlen dort im Pulldown-Men ":hp2.Aktion:ehp2." den Menpunkt ":hp2.L”schen:ehp2." aus. Dieser Vorgang l”scht alle installierten Dateien, Ordner und Objekte von :color fc=DarkPink bc=default.PGPTools fr OS/2:color fc=default bc=default..


:nt text='Hinweis:'.
Sowohl bei der Installation als auch bei einer Deinstallation werden keine Systemdateien oder Systemeinstellungen ver„ndert!
:ent.

.* Ende

:h1 res=1020.Bevor Sie PGPTools fr OS/2 erstmals benutzen
:i1. Dokumentation
:i1 id=1. Umgebungsvariable
:i2 refid=1. CMD.EXE
:i2 refid=1. COMSPEC
:i2 refid=1. CONFIG.SYS
:i2 refid=1. OS2_SHELL
:i2 refid=1. PATH
:i2 refid=1. PGPPATH
:p.
:hp5.Bitte beachten Sie die folgenden Hinweise, bevor Sie PGPTools fr OS/2 erstmals benutzen:ehp5.&colon.
:p.
Wie bereits in der
:link reftype=hd res=1000.Einleitung:elink. erw„hnt, mssen Sie, bevor Sie :color fc=DarkPink bc=default.PGPTools fr OS/2:color fc=default bc=default. benutzen k”nnen, die Kryptographie-Software :hp2.PGP v5.0 fr OS/2:ehp2. erfolgreich installiert haben.
Falls nicht bereits geschehen, mssen Sie noch ein gltiges Schlsselpaar (Ihren ”ffentlichen und Ihren geheimen Schlssel) erzeugen. Dies ist jetzt in komfortabler Weise durch den Start von :color fc=DarkPink bc=default.PGPKeys:color fc=default bc=default. aus :color fc=DarkPink bc=default.PGPTools fr OS/2:color fc=default bc=default. heraus m”glich.
:p.
Eine Beschreibung der Installation von PGP v5.0 fr OS/2 und des Schlsselmanagements von PGP wrde den Rahmen dieser Dokumentation sprengen. Hier sei auf die entsprechende PGP-Literatur verwiesen, die man bei folgenden Adressen
:link refid=A reftype=fn.*:elink. erh„lt&colon.

:ul.
:li.:hp2.:artwork runin
name='World.BMP'.:link reftype=launch object='NETSCAPE.EXE'
data='http://www.openpgp.net'.http&colon.&slash.&slash.www&per.openpgp&per.net:elink.:ehp2.
:li.:hp2.:artwork runin
name='World.BMP'.:link reftype=launch object='NETSCAPE.EXE'
data='http://www.pgpi.com'.http&colon.&slash.&slash.www&per.pgpi&per.com:elink.:ehp2.
:eul.
:p.
In jedem Fall ist es (sowohl fr PGP selbst als auch fr :color fc=DarkPink bc=default.PGPTools fr OS/2:color fc=default bc=default.) erforderlich, daá Sie bei der Installation von PGP v5.0 fr OS/2 die Umgebungsvariable :hp2.PGPPATH:ehp2., die den vollst„ndigen Pfad beinhaltet,
worin sich die ausfhrbare Datei PGP.EXE befindet, mit einem Editor in die Datei CONFIG.SYS eintragen.
:p.
Ab der Version v1.44 ermittelt :color fc=DarkPink bc=default.PGPTools fr OS/2:color fc=default bc=default. den
standardm„áig benutzten OS/2-Kommandoprozessor fr den Aufruf von PGP fr OS/2 durch Auswertung der Umgebungsvariablen :hp2.COMSPEC:ehp2..
Sollte diese Variable nicht gesetzt sein, wird versucht, die Umgebungsvariable :hp2.OS2_SHELL:ehp2. auszuwerten.
Schl„gt auch dieser Versuch fehl, wird als Standardkommandoprozessor :hp2.CMD.EXE:ehp2. angenommen.
.br
Bedingung fr die Benutzung eines alternativen OS/2-Kommandoprozessors (z.B. 4OS2) anstelle von CMD.EXE ist jedoch, daá dieser alternative Kommandoprozessor den Kommandozeilenparameter "/C" untersttzt und das dieser Parameter die gleiche Bedeutung
wie bei CMD.EXE besitzt. Weitere Informationen hierzu finden Sie in der
:link reftype=launch object='view.exe' data='cmdref.inf cmd'.OS/2-Online-Hilfe:elink. bzw. in der Dokumentation des alternativen Kommandozeilenprozessors.
:p.
Auáerdem muá auch die normalerweise bereits existierende Umgebungsvariable :hp2.PATH:ehp2. in der Datei CONFIG.SYS um den Pfad von PGP v5.0 fr OS/2 erweitert werden.

:nt text='Beispiele:'. (unter der Annahme, daá PGP v5.0 fr OS/2 zuvor in das Verzeichnis "C&colon.&bslash.PGP50" installiert wurde)
:xmp.
SET PGPPATH=C&colon.&bslash.PGP50
SET PATH=C&colon.&bslash.PGP50;&percent.PATH&percent.
:exmp.
:ent.

Danach muá das System neu gestartet werden, damit diese nderungen wirksam werden!
.br
.br

.* Ende

:h1 res=1030.Lizenz
:i1. Lizenz
:p.
Ab Version v1.50 wird :color fc=DarkPink bc=default.PGPTools fr OS/2:color fc=default bc=default. unter den Bestimmungen der :hp2.GNU General Public License:ehp2. ver”ffentlicht. Das heiát:
:p.
Dieses Programm ist freie Software. Sie k”nnen es unter den Bedingungen der GNU General Public License, wie von
der Free Software Foundation ver”ffentlicht, weitergeben und/oder modifizieren, entweder gem„á Version 2 der Lizenz oder (nach Ihrer Option) jeder sp„teren Version.
:p.
Die Ver”ffentlichung dieses Programms erfolgt in der Hoffnung, daá es Ihnen von Nutzen sein wird, aber OHNE IRGENDEINE GARANTIE, sogar ohne die implizite Garantie der MARKTREIFE
oder der VERWENDBARKEIT FšR EINEN BESTIMMTEN ZWECK. Details finden Sie in der GNU General Public License.
:p.
Sie sollten eine Kopie der GNU General Public License zusammen mit diesem Programm erhalten haben. Falls nicht, schreiben Sie an die Free Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307, USA.
:p.
:nt text='Bitte beachten:'.Fr die Benutzung der ab v1.42 integrierten Schlsselverwaltung :color fc=DarkPink bc=default.PGPKeys:color fc=default bc=default. von Thomas Bohn gelten eigene Lizenzbedingungen (siehe PGPKEYS.LIC)!
:ent.
.* Ende

:h1 res=1050.Kontakt
:i1. Autor
:nt text='Autor:'.
Bernd Giesen
.br
Nirmer Str. 81
.br
D-52080 Aachen
.br
GERMANY
:p.
:hp2.Email&colon.:ehp2.
:link reftype=launch object='NETSCAPE.EXE' data='mailto:Bernd.Giesen@t-online.de?subject=PGPTools fuer OS/2'.Bernd&per.Giesen@t-online&per.de:elink.
.br
:hp2.Homepage&colon.:ehp2.
:artwork runin name='World.BMP'.
:link reftype=launch object='NETSCAPE.EXE' data='http://home.t-online.de/home/Bernd.Giesen'.http&colon.&slash.&slash.home&per.t-online&per.de&slash.home&slash.Bernd&per.Giesen:elink.
:ent.

:p.
:nt text='Bitte beachten:'.
Bei Problemen und Fragen zu :color fc=DarkPink bc=default.PGPKeys:color fc=default bc=default. wenden Sie sich bitte ausschlieálich direkt an dessen Autor Thomas Bohn! Dies gew„hrleistet in Ihrem eigenen Interesse eine schnellere und unkompliziertere Abwicklung.
:p.
:hp2.Email&colon.:ehp2.
:link reftype=launch object='NETSCAPE.EXE' data='mailto:Thomas@Bohn-Stralsund.de?subject=PGPKeys fuer OS/2'.Thomas@Bohn-Stralsund&per.de:elink.
.br
:hp2.Homepage&colon.:ehp2.
:artwork runin name='World.BMP'.
:link reftype=launch object='NETSCAPE.EXE' data='http://Bohn-Stralsund.de'.http&colon.&slash.&slash.Bohn-Stralsund&per.de:elink.
:ent.

.* Ende

:h1 res=1060.Bekannte Fehler
:i1.Bekannte Fehler
:p.
Wenn Sie zum Verschlsseln einen ”ffentlichen Schlssel zum ersten Mal benutzen, dem Sie per PGP Schlsselmanagement noch kein Vertrauen ausgesprochen haben (s. PGP-Dokumenation), wird die Verschlsselung ber :color fc=DarkPink bc=default.PGPTools fr OS/2:color fc=default bc=default. mit einem Fehler abgebrochen.
:nt text='Abhilfe:'.
Weisen Sie dem betreffenden Schlssel mit dem entsprechenden Schlsselmanagement-Befehl einen Vertrauensstatus zu oder best„tigen Sie alternativ das fehlende Vertrauen, indem Sie :hp5.einmalig:ehp5. ein Dokument mit diesem Schlssel durch das zugeh”rige PGP-Kommando :hp5.von der Kommandozeile:ehp5. aus aufrufen. PGP merkt sich dann diese Best„tigung ber das fehlende Vertrauen, so daá danach eine Benutzung des Schlssels auch mit :color fc=DarkPink bc=default.PGPTools fr OS/2:color fc=default bc=default. m”glich ist.
:ent.


.* Ende

:h1 res=1070.nderungsindex
:p.
:parml tsize=10 compact.
.********************************** v1.50 ********************************
:pt.v1.50&colon.:pd.
:parml tsize=5 break=none compact.
:pt.NEU&colon.:pd.:color fc=DarkPink bc=default.PGPTools fr OS/2:color fc=default bc=default. unterliegt ab sofort den Bestimmungen der :hp2.GNU General Public License:ehp2.. N„here Informationen dazu findet man in den Dateien "COPYING", "GPL-GER.HTM" und "GPL.HTM". Verbindlich ist ausschlieálich die englischsprachige Originalfassung dieser Lizenz!
.br
:eparml.
.********************************** v1.49 ********************************
:pt.v1.49&colon.:pd.
:parml tsize=5 break=none compact.
:pt.FIX&colon.:pd.:color fc=DarkPink bc=default.PGPTools fr OS/2:color fc=default bc=default. akzeptiert jetzt
auch lange Datei- und Verzeichnisnamen, die Leerzeichen beinhalten.
Dies gilt gilt auch fr die Dateinamen der Schlsselringdateien und des Editors (wichtige Erl„uterungen hierzu findet man in der Online-Hilfe fr den "Einstellungen"-Dialog).
.br
:eparml.
.********************************** v1.48 ********************************
:pt.v1.48&colon.:pd.
:parml tsize=5 break=none compact.
:pt.FIX&colon.:pd.Beim Aufruf des "Einstellungen"-Dialogs aus dem Systemmen konnte es vorkommen, dass jedesmal die Meldung :hp1."Die Initialisierungsdatei muss aktualisiert werden. Bitte berprfen Sie die aktuellen Einstellungen und speichern Sie sie erneut ab!":ehp1. erschien, obwohl eine Aktualisierung nicht erforderlich war.
.br
:eparml.
.********************************** v1.47 ********************************
:pt.v1.47&colon.:pd.
:parml tsize=5 break=none compact.
:pt.NEU&colon.:pd.Optional kann die Toolbar von :color fc=DarkPink bc=default.PGPTools fr OS/2:color fc=default bc=default. jetzt auch mit kleinen Benutzerkn”pfen dargestellt werden.
.br
:pt.NEU&colon.:pd.Nach dem Entschlsseln/Prfen kann ein Texteditor zur direkten Anzeige der entschlsselten/geprften Daten aus dem Logfenster heraus aufgerufen werden.
Ein beliebiger Editor (oder jede alternative PM-Applikation) kann hierzu in den Einstellungen konfiguriert werden.
.br
.br
:pt.FIX&colon.:pd.In der deutschen Version von :color fc=DarkPink bc=default.PGPTools fr OS/2:color fc=default bc=default. erschienen falsche Bitmaps fr die 4 Benutzerkn”pfe in der Toolbar, wenn das PGPKeys-Paket nicht installiert war.
.br
:pt.FIX&colon.:pd.Die Bubblehelp-Texte wurden teilweise abgeschnitten, wenn das Hauptfenster zu nahe am Bildschirmrand positioniert war.
.br
:eparml.
.********************************** v1.46 ********************************
:pt.v1.46&colon.:pd.
:parml tsize=5 break=none compact.
:pt.ND&colon.:pd.Verbessertes (moderateres) Verhalten der Anwendung, wenn das Hauptfenster immer im Vordergrund erscheinen soll.
.br
:pt.ND&colon.:pd.Beim Verschlsseln/Prfen werden die Dateinamen im Eingabefeld des 2. Dateiauswahldialogs nicht mehr fest in Groábuchstaben dargestellt.
.br
.br
:pt.FIX&colon.:pd.Die Bubblehelp-Fenster fr die Benutzerkn”pfe erscheinen jetzt wieder korrekt und immer im Vordergrund.
.br
:eparml.
.********************************** v1.45 ********************************
:pt.v1.45&colon.:pd.
:parml tsize=5 break=none compact.
:pt.ND&colon.:pd.Das separate Nachrichtenfenster nach einer erfolgreichen Entschlsselung/Prfung wird nicht mehr angezeigt, da bereits ein anderes Fenster mit dem detaillierten Ergebnis der erfolgreichen PGP-Aktion erscheint.
.br
.br
:pt.FIX&colon.:pd.Die Benutzung von UNC-Dateinamen im Dateiauswahldialog fhrte zu einem SYS3175, wenn der
Dateiauswahldialog ein weiteres Mal derart benutzt wurde.
.br
:eparml.
.********************************** v1.44 ********************************
:pt.v1.44&colon.:pd.
:parml tsize=5 break=none compact.
:pt.ND&colon.:pd.Der Kommandoprozessor zum Aufruf von PGP fr OS/2 ist nicht mehr fest auf "CMD.EXE" eingestellt, sondern wird jetzt ber die Auswertung der Umgebungsvariablen COMSPEC bzw. OS2_SHELL ermittelt.
Dadurch wird nun auch die Benutzung alternativer Kommandoprozessoren wie z.B. 4OS2 erm”glicht.
Sollte die erw„hnte Auswertung fehlschlagen, wird weiterhin "CMD.EXE" verwendet.
:p.
:hp2.Siehe auch&colon.:ehp2.
:link reftype=hd res=1020.Bevor Sie PGPTools fr OS/2 erstmals benutzen:elink.
.br
:eparml.
.********************************** v1.43 ********************************
:pt.v1.43&colon.:pd.
:parml tsize=5 break=none compact.
:pt.NEU&colon.:pd.Die Titelzeile des Hauptfensters kann jetzt ber das Popup-Men wahlweise aus- oder eingeschaltet werden. Der Zustand der Titelzeile wird in PGPTOOLS.INI automatisch gesichert.
Die aus dem System-Men bekannten :color fc=Pink bc=default.Alt:color fc=default bc=default.-Tastenkombinationen k”nnen auch bei ausgeschalteter Titelzeile weiterhin benutzt werden.
Das Popup-Men kann ab jetzt auch durch die Tastenkombination :color fc=Pink bc=default.Umsch+F10:color fc=default bc=default. ge”ffnet werden, wenn das Hauptfenster den Eingabefokus besitzt.
.br
:pt.NEU&colon.:pd.Bei der Installation wird ein Programmobjekt fr :color fc=DarkPink bc=default.PGPKeys fr OS/2:color fc=default bc=default. im Programmordner angelegt, so daá es jetzt auch von dort aus direkt gestartet werden kann.
.br
.br
:pt.ND&colon.:pd.W„hrend eine PGP-Aktion gerade ausgefhrt wird, kann keine weitere PGP-Aktion mehr ausgew„hlt werden. Ein Druck auf einen entsprechenden Pushbutton im Hauptfenster oder die Auswahl eines Eintrags im Popup-Men werden in diesem Fall ignoriert.
.br
.br
:pt.FIX&colon.:pd.Wenn :color fc=DarkPink bc=default.PGPTools fr OS/2:color fc=default bc=default. gestartet war, fehlte der zugeh”rige Eintrag in der Fensterliste.
.br
:pt.FIX&colon.:pd.Die Zust„nde der einzelnen Pushbuttons im Haupfenster wurden nicht korrekt zurckgesetzt, wenn bei gedrckter, linker Maustaste ber dem Button der Mauszeiger aus dem Bereich des Buttons herausbewegt wurde
(eine derart gestartete Anwahl einer PGP-Aktion konnte dadurch nicht wieder - wie eigentlich blich - abgebrochen werden).
.br
:pt.FIX&colon.:pd.Tastatureingaben (z.B. die Cursortasten) im Hauptfenster waren blockiert.
.br
:pt.FIX&colon.:pd.Der Mauszeiger erschien nicht korrekt als Sanduhr innerhalb des Hauptfensterbereiches w„hrend eine PGP-Aktion ausgefhrt wurde.
.br
:pt.FIX&colon.:pd.Speicher wurde nach Benutzung nicht korrekt freigegeben.
.br
:eparml.
.br
.********************************** v1.42 ********************************
:pt.v1.42&colon.:pd.
:parml tsize=5 break=none compact.
:pt.NEU&colon.:pd.Integration einer von vielen Benutzern lang ersehnten PGP-Schlsselverwaltung (:color fc=DarkPink bc=default.PGPKeys:color fc=default bc=default. von Thomas Bohn). Der Aufruf erfolgt ber den neu hinzugefgten Benutzerknopf "PGPKeys starten" oder ber das Popup-Men.
.br
:pt.NEU&colon.:pd.Das Einstellungsnotizbuch (Seite "Allgemein") wurde um die Eintr„ge "Sende-Keyserver" und "Hinweisfenster immer anzeigen" erweitert.  Ist der zuletzt genannte Schalter aktiviert, wird bei fehlendem oder unvollst„ndigem :color fc=DarkPink bc=default.PGPKeys:color fc=default bc=default.-Paket (n„here Details hierzu finden sie in der Online-Hilfe von :color fc=DarkPink bc=default.PGPTools fr OS/2:color fc=default bc=default.)
beim Start von :color fc=DarkPink bc=default.PGPTools fr OS/2:color fc=default bc=default. immer ein entsprechendes Hinweisfenster angezeigt. Unter "Sende-Keyserver" kann eine Serveradresse (URL) angegeben werden, wohin die Schlsselverwaltung :color fc=DarkPink bc=default.PGPKeys:color fc=default bc=default. den ”ffentlichen Schlssel hochladen kann (Standardadresse&colon. hkp&colon.&slash.&slash.wwwkeys&per.pgp&per.net).
.br
:pt.NEU&colon.:pd.:color fc=DarkPink bc=default.PGPTools fr OS/2:color fc=default bc=default. merkt sich jetzt seine letzte Fensterposition auf der Arbeitsoberfl„che.
.br
.br
:pt.FIX&colon.:pd.Falls die Umgebungsvariable PGPPATH nicht nur eine, sondern mehrere (jeweils durch ein Semikolon getrennte) Pfadangaben enth„lt, wird nur der :hp5.erste:ehp5. angegebene Pfad fr die Arbeit mit :color fc=DarkPink bc=default.PGPTools fr OS/2:color fc=default bc=default. bercksichtigt.
:eparml.
.br
.********************************** v1.30 ********************************
:pt.v1.30&colon.:pd.
:parml tsize=5 break=none compact.
:pt.NEU&colon.:pd.Das Systemmen und das Einstellungsnotizbuch (Seite "Allgemein") wurden um den Eintrag "(Fenster) Immer im Vordergrund" erweitert.
Im Systemmen kann diese Einstellung fr die aktuelle Sitzung umgeschaltet werden, w„hrend im Einstellungsnotizbuch der Zustand auch dauerhaft als Voreinstellung gesichert werden kann.
.br
Ist dieser Schalter aktiviert, ist :color fc=DarkPink bc=default.PGPTools fr OS/2:color fc=default bc=default. immer als oberstes Fenster auf der Arbeitsoberfl„che sichtbar auáer im minimierten Zustand.
:pt.NEU&colon.:pd.Im Listenfenster zur Auswahl des Schlssels wird jetzt auch der Algorithmus, mit dem der Schlssel erzeugt wurde, angezeigt.
.br
.br
:pt.ND&colon.:pd.Aufgrund der verst„rkten Nachfrage werden im Listenfenster zur Auswahl der Schlssel jetzt auch private/geheime Schlssel zum Verschlsseln angeboten.
:pt.ND&colon.:pd.Die Anordnung der Listenelementen-Inhalte wurde ge„ndert. Zur bersichtlicheren Darstellung wurde auch eine andere Schriftart (System VIO 10) gew„hlt.
.br
.br
:pt.FIX&colon.:pd.In minimiertem Zustand konnte das Symbol von :color fc=DarkPink bc=default.PGPTools fr OS/2:color fc=default bc=default. nicht mehr per Maus bewegt werden.
:pt.FIX&colon.:pd.Markierte Einstellungen im Popup-Men wurde nicht in allen F„llen bei Ausfhrung einer entsprechenden PGP-Aktion bercksichtigt.
:eparml.
.br
.********************************** v1.21 ********************************
:pt.v1.21&colon.:pd.
:parml tsize=5 break=none compact.
:pt.FIX&colon.:pd.Der gesicherte Zustand "Immer mit dem eigenen Schlssel verschlsseln" wurde nach dem Start nicht korrekt eingelesen und ausgewertet,
sondern erst, wenn diese Einstellung w„hrend eines Programmlaufs im Einstellungen-Notizbuch vor dem Verschlsseln einer Nachricht explizit gespeichert wurde.
:eparml.
.br
.********************************** v1.20 ********************************
:pt.v1.20&colon.:pd.
:parml tsize=5 break=none compact.
:pt.NEU&colon.:pd.Eine laufende PGP-Aktion kann jederzeit durch Druck auf die Taste
:color fc=Pink bc=default.ESC:color fc=default bc=default. abgebrochen werden (wobei das :color fc=DarkPink bc=default.PGPTools fr OS/2:color fc=default bc=default.-Fenster den Eingabefokus besitzen muá!).
:pt.NEU&colon.:pd.Mauscursor wird w„hrend einer laufenden PGP-Aktion im :color fc=DarkPink bc=default.PGPTools fr OS/2:color fc=default bc=default.-Fenster als Sanduhr dargestellt.
:pt.NEU&colon.:pd.Fr die Dateiauswahlfenster ist jetzt eine kontextsensitive Online-Hilfe verfgbar.
.br
.br
:pt.ND&colon.:pd.Das Fenster fr die Einstellungen wurde anstelle eines Standard-Dialogfensters jetzt als Notizbuch angelegt.
:pt.ND&colon.:pd.Das Timeout fr den automatischen Abbruch einer laufenden PGP-Aktion wurde auf 60s erh”ht. Damit sollten jetzt auch sehr groáe Dateien problemlos bearbeitet werden k”nnen.
:pt.ND&colon.:pd.Bei der Anwahl des Passphrasen-Eingabefeldes wird eine evtl. vorhandene Passphrase jetzt sofort selektiert.
.br
.br
:pt.FIX&colon. :pd.Die Eingabezeile fr die Passphrase wird jetzt auch bei unterschiedlichen Bildschirmaufl”sungen immer korrekt im Dialogfenster positioniert.
:eparml.
.br
.********************************** v1.20 ********************************
:pt.v1.01&colon.:pd.Erste ”ffentliche Version
:eparml.

.* Ende

:h1 res=1080.Warenzeichen
:p.
:ul.
:li. OS/2 und Warp sind eingetragene Warenzeichen der IBM International Business Machines, Inc.
:li.Alle brigen Warenzeichen sind Eigentum der jeweiligen Besitzer.
:eul.
.* Ende

:h1 res=1090.Danksagung
:p.
Danke an IBM fr OS/2 und an William H. Geiger III fr die OS/2-Portierung von Pretty Good Privacy v5.0.
:p.
Mein ganz besonderer Dank gilt Thomas Bohn fr die von ihm mit groáem Engagement entwickelte und zur Verfgung gestellte grafische PGP-Schlsselverwaltung :color fc=DarkPink bc=default.PGPKeys:color fc=default bc=default..
.* Ende

:euserdoc.
