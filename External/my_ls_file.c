#include<stdio.h>
#include<stdbool.h>
#include<string.h>
#include<stdlib.h>
#include<dirent.h>

int main(int argc,char* argv[]){
	DIR* dir = opendir(argv[1]);
	struct dirent* thing;
	thing = readdir(dir);
	printf("Files in the folder are:\n");
	while(thing != NULL){
		printf("%s\n",thing->d_name);
		thing = readdir(dir);
	}
	closedir(dir);
	return 0;
}
