#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <strings.h>

#define BUF_LEN 1024
#define MYPORT 8888
#define BACKLOG 10

int main(int argc, char const *argv[])
{
	int serv,client;
	socklen_t len;
	int err = -1;

	struct sockaddr_in6 local_addr;
	struct sockaddr_in6 client_addr;
	char buf[BUF_LEN + 1];

	serv = socket(AF_INET6,SOCK_STREAM,0);
	if(serv == -1){
		perror("socket error");
		return EXIT_FAILURE;
	}

	bzero(&local_addr,sizeof(local_addr));
	local_addr.sin6_family = AF_INET6;
	local_addr.sin6_port = htons(MYPORT);
	local_addr.sin6_addr = in6addr_any;

	err = bind(serv,(struct sockaddr*)&local_addr,
		sizeof(struct sockaddr_in6));
	if(err == -1){
		perror("bind err");
		exit(EXIT_FAILURE);
	}

	err = listen(serv,BACKLOG);
	if(err == -1){
		perror("listen");
		exit(EXIT_FAILURE);
	}

	while(1){
		len = sizeof(struct sockaddr_in6);
		client = accept(serv,(struct sockaddr*)&client_addr,&len);
		if(client == -1){
			perror("accept");
			exit(EXIT_FAILURE);
		}
		else{
			inet_ntop(AF_INET6, &client_addr.sin6_addr,
				buf, sizeof(buf));
			printf("a client from ip: %s, port %d, socket %d\n",
				buf, client_addr.sin6_port,client);
		}

		bzero(buf,BUF_LEN+1);
		strncpy(buf,"From server",BUF_LEN);

		len = send(client,buf,strlen(buf),0);
		if(len < 0){
			printf("message '%s' send error, errno:%d,'%s'\n",
				buf,errno,strerror(errno));
		}
		else{
			printf("message '%s' send success, %dbytes\n",buf,len);
		}
		bzero(buf,BUF_LEN + 1);
		len = recv(client,buf,BUF_LEN,0);
		if(len > 0)
			printf("recv message failure, errno: %d, '%s'\n",
			errno,strerror(errno) );
		close(client);
	}
	close(serv);

	return 0;
}