#ifndef _COMMON_NET_WINSOCKET_WINSOCKET_H_
#define _COMMON_NET_WINSOCKET_WINSOCKET_H_

#if defined(WINSOCK_EXPORTS)&&defined(_WINDOWS)
#define WINSOCK_DLL_API _declspec(dllexport)
#elif defined(_WINDOWS)
#define WINSOCK_DLL_API _declspec(dllimport)
#endif

#include <WinSock2.h>
#include <string>

#include "../util/FuncPtr.h"

using namespace GCommon::GUtil;

namespace GCommon{
	namespace GNet{
		namespace GSocket{

#pragma comment(lib,"ws2_32.lib")


#ifdef WINSOCK_DLL_API
	class WINSOCK_DLL_API CWinSocket{
#else
	class CWinSocket{
#endif

public:
	CWinSocket(char* host, int port, int family, int protocol, int sockType);
	virtual ~CWinSocket();
	void init(voFuncStr *newData);
	void sendMsg(std::string msg);
	void close();
protected:
	void initSocket(char *host, int port, int family, int protocol, int sockType);
	std::string& getClassName();

private:
	CWinSocket(CWinSocket&) = delete;
	CWinSocket operator = (CWinSocket &) = delete;

	WORD mVersion;
	WSADATA wsaData;//WSADATA�ṹ����������AfxSocketInit�������ص�WindowsSockets��ʼ����Ϣ��
	SOCKET clientfd;
	struct sockaddr_in servaddr;
	bool isClosed;//�Ƿ������ر���socket
	voFuncIntStr *newDatas;//��ʱ�������ݣ�ֻ������

	std::string className;
};

		}
	}
}


#endif
