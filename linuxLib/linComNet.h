#ifndef LIN_COM_NET_H_
#define LIN_COM_NET_H_

#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <sys/time.h>
#include <unistd.h> //for close
#include <errno.h> //for errno

/**
 *This is the common net header file.
 *Use for socket.
 *
 * Author:coderguang
 * Date:2015/06/22
 *
 */

const int OK=0;
const int ERROR=-1;

int Socket(int family,int type,int protocol){
	int temp=socket(family,type,protocol);
	if(ERROR==temp){
		std::cout<<"socket init failed!"<<std::endl;
		return ERROR;
	}
	return temp;
}

int Connect(int sockfd,const struct sockaddr *servaddr,socklen_t addrlen){
	int temp=connect(sockfd,servaddr,addrlen);
	if(ERROR==temp){
		std::cout<<"connect failed!"<<std::endl;
		return ERROR;
	}
	return OK;

}

int Bind(int sockfd,const struct sockaddr *myaddr,socklen_t len){
	int temp=bind(sockfd,myaddr,len);
	if(ERROR==temp){
		std::cout<<"bind failed!"<<std::endl;
		return ERROR;
	}
	return OK;
}

int Listen(int sockfd,int backlog){
	int temp=listen(sockfd,backlog);
	if(ERROR==temp){
		std::cout<<"listen failed!"<<std::endl;
		return ERROR;
	}
	return OK;
}

int Accept(int sockfd,struct sockaddr *cliaddr,socklen_t *addrlen){
	int temp=accept(sockfd,cliaddr,addrlen);
	if(ERROR==temp){
		std::cout<<"accept failed!"<<std::endl;
		return ERROR;
	}
	return temp;
}


int Select(int maxfdp1,fd_set *readset,fd_set *writeset,fd_set *exceptset,struct timeval *timeout){
	int temp=select(maxfdp1,readset,writeset,exceptset,timeout);
	if(temp>0){
		return temp;
	}else if(temp==0){
		std::cout<<"select time out!"<<std::endl;
		return 0;
	}else if(temp==ERROR){
		std::cout<<"select occure error!"<<std::endl;
		return ERROR;
	}
	std::cout<<"select occure something unexcepted!please debug the application!"<<std::endl;
	return ERROR; 
}

int Close(int sockfd){
	int temp=close(sockfd);
	if(temp==OK){
		std::cout<<"close socket "<<sockfd<<" success!"<<std::endl;
	}else{
		std::cout<<"close socket "<<sockfd<<" failed!"<<std::endl;
	}
	return temp;

}

ssize_t Read(int sockfd,void *buf,size_t len){
	int temp=read(sockfd,buf,len);
	if(temp<0){
		if(errno==EINTR){//call read() again
			temp=0;
			std::cout<<"should read aggin"<<std::endl;
			return 0;
		}else{
			std::cout<<"read error!"<<std::endl;
			return ERROR;
		}
	}else
		return temp;
}


ssize_t Write(int sockfd,void *buf,size_t len){
	int temp=write(sockfd,buf,len);
	if(temp<=0){
		if(temp<0&&errno==EINTR){
			temp=0;
			std::cout<<"should write aggin"<<std::endl;
			return 0;
		}else{
			return ERROR;
		}
	}
	return temp;

}

ssize_t Writen(int sockfd,const void *vptr,size_t len){
	size_t nleft;
	ssize_t nwritten;
	const char *ptr;

	ptr=(char*)vptr;
	nleft=len;

	while(nleft>0){
		if((nwritten=write(sockfd,ptr,nleft))<0){
			if(nwritten<0&&errno==EINTR){
				nwritten=0;//call write again
			}else{
				std::cout<<"writen error!"<<std::endl;
				return ERROR;
			}
		}
		nleft-=nwritten;
		ptr+=nwritten;
	
	}
	return len;
}


#endif
