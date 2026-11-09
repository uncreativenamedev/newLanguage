compilerCreator is written in C and either:
a> writes file setting.bin for use by the compiler (contains uint8 operatingSystem (windows, linux, mac), uint8 assemblyType (windowsX64, linuxX64, macARM64)).
b> writes compiler executable for the above indicated system and assembly language.

Settings for compilerCreator:
Configuration Manager: x64 Release.
C/C++ > Language > C Langage Standard: C17.

Features compilerCreator includes in compiler:
0) return 1 in Windows x64 PE.

Directions To Run:
To write settings to setting.bin:
Write 0<operatingSystemID><assemblyLanguageID> to compilerCreatorSetting.txt, ensuring compilerCreatorSetting.txt is
saved as utf-8 without BOM.
To write compiler_rmc_<type><extension>:
Write 1<etc.> to compilerCreatorSetting.txt.
run compilerCreator.exe on cmd.exe with "compilerCreator.exe & echo %ERRORLEVEL%"

Utility programs:
numberConverter: used for converting 8 hex numbers to a sequence of 8 binary bytes.
