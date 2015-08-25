#include <iostream>
#include "util\FuncPtr.h"
#include "WinSocket.h";

using namespace GCommon::GNet::GSocket;
int main(int argc, char **argv){

	char *host = "182.254.233.115";
	int port = 9000;
	const int max = 10000;

	CWinSocket *client[max];

	for (int i = 0; i < max; i++){
		client[i] = new CWinSocket(host, port, AF_INET, 0, SOCK_STREAM);
	}

	char buf[128];
	while (true){
		std::cin.getline(buf, 128);
		for (int i = 0; i < max; i++){
			client[i]->sendMsg(buf);
		}
	}


}