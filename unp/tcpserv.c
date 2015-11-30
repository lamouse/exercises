#include <unp.h>
void str_echo(int sockfd);
void sig_child(int signo);
int main(int argc, char const *argv[])
{
	int listenfd, connfd;
	pid_t childpid;
	socklen_t chilen;
	int n;

	struct sockaddr_in cliaddr, servaddr;
	listenfd = Socket(AF_INET, SOCK_STREAM,0);
	bzero(&servaddr, sizeof(servaddr));

	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(SERV_PORT);

	Bind(listenfd,(SA*)&servaddr,sizeof(servaddr));
	Listen(listenfd,LISTENQ);
	Signal(SIGCHLD, sig_child);

	char buf[MAXLINE];
	int maxfd = listenfd;
	int maxi = -1;
	int i = 0;
	int nready, client[FD_SETSIZE];
	for(; i < FD_SETSIZE; i++)
		client[i] = -1;
	fd_set rset, allset;
	FD_ZERO(&allset);
	FD_SET(listenfd, &allset);
	while(1){
		rset = allset;
		nready = Select(maxfd + 1, &rset, NULL, NULL, NULL);
		if(FD_ISSET(listenfd, &rset)){
			chilen = sizeof(cliaddr);
			connfd = Accept(listenfd, (SA*)&cliaddr, &chilen);
			for(i = 0; i < FD_SETSIZE; i++){
				if(client[i] < 0){
					client[i] = connfd;
					break;
				}
			}
			if(i == FD_SETSIZE)
				err_quit("too many clients");
			FD_SET(connfd, &rset);
			if(connfd > maxfd)
				maxfd = connfd;
			if(i > maxi)
				maxi = i;
			if(--nready <= 0)
				continue;

		}

		for(i = 0; i < maxi; i++){
			if(client[i] < 0)
				continue;
			if(FD_ISSET(client[i],&rset)){
				if((n = Read(client[i],buf, MAXLINE)) == 0){
					Close(client[i]);
					FD_CLR(client[i],&rset);
					client[i] = -1;
				}
				else
					Writen(client[i], buf, n);
				if(--nready <= 0)
					break;
			}
		}
	}

	return 0;
}
void str_echo(int sockfd){
	ssize_t n;
	char buf[MAXLINE];

	again:
		while((n = read(sockfd, buf, MAXLINE)) > 0)
			Writen(sockfd, buf, n);
		if(n < 0 && errno == EINTR)
			goto again;
		else if(n < 0)
			err_sys("str_echo: read error");
}
void sig_child(int signo){
	pid_t pid;
	int stat;
	while((pid = waitpid(-1, &stat, WNOHANG)) > 0)
	;
	return;
}