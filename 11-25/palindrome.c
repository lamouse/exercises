#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define del_enter(str) str[strlen(str)-1]='\0'

#define BUFSIZE 100

int main(void){
    char str[BUFSIZE];
    puts("This is a palindrome number on the judgment algorithm!");
    puts("Please input a string");
    fgets(str,BUFSIZE,stdin);
    del_enter(str);

    for(size_t i = 0,j=strlen(str)-1; i < j;i++,j--){
        if(str[i] != str[j]){
            printf("This is not a palindrome\n");
            exit(EXIT_FAILURE);
        }
    }
    printf("This is a palindrome\n");
    return EXIT_SUCCESS;
}
