#ifndef ERR_MESG_H
#define ERR_MESG_H
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#define error_msg(msg)											\
	do{															\
		fprintf(stderr, "file: %s line: %ld, message %s\n", 	\
			__FILE__, __LINE__, msg);							\
	}while(0)

#define error_exit(msg)											\
	do{															\
		fprintf(stderr, "file: %s line: %ld, message %s\n", 	\
			__FILE__, __LINE__, msg);							\
		exit(EXIT_FAILURE);										\
	}while(0)

#define	error_abort(msg)										\
	do{															\
		fprintf(stderr, "file: %s line: %ld, message %s\n", 	\
			__FILE__, __LINE__, msg);							\
		abort();												\
	}while(0)

#define errcode_abort(code)										\
	do{															\
		fprintf(stderr, "file: %s line: %ld, message %s\n", 	\
		__FILE__, __LINE__, strerror(code));					\
		abort();												\
	}while(0)

#endif