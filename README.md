compilerCreator is written in C and either:<br>
a> writes file setting.bin for use by the compiler (contains uint8 operatingSystem (windows, linux, mac), uint8 assemblyType (windowsX64, linuxX64, macARM64)).<br>
b> writes compiler executable for the above indicated system and assembly language:<br>

Settings for compilerCreator:<br>
Configuration Manager: x64 Release.<br>
C/C++ > Language > C Langage Standard: C17.<br>

Features compilerCreator includes in compiler:<br>
0) return 1 in Windows x64 PE (in progress).<br>
