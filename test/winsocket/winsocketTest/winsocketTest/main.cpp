#include <iostream>
#include "util\FuncPtr.h"
#include "WinSocket.h";

using namespace GCommon::GNet::GSocket;
int main(int argc, char **argv){

	char *host = "182.254.233.115";
	int port = 9200;

	CWinSocket *ts=new CWinSocket(host, port, AF_INET, 0, SOCK_STREAM);
	while (true){
		std::cout << "ÊäÈë·¢ËÍÄÚÈÝ" << std::endl;
		char buf[30];
		std::cin.getline(buf, 30);
		std::string str(buf);
		ts->sendMsg(str);
	}

}