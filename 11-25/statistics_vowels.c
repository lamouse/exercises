#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFSIZE 128
#define err_mesg(msg)\
    do{perror(msg);exit(EXIT_FAILURE);}while(0)
#define del_enter(str) str[strlen(str)-1]='\n'

int main(int argc,char* argv[]){
    if(argc < 2)
        err_mesg("argument too less");
    int all_vowels_num = 0;
    int a_number = 0;
    int e_number = 0;
    int i_number = 0;
    int o_number = 0;
    int u_number = 0;
    FILE *pfile;
    pfile = fopen(argv[1],"r");
    if(pfile==NULL){
        fprintf(stderr,"Open file %s failed\n",argv[1]);
        exit(EXIT_FAILURE);
    }
    char string[BUFSIZE];
    while(!feof(pfile)){
         fgets(string,BUFSIZE,pfile);
         for(int i = 0;string[i] != '\0';i++){
             switch(string[i]){
                case 'a': ++a_number;    break;
                case 'e': ++e_number;    break;
                case 'i': ++i_number;    break;
                case 'o': ++o_number;    break;
                case 'u': ++u_number;    break;
             }
         }
    }
    all_vowels_num = a_number+e_number+i_number+o_number+u_number;
    printf("a number: %d\n",a_number);
    printf("e number: %d\n",e_number);
    printf("i number: %d\n",i_number);
    printf("o number: %d\n",o_number);
    printf("u number: %d\n",u_number);
    printf("All vowels is %d\n",all_vowels_num);

    return EXIT_SUCCESS;
}
