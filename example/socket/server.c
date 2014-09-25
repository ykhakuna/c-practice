/*
 * the file is kind of chat terminal
 * 1. setup a daemon server
 * 2. create a key input thread
 * 3. chat between server and client with the input content
 *
 * sever_daemon: listen and create client thread
 * input_func:get keyboard input
 * client_func: connection response to client
 */
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

void input_func(void *ptr);
void client_func(void *ptr);

#define BUF_SIZE 128
char input_buf[BUF_SIZE];

void input_func(void *ptr) {
	char *input;
	int length;
	while (1) {
		gets(input);
		length = (BUF_SIZE > sizeof(input)) ? sizeof(input) : BUF_SIZE;
		snprintf(input_buf, length, input);
	}
}

int main() {
	struct sockaddr_in server_sockaddr, client_sockaddr;
	int sin_size, recvbytes, send_bytes;
	int sockfd, client_fd;
	char buf[MAXDATASIZE];
	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		perror("socket");
		exit(1);
	}
	printf("socket success!,sockfd=%d\n", sockfd);
	server_sockaddr.sin_family = AF_INET;
	server_sockaddr.sin_port = htons(SERVPORT);
	server_sockaddr.sin_addr.s_addr = INADDR_ANY;
	bzero(&(server_sockaddr.sin_zero), 8);
	if (bind(sockfd, (struct sockaddr *) &server_sockaddr,
			sizeof(struct sockaddr)) == -1) {
		perror("bind");
		exit(1);
	}
	printf("bind success!\n");
	if (listen(sockfd, BACKLOG) == -1) {
		perror("listen");
		exit(1);
	}
	printf("listening....\n");
	if ((client_fd = accept(sockfd, (struct sockaddr *) &client_sockaddr,
			&sin_size)) == -1) {
		perror("accept");
		exit(1);
	}
	if ((recvbytes = recv(client_fd, buf, MAXDATASIZE, 0)) == -1) {
		perror("recv");
		exit(1);
	}
	printf("received a connection :%s\n", buf);

	if ((send_bytes = send(client_fd, buf, sizeof(buf), 0)) == -1) {
		perror("send");
		exit(1);
	}

	close(sockfd);
}

