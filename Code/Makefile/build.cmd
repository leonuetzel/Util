@echo off



mingw32-make -j48 -f Code/Makefile/makefile.mk
if %errorlevel% == 0 "./Code/Makefile/run"