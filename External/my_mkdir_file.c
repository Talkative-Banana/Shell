#include<stdio.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<string.h>

int main(int argc, char* argv[]){
	if(!strcmp(argv[1],"-m777")){
		mkdir(argv[2],0777);
	
	} else if(!strcmp(argv[1],"-v")){
		mkdir(argv[2],0775);
		printf("%s created!\n",argv[2]);
		if(strcmp(argv[3],"NULL") != 0){
			mkdir(argv[3],0775);
			printf("%s created!\n",argv[3]);
		}
	}
	return 0;
}
