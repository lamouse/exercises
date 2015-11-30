#include <unp.h>

int main(int argc, char const *argv[])
{
	union{
		short s;
		char c[sizeof(short)];
	}un;

	un.s=0x0102;

	printf("%s:\n", CPU_VENDOR_OS);
	if(sizeof(short) == 2){
		if(un.c[0] == 1 && un.c[1] == 2)
			printf("dig-ending\n");
		else if(un.c[0] == 2 && un.c[1] == 1)
			printf("little-endia\n");
		else
			printf("unknow\n");
	}
	else{
		printf("sizeof(short) == %zd\n", sizeof(short));
	}
	return 0;
}