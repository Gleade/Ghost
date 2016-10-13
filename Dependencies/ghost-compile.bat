set myPath=%cd%

set testPath = %myPath% 

cd "C:\Python33\Scripts"

@echo Removing: %myPath%\test.build

@RD /S /Q %myPath%\test.build

@echo Compiling...

START xcopy "C:\Python33\python33.dll" %myPath%\ /C /Y /Z

C:\Python33\Scripts\nuitka.bat %myPath%\test.py

@echo Removing: %myPath%\test.build

@RD /S /Q %myPath%\test.build

PAUSE