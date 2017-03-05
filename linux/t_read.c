#include <unistd.h>
#include <setjmp.h>
#include <signal.h>
#include <stdio.h>

#define MAXLEN 1024

static void sig_alarm(int);
static jmp_buf env_alarm;
int main(void)
{
	int n;
	char line[MAXLEN] = {'\0'};
	if(signal(SIGALRM, sig_alarm) == SIG_ERR)
		perror("signal(SIGALRM) error");
	if(setjmp(env_alarm) != 0){
		perror("read time out");
	}
	alarm(10);
	if((n = read(STDIN_FILENO, line, MAXLEN)) < 0)
		perror("read error");
	return 0;
}

static void sig_alarm(int signo){
	longjmp(env_alarm, 1);
}
