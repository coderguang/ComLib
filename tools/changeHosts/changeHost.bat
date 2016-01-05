@echo off

@rem set you ip replace source data
set IPDATA=ipReplace.txt
@rem set what ip you want to when person enter this web address
set IPAIM=127.0.0.1

@rem copy the data to hosts dir
echo.
copy /y %IPDATA% c:\windows\system32\drivers\etc\

@rem enter the hosts dir,if not ,will happen permission error
c:
cd \
cd \windows\system32\drivers\etc

for /f  "tokens=2 delims= " %%i in (%IPDATA%) do echo %IPAIM% %%i >>hosts