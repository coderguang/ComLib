#ifndef _COMMON_NET_SOCKET_SOCKET_BASE_H_
#define _COMMON_NET_SOCKET_SOCKET_BASE_H_

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <poll.h>
#include <sys/time.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>
#include <sys/epoll.h>
#include <string>

/*
 * data:2015-08-18
 *
 * author:coderguang
 *
 * e-mail:royalchen@royalchen.com
 *
 */





namespace GCommon{
  namespace GNet{
    namespace GSocket{

const int OK=0;
const int ERROR=-1;

/*
 * this class is use for GSocket
 *
 */

class CSocketBase{
  public:
    static int Socket(int family,int type,int protocol);
	
    static int Connect(int sockfd,const struct sockaddr *servaddr,socklen_t addrlen);
    
    static int Bind(int sockfd,const struct sockaddr *servaddr,socklen_t addrlen);
    
    static int Listen(int sockfd,int backlog);

    static int Accept(int sockfd,struct sockaddr *cliaddr,socklen_t *addrlen);

    static int Select(int maxfd,fd_set *readset,fd_set *writeset,fd_set *exceptset,struct timeval *timeout);

    static int Poll(struct pollfd *fdarray,unsigned long nfds,int timeout);

    static int Epoll_create(int size);

    static int Epoll_ctl(int epfd,int op,int fd,struct epoll_event *event);

    static int Epoll_wait(int epfd,struct epoll_event *events,int maxevents,int timeout);

    static int Close(int sockfd);

    static ssize_t Read(int sockfd,void *buf,size_t len);

    static ssize_t Write(int sockfd,void *buf,size_t len);

    static ssize_t Readn(int sockfd,void *vptr,size_t len);

    static ssize_t Writen(int sockfd,const void *vptr,size_t len);

    static ssize_t Writen(int sockfd,const char* vprt,size_t len);

    static ssize_t Recv(int sockfd,void *buf,size_t len,int flags);

    static std::string getClassName(){
      return "CSocketBase";
    }


};
    }
  }
}
#endif
