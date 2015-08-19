#include "../../log/Log.h"
#include "../../util/TypeTransform.h"

#include "SocketBase.h"

using namespace GCommon::GNet::GSocket;
using namespace GCommon::GUtil;
using namespace GCommon::GLog;

int CSocketBase::Socket(int family,int type,int protocol){
  int temp=socket(family,type,protocol);
  if(ERROR==temp){
    CLog::Log("socket init failed when call socket","GSockBase");
    return ERROR;
  }
  return temp;
}

int CSocketBase::Connect(int sockfd,const struct sockaddr *servaddr,socklen_t addrlen){
  int temp=connect(sockfd,servaddr,addrlen);
  if(ERROR==temp){
    CLog::Log("socket init failed when call connect","GSockBase");
    return ERROR;
  }
  return temp;
}

int CSocketBase::Bind(int sockfd,const struct sockaddr *servaddr,socklen_t addrlen){
  int temp=bind(sockfd,servaddr,addrlen);
  if(ERROR==temp){
    CLog::Log("socket init failed when call bind","GSockBase");
    return ERROR;
  }
  return temp;
}

int CSocketBase::Listen(int sockfd,int backlog){
  int temp=listen(sockfd,backlog);
  if(ERROR==temp){
    CLog::Log("socket init failed when call listen","GSockBase");
    return ERROR;
  }
  return temp;
  
}

int CSocketBase::Accept(int sockfd,struct sockaddr *cliaddr,socklen_t *addrlen){
  int temp=accept(sockfd,cliaddr,addrlen);
  if(ERROR==temp){
    CLog::Log("socket init failed when call accept","GSockBase");
    return ERROR;
  }
  return temp;
}

int CSocketBase::Select(int maxfd,fd_set *readset,fd_set *writeset,fd_set *exceptset,struct timeval *timeout){
  int temp=select(maxfd,readset,writeset,exceptset,timeout);
  if(temp>0||0==temp){
    return temp;
  }else if(ERROR==temp){
    CLog::Log("select occur error!","CSocketBase");
    return ERROR;
  }
  CLog::Log("select occur unexcepted error!","CSocketBase");
  return ERROR;
}

int CSocketBase::Poll(struct pollfd* fdarray,unsigned long nfds,int timeout){
  int temp=poll(fdarray,nfds,timeout);
  if(temp>0||temp==0){
    return temp;
  }else if(ERROR==temp){
    CLog::Log("poll occur error","CSocketBase");
    return ERROR;
  }
  CLog::Log("poll occur unexcepted error!","CSocketBase");
  return ERROR;
}

int CSocketBase::Epoll_create(int maxfd){
  int temp=epoll_create(maxfd);
  if(temp>0){
    return temp;
  }else if(ERROR==temp){
    CLog::Log("epoll_create occur error","CSocketBase");
    return ERROR;
  }
  CLog::Log("epoll_create occur unexcepted error!","CSocketBase");
  return ERROR;
}

int CSocketBase::Epoll_ctl(int epfd,int op,int fd,struct epoll_event *event){
  int temp=epoll_ctl(epfd,op,fd,event);
  if(0==temp){
    return OK;
  }else if(ERROR==temp){
    CLog::Log("epoll_ctl occur error","CSocketBase");
    return ERROR;
  }
  CLog::Log("epoll_ctl occur unexcepted error!","CSocketBase");
  return ERROR;
}

int CSocketBase::Epoll_wait(int epfd,struct epoll_event *events,int maxfd,int timeout){
  int temp=epoll_wait(epfd,events,maxfd,timeout);
  if(temp>0||0==temp){
    return temp;
  }else if(ERROR==temp){
    CLog::Log("epoll_wait occur error","CSocketBase");
    return ERROR;
  }
  CLog::Log("epoll_wait occur unexcepted error!","CSocketBase");
  return ERROR;
}

int CSocketBase::Close(int sockfd){
  int temp=close(sockfd);
  if(OK==temp){
    return temp;
  }else{
    CLog::Log("socket close occur error","CSocketBase");
    return ERROR;
  }
}

ssize_t CSocketBase::Read(int sockfd,void *buf,size_t len){
  int temp=read(sockfd,buf,len);
  if(temp<0){
    if(errno==EINTR){//should call read again
      temp=0;
      return OK;
    }else{
      CLog::Log("read socket error!","CSocketBase");
      return ERROR;
    }
  }else{
    return temp;
  }
}

ssize_t CSocketBase::Write(int sockfd,void *buf,size_t len){
  int temp=write(sockfd,buf,len);
  if(temp<=0){
    if(temp<0&&errno==EINTR){//should call write again
      temp=0;
      return OK;
    }else{
      CLog::Log("write socket error","CSocketBase");
      return ERROR;
    }
  }else{
    return temp;
  }
}

ssize_t CSocketBase::Readn(int sockfd,void *vptr,size_t len){
  size_t nleft;
  ssize_t nread;

  char *ptr;
  ptr=(char*)vptr;

  nleft=len;
  
  while(nleft>0){
    if((nread=read(sockfd,ptr,nleft))<0){
      if(errno==EINTR){
        nread=0; //should call read again
      }else{
        CLog::Log("readn sockfd error","CSocketBase");
        return ERROR;
      }
    }else if(nread==0){
      break;//EOF
    }
    nleft=nleft-nread;
    ptr=ptr+nread;
  }  
  return (len-nleft);

}


ssize_t Writen(int sockfd,const void *vptr,size_t len){
  size_t nleft;
  ssize_t nwritten;
  const char *ptr;
  
  ptr=(char*)vptr;
  nleft=len;

  while(nleft>0){
    if((nwritten=write(sockfd,ptr,nleft))<0){
      nwritten=0;
    }else{
      CLog::Log("writen sockfd error","CSocketBase");
      return ERROR;
    }
    nleft=nleft-nwritten;
    ptr+=nwritten;
  }
  return len;
}












