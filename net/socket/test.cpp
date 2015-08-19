#include "Socket.h"
#include <string>
#include <iostream>

using namespace GCommon::GNet::GSocket;

void newConn(int sockfd,std::string ip){
  std::cout<<"get the new sockfd="<<sockfd<<",ip="<<ip<<std::endl;
}
void newData(int sockfd,char *buf){
  std::cout<<"new data from sockfd="<<sockfd<<",msg="<<buf<<std::endl;
}

void disconn(int sockfd){
  std::cout<<"sockfd="<<sockfd<<"disconnect"<<std::endl;
}


int main(int argc,char **argv){

  GSocket msock(IOSelect,AF_INET,SOCK_STREAM,0,9000,10);
  voFuncIntStr f1=newConn;

  msock.init(newConn,newData,disconn,NULL);


}
