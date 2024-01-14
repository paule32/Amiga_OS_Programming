:: ----------------------------------------------------------------------------
:: Datei:  hello_1.py
:: Author: Jens Kallup - paule32
::
:: Rechte: (c) 2023 by kallup non-profit software
::         Alle Rechte vorbehalten.
::
:: Nur für schulische, oder nicht kommerzielle Zwecke !!!
:: ----------------------------------------------------------------------------
@echo on
set VBCC=E:\Amiga-Dev
set PATH=%VBCC%\bin;%PATH%

set TARGET=%VBCC%\targets\m68k-amigaos

set FLAGS= ^
  -c99 -cpp-comments -O=3 -DAMIGA=1 -DCPU=68000 ^
  -I%TARGET%\include -I%TARGET%\netinclude -I%TARGET%\ndk\include_h

vc %FLAGS% -c graphic.c
vc %FLAGS% -o graphic   graphic.o -lamiga -lmieee

::cranker.exe -d cinema -f hello -o hello.hunk
