#include <stdio.h>
unsigned short checksum(char buf[], int len);

int main(int argc, char const *argv[])
{

	unsigned char str[16];
	int len = 16;
	unsigned short byte = *(unsigned short*)str;
	byte = 333;
	int sum = 0;
	unsigned short *data = (unsigned short*)str;
	while(len > 1){
		sum += *data++;
		len -= sizeof(unsigned short);
	}

	if(len){
		sum += *data;
	}

	sum=(sum >> 16) + (sum&0xffff);
	sum += (sum >> 16);
	unsigned short test = checksum(str,16);

	printf("Test %x\n",test + sum);

	return 0;
}
unsigned short checksum(char buf[], int len){
	int sum = 0;
	unsigned short *data = (unsigned short*)buf;
	while(len > 1){
		sum += *data++;
		len -= sizeof(unsigned short);
	}

	if(len){
		sum += *data;
	}

	sum=(sum >> 16) + (sum&0xffff);
	sum += (sum >> 16);

	return (unsigned short)(~sum);
}