#include <sys/socket.h>
#include <strings.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <stdlib.h>
#include "../../include/net/SocketBase.h"

using namespace GCommon::GNet::GSocket;

int main(int argc,char **argv){
  
  int sockfd;
  struct sockaddr_in servaddr,cliaddr;
  
  sockfd=CSocketBase::Socket(AF_INET,SOCK_DGRAM,0);
  
  bzero(&servaddr,sizeof(servaddr));

  servaddr.sin_family=AF_INET;
  servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
  servaddr.sin_port=htons(9500);
  
  CSocketBase::Bind(sockfd,(struct sockaddr*)&servaddr,sizeof(servaddr));
 

  int n;
  socklen_t len;
  char msg[1024];
  len=sizeof(cliaddr); 

  for(;;){
    n=recvfrom(sockfd,msg,1024,0,(struct sockaddr*)&cliaddr,&len);
    
  }


}

