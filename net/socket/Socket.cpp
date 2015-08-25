#include <string>
#include <stdlib.h>
#include "Socket.h"
#include "../../log/Log.h"
#include "../../util/TypeTransform.h"

using namespace GCommon::GNet::GSocket;
using namespace GCommon::GLog;

CSocket::CSocket(IOType type,int family,int sockType,int protocol,int port,int backlog,struct epoll_event evs){

  ioType=type;
 
  ev=evs;//if is epoll mode,need this args


  listenfd=CSocketBase::Socket(family,sockType,protocol);

  if(type==IOEpoll){
    int yes;
    if(setsockopt(listenfd,SOL_SOCKET,SO_REUSEADDR,&yes,sizeof(int))==-1){
      CLog::Log("setsockopt failed!",getClassName());
    }
  }
   
  bzero(&serveraddr,sizeof(serveraddr));

  serveraddr.sin_family=family;
  serveraddr.sin_port=htons(port);
  serveraddr.sin_addr.s_addr=INADDR_ANY;



  CSocketBase::Bind(listenfd,(struct sockaddr*)&serveraddr,sizeof(serveraddr));

  CSocketBase::Listen(listenfd,backlog);

  maxfd=listenfd;//maxfd use only for select and poll
  
  counter=0;

  sockfdMap.clear();

}

CSocket::~CSocket(){
  if(IOEpoll==ioType){
    CSocketBase::Close(epfd);
  }
}

void CSocket::init(voFuncIntStr *newConnect,voFuncIntCharptr *newData,voFuncInt *disconnect,voFuncIntInt *except){
  newConnects=newConnect;
  newDatas=newData;
  disconnects=disconnect;
  excepts=except;
  switch(ioType){
   case IOSelect:
	selectLoop();
        break;
   case IOPoll:
        pollLoop();
        break;
   case IOEpoll:
        epollLoop();
        break;
   default:
        CLog::Log("invaild ioType input!",getClassName());
  }

}

void CSocket::selectLoop(){

   for(int i=0;i<FD_SETSIZE;i++){//insure the sclient every elements is -1 before select
     sclient[i]=-1;
   }

   FD_ZERO(&allset);

   FD_SET(listenfd,&allset);
   //this is the select loop,it will block the process run who run this function
   //when data ready,it will call the function who regist in init function

   for(;;){

     rset=allset;
     
     
     int nready=CSocketBase::Select(maxfd+1,&rset,NULL,NULL,NULL);//will test 0-maxfd ,every fd in this scope will be test

     if(FD_ISSET(listenfd,&rset)){//when a new connections come,add it to set and sclient array and sockMap;
       socklen_t clilen=sizeof(clientaddr);
       connfd=CSocketBase::Accept(listenfd,(struct sockaddr *)&clientaddr,&clilen);

       std::string ip=inet_ntoa(clientaddr.sin_addr);
       
       CLog::Log("new client connect,sockfd="+ToStr(connfd)+",ip="+ip,getClassName());

       int index=0;
       for(index=0;connfd!=-1&&index<FD_SETSIZE;index++){
         if(sclient[index]<0){
           //add sockfd to sclient[]
           sclient[index]=connfd;
           //add sockfd to allset
           FD_SET(connfd,&allset); 

           //add sockfd to map ,because clang++ can't complie it,hide it 
           //sockfdMap[connfd]=connfd;
           counter++;
           (*newConnects)(connfd,ip);//call function who regeist in init();
           break;
         }
       }
       
       if(FD_SETSIZE==index){
         CLog::Log("too much sock connect,array is full!,index="+ToStr(index),getClassName());
       }
       if(connfd>maxfd){//maxfd in sclient[],be care maxfd did't eq max index in sclient
         maxfd=connfd;
       }

       if(--nready<=0){ //if no more data ready,don't continue to left code
         continue; 
       }
     
     }

    //if not a new connection but a already socket data come
    int sockfd;
    for(int i=0;i<maxfd+1;i++){
      if((sockfd=sclient[i])<0){
        continue;
      }
      if(FD_ISSET(sockfd,&rset)){
        memset(buf,'\0',sizeof(buf));
        int nread;
        if((nread=CSocketBase::Read(sockfd,buf,MAX_BUF_SIZE))<0){
          CLog::Log("socket close by client or socket occur error",getClassName());
          CSocketBase::Close(sockfd);
          sclient[i]=-1;
          //sockfdMap[sockfd]=-1;
          counter--;
          FD_CLR(sockfd,&allset);
          //callback
          (*disconnects)(sockfd);
          if(0!=errno){
            (*excepts)(sockfd,errno);      
          }
        }else if(0==nread){
          CLog::Log("read==0",getClassName());
          continue;
        }else{//get new data
          (*newDatas)(sockfd,buf);
        }
        if(--nready<=0){
          break;
        }
      }
    }
 
   }
}

void CSocket::send(int sockfd,const char* buf){
  CSocketBase::Writen(sockfd,buf,strlen(buf));
}

int CSocket::getCounter(){
  return counter;
}

void CSocket::close(int sockfd){
  if(ioType==IOSelect){
    for(int i=1;i<maxfd;i++){
      if(sclient[i]==sockfd){
        sclient[i]=-1;
        FD_CLR(sockfd,&allset);
        counter--;
      }
    }
   }else if(ioType==IOPoll){
     for(int i=1;i<maxfd;i++){
       if(pclient[i].fd==sockfd){
         pclient[i].fd=-1;
         counter--;
       }
     }
   }else if(ioType==IOEpoll){
     CSocketBase::Epoll_ctl(epfd,EPOLL_CTL_DEL,sockfd,&ev);
     counter--;
 }
 CSocketBase::Close(sockfd);
}


void CSocket::pollLoop(){
  pclient[0].fd=listenfd;
  pclient[0].events=POLLRDNORM;

  maxIndex=0;

  for(int i=1;i<MAX_USER_SIZE;i++){
    pclient[i].fd=-1;
  }

  //come to poll loop
  for(;;){
    int nready=CSocketBase::Poll(pclient,maxIndex+1,1000);//time out is 1s
  
    if(pclient[0].revents&POLLRDNORM){
      socklen_t clilen=sizeof(clientaddr);
      connfd=CSocketBase::Accept(listenfd,(struct sockaddr *)&clientaddr,&clilen);

      std::string ip=inet_ntoa(clientaddr.sin_addr);
       
      CLog::Log("new client connect,sockfd="+ToStr(connfd)+",ip="+ip,getClassName());
       
      int index=1;
      for(index=1;connfd!=-1&&index<MAX_USER_SIZE;index++){
        if(pclient[index].fd<0){
          pclient[index].fd=connfd;
          //pclient[index].events=ev.events;
          pclient[index].events=POLLRDNORM;
          counter++;
          (*newConnects)(connfd,ip);
          break;
        }
      }
      if(MAX_USER_SIZE==index){
         CLog::Log("too much sock connect,array is full!,index="+ToStr(index),getClassName());
       }
       if(index>maxIndex){//max index in pclient[]
         maxIndex=index;
       }
       if(--nready<=0){ //if no more data ready,don't continue to left code
         continue; 
       }

    }

    int sockfd;
    for(int i=1;i<maxIndex+1;i++){
      if((sockfd=pclient[i].fd)<0){
        continue;
      }
      //if(pclient[i].revents&ev.events){
      if(pclient[i].revents&POLLRDNORM){
        memset(buf,sizeof(buf),'\0');
        int nread;
        if((nread=CSocketBase::Read(sockfd,buf,MAX_BUF_SIZE))<0){
          CLog::Log("socket close by client or socket occur error",getClassName());
          CSocketBase::Close(sockfd);
          pclient[i].fd=-1;
          //sockfdMap[sockfd]=-1;
          counter--;
          (*disconnects)(sockfd);
          if(0!=errno){
            (*excepts)(sockfd,errno);      
          }
        }else if(0==nread){
          continue;
        }else{//get the data
          (*newDatas)(sockfd,buf);
        }
        if(--nready<=0){//no more ready
          break;
        }
      }
    }
  }

}


void CSocket::epollLoop(){
  events=(epoll_event*)calloc(MAX_USER_SIZE,sizeof(struct epoll_event));

  epfd=CSocketBase::Epoll_create(MAX_USER_SIZE);
  
  ev.events=POLLIN;//now ,only listen POLLIN 
  ev.data.fd=listenfd;

  CSocketBase::Epoll_ctl(epfd,EPOLL_CTL_ADD,listenfd,&ev); 

  for(;;){
    int nready=CSocketBase::Epoll_wait(epfd,events,MAX_USER_SIZE,-1);

    int sockfd;
    for(int index=0;connfd!=-1&&index<nready;index++){
      sockfd=events[index].data.fd;
      if(sockfd==listenfd){//new connections
        socklen_t clilen=sizeof(clientaddr);
        connfd=CSocketBase::Accept(listenfd,(struct sockaddr *)&clientaddr,&clilen);

        std::string ip=inet_ntoa(clientaddr.sin_addr);
       
        CLog::Log("new client connect,sockfd="+ToStr(connfd)+",ip="+ip,getClassName());
        
        ev.data.fd=connfd;//why set ev.data.fd eq newfd,and why send it to ctl function twices,first in newfd,second is newfd itself
        CSocketBase::Epoll_ctl(epfd,EPOLL_CTL_ADD,connfd,&ev);
        counter++;
        (*newConnects)(connfd,ip);
        continue;
      }else if(events[index].events&EPOLLHUP){//close by client
        CLog::Log("socket close by client or socket occur error",getClassName());
        CSocketBase::Epoll_ctl(epfd,EPOLL_CTL_DEL,sockfd,&ev);
        (*disconnects)(sockfd);
        if(0!=errno){
          (*excepts)(sockfd,errno);
        }
        CSocketBase::Close(sockfd);
        continue;
     }else if(events[index].events&EPOLLIN){
       memset(buf,'\0',sizeof(buf));
       CSocketBase::Recv(sockfd,buf,sizeof(buf),0);
       (*newDatas)(sockfd,buf);   
     }
    }
  }
  

}




























