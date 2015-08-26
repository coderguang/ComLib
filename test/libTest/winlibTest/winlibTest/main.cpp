#include <iostream>
#include "../../../../include/log/Log.h"
#include "../../../../include/net/WinSocket.h"

using namespace GCommon::GLog;
using namespace GCommon::GNet::GSocket;

#pragma comment(lib,"../../../../winlib/log.lib")
#pragma comment(lib,"../../../../winlib/winsock.lib")
int main(int argc, char **argv){
	CLog::Log("hello,boy", "ok");


	CWinSocket *so = new CWinSocket("182.254.233.115", 9200, AF_INET, 0, SOCK_STREAM);
	

	std::string s;
	std::cin >> s;
}