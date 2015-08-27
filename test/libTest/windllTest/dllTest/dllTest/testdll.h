#ifndef _TEST_DLL_H_
#define _TEST_DLL_H_
#include <Windows.h>
#include <string>
//don't need this header file
//#include "../../../../../include/log/Log.h"
//#include "../../../../../include/util/Time.h"
//#include "../../../../../include/net/WinSocket.h"
/*
using namespace GCommon::GLog;
using namespace GCommon::GUtil;
using namespace GCommon::GNet::GSocket;
*/

void testSock(){
	
	typedef void(*cs)(char* host, int port, int family, int protocol, int sockType);
	HINSTANCE hdll;

	hdll = LoadLibrary("../../../../../dll/winsock.dll");

	if (hdll == NULL){
		std::cout << "load winsock.dll faild!" << std::endl;
	}
	else{
		std::cout << "good luck ! load winsock.dll success!" << std::endl;
	}



	cs flog = (cs)GetProcAddress(hdll, "??0CWinSocket@GSocket@GNet@GCommon@@QEAA@PEADHHHH@Z");

	if (flog == NULL){
		std::cout << "load socket faild!" << std::endl;
	}
	else{
		std::cout << "good luck ! socket time success!" << std::endl;
	}
	char host[30] = "182.254.233.115";
	//std::string host="182.254.233.115";
	flog(host, 9200, AF_INET, 0, SOCK_STREAM);
	
}

void testUtil(){
	typedef std::string(*p_time)();
	HINSTANCE hdll;

	hdll = LoadLibrary("../../../../../dll/util.dll");

	if (hdll == NULL){
		std::cout << "load util.dll faild!" << std::endl;
	}
	else{
		std::cout << "good luck ! load util.dll success!" << std::endl;
	}



	p_time flog = (p_time)GetProcAddress(hdll, "?getTimeNow@CTime@GUtil@GCommon@@SA?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ");

	if (flog == NULL){
		std::cout << "load time faild!" << std::endl;
	}
	else{
		std::cout << "good luck ! load time success!" << std::endl;
	}
	std::cout << "now time is" << flog() << std::endl;;
}

void test(){
	typedef int(*p_add)(int, int);
	HINSTANCE hdll;
	hdll = LoadLibrary("../../../../../dll/test.dll");

	if (hdll == NULL){
		std::cout << "load test.dll faild!" << std::endl;
	}
	else{
		std::cout << "good luck ! load test.dll success!" << std::endl;
	}

	p_add flog = (p_add)GetProcAddress(hdll, "add");

	if (flog == NULL){
		std::cout << "load test faild!" << std::endl;
	}
	else{
		std::cout << "good luck ! test flog success!" << std::endl;
	}

	//std::cout << "5+6=" << flog(5, 6) << std::endl;
}

void testLog(){
	typedef void(*p_Log)(std::string, std::string);
	HINSTANCE hdll;

	hdll = LoadLibrary("../../../../../dll/log.dll");

	if (hdll == NULL){
		std::cout << "load log.dll faild!" << std::endl;
	}
	else{
		std::cout << "good luck ! load log.dll success!" << std::endl;
	}



	p_Log flog = (p_Log)GetProcAddress(hdll, "?Log@CLog@GLog@GCommon@@SAXV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@0@Z");

	if (flog == NULL){
		std::cout << "load CLog::Log faild!" << std::endl;
	}
	else{
		std::cout << "good luck ! load load CLog::Log success!" << std::endl;
	}
	flog("yes", "are you ok");
}


#endif