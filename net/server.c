#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#define SERVPORT 3333
#define BACKLOG 10
#define MAX_CONNECTED_NO 10
#define MAXDATASIZE 100

int main()
{
	struct sockaddr_in server_sockaddr,client_sockaddr;
	int sin_size,recvbytes,send_bytes;
	char input_str[128]="hello";
	int sockfd,client_fd;
	char buf[MAXDATASIZE];
	if((sockfd = socket(AF_INET,SOCK_STREAM,0))==-1){
		perror("socket");
		exit(1);
	}
	printf("socket success!,sockfd=%d\n",sockfd);
	server_sockaddr.sin_family=AF_INET;
	server_sockaddr.sin_port=htons(SERVPORT);
	server_sockaddr.sin_addr.s_addr=INADDR_ANY;
	bzero(&(server_sockaddr.sin_zero),8);
	if(bind(sockfd,(struct sockaddr *)&server_sockaddr,sizeof(struct sockaddr))==-1){
		perror("bind");
		exit(1);
	}
	printf("bind success!\n");
	if(listen(sockfd,BACKLOG)==-1){
		perror("listen");
		exit(1);
	}
	printf("listening....\n");
	if((client_fd=accept(sockfd,(struct sockaddr *)&client_sockaddr,&sin_size))==-1){
		perror("accept");
		exit(1);
	}
	if((recvbytes=recv(client_fd,buf,MAXDATASIZE,0))==-1){
		perror("recv");
		exit(1);
	}
	printf("received a connection :%s\n",buf);

//	char *s;
int times=2;
	while(1){
//	s=gets(input_str);
//	s=input_str;	
//	if(strncmp(s,"quit",4)!=0){
		if((send_bytes=send(client_fd,input_str,(strlen(input_str)+1),0))==-1){
			perror("send");
			exit(1);
		}
printf("buf size is:%d\n",sizeof(input_str));
		printf("send message \"%s\" to client.\n",input_str);
	//	memset(input_str,0,sizeof(input_str));
//		fflush(stdin);
//		}else break;
times--;
	}
	close(sockfd);
}

