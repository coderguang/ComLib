
#ifndef CHAT_INPUT_H_
#define CHAT_INPUT_H_
#include <WinSock2.h>
#include <string>
#include <iostream>
#include "Config.h"

void ChatInput(SOCKET sockfd){
	using namespace std;
	char buf[MSGSIZE];
	cout << "ֱ��������Ϣ��Ȼ��س����ɷ�����Ϣ:";
	while (true){
		//cin >> buf;
		cin.getline(buf, MSGSIZE);
		int slen = send(sockfd, buf, strlen(buf),0);
		if (slen == SOCKET_ERROR){
			cout << "����ʧ��!" << endl;
			break;
		}else{
			//cout << "���ͳɹ���" << endl;
		}
	}
}




#endif