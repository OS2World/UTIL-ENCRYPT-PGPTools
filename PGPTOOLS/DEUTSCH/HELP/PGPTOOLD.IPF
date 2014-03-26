.* Dieses Dokument wurde mit Phelsuma/2 erstellt
:userdoc.
:title.PGPTools fr OS/2 Hilfe
:h1 res=1.Das Hauptfenster
:i1. Hauptfenster
.br
šber das Hauptfenster von :color fc=DarkPink bc=default.PGPTools fr OS/2:color fc=default bc=default. kann man im wesentlichen auf folgende Elemente zugreifen:
.br
:ul compact.
:li. 5 :link reftype=hd res=2.Benutzerkn”pfe:elink.
:li. ein :link reftype=hd res=3.erweitertes Systemmen:elink.
:li. ein :link reftype=hd res=4.Popup-Men:elink.
:eul.
.br
.* Ende Das Hauptfenster
.* -----------------------------------------------------------------------------
:h2 res=2.Die Benutzerkn”pfe
:i1 id=clipboard. Zwischenablage
:i1 id=buttons. Benutzerkn”pfe
:i2 refid=buttons. PGPKeys starten
:i2 refid=buttons. Unterschreiben
:i2 refid=buttons. Verschlsseln
:i2 refid=buttons. Verschlsseln und Unterschreiben
:i2 refid=buttons. Entschlsseln oder Prfen
:i1 id=Info. Protokollierung
:i2 refid=Info. Info-Fenster
:i2 refid=Info. Log-Fenster
:i1 id=actions. PGP-Aktionen
:i2 refid=actions. Abbrechen
.br
:artwork align=center name='F:\WC10SRC\PGPTOOLS\DEUTSCH\HELP\dmainwin.bmp'.
.br
Die 5 Benutzerkn”pfe zur Steuerung von PGP(Pretty Good Privacy) v5.0 fr OS/2 haben (von links nach rechts angeordnet) folgende Bedeutung:
:ul compact.
:li. PGPKeys starten
:li. Unterschreiben
:li. Verschlsseln
:li. Verschlsseln und Unterschreiben
:li. Entschlsseln oder Prfen
:eul.
:p.
Befindet sich der Mauszeiger eine bestimmte Zeit ber einem der Kn”pfe, ohne daá eine Maustaste gedrckt wurde, erscheint ein Hilfetext, der die Bedeutung des Knopfes erkl„rt.
Die 4 oben zuletzt genannten PGP-Aktionen werden in der Regel auf vorhandene Dateien angewandt. :color fc=DarkPink bc=default.PGPTools fr OS/2:color fc=default bc=default. bietet zus„tzlich die M”glichkeit, diese Aktionen auch auf die OS/2-Zwischenablage anzuwenden.
Voraussetzung dafr ist jedoch, daá sich in der Zwischenablage Textdaten befinden, andernfalls erfolgt eine Fehlermeldung. Die mit PGP behandelten Textdaten werden wieder in der Zwischenablage abgelegt.
.br
.br
Befindet sich der Mauszeiger ber dem Hauptfenster, ”ffnet ein Druck auf die rechte Maustaste (Maustaste 2) ein :link reftype=hd res=4.Popup-Men:elink..
Alternativ kann es auch ber die Tastenkombination Umsch+F10 ge”ffnet werden, wenn das Hauptfenster den Eingabefokus besitzt.
.br
Die Auswahl von "PGPKeys starten" startet die ab v1.42 integrierte
:link reftype=hd res=10.PGP-Schlsselverwaltung:elink. von Thomas Bohn.
Bei der Auswahl einer der brigen 4 PGP-Aktionen ”ffnet sich als zun„chst ein Dateiauswahldialog, wo eine mit PGP v5.0 fr OS/2 zu bearbeitende Datei selektiert werden kann.
Alternativ hat man hier die M”glichkeit, durch Druck auf den Knopf "Zwischenablage", statt einer Datei evtl. vorhandene Daten aus der Zwischenablage zu bearbeiten.
Nach erfolgter Auswahl des Quellmediums h„ngt die weitere Vorgehensweise davon ab, welche PGP Aktion ausgefhrt werden soll.
Bei Auswahl von "Unterzeichnen", "Verschlsseln und Unterzeichnen" und "Entschlsseln/Prfen" erscheint als n„chstes ein Dialogfenster, in dem die
:link reftype=hd res=5.Passphrase eingegeben:elink.
werden muá. Hat man "Verschlsseln" ausgew„hlt, erscheint eine Listbox zur :link reftype=hd res=6.Auswahl des/der Schlssel(s):elink., mit dem/denen das Quellmedium verschlsselt werden soll.
:p.
Nach allen Aktionen erscheint immer ein Info-Fenster mit einer generellen Meldung ber Erfolg oder Miáerfolg der Aktion.
.br
Hat man "Entschlsseln/Prfen" ausgew„hlt, erscheint zus„tzlich nach der Ausfhrung dieser Aktion ein
:link reftype=hd res=11.Logfenster:elink., wo das genaue Ergebnis des Entschlsselungs- bzw. Prfvorganges noch einmal protokolliert wird.
Hierbei handelt es sich um den Original-Text, den PGP v5.0 fr OS/2 ausgibt.
.br
Unabh„ngig von der Sprache, in der :color fc=DarkPink bc=default.PGPTools fr OS/2:color fc=default bc=default. arbeitet, erscheint der Inhalt des Log-Fensters immer in der Sprache, die fr PGP v5.0 fr OS/2 in dessen Konfigurationsdatei PGP.CFG eingestellt wurde (standardm„áig Englisch).
:p.
Jede gestartete PGP-Aktion kann durch Druck auf die Taste
:color fc=Pink bc=default.ESC:color fc=default bc=default. abgebrochen werden.
Dazu muá das :color fc=DarkPink bc=default.PGPTools fr OS/2:color fc=default bc=default.-Fenster den Eingabefokus besitzen!
:p.
.* Ende Benutzerkn”pfe
.* -----------------------------------------------------------------------------
:h2 res=3.Das erweiterte Systemmen
:i1.Systemmen
:i1.Immer im Vordergrund
.br
:artwork align=center name='F:\WC10SRC\PGPTOOLS\DEUTSCH\HELP\dsysmenu.bmp'.
.br
Das erweiterte Systemmen des Hauptfensters enth„lt neben einem Hilfe-Meneintrag, der das Inhaltverzeichnis der Online-Hilfe aufruft, jeweils einen weiteren Eintrag, um Informationen ber das Programm zu erhalten und um das Notizbuch :link reftype=hd res=7.Einstellungen:elink. zu ”ffnen.
.br
Ist der Menpunkt :hp1."Immer im Vordergrund":ehp1. markiert, bleibt das Fenster immer als oberstes auf der Arbeitsoberfl„che sichtbar. Dieser Zustand kann hier nur fr die aktuelle Sitzung umgeschaltet werden.
Dauerhaft gespeichert werden kann der gewnschte Grundzustand (der dann auch beim Starten von :color fc=DarkPink bc=default.PGPTools fr OS/2:color fc=default bc=default. immer voreingestellt ist) im Notizbuch "Einstellungen", Seite "Allgemein".
.* Ende Systemmen
.* -----------------------------------------------------------------------------
:h2 res=4.Das Popup-Men
:i1. Popup-Men
:i1. Titelzeile
:i2 refid=clipboard. Popup-Men
:p.
Befindet sich der Mauszeiger ber dem :link reftype=hd res=1.Hauptfenster:elink., ”ffnet ein Druck auf die rechte Maustaste (Maustaste 2) ein Popup-Men. Alternativ kann es auch ber die Tastenkombination :color fc=Pink bc=default.Umsch+F10:color fc=default bc=default. ge”ffnet werden, wenn das Hauptfenster den Eingabefokus besitzt.
.br
:artwork align=center name='F:\WC10SRC\PGPTOOLS\DEUTSCH\HELP\dpopup.bmp'.
.br
Dieses Popup-Men dient haupts„chlich dem schnellen Zugriff auf Aktionen mit der Zwischenablage, allerdings k”nnen hier auáerdem noch einige PGP-spezifische Schalter aktiviert und deaktiviert werden (Erl„uterungen dazu finden Sie
:link reftype=hd res=5.hier:elink.).
:nt text='Hinweis:'.
Auch wenn die Titelzeile ber den entsprechenden Eintrag im Popup-Men ausgeschaltet ist, k”nnen die bekannten Alt-Tastenkombinationen aus dem Systemmen weiterhin verwendet werden.
Im einzelnen sind das :color fc=Pink bc=default.Alt+F4:color fc=default bc=default. (Beenden), :color fc=Pink bc=default.Alt+F5:color fc=default bc=default. (Wiederherstellen), :color fc=Pink bc=default.Alt+F7:color fc=default bc=default. (Verschieben) und :color fc=Pink bc=default.Alt+F9:color fc=default bc=default. (Symbolgr”áe).
:ent.
.br
.* Ende Popup-Men
.* -----------------------------------------------------------------------------
:h1 res=7.Einstellungen
:i1 id=pref. Einstellungen
:i2 refid=pref.Dateien
:i2 refid=pref.Editor
:i2 refid=pref.Kommentar
:i2 refid=pref.Cache
:i2 refid=pref.PGP&period.CFG
:i2 refid=pref.Sende-Keyserver
:i2 refid=switches.Immer mit eigenem Schlssel verschlsseln
:p.
Das Notizbuch "Einstellungen" dient u.a. zur Angabe der Dateinamen des von PGP zu benutzenden ”ffentlichen Schlsselrings, des geheimen (privaten) Schlsselrings, und der Zufallszahlendatei.
Beim erstmaligen Start von :color fc=DarkPink bc=default.PGPTools fr OS/2:color fc=default bc=default. erscheint dieses Notizbuch-Fenster automatisch. :color fc=DarkPink bc=default.PGPTools fr OS/2:color fc=default bc=default. sucht dabei nach dem Wert
der Umgebungsvariablen PGPPATH (diese muá bereits in der Datei CONFIG.SYS existieren!) und schl„gt daraus resultierend die kompletten Dateinamen als Standard vor.
:p.
.br
:hp7.Die Notizbuchseite "Allgemein"&colon.:ehp7.
.br
:parml tsize=10 break=all compact.
:pt.:hp2.Kommentar&colon.:ehp2. :pd.Optionaler Kommentar (max. 69 Zeichen), der beim Unterschreiben und/oder Verschlsseln mit ASCII-Schutzhlle in die Schutzhlle integriert wird.
.br
:pt.:hp2.Sende-Keyserver&colon.:ehp2. :pd.Hier kann eine Serveradresse eingetragen werden, an den die
:link reftype=hd res=10.PGP-Schlsselverwaltung:elink. den ”ffentlichen Schlssel hochladen kann (Voreingestellte Standardadresse&colon. "hkp&colon.&slash.&slash.wwwkeys&per.pgp&per.net").
.br
:pt.:hp2.Editor&colon.:ehp2. :pd.Hier kann der Kommandozeilenaufruf fr einen Editor voreingestellt werden, der im
:link reftype=hd res=11.Logfenster:elink.
zur Anzeige entschlsselter bzw. geprfter Daten benutzt werden kann. Voreingestellt ist der OS/2-Systemeditor.
Der Parameter %f ist ein Platzhalter fr die zu bearbeitende Datendatei und muá in jedem Fall immer mit angegeben werden.
Durch die Benutzung dieses Platzhalters kann die Angabe des Dateinamens an beliebiger Stelle beim Editoraufruf erfolgen, z. B. wenn bestimmte andere Editorparameter eine spezielle Reihenfolge verlangen.
Wenn der Name der Datendatei Leerzeichen enthalten soll, muá der Parameter %f in doppelte Anfhrungszeichen eingeschlossen werden ("%f")!
Wenn der Dateiname bzw. der Pfadname des gewnschten Editors Leerzeichen enthalten soll, muá dieser Dateiname komplett in doppelte Anfhrungszeichen eingeschlossen werden!
.br
:pt.:hp2.Passphrase im Cache behalten fr&colon.:ehp2. :pd.Hier k”nnen Sie eine Zeitdauer (hh&colon.mm&colon.ss) angeben, wie lange :color fc=DarkPink bc=default.PGPTools fr OS/2:color fc=default bc=default. eine eingegebene Passphrase (Ihr PGP-Passwort) in seinem Speicher behalten soll.
Dies ist hilfreich, wenn Sie z.B. mehrere PGP-Aktionen ausfhren wollen, ohne immer wieder die Passphrase erneut eingeben zu mssen.
:color fc=Red bc=default.
:hp2.
:caution text='Achtung!'.
:ehp2.
Bedenken Sie beim Festlegen der Zeitdauer, daá eine gespeicherte Passphrase immer ein Sicherheitsrisiko darstellt, falls z.B. andere Personen w„hrend dieser Zeit Zugang zu Ihrem Rechner haben sollten!
:ecaution.
:color fc=default bc=default.
.br
Nach Ablauf der angegebenen Zeitspanne wird die Passphrase wieder automatisch gel”scht, so daá sie bei entsprechender PGP-Aktion erneut eingegeben werden muá.
.br
:pt.:hp2.Immer mit eigenem Schlssel verschlsseln&colon.:ehp2.:pd.Ist dieser Schalter eingeschaltet, wird das Quellmedium standardm„áig zus„tzlich immer noch mit dem eigenen Schlssel verschlsselt.
Dies hat den Vorteil, daá man ein mit einem (fremden) Schlssel verschlsseltes Quellmedium auch selbst wieder entschlsseln kann.
.br
:pt.:hp2.Fenster immer im Vordergrund&colon.:ehp2.:pd.Ist dieser Schalter aktiviert,
bleibt :color fc=DarkPink bc=default.PGPTools fr OS/2:color fc=default bc=default. immer als oberstes Fenster auf der Arbeitsoberfl„che sichtbar.
.br
:pt.:hp2.Hinweisfenster immer anzeigen&colon.:ehp2.:pd.Fehlt die komplette PGP-Schlsselverwaltung (PGPKeys) von Thomas Bohn oder einzelne Teile davon, erscheint beim Start von :color fc=DarkPink bc=default.PGPTools fr OS/2:color fc=default bc=default. ein Hinweisfenster mit einer entsprechenden Mitteilung. Das Erscheinen dieses Hinweisfensters kann hier dauerhaft aus- oder eingeschaltet werden.
.br
:pt.:hp2.Kleine Symbole&colon.:ehp2.:pd.Wenn aktiviert, wird das Hauptfenster von :color fc=DarkPink bc=default.PGPTools fr OS/2:color fc=default bc=default. mit kleinen Benutzerkn”pfen und Symbolen dargestellt.
:artwork align=center name='F:\WC10SRC\PGPTOOLS\DEUTSCH\HELP\MAINSMT5.BMP'.
Dabei gilt es zu beachten, dass eine nderung dieser Einstellung erst wirksam wird, nachdem :color fc=DarkPink bc=default.PGPTools fr OS/2:color fc=default bc=default. beendet und erneut gestartet wurde.
:eparml.
:p.
.br
:hp7.Die Notizbuchseite "Dateien"&colon.:ehp7.
.br
:parml tsize=10 break=all compact.
:pt.:hp2.Datei mit dem ”ffentlichen Schlsselring&colon.:ehp2. :pd.Geben Sie hier den vollst„ngigen Namen inkl. Pfad der Datei an, die den zu benutzenden ”ffentlichen Schlsselring enth„lt (Standardname: PUBRING.PKR).
Auch wenn der vollst„ndige Dateiname Leerzeichen enth„lt, darf er hier :hp5.nicht:ehp5. in doppelte Anfhrungszeichen eingeschlossen werden!
.br
:pt.:hp2.Datei mit dem privaten Schlsselring&colon.:ehp2. :pd.Geben Sie hier den vollst„ngigen Namen inkl. Pfad der Datei an, die den zu benutzenden geheimen Schlsselring enth„lt (Standardname: SECRING.PKR).
Auch wenn der vollst„ndige Dateiname Leerzeichen enth„lt, darf er hier :hp5.nicht:ehp5. in doppelte Anfhrungszeichen eingeschlossen werden!
.br
:pt.:hp2.Zufallszahlendatei&colon.:ehp2. :pd.Geben Sie hier den vollst„ngigen Namen inkl. Pfad der von PGP benutzte Zufallszahlendatei (Standardname: RANDSEED.BIN).
Auch wenn der vollst„ndige Dateiname Leerzeichen enth„lt, darf er hier :hp5.nicht:ehp5. in doppelte Anfhrungszeichen eingeschlossen werden!
:eparml.
:p.
.br
:hp7.Benutzerkn”pfe&colon.:ehp7.
.br
:parml tsize=10 break=all compact.
:pt.:hp2.Sichern:ehp2. :pd.Die eingebenen Daten werden in der Datei PGPTOOLS.INI gesichert.
.br
:pt.:hp2.Abbruch:ehp2. :pd.Das Dialogfenster wird geschlossen, ohne die Einstellungen zu sichern.
.br
:pt.:hp2.Hilfe:ehp2. :pd.Das Hilfefenster, das sie gerade lesen, wird aufgerufen.
.br
:eparml.
:color fc=Pink bc=default.
:nt text='Hinweis:'.
Bedingt durch einen offensichtlichen Bug in PGP v5.0 fr OS/2 werden in einigen F„llen die Aufrufoptionen fr die ”ffentlichen und privaten Schlsselringdateien bei einem PGP-Aufruf ignoriert.
Als Abhilfe mssen die Dateinamen fr den eingestellten ”ffentlichen und privaten Schlsselring direkt in die Datei PGP.CFG eingetragen werden. Dies wird beim Verlassen des Einstellungenfensters durch Drcken des "Sichern"-Knopfes automatisch durchgefhrt.
Vorher wird jedoch jedesmal der aktuelle Zustand dieser Datei in einer Backup-Kopie namens PGP.BAK gesichert.
:p.
.br
:color fc=Red bc=default.
In jedem Fall empfiehlt sich eine vorherige Kopie aller Dateien Ihres Verzeichnisses, in dem PGP v5.0 fr OS/2 installiert ist, bevor Sie :color fc=DarkPink bc=default.PGPTools fr OS/2:color fc=Red bc=default. erstmals benutzen!
:ent.
:color fc=default bc=default.
.* Ende Einstellungen
.* -----------------------------------------------------------------------------
:h1 res=5 hide. Passphrase eingeben
:i1. Passphrase eingeben
:i1 id=switches. PGP-Schalter
:i2 refid=switches. Textausgabe
:i2 refid=switches. Signatur in separate Datei
:i2 refid=switches. ASCII-Schutzhlle
:p.
Die PGP-Passphrase ist das Passwort fr die Benutzung des geheimen PGP-Schlssels beim Unterschreiben und Entschlsseln.
Der gewnschte Schlssel kann durch die Auswahl in der Dropdown-Liste ausgew„hlt (sofern mehrere vorhanden sind).
:p.
Standardm„áig wird die Eingabe der Passphrase immer verdeckt erfolgen, d.h., die eingegebenen Zeichen werden nicht in Klartext, sondern jeweils durch ein '*'-Zeichen dargestellt, um sie gegen Aussp„hen zu schtzen.
.br
Zwecks direkter Kontrolle der eingegebenen Passphrase kann man allerdings in einen Klartextmodus umschalten, indem man das K„stchen "Eingabe unsichtbar" deaktiviert.
Die Umschaltung zwischen verdecktem und Klartextmodus und zurck kann auch jederzeit w„hrend der Eingabe der Passphrase erfolgen.
:p.
Optional k”nnen noch 3 Schalter aktiviert/deaktiviert werden, die die Verarbeitung der Daten durch PGP v5.0 fr OS/2 entsprechend beeinflussen. In aktiviertem Zustand haben die Schalter folgende Bedeutung:
:p.
:parml tsize=10 break=all compact.
:pt.:hp2.Textausgabe&colon.:ehp2.:pd.Textmodus ist eingeschaltet.  Dadurch wird PGP veranlaát, die Quelldaten in ein plattformunabh„ngiges Format zu konvertieren.
Dies wird haupts„chlich dann benutzt, wenn Dateien auf ein anderes Betriebssystem bertragen werden sollen.
.br
:pt.:hp2.Signatur in separate Datei&colon.:ehp2.:pd.PGP erzeugt die Unterschrift in eine separate Datei (standardm„áig mit der Endung ".sig") anstatt sie zusammen mit den Zieldaten in einer einzigen Datei abzulegen.
.br
:nt text='Bitte beachten:'.
Dieser Schalter ist bei Verwendung der Zwischenablage gesperrt, da die behandelten Zieldaten immer komplett in die Zwischenablage zurckgestellt werden!
:ent.
.br
:pt.:hp2.ASCII-Schutzhlle&colon.:ehp2.:pd.Wenn diese Option aktiviert ist, schlieát PGP die Daten in eine Klartext-Schutzhlle ein. Dies macht die Daten sicher fr einen Email-Transport, allerdings nimmt der Datenumfang dadurch um ca. 30% zu.
Im Gegensatz zu frheren Versionen von PGP wird hiermit auch gleichzeitig eine Klartextunterschrift um die Daten erzeugt, wobei lesbare Daten (EMails, ASCII-Textdateien etc.) auch nach der Verarbeitung durch PGP weiterhin im Klartext lesbar bleiben.
:eparml.
:p.
W„hrend einer Entschlsselungs-/Prfungsaktion sind diese 3 Schalter nicht vorhanden!
.* Ende Passphrase eingeben
.* -----------------------------------------------------------------------------
:h1 res=6 hide. Schlssel ausw„hlen
:i1 id=key. Schlssel
:i2 refid=key. Schlssel ausw„hlen
:i2 refid=key. Auswahlliste/Listbox
:p.
Aus der dargestellten Listbox k”nnen ein oder mehrere PGP-Schlssel ausgew„hlt werden, mit denen das Quellmedium verschlsselt werden soll.
Die Liste enth„lt zu jedem Schlssel die hexadezimale Schlssel-ID, den Verschlsselungsalgorithmus, mit dem der Schlssel erzeugt wurde und die zugeh”rige Benutzer-ID.
Das Krzel ":hp2.(priv):ehp2." weist darauf hin, daá es sich hierbei um einen privaten/geheimen Schlssel handelt.
:p.
Zus„tzlich zur Schlsselauswahl k”nnen Sie hier noch folgende Option ein- oder ausschalten:
.br
:parml tsize=10 break=all compact.
:pt.:hp2.ASCII-Schutzhlle&colon.:ehp2.:pd.N„here Erl„uterungen zu diesem Schalter finden Sie :link reftype=hd res=5.hier:elink..
:nt text='Hinweis:'.
Dieser Schalter ist hier nicht vorhanden, wenn als PGP-Aktion "Verschlsseln :hp7.:hp5.und:ehp5.:ehp7. Unterschreiben" ausgew„hlt worden ist. Stattdessen findet man ihn dann im Dialogfenster ":link reftype=hd res=5.Passphrase eingeben:elink.".
:ent.
.br
:eparml.
.* Ende Listbox
.* -----------------------------------------------------------------------------

:h1 res=8.Quelldatei ausw„hlen
:p.
W„hlen Sie hier die Quelldatei aus, die Sie mit PGP bearbeiten wollen. Abh„ngig von der ausgew„hlten PGP-Aktion hat die Quelldatei folgende Bedeutung&colon.
:p.
:parml tsize=20 break=fit compact.
:pt.:hp2.Unterschreiben:pd.
:pt.Verschlsseln:pd.
:pt.Verschlsseln &amp.
.br
Unterschreiben&colon.:ehp2.:pd.W„hlen Sie hier die Quelldatei aus, die Sie unterschreiben oder verschlsseln bzw. verschlsseln und unterschreiben wollen. Die Zieldatei erh„lt dabei eine der folgenden Dateinamenerweiterungen&colon.
.br
:sl.
:li.:hp2.&per.asc:ehp2. wenn eine Zieldatei mit ASCII-Schutzhlle erzeugt wurde.
:li.:hp2.&per.pgp:ehp2. wenn eine Zieldatei ohne ASCII-Schutzhlle erzeugt wurde.
:li.:hp2.&per.sig:ehp2. wenn eine separate Unterschrift (ohne ASCII-Schutzhlle) fr die Quelldatei erzeugt wurde.
:esl.
.br
:pt.:hp2.Entschlsseln oder
.br
Prfen&colon.:ehp2.:pd.Wenn Sie eine separate Unterschrift (Dateierweiterung :hp2.&per.asc:ehp2. bzw. :hp2.&per.sig:ehp2.) verifizieren wollen, geben Sie hier die Datei an, welche die separate Unterschrift enth„lt.
.br
Zum Entschlsseln einer Datei geben Sie hier den Namen der verschlsselten Quelldatei (Dateinamenerweiterung :hp2.&per.asc:ehp2. bzw. :hp2.&per.pgp:ehp2.) an.
:eparml.


.* Ende Quelldatei ausw„hlen
.* -----------------------------------------------------------------------------

:h1 res=9.Zieldatei ausw„hlen
:p.
W„hlen Sie hier die Zieldatei aus, die Sie mit PGP bearbeiten wollen. Je nachdem, ob es sich bei der zuvor ausgew„hlten Quelldatei um eine Quelldatei mit einer separaten
Unterschrift handelt oder um eine Quelldatei, die neben den eigentlichen Daten auch gleichzeitig eine Unterschrift enth„lt oder um eine PGP-verschlsselte Quelldatei, hat die hier gew„hlte Datei folgende Bedeutung&colon.
:p.
:parml tsize=10 break=fit compact.
:pt.:hp2.Quelldatei enth„lt separate Unterschrift&colon.:ehp2.:pd.W„hlen Sie hier die Datei aus, zu der die vorher ausgew„hlte separate Unterschriftdatei (Dateierweiterung :hp2.&per.asc:ehp2. bzw. :hp2.&per.sig:ehp2.) geh”rt.
.br
:pt.:hp2.Quelldatei enth„lt PGP-verschlsselte Daten und/oder eine PGP-Unterschrift&colon.:ehp2.:pd.Geben Sie hier einen Namen fr die Datei an, die nachher die entschlsselten bzw. die von der Unterschrift befreiten Daten enthalten soll.
:eparml.

.* Ende Zieldatei ausw„hlen
.* -----------------------------------------------------------------------------

:h1 res=10.PGP-Schlsselverwaltung
:i1 id=pgpkeys. Schlsselverwaltung
:i1. PGPKeys
:i2 refid=pgpkeys. Zugeh”rige Dateien
:i2 refid=pgpkeys. VROBJ.DLL
:p.
Ab der Version v1.42 von :color fc=DarkPink bc=default.PGPTools fr OS/2:color fc=default bc=default. ist erstmals auch eine von vielen Benutzern gewnschte PGP-Schlsselverwaltung integriert. Hierbei handelt es sich um das eigenst„ndige Paket
:color fc=DarkBlue bc=default.
PGPKeys
:color fc=default bc=default.
von Thomas Bohn. Z. Zt. besteht dieses Paket aus mindestens 3 Dateien:

:ul compact.
:li. PGPKEYS.EXE
:li. FILEREXX.DLL
:li. PGPKK.CMD
:eul.
.br
Diese 3 Dateien mssen sich in dem Pfad befinden, in dem auch :color fc=DarkPink bc=default.PGPTools fr OS/2:color fc=default bc=default. installiert ist.
Fehlt eine dieser Dateien, ist das PGPKeys-Paket nicht lauff„hig. In dem Fall erscheint beim Start von :color fc=DarkPink bc=default.PGPTools fr OS/2:color fc=default bc=default. ein entsprechendes
:link reftype=hd res=7.Hinweisfenster:elink., der "PGPKeys starten"-
:link reftype=hd res=2.Benutzerknopf:elink. im Hauptfenster ist ausgeblendet und in den Einstellungen ist der Eintrag fr den :link reftype=hd res=7.Sende-Keyserver:elink. gesperrt.
:p.
Zus„tzlich wird noch die Watcom VX REXX Laufzeitbibliothek VROBJ.DLL v2.1d ben”tigt. Diese Datei kann ber die diversen Netze (Internet, Fido etc.) besorgt werden und muá sich blicherweise
im Verzeichnis C&colon.&bslash.OS2&bslash.DLL befinden (unter der Annahme, daá C&colon. die OS/2-Bootpartition ist).

.* Ende

:h1 res=11.Das Logfenster
:i1 id=logwin. Logfenster
:p.
Nach Beendigung einer Entschlsselungs- oder Prfaktion erscheint ein Logfenster, welches das Ergebnis der Aktion anzeigt.
Bestehen die entschlsselten bzw. geprften Daten ausschlieálich aus darstellbaren ("druckbaren") Zeichen, kann man durch Drcken des Buttons "Entschlsselte/geprfte Daten editieren" einen Texteditor starten, der die Daten l„dt und anzeigt.
Enth„lt der Datenbestand irgendein nicht darstellbares("druckbares") Zeichen, ist der Button gesperrt!
:p.
Einen beliebigen Editor kann man in den
:link reftype=hd res=7.Einstellungen:elink. festlegen.
.* Ende

:euserdoc.
