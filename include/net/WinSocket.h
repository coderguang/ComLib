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
	WSADATA wsaData;//WSADATA结构被用来保存AfxSocketInit函数返回的WindowsSockets初始化信息。
	SOCKET clientfd;
	struct sockaddr_in servaddr;
	bool isClosed;//是否主动关闭了socket
	voFuncIntStr *newDatas;//暂时不接数据，只发数据

	std::string className;
};

		}
	}
}


#endif
