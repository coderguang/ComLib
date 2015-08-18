#ifndef _COMMON_NET_SOCKET_SOCKET_H_
#define _COMMON_NET_SOCKET_SOCKET_H_

#include "SocketBase.h"
#include "../../util/FuncPtr.h"

namespace GCommon{
  namespace GNet{
    namespace GSocket{

using namespace GCommon::GUtil;

static const int MAX_BUF_SIZE=10240;//the socket read and write buf size
//static const FD_SETSIZE=1024;
static const int MAX_USER_SIZE=99999;

class GSocket{
  public:
    GSocket(int IOType,int family,int sockType,int protocol,int port,int backlog);
    
    bool init(voFuncInt *newConnect,voFuncIntCharptr *newData,voFuncInt *disconnect,voFuncIntInt *except);

    bool send(int sockfd,char *buf);
   
    bool close(int sockfd);

    int getCounter(){
      return counter;
    }
  
  protected:
    void SelectLoop();
    
    void PollLoop();
 
    void EpollLoop();

  private:
    GSocket(GSocket&)=delete;
    GSocket operator=(GSocket&)=delete;
  
    char buf[MAX_BUF_SIZE];
    
    int counter;//the sockfd counter

    fd_set rset,allset;//use for select mode
   
    int sclient[FD_SETSIZE];//use for select mode
    
    struct epollfd eclient[MAX_USER_SIZE];//use for poll mode
   
    struct epoll_event *events;//use for epoll mode 
    struct epoll_event ev;//use for epoll mode
   


};


    }
  }
}
#endif
