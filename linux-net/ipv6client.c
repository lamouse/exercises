#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/socket.h>
#include <resolv.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <strings.h>
#include <sys/types.h>

#define BUF_LEN 1024
#define MYPORT 8888
#define BACKLOG 10

int main(int argc, char const *argv[])
{
	int clent;
	socklen_t len;
	int err = -1;
	char buf[BUF_LEN];

	struct sockaddr_in6 serv_addr,client_addr;

	clent = socket(AF_INET6,SOCK_STREAM,0);
	if(clent == -1){
		perror("socket error");
		return(EXIT_FAILURE);
	}

	bzero(&serv_addr,sizeof(serv_addr));
	serv_addr.sin6_family = AF_INET6;
	serv_addr.sin6_port = htons(MYPORT);
	serv_addr.sin6_addr = in6addr_any;

	err = connect(clent,(struct sockaddr*)&serv_addr,
		sizeof(serv_addr));

	if(err == -1){
		perror("connect error");
		exit(EXIT_FAILURE);
	}

	bzero(buf,BUF_LEN + 1);

	len = recv(clent,buf,BUF_LEN,0);
	printf("recved %dbytes: %s\n",len,buf);

	bzero(buf,BUF_LEN + 1);
	strncpy(buf,"From Client",BUF_LEN);

	len = send(clent,buf,strlen(buf),0);
	close(clent);

	return 0;
}