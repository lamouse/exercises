#include <unp.h>
void dg_echo(int sockfd, SA* pcliaddr, socklen_t clilen);
int main(int argc, char const *argv[])
{
	int sockfd;
	struct sockaddr_in servaddr, cliaddr;
	sockfd = socket(AF_INET, SOCK_DGRAM,0);

	bzero(&servaddr, sizeof(servaddr));

	servaddr.sin_family=AF_INET;
	servaddr.sin_port = htons(SERV_PORT);
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	Bind(sockfd, (SA*)&servaddr, sizeof(servaddr));

	dg_echo(sockfd, (SA*)&cliaddr, sizeof(cliaddr));
	return 0;
}

void dg_echo(int sockfd, SA* pcliaddr, socklen_t clilen){
	int n;
	socklen_t len;
	char mesg[MAXLINE];
	while(1){
		len = clilen;
		n = Recvfrom(sockfd, mesg, MAXLINE, 0, pcliaddr, &len);
		Sendto(sockfd, mesg, n,0, pcliaddr, len);
	}
}