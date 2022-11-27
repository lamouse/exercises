#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <sys/wait.h>
#include <string.h>
#include <signal.h>
#include <stdexcept>
#include <sys/time.h>
#include <pthread.h>
#include "socket.hpp"

sigset_t mask;

#define MAX_LEN 64

void connect_test(char addr[]);
void serv_test();
void sig_child(int signo);
void time_write(::net::Socket sock);
void* thread_signal(void * arg);

int main(int argc, char* argv[]){
	timeval tv;
	gettimeofday(&tv, nullptr);
	if (argc > 1){
		connect_test(argv[1]);
	}else{
		serv_test();
	}
	return 0;
}

void serv_test(){
	printf("server start\n");
	using namespace ::std;
	using namespace ::net;
	//sigset_t oldmask;
	//pthread_t pid;
	struct sigaction sigact;
	sigact.sa_handler = sig_child;
	sigemptyset(&sigact.sa_mask);
	sigact.sa_flags = 0;
	sigaction(SIGCHLD, &sigact, NULL);

	//::signal(SIGCHLD, sig_child);
	//sigemptyset(&mask);
	//sigaddset(&mask, SIGCHLD);
	//pthread_sigmask(SIG_BLOCK, &mask, &oldmask);
	//pthread_create(&pid, NULL, thread_signal, NULL);
	pid_t cpid;
	try{
		string addr = "0::0";
		short port = 9999;

		Socket s;
		s.listen(addr, port);

		while(true){
			auto c = s.accept();
			printf("client address: %s, port: %d\n", c.getAddress().ip_str().c_str(), c.getAddress().port());
			if((cpid = fork()) == 0){
				time_write(c);
				exit(0);
			}
		}
	
	}catch(runtime_error& i){
		printf("%s\n", i.what());
		exit(-1);
	}
	//sigprocmask(SIG_SETMASK, &oldmask, NULL);
}

void time_write(::net::Socket sock){
	char buff[1024] = {0};
	printf("sock fd %d, client address: %s\n", sock(), sock.getAddress().ip_str().c_str());
	time_t ticks;
	ticks = time(NULL);
	snprintf(buff, sizeof(buff), "%.24s\r\n", ctime(&ticks));
	write(sock(), buff, strlen(buff));
}

void connect_test(char addr[]){
	printf("client start: %s\n", addr);
	using namespace ::std;
    using namespace ::net;
	try{
    	char recLine[MAX_LEN] = {0};
    	short port = 9999;

    	Socket s;
    	s.connect(addr, port);
    	int n;
    	while((n = read(s(), recLine, MAX_LEN)) > 0){
        	recLine[n] = 0;
	        if(fputs(recLine, stdout) == EOF){
    	         perror("fputs error");
        	 }
	     }
	}catch(runtime_error& i){
		printf("%s\n", i.what());
		exit(-1);
	}
}

void sig_child(int sign){
	pid_t pid;
	int stat;
	while ((pid = waitpid(-1, &stat, WNOHANG)) > 0)
	{
		printf("child %d terminated\n", pid);
	}
	return;
	
}

void* thread_signal(void * arg){
	pid_t pid;
	int err, signo, stat;

	while (true)
	{
		err = sigwait(&mask, &signo);
		if(err != 0){
			exit(-33);
		}

		switch (signo)
		{
		case SIGCHLD:{
				while ((pid = waitpid(-1, &stat, WNOHANG)) > 0)
				{
					printf("child %d terminated\n", pid);
					break;
				}
		}
		
		default:
			break;
		}
	}
	
}
