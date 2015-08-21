#include "../../net/socket/Socket.h"
#include <string>
#include <iostream>

using namespace GCommon::GNet::GSocket;

char buf[128];

void newConn(int sockfd,std::string ip){
  
  std::cout<<"test new socket="<<sockfd<<",ip="<<ip<<std::endl;
}
void newData(int sockfd,char *buf){
  std::cout<<"test data from sockfd="<<sockfd<<",msg="<<buf<<std::endl;
  CSocketBase::Writen(sockfd,buf,strlen(buf));
}

void disconn(int sockfd){
  std::cout<<"test sockfd="<<sockfd<<" disconnect....."<<std::endl;
}

void excep(int sockfd,int err){
  std::cout<<"test sockfd="<<sockfd<<" ,errno="<<err<<std::endl;
}


int main(int argc,char **argv){
  struct epoll_event ev;
  ev.events=POLLIN;
  CSocket msock(IOSelect,AF_INET,SOCK_STREAM,0,9000,10,ev); //test ok
  //CSocket msock(IOPoll,AF_INET,SOCK_STREAM,0,9000,10,ev); //test ok
  //CSocket msock(IOEpoll,AF_INET,SOCK_STREAM,0,9000,10,ev);
  voFuncIntStr f1=newConn;
  voFuncIntCharptr f2=newData;
  voFuncInt f3=disconn;
  voFuncIntInt f4=excep;

  msock.init(&f1,&f2,&f3,&f4);


}
