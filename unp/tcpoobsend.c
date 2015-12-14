#include <unp.h>

int main(int argc, char const *argv[])
{
	int sockfd;
	sockfd = Tcp_connect("127.0.0.1","9990");
	Write(sockfd,"123",3);
	printf("wrote 3 bytes of normal data\n");
	sleep(1);
	Send(sockfd,"4",1, MSG_OOB);
	printf("wrote 1 byte of OOB data\n");
	sleep(1);

	Write(sockfd,"56",2);
	printf("wrote 2 bytes of normal data\n");
	sleep(1);

	Send(sockfd,"7",1,MSG_OOB);
	printf("wrote 1 byte of OOB data\n");
	sleep(1);
	Write(sockfd,"98",2);
	printf("wrote 2 bytes of normal data\n");
	sleep(1);
	return 0;
}