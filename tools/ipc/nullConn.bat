 
 set RESULT=../../../nullConn.txt
 set DORKING=../../../dorking.txt
 
 title nullConn.bat
 
 for /f "delims= " %%i in (%DORKING%) do (
	echo %%i >>%RESULT%
	net use \\%%i\ipc$ "" /user:""
	
 )
 
 pause