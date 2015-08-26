#include <iostream>
#include <Windows.h>

#include "../../../../../include/log/Log.h"
using namespace GCommon::GLog;

int main(int argc, char **argv){
	typedef void(*p_Log)(std::string, std::string);

	HINSTANCE hdll;
	hdll = LoadLibrary("../../../../../dll/log.dll");

	if (hdll == NULL){
		std::cout << "load log.dll faild!" << std::endl;
	}
	else{
		std::cout << "good luck ! load log.dll success!" << std::endl;
	}

	//CLog::Log("hello,ok");
	p_Log flog;
	flog = (p_Log)GetProcAddress(hdll, "CLog::Log");

	if (flog == NULL){
		std::cout << "load flog faild!" << std::endl;
	}
	else{
		std::cout << "good luck ! load flog success!" << std::endl;
	}

	getchar();
}