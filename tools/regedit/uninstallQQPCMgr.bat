@rem set seach dir
set QQPATH=HKEY_CURRENT_USER\SOFTWARE\Tencent\QQPCMgr

@rem find dir in regedit
for /f "tokens=2,* delims=Z " %%i in ('Reg Query "%QQPATH%" /v "InstallDir" ') do set QQDIR=%%j
echo %QQDIR%>dir.txt

@rem find what driver in
for /f "tokens=1 delims=: " %%i in ("%QQDIR%") do set QQDRIVER=%%i

@rem change the envirment to this driver
%QQDRIVER%:

echo.
cd %QQDIR%

start Uninst.exe


pause