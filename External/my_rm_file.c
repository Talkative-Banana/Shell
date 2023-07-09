#include<stdio.h>
#include<stdlib.h>
#include<string.h>


int main(int argc,char* argv[]){
	if(!strcmp(argv[1],"-i")){
		printf("Do you want to remove the file? y/n\n");
		char k;
		scanf("%c",&k);
		if(k == 'y'){
			if(remove(argv[2]) == 0){
				printf("Removed Successfully\n");
			} else{
				printf("Failed\n");
			}
		}
	} else if (!strcmp(argv[1],"-v")){
		remove(argv[2]);
		printf("removed %s\n",argv[2]);
		if(strcmp(argv[3],"NULL") != 0){
			remove(argv[3]);
			printf("removed %s\n",argv[3]);
		}
	}
	return 0;
}
