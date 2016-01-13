 
 set RESULT=result.txt
 
 for /f "delims= " %%i in (../../../dorking.txt) do (
	echo %%i >>%RESULT%
	net use \\%%i\ipc$ "" /user:"" >>%RESULT% 2>&1
 )
 
 pause