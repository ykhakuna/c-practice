#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#define SERVPORT 3333
#define MAX_DATA_SIZE 100
main(int argc,char *argv[]){
	int sockfd,sendbytes,recvbytes;
	char buf[MAX_DATA_SIZE]="{name:hello,address:2233 rue de sheet}";
	struct hostent *host;
	struct sockaddr_in serv_addr;
	if(argc < 2){
		fprintf(stderr,"Please enter the server's hostname!\n");
		exit(1);
	}
	if((host=gethostbyname(argv[1]))==NULL){
		perror("gethostbyname");
		exit(1);
	}
	if((sockfd=socket(AF_INET,SOCK_STREAM,0))==-1){
		perror("socket");
		exit(1);
	}
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_port=htons(SERVPORT);
	serv_addr.sin_addr=*((struct in_addr *)host->h_addr);
	bzero(&(serv_addr.sin_zero),8);
	if(connect(sockfd,(struct sockaddr *)&serv_addr,\
		sizeof(struct sockaddr))==-1){
		perror("connect");
		exit(1);
	}
	if((sendbytes=send(sockfd,buf,sizeof(buf),0))==-1){
		perror("send");
		exit(1);
	}
	
	if((recvbytes=recv(sockfd,buf,MAX_DATA_SIZE,0))==-1){
		perror("recieve error\n");
		exit(1);
	}
	printf("received a message:%s\n",buf);
	close(sockfd);
}

