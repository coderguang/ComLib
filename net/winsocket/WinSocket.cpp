#include "stdafx.h"
#include "../../include/log/Log.h"
#include "../../include/net/WinSocket.h"

using namespace GCommon::GNet::GSocket;
using namespace GCommon::GUtil;
using namespace GCommon::GLog;

CWinSocket::CWinSocket(char* host, int port, int family, int protocol, int sockType){
	className = "CWinSocket";
	isClosed = false;
	initSocket(host, port, family, protocol, sockType);
}
CWinSocket::~CWinSocket(){ 
	if (!clientfd){
		closesocket(clientfd);
		WSACleanup();
	}
}

std::string& CWinSocket::getClassName(){ 
	return className;
}

void CWinSocket::initSocket(char* host, int port, int family, int protocol, int sockType){
	
	mVersion = MAKEWORD(2, 2);//WinSock dll�İ汾

	if (0!=WSAStartup(mVersion, &wsaData)){
		CLog::Log("winsocket WSAStartup failed", getClassName());
	}

	clientfd = socket(family, sockType, protocol);
	if (INVALID_SOCKET == clientfd){
		CLog::Log("winsocket socket failed,invalid socket", getClassName());
	}

	servaddr.sin_family = family;
	servaddr.sin_port = htons(port);
	servaddr.sin_addr.S_un.S_addr = inet_addr(host);

	if (SOCKET_ERROR == connect(clientfd, (struct sockaddr *)&servaddr, sizeof(servaddr))){
		CLog::Log("winsocket connect failed", getClassName());		
	}

}

void CWinSocket::sendMsg(std::string msg){
	if (send(clientfd, msg.c_str(), sizeof(msg) + 1, 0) <= 0){
		CLog::Log("winsocket send error:msg=" + msg, getClassName());
	}
}


void CWinSocket::close(){
	closesocket(clientfd);
	WSACleanup();
	isClosed = true;
}