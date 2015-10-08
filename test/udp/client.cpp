#include <sys/socket.h>
#include <strings.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <stdlib.h>
#include <iostream>
#include "../../include/net/SocketBase.h"

using namespace GCommon::GNet::GSocket;

int main(int argc,char **argv){
  
  int sockfd;
  struct sockaddr_in servaddr;
  
  sockfd=CSocketBase::Socket(AF_INET,SOCK_DGRAM,0);
  
  bzero(&servaddr,sizeof(servaddr));

  servaddr.sin_family=AF_INET;
  servaddr.sin_port=htons(9500);
  if(-1==inet_pton(AF_INET,"182.254.233.115",&servaddr.sin_addr)){
    std::cout<<"inet_pton error"<<std::endl;
  };
  
  int n;
  socklen_t len;
  char msg[1024];
  char sendBuf[1024]="hello,udp";

  for(int i=0;i<10;i++){
    sendto(sockfd,sendBuf,1024,0,(struct sockaddr*)&servaddr,len);
    
  }


}

