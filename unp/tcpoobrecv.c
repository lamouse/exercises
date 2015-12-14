#include <unp.h>

int listenfd, connfd;

void sig_urg(int);

int main(int argc, char const *argv[])
{
	int n;
	char buff[100];
	listenfd = Tcp_listen("127.0.0.1","9990",NULL);
	connfd = Accept(listenfd, NULL,NULL);
	Signal(SIGURG, sig_urg);
	Fcntl(connfd, F_SETOWN,getpid());

	for (; ;)
	{
		if((n = Read(connfd, buff, sizeof(buff)-1))==0){
			printf("received EOF\n");
			exit(0);
		}
		buff[n] = 0;
		printf("read %d bytes: %s\n", n,buff);
	}
	return 0;
}

void sig_urg(int signo){
	int n;
	char buff[100];

	printf("SIGURG received\n");

	n = Recv(connfd, buff, sizeof(buff)-1, MSG_OOB);
	buff[n] = 0;
	printf("read %d OOB bytes: %s\n",n, buff);
}