#include<netdb.h>
#include<iostream>

int main(int argc,char **argv)
{
  struct hostent *hs;
  //char *host="182.254.233.115";
  /*
  char *host="180.97.33.108";
  hs=gethostbyname(host);
  
  int i;
  std::cout<<h_errno<<std::endl;
  std::cout<<hs->h_name<<std::endl;
  std::cout<<hs->h_aliases<<std::endl;
  std::cout<<hs->h_addrtype<<std::endl;
  std::cout<<hs->h_length<<std::endl;
  std::cout<<hs->h_addr_list<<std::endl;
  */
  struct servent *ptr;
  ptr=getservbyname("ftp","tcp");
  

  int i;
}
