#ifndef _COMMON_NET_WINSOCKET_WINSOCKET_H_
#define _COMMON_NET_WINSOCKET_WINSOCKET_H_

#include <WinSock2.h>
#include <string>

#include "../util/FuncPtr.h"

using namespace GCommon::GUtil;

namespace GCommon{
	namespace GNet{
		namespace GSocket{

#pragma comment(lib,"ws2_32.lib")
class CWinSocket{
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
