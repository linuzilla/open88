@echo off
echo:
if not [%1] == [] goto fileck
echo usage: %0 [filename]
goto quit
:fileck
if exist %1.asm goto assem
echo %1.asm: file not found!
goto quit
:assem
masm %1;
if errorlevel 1 goto quit
if not exist %1.obj goto quit
link %1;
:quit
shift
if not [%1] == [] goto fileck
echo:
