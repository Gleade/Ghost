set myPath=%cd%

set testPath = %myPath% 

cd "C:\Python33\Scripts"

@echo Removing: %myPath%\test.build

@RD /S /Q %myPath%\test.build

@echo Compiling...

START xcopy %mypath%\DLL\python33.dll %myPath%\ /C /Y /Z

START xcopy /e /v C:\Python33\Lib %myPath%\Lib\ /C /Y / Z

C:\Python33\Scripts\nuitka.bat %myPath%\Test.py

@echo Removing: %myPath%\test.build

@RD /S /Q %myPath%\test.build