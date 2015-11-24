#include<stdio.h>
#include<string.h>

#define MAX_SIZE 255
#define del_enter(str) str[strlen(str)-1]='\0'

void reverse_string(char[],size_t);

int main(void){
    char str[MAX_SIZE];
    puts("Please input a string: ");
    fgets(str,MAX_SIZE,stdin);
    del_enter(str);
    reverse_string(str,strlen(str));
    printf("reverse string %s\n",str);

    return 0;
}

void reverse_string(char str[], size_t size){
    char temp;
     for(int i = 0, j = size-1; i < j;i++,j-- ){
         temp = str[i];
         str[i] = str[j];
         str[j] = temp;
    }
}
