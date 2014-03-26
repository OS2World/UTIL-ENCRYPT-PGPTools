@echo off

REM englische Version

cd .\ENGLISH
del *.obj
del *.res
del *.map
del *.sym
del pgptools.exe
del pgptools.dll
del pgptools.lib
del pgptools.hlp
del filerexx.dll

cd ..\ENGLISH\DLL
del *.obj
del *.dll
del *.lib
del *.res
del *.map
del *.sym

cd ..\..\ENGLISH\DOC
del *.inf
del *.bak

cd ..\..\ENGLISH\HELP
del *.hlp
del *.bak

cd ..\..\ENGLISH\RUN
del pgptools.exe
del pgptools.dll
del pgptools.inf
del pgptools.hlp


REM deutsche Version

cd ..\..\DEUTSCH
del *.obj
del *.res
del *.map
del *.sym
del pgptools.exe
del pgptools.dll
del pgptools.lib
del pgptools.hlp
del filerexx.dll

cd ..\DEUTSCH\DLL
del *.obj
del *.dll
del *.lib
del *.res
del *.map
del *.sym

cd ..\..\DEUTSCH\DOC
del *.inf
del *.bak

cd ..\..\DEUTSCH\HELP
del *.hlp
del *.bak

cd ..\..\DEUTSCH\RUN
del pgptools.exe
del pgptools.dll
del pgptools.inf
del pgptools.hlp



