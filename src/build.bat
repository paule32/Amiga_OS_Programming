:: ----------------------------------------------------------------------------
:: Datei:  hello_1.py
:: Author: Jens Kallup - paule32
::
:: Rechte: (c) 2023 by kallup non-profit software
::         Alle Rechte vorbehalten.
::
:: Nur für schulische, oder nicht kommerzielle Zwecke !!!
:: ----------------------------------------------------------------------------
set VBCC=E:\Amiga-Dev
set PATH=%VBCC%\bin;%PATH%

set TARGET=%VBCC%\targets\m68k-amigaos

vc.exe  -O2                      ^
	-DAMIGA=1                ^
	-DCPU=68000              ^
	-I%TARGET%\include       ^
	-I%TARGET%\netinclude    ^
	-I%TARGET%\ndk\include_h ^
	-I%TARGET%\posix\include ^
        -L%TARGET%\lib           ^
	-L%TARGET%\posix\lib     ^
	+%TARGET%\config\kick13  ^
	hello.c                  ^
	-o hello -lmieee

vasmm68k_mot -Fhunk -o bootblock.hunk bootblock.asm
