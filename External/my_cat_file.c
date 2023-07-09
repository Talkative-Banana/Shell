#include<stdio.h>
#include<stdlib.h>
#include<string.h>



int main(int argc, char* argv[]){
	FILE* filepointer;
	if(!strcmp(argv[1],">")){
		char * f = argv[2];
		filepointer = fopen(f,"w");
		printf("Enter something\n");
		char input[100];
		fgets(input,100,stdin);
		fputs(input,filepointer);
		fclose(filepointer);
	
	} else if(!strcmp(argv[1],"-n")){
		char *f = argv[2];
		char * line = NULL;
		size_t len = 0;
		ssize_t li;
		filepointer = fopen(f,"r");
		int k = 1;
		for(int i = fgetc(filepointer);i != EOF ;i = fgetc(filepointer)){

			if(i == '\n'){
				k++;
			}
		}
		fclose(filepointer);
		FILE * gh = fopen(f,"r");
		for (int j=0;j<k-1;j++){
			printf("%d ",j+1);
			li = getline(&line,&len,gh);
			printf("%s",line);
		
		}
		fclose(gh);
	}
	return 0;
}
