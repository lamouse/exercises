#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define OK 0
#define NO 1

#define del_enter(str) str[strlen(str)-1]='\0'

#define WORD_SIZE 30

char move_word(char str[], size_t position, size_t size);

int main(void){
    char str[WORD_SIZE];
    printf("please input a word: ");
    fgets(str,WORD_SIZE-3,stdin);
    del_enter(str);
    size_t index = 0;
    size_t str_size = strlen(str);
    int flag = NO;
    char temp;

    while(str[index] != '\0'&&flag){
         switch(str[index]){
            case 'a':
            case 'e':
            case 'i':
            case 'o':
            case 'u':
                ++index; break;
            default:
                temp = move_word(str,index,str_size);
                str[str_size-1] = '-';
                str[str_size] = temp;
                str[str_size+1] = 'a';
                str[str_size+2] = 'y';
                str[str_size+3] = '\0';
                flag = OK;
                break;

         }
    }
    if(flag){
         puts("No have extract\n");
    }
    else
        printf("results %s\n",str);
    return EXIT_SUCCESS;
}

char move_word(char str[], size_t position, size_t size){
    char temp = str[position];
    for(int i = position; i < size; i++){
       str[i] = str[i+1];
    }
    return temp;
}

