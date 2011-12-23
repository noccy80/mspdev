CLS
@echo off
rem This is a small helper script that runs through the test collection for one device (folder)
rem
rem William Goh, MSP430 Applications, Texas Instruments, Inc.
rem Last modified: 06/21/2011
set device=MSP430F5529
set firmware=MSP-EXP430F5529UserExperience.txt
goto program




:program
@echo Programing %firmware% into %device% ......
MSP430Flasher.exe -n %device% -w %firmware% -v -g -z [VCC]

pause