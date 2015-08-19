#include <string>
#include <stdlib.h>
#include "Socket.h"
#include "../../log/Log.h"
#include "../../util/TypeTransform.h"

using namespace GCommon::GNet::GSocket;
using namespace GCommon::GLogger;

GSocket::GSocket(IOType type,int family,int sockType,int protocol,int port,int backlog){

  ioType=type;

  listenfd=GSocketBase::Socket(family,sockType,protocol);
   
  bzero(&serveraddr,sizeof(serveraddr));

  serveraddr.sin_family=family;
  serveraddr.sin_port=htons(port);
  serveraddr.sin_addr.s_addr=INADDR_ANY;

  GSocketBase::Bind(listenfd,(struct sockaddr*)&serveraddr,sizeof(serveraddr));

  GSocketBase::Listen(listenfd,backlog);

  maxIndex=listenfd;//maxIndex use only for select and poll
  
  counter=0;

  sockfdMap.clear();

}

void GSocket::init(voFuncIntStr *newConnect,voFuncIntCharptr *newData,voFuncInt *disconnect,voFuncIntInt *except){
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
        GLog::Log("invaild ioType input!","GSocket");
  }

}

void GSocket::selectLoop(){

   for(int i=0;i<FD_SETSIZE;i++){//insure the sclient every elements is -1 before select
     sclient[i]=-1;
   }

   FD_ZERO(&allset);

   FD_SET(listenfd,&allset);
   //this is the select loop,it will block the process run who run this function
   //when data ready,it will call the function who regist in init function

   for(;;){

     rset=allset;
     
     int nready=GSocketBase::Select(maxIndex+1,&rset,NULL,NULL,NULL);

     if(FD_ISSET(listenfd,&rset)){//when a new connections come,add it to set and sclient array and sockMap;
       socklen_t clilen=sizeof(clientaddr);
       connfd=GSocketBase::Accept(listenfd,(struct sockaddr *)&clientaddr,&clilen);

       std::string ip=inet_ntoa(clientaddr.sin_addr);
       
       GLog::Log("new client connect,sockfd="+ToStr(connfd)+",ip="+ip,"GSocket");

       int index=1;
       for(index=1;index<FD_SETSIZE;index++){
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
         GLog::Log("too much sock connect,array is full!,index="+ToStr(index),"GSocket");
       }
       if(index>maxIndex){//maxIndex in sclient[]
         maxIndex=index;
       }
       if(--nready<=0){ //if no more data ready,don't continue to left code
         continue; 
       }
     
     }


    //if not a new connection but a already socket data come
    int sockfd;
    for(int i=1;i<maxIndex;i++){
      if((sockfd=sclient[i])<0){
        continue;
      }
      if(FD_ISSET(sockfd,&rset)){
        memset(buf,sizeof(buf),'\0');
	int nread;
        if((nread=GSocketBase::Read(sockfd,buf,MAX_BUF_SIZE))<0){
          GLog::Log("socket close by client or socket occur error","GSocket");
          GSocketBase::Close(sockfd);
          sclient[i]=-1;
          //sockfdMap[sockfd]=-1;
          counter--;
          FD_CLR(sockfd,&allset);
          //callback
          (*disconnects)(sockfd);
          (*excepts)(sockfd,errno);      

        }else if(0==nread){
          continue;
        }else{//get the data
          (*newDatas)(sockfd,buf);
        }
      }

    }
 
   }
}



































