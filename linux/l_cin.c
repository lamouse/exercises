#include <pthread.h>
#include <time.h>
#include <unistd.h>
#include "errors.h"

typedef struct my_struct_tag{
	pthread_mutex_t 	mutex;		//Protects access to value
	pthread_cond_t 		cond;		//Signals change to value
	int 				value;		//Access protected by mutex
}my_struct_tag_t;

my_struct_tag_t data = {
	PTHREAD_MUTEX_INITIALIZER,  PTHREAD_COND_INITIALIZER, 0
};

int hibernation = 1;		//Default to 1 second

void* wait_thread(void *arg){
	int status;
	sleep(hibernation);
	status = pthread_mutex_lock(&data.mutex);
	if(status)
		error_abort("pthread_mutex_lock");
	data.value = 1;		//set predicate

	status = pthread_cond_signal(&data.cond);
	if(status)
		error_abort("pthread_cond_signal");
	status = pthread_mutex_unlock(&data.mutex);
	if(status)
		error_abort("pthread_mutex_unlock");
	return NULL;
}

int main(int argc, char* argv[]){
	int status;
	pthread_t wait_thread_id;
	struct timespec timeout;
	if(argc > 1)
		hibernation = atoi(argv[1]);
	status = pthread_create(&wait_thread_id, NULL, wait_thread, NULL);
	if(status)
		error_abort("pthread_create");
	timeout.tv_sec = time(NULL) + 2;
	timeout.tv_nsec = 0;
	status = pthread_mutex_lock(&data.mutex);
	if(status)
		error_abort("pthread_mutex_lock");

	while(data.value == 0){
		status = pthread_cond_timedwait(&data.cond, &data.mutex,
			&timeout);
		if(status == ETIMEDOUT){
			printf("Condition wait timed out.\n");
			break;
		}
		else if(status)
			error_abort("pthread_cond_timewait");
	}
	if(data.value != 0)
		printf("Condition was signaled.\n");
	status = pthread_mutex_unlock(&data.mutex);
	if(status)
		error_abort("pthread_mutex_unlock");
	return EXIT_SUCCESS;
}