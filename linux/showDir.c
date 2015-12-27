#include <unistd.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <stdlib.h>

void printDir(char *dirName, int depth){
	DIR *pDir = NULL;
	struct dirent *entry;
	struct stat statbuf;

	if((pDir = opendir(dirName)) == NULL){
		fprintf(stderr, "cann't open directiry: %s\n", dirName);
		return;
	}
	chdir(dirName);
	while((entry = readdir(pDir)) != NULL){
		lstat(entry->d_name, &statbuf);

		if(S_ISDIR(statbuf.st_mode)){
			if(strcmp(".",entry->d_name) == 0 || 
				strcmp("..",entry->d_name)==0)
				continue;
			printf("%*s%s\n",depth," ",entry->d_name );
			printDir(entry->d_name, depth+4);
		}
		else
			printf("%*s%s\n",depth, " ", entry->d_name );

	}
	chdir("..");
	closedir(pDir);

}

int main(int argc, char const *argv[])
{
	printf("directiry scan of /home:\n");
	printDir("/home",0);

	printf("Done!\n");
	return 0;
}